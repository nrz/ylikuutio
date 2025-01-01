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

#ifndef YLIKUUTIO_ONTOLOGY_MESH_PROVIDER_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MESH_PROVIDER_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "request.hpp"
#include "code/ylikuutio/load/model_loader_struct.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::ontology
{
    class Ecosystem;
    class Scene;
    class ShapeshifterTransformation;
    class VectorFont;

    struct MeshProviderStruct : public EntityStruct
    {
        yli::load::ModelLoaderStruct model_loader_struct;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        uint32_t vertex_count { std::numeric_limits<uint32_t>::max() };
    };
}

#endif
