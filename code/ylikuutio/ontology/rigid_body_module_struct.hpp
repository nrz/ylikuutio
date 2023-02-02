// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_RIGID_BODY_MODULE_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_RIGID_BODY_MODULE_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string> // std::string

namespace yli::ontology
{
    struct RigidBodyModuleStruct
    {
        std::string type;
        glm::vec3 half_extents { 0.0f, 0.0f, 0.0f }; // For `"box"` type.
        float radius           { 0.0f };             // For `"sphere"` type.
        float mass             { 0.0f };             // An object is static if and only if its mass is 0.
    };
}

#endif
