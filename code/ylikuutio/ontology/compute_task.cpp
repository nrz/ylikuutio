#include "compute_task.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>       // std::size_t
#include <iomanip>       // std::setfill, std::setw
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <utility>       // std::swap etc.

namespace yli
{
    namespace ontology
    {
        class Entity;

        void ComputeTask::bind_to_parent()
        {
            // Requirements:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Shader* const shader = this->parent;

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `ComputeTask::bind_to_parent`: `shader` is `nullptr`!\n";
                return;
            }

            // Get `childID` from `Shader` and set pointer to this `ComputeTask`.
            shader->bind_compute_task(this);
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

            this->parent->unbind_compute_task(this->childID);
        }

        void ComputeTask::render()
        {
            if (!this->is_texture_loaded)
            {
                // Do not render anything if texture is not loaded.
                return;
            }

            this->prerender();

            if (this->is_ready)
            {
                // If `ComputeTask` is ready, it does not need to be rendered.
                this->postrender();
                return;
            }

            if (!this->is_framebuffer_initialized)
            {
                // Create an FBO (off-screen framebuffer object).
                glGenFramebuffers(1, &this->framebuffer);
            }

            // Bind the offscreen buffer.
            glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

            if (!this->is_framebuffer_initialized)
            {
                // Create a target texture.
                glGenTextures(1, &this->target_texture);
                glBindTexture(GL_TEXTURE_2D, this->target_texture);

                // Define the texture.
                glTexImage2D(GL_TEXTURE_2D, 0, this->format, this->texture_width, this->texture_height, 0, this->format, this->type, NULL);

                yli::opengl::set_filtering_parameters();

                // Attach the texture.
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target_texture, 0);

                // Set background color for the framebuffer.
                this->universe->set_opengl_background_color();

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
                    std::shared_ptr<yli::datatypes::AnyValue> end_condition_any_value = this->end_condition_callback_engine->execute();

                    if (end_condition_any_value->type == yli::datatypes::BOOL && end_condition_any_value->bool_value)
                    {
                        break; // End condition was satisfied. Therefore, no more iterations.
                    }
                }

                // Update the value of `uniform` variable `iteration_i`.
                glUniform1i(this->iteration_i_uniform_ID, iteration_i);

                this->preiterate();

                // Bind our texture in Texture Unit 0.
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, this->source_texture);

                // Set our "texture_sampler" sampler to use Texture Unit 0.
                glUniform1i(this->openGL_textureID, 0);

                // 1st attribute buffer: vertices.
                glEnableVertexAttribArray(this->vertex_position_modelspaceID);

                // 2nd attribute buffer: UVs.
                glEnableVertexAttribArray(this->vertexUVID);

                // 1st attribute buffer: vertices.
                glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
                glVertexAttribPointer(
                        this->vertex_position_modelspaceID, // The attribute we want to configure
                        2,                                  // size
                        GL_FLOAT,                           // type
                        GL_FALSE,                           // normalized?
                        0,                                  // stride
                        (void*) 0                           // array buffer offset
                        );

                // 2nd attribute buffer: UVs.
                glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
                glVertexAttribPointer(
                        this->vertexUVID, // The attribute we want to configure
                        2,                // size : U+V => 2
                        GL_FLOAT,         // type
                        GL_FALSE,         // normalized?
                        0,                // stride
                        (void*) 0         // array buffer offset
                        );

                // Draw the triangles!
                glDrawArrays(GL_TRIANGLES, 0, this->vertices_size); // draw 2 triangles (6 vertices, no VBO indexing).

                glDisableVertexAttribArray(this->vertex_position_modelspaceID);
                glDisableVertexAttribArray(this->vertexUVID);

                if (this->should_ylikuutio_save_intermediate_results && !this->output_filename.empty())
                {
                    std::stringstream filename_stringstream;
                    filename_stringstream << this->output_filename << "_" << std::setfill('0') << std::setw(this->n_index_characters) << iteration_i;

                    // Transfer data from the GPU texture to a CPU array and save into a file.
                    yli::opengl::save_data_from_gpu_texture_into_file(
                            this->format, this->type, this->texture_width, this->texture_height, filename_stringstream.str(), this->should_ylikuutio_flip_texture);
                }

                // Ping pong.
                std::swap(this->source_texture, this->target_texture);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->target_texture, 0);

                GLenum error;

                while (true)
                {
                    error = glGetError();

                    if (error == GL_NO_ERROR)
                    {
                        break;
                    }

                    std::cout << "OpenGL error: 0x" << std::setfill('0') << std::setw(4) << std::hex << error << std::dec << "\n";
                }

                this->postiterate();
            }

            // Transfer data from the GPU texture to a CPU array and save into a file.
            yli::opengl::save_data_from_gpu_texture_into_file(
                    this->format, this->type, this->texture_width, this->texture_height, this->output_filename, this->should_ylikuutio_flip_texture);

            universe->restore_onscreen_rendering();

            this->is_ready = true;

            this->postrender();
        }

        yli::ontology::Entity* ComputeTask::get_parent() const
        {
            return this->parent;
        }

        std::size_t ComputeTask::get_number_of_children() const
        {
            return 0; // `ComputeTask` has no children.
        }

        std::size_t ComputeTask::get_number_of_descendants() const
        {
            return 0; // `ComputeTask` has no children.
        }

        void ComputeTask::preiterate() const
        {
            // Requirements:
            // `this->preiterate_callback` must not be `nullptr`.
            // `this->universe` must not be `nullptr`.
            // `this->universe->setting_master` must not be `nullptr`.

            if (this->preiterate_callback != nullptr &&
                    this->universe != nullptr &&
                    this->universe->get_setting_master() != nullptr)
            {
                this->preiterate_callback(this->universe, this->universe->get_setting_master());
            }
        }

        void ComputeTask::postiterate() const
        {
            // Requirements:
            // `this->postiterate_callback` must not be `nullptr`.
            // `this->universe` must not be `nullptr`.
            // `this->universe->setting_master` must not be `nullptr`.

            if (this->postiterate_callback != nullptr &&
                    this->universe != nullptr &&
                    this->universe->get_setting_master() != nullptr)
            {
                this->postiterate_callback(this->universe, this->universe->get_setting_master());
            }
        }
    }
}
