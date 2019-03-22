#ifndef __CAMERA_HPP_INCLUDED
#define __CAMERA_HPP_INCLUDED

#include "movable.hpp"
#include "universe.hpp"
#include "camera_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;

        class Camera: public yli::ontology::Movable
        {
            public:
                Camera(yli::ontology::Universe* const universe, const CameraStruct& camera_struct)
                    : Movable(universe, camera_struct.cartesian_coordinates)
                {
                    // constructor.

                    this->horizontal_angle  = NAN;
                    this->vertical_angle    = NAN;

                    // variables related to the projection.
                    this->projection_matrix = glm::mat4(1.0f); // identity matrix (dummy value).
                    this->view_matrix       = glm::mat4(1.0f); // identity matrix (dummy value).
                    this->parent            = camera_struct.parent;

                    // Get `childID` from the `Scene` and set pointer to this `Camera`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Camera*";
                }

                // destructor.
                virtual ~Camera();

                yli::ontology::Entity* get_parent() const override;

                const glm::vec3& get_direction() const;
                const glm::vec3& get_up() const;
                const glm::vec3& get_right() const;
                void adjust_horizontal_angle(float adjustment);

                glm::mat4& get_projection_matrix();
                glm::mat4& get_view_matrix();
                float get_horizontal_angle() const;
                float get_vertical_angle() const;

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                friend class Universe;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                bool compute_and_update_matrices_from_inputs();

                // variables related to location and orientation.

                yli::ontology::Scene* parent;

                // variables related to the projection.
                glm::mat4 projection_matrix;
                glm::mat4 view_matrix;
                double horizontal_angle;
                double vertical_angle;
        };
    }
}

#endif
