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

#ifndef YLIKUUTIO_ONTOLOGY_SPECIES_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SPECIES_STRUCT_HPP_INCLUDED

#include "mesh_provider_struct.hpp"
#include "request.hpp"

// Include standard headers
#include <utility> // std::move
#include <variant> // std::variant

namespace yli::ontology
{
    class Ecosystem;
    class Scene;
    class Material;

    struct SpeciesStruct final : public MeshProviderStruct
    {
        SpeciesStruct(
                Request<Ecosystem>&& ecosystem_parent,
                Request<Material>&& material_master)
            : parent { std::move(ecosystem_parent) },
            material_master { std::move(material_master) }
        {
        }

        SpeciesStruct(
                Request<Scene>&& scene_parent,
                Request<Material>&& material_master)
            : parent { std::move(scene_parent) },
            material_master { std::move(material_master) }
        {
        }

        // TODO: rename `parent` to `ecosystem_or_scene` parent and
        // modify `EntityFactory` accordingly!
        std::variant<Request<Ecosystem>, Request<Scene>> parent {};
        Request<Material> material_master {};
    };
}

#endif
