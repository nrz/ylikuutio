#ifndef __COMPUTE_TASK_HPP_INCLUDED
#define __COMPUTE_TASK_HPP_INCLUDED

#include "entity.hpp"
#include "compute_task_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
    }

    namespace ontology
    {
        class Shader;

        class ComputeTask: public yli::ontology::Entity
        {
            public:
                ComputeTask(yli::ontology::Universe* const universe, const ComputeTaskStruct& compute_task_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent = compute_task_struct.parent;
                    this->end_condition_callback_engine = compute_task_struct.end_condition_callback_engine;
                    this->n_max_iterations = compute_task_struct.n_max_iterations;
                    this->compute_taskID = compute_task_struct.compute_taskID;
                    this->framebuffer = 0;
                    this->texture = 0;
                    this->render_buffer = 0;

                    this->texture_width = compute_task_struct.texture_width;
                    this->texture_height = compute_task_struct.texture_height;

                    // Create FBO (off-screen framebuffer object).
                    glGenFramebuffers(1, &this->framebuffer);

                    // Bind offscreen buffer.
                    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

                    // Create texture.
                    glGenTextures(1, &this->texture);
                    glBindTexture(GL_TEXTURE_2D, this->texture);

                    // Define texture.
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texture_width, this->texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

                    yli::opengl::set_filtering_parameters();

                    // Attach texture.
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture, 0);

                    // Create and bind render buffer with depth and stencil attachments.
                    glGenRenderbuffers(1, &this->render_buffer);
                    glBindRenderbuffer(GL_RENDERBUFFER, this->render_buffer);
                    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->texture_width, this->texture_height);
                    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->render_buffer);

                    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                    {
                        std::cerr << "ERROR: `ComputeTask::ComputeTask`: framebuffer is not complete!\n";
                    }

                    // Get `childID` from `Shader` and set pointer to this `ComputeTask`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::ComputeTask*";
                }

                // destructor.
                ~ComputeTask();

                yli::ontology::Entity* get_parent() const override;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend std::size_t yli::ontology::get_number_of_descendants(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                yli::ontology::Shader* parent; // pointer to the `Shader`.

                // End iterating when `end_condition_callback_engine` returns `true`.
                std::shared_ptr<yli::callback_system::CallbackEngine> end_condition_callback_engine;

                // This is the maximum number of iterations.
                // If `end_condition_callback_engine` is `nullptr`, then this is the number of iterations.
                // If `end_condition_callback_engine` is not `nullptr`, then this is the maximum number of iterations.
                std::size_t n_max_iterations;

                std::size_t compute_taskID;

                uint32_t framebuffer;
                uint32_t texture;
                uint32_t render_buffer;

                std::size_t texture_width;
                std::size_t texture_height;
        };
    }
}

#endif
