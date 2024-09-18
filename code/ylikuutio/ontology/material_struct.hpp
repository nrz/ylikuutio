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

#ifndef YLIKUUTIO_ONTOLOGY_MATERIAL_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MATERIAL_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include standard headers
#include <string>   // std::string
#include <variant>  // std::variant

namespace yli::ontology
{
    class Ecosystem;
    class Scene;
    class Pipeline;

    struct MaterialStruct : public EntityStruct
    {
        MaterialStruct(Ecosystem* const ecosystem_parent,
                Pipeline* const pipeline)
            : parent { ecosystem_parent },
            pipeline { pipeline }
        {
        }

        MaterialStruct(Scene* const scene_parent,
                Pipeline* const pipeline)
            : parent { scene_parent },
            pipeline { pipeline }
        {
        }

        MaterialStruct(const std::string& parent,
                Pipeline* const pipeline)
            : parent { parent },
            pipeline { pipeline }
        {
        }

        std::string texture_file_format;     // Type of the texture file. supported file formats so far: `"png"`/`"PNG"`.
        std::string texture_filename;        // Filename of the model file.
        std::variant<Ecosystem*, Scene*, std::string> parent;
        Pipeline* pipeline { nullptr };
    };
}

#endif
