// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include "universe.hpp"
#include "scene.hpp"
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

namespace yli::ontology
{
    Camera::~Camera()
    {
        // destructor.
    }

    void Camera::activate()
    {
        if (this->universe != nullptr)
        {
            this->universe->set_active_camera(this);
        }
    }

    yli::ontology::Scene* Camera::get_scene() const
    {
        return static_cast<yli::ontology::Scene*>(this->child.get_parent());
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
