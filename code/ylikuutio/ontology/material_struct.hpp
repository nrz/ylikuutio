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
#include "request.hpp"

// Include standard headers
#include <string>  // std::string
#include <utility> // std::move
#include <variant> // std::variant

namespace yli::ontology
{
    class Ecosystem;
    class Scene;
    class Pipeline;

    struct MaterialStruct : public EntityStruct
    {
        MaterialStruct(
                Request<Ecosystem>&& ecosystem_parent,
                Request<Pipeline>&& pipeline_master)
            : parent { std::move(ecosystem_parent) },
            pipeline_master { std::move(pipeline_master) }
        {
        }

        MaterialStruct(
                Request<Scene>&& scene_parent,
                Request<Pipeline>&& pipeline_master)
            : parent { std::move(scene_parent) },
            pipeline_master { std::move(pipeline_master) }
        {
        }

        std::variant<Request<Ecosystem>, Request<Scene>> parent {};
        Request<Pipeline> pipeline_master {};
        std::string texture_file_format;     // Type of the texture file. supported file formats so far: `"png"`/`"PNG"`.
        std::string texture_filename;        // Filename of the model file.
    };
}

#endif
