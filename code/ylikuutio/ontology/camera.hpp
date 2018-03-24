#ifndef __CAMERA_HPP_INCLUDED
#define __CAMERA_HPP_INCLUDED

#include "movable.hpp"
#include "universe.hpp"
#include "camera_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Universe;

    class Camera: public ontology::Movable
    {
        public:
            // constructor.
            Camera(ontology::Universe* const universe, CameraStruct& camera_struct)
                : Movable(universe, camera_struct.cartesian_coordinates)
            {
                this->horizontal_angle = NAN;
                this->vertical_angle = NAN;

                // Variables related to the camera.
                this->projection_matrix = glm::mat4(1.0f); // identity matrix (dummy value).
                this->view_matrix = glm::mat4(1.0f);       // identity matrix (dummy value).

                // constructor.
                this->parent = camera_struct.parent;

                // get `childID` from `Scene` and set pointer to this `Camera`.
                this->bind_to_parent();
            }

            // destructor.
            virtual ~Camera();

            ontology::Entity* get_parent() const override;

            glm::vec3 get_direction() const;
            glm::vec3 get_up() const;
            glm::vec3 get_right() const;
            void adjust_horizontal_angle(float adjustment);

            glm::mat4& get_projection_matrix();
            glm::mat4& get_view_matrix();
            float get_horizontal_angle() const;
            float get_vertical_angle() const;

            friend class Universe;

            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);

        private:
            void bind_to_parent();

            int32_t get_number_of_children() const override;
            int32_t get_number_of_descendants() const override;

            bool compute_and_update_matrices_from_inputs();

            // Variables related to location and orientation.

            ontology::Scene* parent;

            // Variables related to the camera.
            glm::mat4 projection_matrix;
            glm::mat4 view_matrix;
            double horizontal_angle;
            double vertical_angle;
    };
}

#endif
