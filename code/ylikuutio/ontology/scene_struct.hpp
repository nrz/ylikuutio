// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_SCENE_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SCENE_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "camera_struct.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli::ontology
{
    struct SceneStruct: public yli::ontology::EntityStruct
    {
        CameraStruct default_camera_struct;      // Parameters of the default `Camera`.

        float gravity { 9.81f / 60.0f };         // Default gravity: Earth gravity, 9.81 m/s^2.
        glm::vec4 light_position { 0.0f, 0.0f, 0.0f, 1.0f }; // Default light position: origin.
        float water_level { 0.0f };              // Default water level: 0.0 meters.
        bool is_flight_mode_in_use { true };
    };
}

#endif
