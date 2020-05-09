// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __COMPUTE_TASK_HPP_INCLUDED
#define __COMPUTE_TASK_HPP_INCLUDED

#include "entity.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "compute_task_struct.hpp"
#include "pre_iterate_callback.hpp"
#include "post_iterate_callback.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/load/common_texture_loader.hpp"
#include "code/ylikuutio/load/csv_texture_loader.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

// `yli::ontology::ComputeTask` is a class which contains the data for a single
// computing task. `ComputeTask` does not have the OpenGL shaders used to process
// the data. Instead, the shaders are contained by the parent `Entity` which is
// an `yli::ontology::Shader` instance.
//
// For example, `yli::ontology::Shader` can have vertex and fragment shaders for
// computing the distances between nodes of a graph. Then, each `ComputeTask`
// would contain the graph data, eg. as a distance matrix. Then, rendering a
// `ComputeTask` means computing that task.
//
// Rendering a `ComputeTask` is done by iterating the task until either
// `end_condition_callback_engine->execute(nullptr)` returns `true`, or until
// `n_max_iterations` is reached. If `end_condition_callback_engine` is `nullptr`
// or `end_condition_callback_engine->execute(nullptr)` does not not return an `AnyValue`
// which contains `yli::common::BOOL`, then `end_condition_callback_engine` is ignored
// and `n_max_iterations` is the exact number of iterations to be done. However,
// even if `end_condition_callback_engine->execute(nullptr)` would return an invalid return
// value, that is, not an `AnyValue` which contains `common::BOOL`,
// `end_condition_callback_engine->execute(nullptr)` is still called and taken into account
// in every iteration.
//
// When iterating, there is a `PreIterateCallback` which is executed before each iteration,
// and also a `PostIterateCallback` which is executed correspondingly after each iteration.
// Of course `PreRenderCallback` and `PostRenderCallback` can be used as well.
// `PreRenderCallback` gets executed before the first `PreIterateCallback` call, and
// `PostRenderCallback` gets executed after the last `PostRenderCallback` call.
// All these callbacks are optional and can be left to `nullptr` if they are not needed.

namespace yli::callback
{
    class CallbackEngine;
}

namespace yli::ontology
{
    class Shader;

    class ComputeTask: public yli::ontology::Entity
    {
        public:
            ComputeTask(yli::ontology::Universe* const universe, const yli::ontology::ComputeTaskStruct& compute_task_struct)
                : Entity(universe)
            {
                // constructor.
                this->texture_file_format = compute_task_struct.texture_file_format;
                this->texture_filename = compute_task_struct.texture_filename;
                this->output_filename = compute_task_struct.output_filename;
                this->parent = compute_task_struct.parent;
                this->left_filler_vector_any_value = compute_task_struct.left_filler_vector_any_value;
                this->right_filler_vector_any_value = compute_task_struct.right_filler_vector_any_value;
                this->end_condition_callback_engine = compute_task_struct.end_condition_callback_engine;

                this->result_vector = nullptr;

                this->n_max_iterations = compute_task_struct.n_max_iterations;
                this->compute_taskID = compute_task_struct.compute_taskID;
                this->texture_width = compute_task_struct.texture_width;
                this->texture_height = compute_task_struct.texture_height;
                this->texture_size = 0; // dummy value.
                this->n_index_characters = compute_task_struct.n_index_characters;

                this->vertices_size                = 0;
                this->uvs_size                     = 0;

                // variables related to the framebuffer.
                this->framebuffer                  = 0; // some dummy value.
                this->source_texture               = 0; // some dummy value.
                this->target_texture               = 0; // some dummy value.
                this->openGL_textureID             = 0; // some dummy value.
                this->is_texture_loaded            = false;
                this->is_framebuffer_initialized   = false;
                this->is_ready                     = false;

                this->vertex_position_modelspace_id = 0; // some dummy value.
                this->vertex_uv_id                   = 0; // some dummy value.
                this->screen_width_uniform_id      = 0; // some dummy value.
                this->screen_height_uniform_id     = 0; // some dummy value.
                this->iteration_i_uniform_id       = 0; // some dummy value.
                this->vertexbuffer                 = 0; // some dummy value.
                this->uvbuffer                     = 0; // some dummy value.

                this->format                       = compute_task_struct.format;
                this->internal_format              = compute_task_struct.internal_format;
                this->output_format                = compute_task_struct.output_format;
                this->type                         = compute_task_struct.type;
                this->should_ylikuutio_save_intermediate_results = compute_task_struct.should_ylikuutio_save_intermediate_results;
                this->should_ylikuutio_flip_texture              = compute_task_struct.should_ylikuutio_flip_texture;

                this->preiterate_callback = compute_task_struct.preiterate_callback;
                this->postiterate_callback = compute_task_struct.postiterate_callback;

                // Get `childID` from `Shader` and set pointer to this `ComputeTask`.
                this->bind_to_parent();

                const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());

                if (!is_headless)
                {
                    // Get a handle for our buffers.
                    this->vertex_position_modelspace_id = glGetAttribLocation(this->parent->get_programID(), "vertex_position_modelspace");
                    this->vertex_uv_id = glGetAttribLocation(this->parent->get_programID(), "vertexUV");

                    glUseProgram(this->parent->get_programID());
                }

                // Load the source texture, just like in `yli::ontology::Material` constructor.
                if (this->texture_file_format == "bmp" || this->texture_file_format == "BMP")
                {
                    if (!yli::load::load_common_texture(this->texture_filename, this->texture_width, this->texture_height, this->texture_size, this->source_texture, is_headless))
                    {
                        std::cerr << "ERROR: loading BMP texture failed!\n";
                    }
                    else
                    {
                        this->is_texture_loaded = true;
                    }
                }
                else if (this->texture_file_format == "csv" || this->texture_file_format == "CSV")
                {
                    if (!yli::load::load_csv_texture(
                                this->texture_filename,
                                this->format,
                                this->internal_format,
                                this->type,
                                this->left_filler_vector_any_value,
                                this->right_filler_vector_any_value,
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

                if (!is_headless && this->is_texture_loaded)
                {
                    // Get a handle for our "texture_sampler" uniform.
                    this->openGL_textureID = glGetUniformLocation(this->parent->get_programID(), "texture_sampler");

                    // Initialize uniform window width.
                    // This is named `screen_width` instead of `texture_width` for compatibility with other shaders.
                    this->screen_width_uniform_id = glGetUniformLocation(this->parent->get_programID(), "screen_width");
                    yli::opengl::uniform_1i(this->screen_width_uniform_id, this->texture_width);

                    // Initialize uniform window height.
                    // This is named `screen_height` instead of `texture_height` for compatibility with other shaders.
                    this->screen_height_uniform_id = glGetUniformLocation(this->parent->get_programID(), "screen_height");
                    yli::opengl::uniform_1i(this->screen_height_uniform_id, this->texture_height);

                    // Initialize uniform iteration index.
                    this->iteration_i_uniform_id = glGetUniformLocation(this->parent->get_programID(), "iteration_i");
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

                    // Load model into a VBO.

                    // Vertices.
                    glGenBuffers(1, &this->vertexbuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
                    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

                    // UVs.
                    glGenBuffers(1, &this->uvbuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
                    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::ComputeTask*";
                this->can_be_erased = true;
            }

            ComputeTask(const ComputeTask&) = delete;            // Delete copy constructor.
            ComputeTask &operator=(const ComputeTask&) = delete; // Delete copy assignment.

            // destructor.
            ~ComputeTask();

            yli::ontology::Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        private:
            void bind_to_parent();

            // This method renders this `ComputeTask`, that is, computes this task.
            void render() override;

            void preiterate() const;
            void postiterate() const;

            std::string texture_file_format; // Type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"csv"`/`"CSV"`.
            std::string texture_filename;    // Filename of the model file.
            std::string output_filename;     // Filename of the output file.

            yli::ontology::Shader* parent; // pointer to the `Shader`.

            std::shared_ptr<yli::common::AnyValue> left_filler_vector_any_value;
            std::shared_ptr<yli::common::AnyValue> right_filler_vector_any_value;

            // End iterating when `end_condition_callback_engine` returns `true`.
            std::shared_ptr<yli::callback::CallbackEngine> end_condition_callback_engine;

            std::shared_ptr<std::vector<uint8_t>> result_vector;

            // This is the maximum number of iterations.
            // If `end_condition_callback_engine` is `nullptr`, then this is the number of iterations.
            // If `end_condition_callback_engine` is not `nullptr`, then this is the maximum number of iterations.
            std::size_t n_max_iterations;

            std::size_t compute_taskID;

            std::size_t texture_width;
            std::size_t texture_height;
            std::size_t texture_size;

            std::size_t n_index_characters; // For intermediate results' filenames.

            std::size_t vertices_size;
            std::size_t uvs_size;

            // variables related to the framebuffer.
            uint32_t framebuffer;
            uint32_t source_texture;
            uint32_t target_texture;
            GLint openGL_textureID;              // Texture ID, returned by `glGetUniformLocation(this->parent->get_programID(), "texture_sampler")`.
            bool is_texture_loaded;
            bool is_framebuffer_initialized;
            bool is_ready;

            GLint vertex_position_modelspace_id;
            GLint vertex_uv_id;
            GLint screen_width_uniform_id;             // Location of the program's window width uniform.
            GLint screen_height_uniform_id;            // Location of the program's window height uniform.
            GLint iteration_i_uniform_id;              // Location of the program's iteration index uniform.

            uint32_t vertexbuffer;
            uint32_t uvbuffer;

            GLenum format;
            GLenum internal_format;
            GLenum output_format;
            GLenum type;

            bool should_ylikuutio_save_intermediate_results;
            bool should_ylikuutio_flip_texture;

            PreIterateCallback preiterate_callback;
            PostIterateCallback postiterate_callback;
    };
}

#endif
