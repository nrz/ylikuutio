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

#ifndef YLIKUUTIO_ONTOLOGY_PIPELINE_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_PIPELINE_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include standard headers
#include <string> // std::string
#include <variant> // std::holds_alternative, std::monostate, std::variant

namespace yli::ontology
{
    class Ecosystem;
    class Scene;

    struct PipelineStruct: public yli::ontology::EntityStruct
    {
        std::string vertex_shader;    // filename of vertex shader.
        std::string fragment_shader;  // filename of fragment shader.
        std::variant<std::monostate, yli::ontology::Ecosystem*, yli::ontology::Scene*> parent; // Pointer to `Ecosystem` or `Scene`.
        bool is_gpgpu_pipeline { false }; // TODO: GPGPU `Pipeline`s are not rendered on screen but their result textures can be used by `Material`s.
    };
}

#endif