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

#ifndef YLIKUUTIO_ONTOLOGY_MATERIAL_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MATERIAL_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "request.hpp"
#include "texture_file_format.hpp"

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
                Request<Pipeline>&& pipeline_master,
                const TextureFileFormat texture_file_format)
            : parent { std::move(ecosystem_parent) },
            pipeline_master { std::move(pipeline_master) },
            texture_file_format { texture_file_format }
        {
        }

        MaterialStruct(
                Request<Scene>&& scene_parent,
                Request<Pipeline>&& pipeline_master,
                const TextureFileFormat texture_file_format)
            : parent { std::move(scene_parent) },
            pipeline_master { std::move(pipeline_master) },
            texture_file_format { texture_file_format }
        {
        }

        std::variant<Request<Ecosystem>, Request<Scene>> parent {};
        Request<Pipeline> pipeline_master {};
        const TextureFileFormat texture_file_format; // Type of the texture file.
        std::string texture_filename;        // Filename of the model file.
    };
}

#endif
