#include "compute_task.hpp"
#include "shader.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr

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

            glDeleteTextures(1, &this->texture);

            if (this->parent == nullptr)
            {
                return;
            }

            this->parent->unbind_compute_task(this->childID);
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
    }
}
