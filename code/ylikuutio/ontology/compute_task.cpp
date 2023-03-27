// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "compute_task.hpp"
#include "universe.hpp"
#include "callback_engine.hpp"
#include "pipeline.hpp"
#include "compute_task_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/load/common_texture_loader.hpp"
#include "code/ylikuutio/load/csv_texture_loader.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>       // std::size_t
#include <iomanip>       // std::setfill, std::setw
#include <ios>           // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream>      // std::cout, std::cin, std::cerr
#include <optional>      // std::optional
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h>      // uint32_t etc.
#include <utility>       // std::swap etc.
#include <variant>       // std::holds_alternative, std::variant
#include <vector>        // std::vector

namespace yli::ontology
{
    class Entity;
    class Scene;

    void ComputeTask::bind_to_parent() noexcept
    {
        // Requirements:
        // `this->parent` must not be `nullptr`.

        yli::ontology::Pipeline* const pipeline = this->parent;

        if (pipeline == nullptr)
        {
            std::cerr << "ERROR: `ComputeTask::bind_to_parent`: `pipeline` is `nullptr`!\n";
            return;
        }

        // Get `childID` from `Pipeline` and set pointer to this `ComputeTask`.
        pipeline->parent_of_compute_tasks.bind_child(this);
    }

    ComputeTask::ComputeTask(
            yli::ontology::Universe& universe,
            const yli::ontology::ComputeTaskStruct& compute_task_struct)
        : Entity(universe, compute_task_struct),
        texture_file_format              { compute_task_struct.texture_file_format },
        texture_filename                 { compute_task_struct.texture_filename },
        output_filename                  { compute_task_struct.output_filename },
        parent                           { compute_task_struct.parent },
        left_filler_vector_any_value     { compute_task_struct.left_filler_vector_any_value },
        right_filler_vector_any_value    { compute_task_struct.right_filler_vector_any_value },
        end_condition_callback_engine    { compute_task_struct.end_condition_callback_engine },
        n_max_iterations                 { compute_task_struct.n_max_iterations },
        compute_taskID                   { compute_task_struct.compute_taskID },
        texture_width                    { compute_task_struct.texture_width },
        texture_height                   { compute_task_struct.texture_height },
        n_index_characters               { compute_task_struct.n_index_characters },
        format                           { compute_task_struct.format },
        internal_format                  { compute_task_struct.internal_format },
        output_format                    { compute_task_struct.output_format },
        type                             { compute_task_struct.type },
        should_save_intermediate_results { compute_task_struct.should_save_intermediate_results },
        should_flip_texture              { compute_task_struct.should_flip_texture }
    {
        // constructor.

        // Get `childID` from `Pipeline` and set pointer to this `ComputeTask`.
        this->bind_to_parent();

        // `ComputeTask` is currently designed to be a GPGPU class that uses GLSL shaders for computation.
        // If support for using YliLisp as a shading language that compiles to SPIR-V or GLSL is implemented,
        // then `ComputeTask` could and should support software rendering as well.
        const bool should_load_texture =
            this->universe.get_is_opengl_in_use() ||
            this->universe.get_is_vulkan_in_use();

        if (should_load_texture && this->universe.get_is_opengl_in_use())
        {
            // Get a handle for our buffers.
            this->vertex_position_modelspace_id = glGetAttribLocation(this->parent->get_program_id(), "vertex_position_modelspace");
            this->vertex_uv_id = glGetAttribLocation(this->parent->get_program_id(), "vertexUV");

            glUseProgram(this->parent->get_program_id());
        }

        // Load the source texture, just like in `yli::ontology::Material` constructor.
        if (should_load_texture && (this->texture_file_format == "png" || this->texture_file_format == "PNG"))
        {
            uint32_t n_color_channels = 0;

            if (!yli::load::load_common_texture(
                        this->texture_filename,
                        yli::load::ImageLoaderStruct(),
                        this->texture_width,
                        this->texture_height,
                        this->texture_size,
                        n_color_channels,
                        this->source_texture,
                        this->universe.get_graphics_api_backend()))
            {
                std::cerr << "ERROR: loading PNG texture failed!\n";
            }
            else
            {
                this->is_texture_loaded = true;
            }
        }
        else if (should_load_texture && (this->texture_file_format == "csv" || this->texture_file_format == "CSV"))
        {
            if (!yli::load::load_csv_texture(
                        this->texture_filename,
                        this->format,
                        this->internal_format,
                        this->type,
                        &this->left_filler_vector_any_value,
                        &this->right_filler_vector_any_value,
                        this->texture_width,
                        this->texture_height,
                        this->texture_size,
                        this->source_texture))
            {
                std::cerr << "ERROR: loading CSV texture failed!\n";
            }
            else
            {
                this->is_texture_loaded = true;
            }
        }
        else
        {
            std::cerr << "no texture was loaded!\n";
            std::cerr << "texture file format: " << this->texture_file_format << "\n";
        }

        if (this->is_texture_loaded && this->universe.get_is_opengl_in_use())
        {
            // Get a handle for our "texture_sampler" uniform.
            this->opengl_texture_id = glGetUniformLocation(this->parent->get_program_id(), "texture_sampler");

            // Initialize uniform window width.
            // This is named `screen_width` instead of `texture_width` for compatibility with other shaders.
            this->screen_width_uniform_id = glGetUniformLocation(this->parent->get_program_id(), "screen_width");
            yli::opengl::uniform_1i(this->screen_width_uniform_id, this->texture_width);

            // Initialize uniform window height.
            // This is named `screen_height` instead of `texture_height` for compatibility with other shaders.
            this->screen_height_uniform_id = glGetUniformLocation(this->parent->get_program_id(), "screen_height");
            yli::opengl::uniform_1i(this->screen_height_uniform_id, this->texture_height);

            // Initialize uniform iteration index.
            this->iteration_i_uniform_id = glGetUniformLocation(this->parent->get_program_id(), "iteration_i");
            yli::opengl::uniform_1i(this->iteration_i_uniform_id, 0);

            // Create model (a square which consists of 2 triangles).
            // *---*
            // |  /|
            // | / |
            // |/  |
            // *---*
            const std::vector<glm::vec2> vertices
            { { -1.0f, 1.0f }, { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 1.0f, -1.0f } };
            this->vertices_size = vertices.size();

            const std::vector<glm::vec2> uvs
            { { 0.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f } };
            this->uvs_size = uvs.size();

            const std::vector<GLuint> indices { 0, 1 };

            // Load model.

            // VAO.
            glGenVertexArrays(1, &this->vao);

            // Vertices.
            glGenBuffers(1, &this->vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

            // UVs.
            glGenBuffers(1, &this->uvbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

            // Index buffer.
            glGenBuffers(1, &this->elementbuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementbuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2, &indices[0], GL_STATIC_DRAW);
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::ComputeTask*";
        this->can_be_erased = true;
    }

    ComputeTask::~ComputeTask()
    {
        // destructor.
        //
        // Requirements:
        // `this->parent` must not be `nullptr`.

        if (this->is_texture_loaded)
        {
            // Cleanup buffers and texture.
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);
            glDeleteTextures(1, &this->source_texture);
        }

        if (this->is_framebuffer_initialized)
        {
            glDeleteTextures(1, &this->target_texture);
            glDeleteFramebuffers(1, &this->framebuffer);
        }

        if (this->parent == nullptr)
        {
            return;
        }

        this->parent->parent_of_compute_tasks.unbind_child(this->childID);
    }

    void ComputeTask::render(const yli::ontology::Scene* const)
    {
        if (!this->is_texture_loaded)
        {
            // Do not render anything if texture is not loaded.
            return;
        }

        if (this->is_ready)
        {
            // If `ComputeTask` is ready, it does not need to be rendered.
            return;
        }

        if (!this->is_framebuffer_initialized)
        {
            // Create an FBO (off-screen framebuffer object).
            glGenFramebuffers(1, &this->framebuffer);
        }

        // Bind the offscreen buffer.
        yli::opengl::bind_gl_framebuffer(this->framebuffer);

        if (!this->is_framebuffer_initialized)
        {
            // Create a target texture.
            glGenTextures(1, &this->target_texture);
            glBindTexture(GL_TEXTURE_2D, this->target_texture);

            // Define the texture.
            if (internal_format == GL_INVALID_ENUM)
            {
                // Internal format not defined, use format as internal format.
                glTexImage2D(
                        GL_TEXTURE_2D,
                        0,
                        this->format,
                        this->texture_width,
                        this->texture_height,
                        0,
                        this->format,
                        this->type,
                        nullptr);
            }
            else
            {
                // Internal format is defined.
                glTexImage2D(
                        GL_TEXTURE_2D,
                        0,
                        this->internal_format,
                        this->texture_width,
                        this->texture_height,
                        0,
                        this->format,
                        this->type,
                        nullptr);
            }

            yli::opengl::set_nearest_filtering_parameters();

            // Attach the texture.
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target_texture, 0);

            // Set background color for the framebuffer.
            this->universe.set_opengl_background_color();

            this->is_framebuffer_initialized = true;
        }

        // Clear the framebuffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Adjust viewport for the framebuffer.
        glViewport(0, 0, this->texture_width, this->texture_height);

        for (std::size_t iteration_i = 0; iteration_i < n_max_iterations; iteration_i++)
        {
            if (this->end_condition_callback_engine != nullptr)
            {
                std::optional<yli::data::AnyValue> end_condition_any_value = this->end_condition_callback_engine->execute(yli::data::AnyValue());

                if (end_condition_any_value && std::holds_alternative<bool>(end_condition_any_value->data) && std::get<bool>(end_condition_any_value->data))
                {
                    break; // End condition was satisfied. Therefore, no more iterations.
                }
            }

            // Update the value of `uniform` variable `iteration_i`.
            yli::opengl::uniform_1i(this->iteration_i_uniform_id, iteration_i);

            // Bind our texture in Texture Unit 0.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->source_texture);

            // Set our "texture_sampler" sampler to use Texture Unit 0.
            yli::opengl::uniform_1i(this->opengl_texture_id, 0);

            // Bind VAO.
            glBindVertexArray(this->vao);

            // 1st attribute buffer: vertices.
            yli::opengl::enable_vertex_attrib_array(this->vertex_position_modelspace_id);

            // 2nd attribute buffer: UVs.
            yli::opengl::enable_vertex_attrib_array(this->vertex_uv_id);

            // 1st attribute buffer: vertices.
            glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);

            glVertexAttribPointer(
                    this->vertex_position_modelspace_id, // The attribute we want to configure
                    2,                                  // size
                    GL_FLOAT,                           // type
                    GL_FALSE,                           // normalized?
                    0,                                  // stride
                    (void*) 0                           // array buffer offset
                    );
            yli::opengl::enable_vertex_attrib_array(this->vertex_position_modelspace_id);

            // 2nd attribute buffer: UVs.
            glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
            glVertexAttribPointer(
                    this->vertex_uv_id, // The attribute we want to configure
                    2,                // size : U+V => 2
                    GL_FLOAT,         // type
                    GL_FALSE,         // normalized?
                    0,                // stride
                    (void*) 0         // array buffer offset
                    );
            yli::opengl::enable_vertex_attrib_array(this->vertex_uv_id);

            // Draw the triangles!
            glDrawArrays(GL_TRIANGLE_STRIP, 0, this->vertices_size); // Draw 2 triangles (6 vertices).

            yli::opengl::disable_vertex_attrib_array(this->vertex_position_modelspace_id);
            yli::opengl::disable_vertex_attrib_array(this->vertex_uv_id);

            if (this->should_save_intermediate_results && !this->output_filename.empty())
            {
                std::stringstream filename_stringstream;
                filename_stringstream << this->output_filename << "_" << std::setfill('0') << std::setw(this->n_index_characters) << iteration_i;

                // Transfer data from the GPU texture to a CPU array and save into a file.
                if (this->output_format == GL_INVALID_ENUM)
                {
                    // Output format not defined, use format as output format.
                    yli::opengl::save_data_from_gpu_texture_into_file(
                            this->format,
                            this->type,
                            this->texture_width,
                            this->texture_height,
                            filename_stringstream.str(),
                            this->should_flip_texture);
                }
                else
                {
                    // Output format is defined.
                    yli::opengl::save_data_from_gpu_texture_into_file(
                            this->output_format,
                            this->type,
                            this->texture_width,
                            this->texture_height,
                            filename_stringstream.str(),
                            this->should_flip_texture);
                }
            }

            // Ping pong.
            std::swap(this->source_texture, this->target_texture);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target_texture, 0);
            yli::opengl::print_opengl_errors("glFramebufferTexture2D");
        }

        // Ping pong once more, so that last output target texture gets saved to file.
        std::swap(this->source_texture, this->target_texture);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target_texture, 0);

        // Transfer data from the GPU texture to a CPU array and save into a file.
        if (this->output_format == GL_INVALID_ENUM)
        {
            // Output format not defined, use format as output format.
            yli::opengl::save_data_from_gpu_texture_into_file(
                    this->format,
                    this->type,
                    this->texture_width,
                    this->texture_height,
                    this->output_filename,
                    this->should_flip_texture);
        }
        else
        {
            // Output format is defined.
            yli::opengl::save_data_from_gpu_texture_into_file(
                    this->output_format,
                    this->type,
                    this->texture_width,
                    this->texture_height,
                    this->output_filename,
                    this->should_flip_texture);
        }

        this->universe.restore_onscreen_rendering();

        this->is_ready = true;
    }

    yli::ontology::Entity* ComputeTask::get_parent() const
    {
        return this->parent;
    }

    yli::ontology::Scene* ComputeTask::get_scene() const
    {
        const yli::ontology::Entity* const parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    std::size_t ComputeTask::get_number_of_children() const
    {
        return 0; // `ComputeTask` has no children.
    }

    std::size_t ComputeTask::get_number_of_descendants() const
    {
        return 0; // `ComputeTask` has no children.
    }
}
