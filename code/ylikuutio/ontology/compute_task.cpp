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

                // TODO: do the computation.

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
