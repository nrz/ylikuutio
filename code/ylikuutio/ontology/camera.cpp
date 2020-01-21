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

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

#include "camera.hpp"
#include "entity.hpp"
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
            scene->parent_of_cameras.bind_child(this);
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
            scene->parent_of_cameras.unbind_child(this->childID);
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
    }
}
