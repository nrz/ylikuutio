// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
#include <variant> // std::variant
#include <vector>  // std::vector

namespace yli::ontology
{
    class Brain;
    class Scene;

    struct MovableStruct : public EntityStruct
    {
        MovableStruct()
            : orientation(0.0f, 0.0f, 0.0f)
        {
        }

        MovableStruct(
                Brain* const brain_master,
                const glm::vec3& cartesian_coordinates,
                const float roll,
                const float yaw,
                const float pitch)
            : brain_master { brain_master },
            cartesian_coordinates { cartesian_coordinates },
            orientation(roll, yaw, pitch)
        {
        }

        MovableStruct(
                Brain* const brain_master,
                const glm::vec3& cartesian_coordinates,
                const float roll,
                const float yaw,
                const float pitch,
                const std::string& global_name,
                const std::string& local_name)
            : EntityStruct(global_name, local_name),
            brain_master { brain_master },
            cartesian_coordinates { cartesian_coordinates },
            orientation(roll, yaw, pitch)
        {
        }

        MovableStruct(
                Brain* const brain_master,
                Scene* const scene)
            : brain_master { brain_master },
            scene { scene }
        {
        }

        MovableStruct(
                Brain* const brain_master,
                const std::string& scene)
            : brain_master { brain_master },
            scene { scene }
        {
        }

        yli::input::InputMethod input_method { yli::input::InputMethod::AI };
        Brain* brain_master { nullptr };
        std::variant<Scene*, std::string> scene {};

        std::vector<glm::vec3> initial_rotate_vectors;
        std::vector<float> initial_rotate_angles;

        glm::vec3 original_scale_vector { glm::vec3(1.0f, 1.0f, 1.0f) };

        CartesianCoordinatesModule cartesian_coordinates { NAN, NAN, NAN };
        OrientationModule orientation;

        float scale { 1.0f };

        RigidBodyModuleStruct rigid_body_module_struct;
    };
}

#endif
