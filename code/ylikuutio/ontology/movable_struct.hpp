// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_MOVABLE_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MOVABLE_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "cartesian_coordinates_module.hpp"
#include "orientation_module.hpp"
#include "request.hpp"
#include "rigid_body_module_struct.hpp"
#include "code/ylikuutio/input/input.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>   // NAN
#include <string>  // std::string
#include <utility> // std::move
#include <variant> // std::variant
#include <vector>  // std::vector

namespace yli::ontology
{
    class Scene;
    class Brain;

    struct MovableStruct : public EntityStruct
    {
        // Default constructor of `MovableStruct` is used
        // for the default `Camera` in each `Scene`.
        MovableStruct() = default;

        explicit MovableStruct(
                Request<Scene>&& scene)
            : scene { std::move(scene) }
        {
        }

        MovableStruct(
                Request<Scene>&& scene,
                Request<Brain>&& brain_master)
            : scene { std::move(scene) },
            brain_master { std::move(brain_master) }
        {
        }

        MovableStruct(
                Request<Scene>&& scene,
                Request<Brain>&& brain_master,
                const glm::vec3& cartesian_coordinates,
                const float roll,
                const float yaw,
                const float pitch)
            : scene { std::move(scene) },
            brain_master { std::move(brain_master) },
            cartesian_coordinates { cartesian_coordinates },
            orientation(roll, yaw, pitch)
        {
        }

        MovableStruct(
                Request<Brain>&& brain_master,
                const glm::vec3& cartesian_coordinates,
                const float roll,
                const float yaw,
                const float pitch,
                const std::string& global_name,
                const std::string& local_name)
            : EntityStruct(global_name, local_name),
            brain_master { std::move(brain_master) },
            cartesian_coordinates { cartesian_coordinates },
            orientation(roll, yaw, pitch)
        {
        }

        yli::input::InputMethod input_method { yli::input::InputMethod::AI };
        Request<Scene> scene        {};
        Request<Brain> brain_master {};

        std::vector<glm::vec3> initial_rotate_vectors;
        std::vector<float> initial_rotate_angles;

        glm::vec3 original_scale_vector { glm::vec3(1.0f, 1.0f, 1.0f) };

        CartesianCoordinatesModule cartesian_coordinates { NAN, NAN, NAN };
        OrientationModule orientation { 0.0f, 0.0f, 0.0f };

        float scale { 1.0f };

        RigidBodyModuleStruct rigid_body_module_struct;
    };
}

#endif
