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

#ifndef __YLIKUUTIO_ONTOLOGY_MOVABLE_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MOVABLE_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/input/input.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>  // NAN, std::isnan, std::pow
#include <string> // std::string
#include <vector> // std::vector

namespace yli::ontology
{
    class Brain;

    struct MovableStruct: public yli::ontology::EntityStruct
    {
        MovableStruct()
            : EntityStruct()
        {
            // constructor.
        }

        MovableStruct(
                yli::ontology::Brain* const brain,
                const glm::vec3& cartesian_coordinates,
                yli::data::SphericalCoordinatesStruct spherical_coordinates,
                const float yaw,
                const float pitch)
            : EntityStruct(),
            brain(brain),
            cartesian_coordinates(cartesian_coordinates),
            spherical_coordinates(spherical_coordinates),
            yaw(yaw),
            pitch(pitch)
        {
            // constructor.
        }

        MovableStruct(
                yli::ontology::Brain* const brain,
                const glm::vec3& cartesian_coordinates,
                yli::data::SphericalCoordinatesStruct spherical_coordinates,
                const float yaw,
                const float pitch,
                const std::string& global_name,
                const std::string& local_name)
            : EntityStruct(global_name, local_name),
            brain(brain),
            cartesian_coordinates(cartesian_coordinates),
            spherical_coordinates(spherical_coordinates),
            yaw(yaw),
            pitch(pitch)
        {
            // constructor.
        }

        yli::input::InputMethod input_method { yli::input::InputMethod::AI };
        yli::ontology::Brain* brain { nullptr };

        std::vector<glm::vec3> initial_rotate_vectors;
        std::vector<float> initial_rotate_angles;

        glm::vec3 original_scale_vector { glm::vec3(1.0f, 1.0f, 1.0f) };

        glm::vec3 cartesian_coordinates { glm::vec3(NAN, NAN, NAN) };
        yli::data::SphericalCoordinatesStruct spherical_coordinates { NAN, NAN, NAN };
        float yaw { 0.0f };
        float pitch { 0.0f };
    };
}

#endif
