// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

#include "entity.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "ground_level.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void Camera::bind_to_parent()
        {
            // Requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Scene* const scene = this->parent;

            if (scene == nullptr)
            {
                std::cerr << "ERROR: `Camera::bind_to_parent`: `scene` is `nullptr`!\n";
                return;
            }

            // Get `childID` from `Scene` and set pointer to this `Camera`.
            scene->bind_camera(this);
        }

        Camera::~Camera()
        {
            // destructor.
            //
            // Requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Scene* const scene = this->parent;

            if (scene == nullptr)
            {
                std::cerr << "ERROR: `Camera::~Camera`: `scene` is `nullptr`!\n";
                return;
            }

            if (scene->get_active_camera() == this)
            {
                // Make this `Camera` no more the active `Camera`.
                scene->set_active_camera(nullptr);
            }

            // Set pointer to this `Camera` to `nullptr`.
            scene->unbind_camera(this->childID);
        }

        yli::ontology::Entity* Camera::get_parent() const
        {
            return this->parent;
        }

        std::size_t Camera::get_number_of_children() const
        {
            return 0; // `Camera` has no children.
        }

        std::size_t Camera::get_number_of_descendants() const
        {
            return 0; // `Camera` has no children.
        }

        const glm::mat4& Camera::get_projection_matrix() const
        {
            return this->projection_matrix;
        }

        const glm::mat4& Camera::get_view_matrix() const
        {
            return this->view_matrix;
        }

        bool Camera::get_is_static_view() const
        {
            return this->is_static_view;
        }

        bool Camera::compute_and_update_matrices_from_inputs()
        {
            if (!this->universe->is_flight_mode_in_use)
            {
                this->universe->fall_speed += this->universe->gravity;
                this->cartesian_coordinates.y -= this->universe->fall_speed;
            }

            float FoV = this->universe->get_initialFoV();

            // Adjust position according to the ground.
            if (!this->universe->is_flight_mode_in_use)
            {
                if (this->universe->get_terrain_species() != nullptr)
                {
                    float ground_y = yli::ontology::get_floor_level(
                            static_cast<yli::ontology::Species*>(this->universe->get_terrain_species()),
                            this->cartesian_coordinates);

                    if (!std::isnan(ground_y) && this->cartesian_coordinates.y < ground_y)
                    {
                        this->cartesian_coordinates.y = ground_y;
                        this->universe->fall_speed = 0.0f;
                    }
                }
            }

            if (this->universe->testing_spherical_terrain_in_use)
            {
                // Compute spherical coordinates.
                this->spherical_coordinates.rho = sqrt(
                        (this->cartesian_coordinates.x * this->cartesian_coordinates.x) +
                        (this->cartesian_coordinates.y * this->cartesian_coordinates.y) +
                        (this->cartesian_coordinates.z * this->cartesian_coordinates.z));
                this->spherical_coordinates.theta = RADIANS_TO_DEGREES(atan2(sqrt(
                                (this->cartesian_coordinates.x * this->cartesian_coordinates.x) +
                                (this->cartesian_coordinates.y * this->cartesian_coordinates.y)),
                            this->cartesian_coordinates.z));
                this->spherical_coordinates.phi = RADIANS_TO_DEGREES(atan2(
                            this->cartesian_coordinates.y,
                            this->cartesian_coordinates.x));
            }

            glm::vec3 camera_cartesian_coordinates;
            camera_cartesian_coordinates.x = this->cartesian_coordinates.x;
            camera_cartesian_coordinates.y = this->cartesian_coordinates.y;
            camera_cartesian_coordinates.z = this->cartesian_coordinates.z;
            camera_cartesian_coordinates.y += 2.0f;

            // Projection matrix: field of view, aspect ratio, display range: 0.1 unit <-> 100 units.
            this->projection_matrix = glm::perspective(
                    DEGREES_TO_RADIANS(FoV),
                    this->universe->get_aspect_ratio(),
                    0.001f,
                    5000.0f + 2.0f * this->universe->get_planet_radius());
            // Camera matrix.
            this->view_matrix = glm::lookAt(
                    camera_cartesian_coordinates,                   // Camera coordinates.
                    camera_cartesian_coordinates + this->direction, // Camera looks here: at the same position, plus "direction".
                    this->up);                                      // Head is up (set to 0,-1,0 to look upside-down).

            return true;
        }
    }
}
