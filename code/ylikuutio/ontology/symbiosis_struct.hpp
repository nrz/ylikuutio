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

#ifndef YLIKUUTIO_ONTOLOGY_SYMBIOSIS_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SYMBIOSIS_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include standard headers
#include <string>  // std::string
#include <variant> // std::monostate, std::variant

namespace yli::ontology
{
    class Ecosystem;
    class Scene;
    class Pipeline;

    struct SymbiosisStruct final : public yli::ontology::EntityStruct
    {
        SymbiosisStruct(
                yli::ontology::Ecosystem* const ecosystem_parent,
                yli::ontology::Pipeline* const pipeline_master)
            : parent { ecosystem_parent },
            pipeline { pipeline_master }
        {
        }

        SymbiosisStruct(
                yli::ontology::Scene* const scene_parent,
                yli::ontology::Pipeline* const pipeline_master)
            : parent { scene_parent },
            pipeline { pipeline_master }
        {
        }

        std::string model_filename;                         // Filename of the model file.
        std::string model_file_format;                      // Type of the model file. Supported file formats so far:
                                                            // `"fbx"`/`"FBX"` - FBX model.

        std::variant<yli::ontology::Ecosystem*, yli::ontology::Scene*> parent {};
        yli::ontology::Pipeline* pipeline { nullptr };
    };
}

#endif
