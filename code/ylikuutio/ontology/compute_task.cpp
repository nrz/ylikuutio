#include "compute_task.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr

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

            // Cleanup buffers and texture.
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);
            glDeleteTextures(1, &this->texture);

            if (this->parent == nullptr)
            {
                return;
            }

            this->parent->unbind_compute_task(this->childID);
        }

        void ComputeTask::render()
        {
            this->prerender();

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

                this->preiterate();

                // 1st attribute buffer: vertices.
                glEnableVertexAttribArray(this->vertex_position_modelspaceID);

                // 2nd attribute buffer: UVs.
                glEnableVertexAttribArray(this->vertexUVID);

                // TODO: do the computation.

                // 1st attribute buffer: vertices.
                glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
                glVertexAttribPointer(
                        this->vertex_position_modelspaceID, // The attribute we want to configure
                        3,                                  // size
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

                const std::size_t n_triangles = 2;
                const std::size_t n_vertices_in_triangle = 3;
                glDrawArrays(GL_TRIANGLES, 0, n_triangles * n_vertices_in_triangle); // draw 2 triangles (6 vertices, no VBO indexing).

                glDisableVertexAttribArray(this->vertex_position_modelspaceID);
                glDisableVertexAttribArray(this->vertexUVID);

                this->postiterate();
            }

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
