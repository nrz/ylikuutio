// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_STRUCT_HPP_INCLUDED

#include "mesh_provider_struct.hpp"
#include "request.hpp"

// Include standard headers
#include <utility>  // std::move

namespace yli::ontology
{
    class SymbiontMaterial;

    struct SymbiontSpeciesStruct final : public MeshProviderStruct
    {
        explicit SymbiontSpeciesStruct(Request<SymbiontMaterial>&& symbiont_material_parent)
            : symbiont_material_parent { std::move(symbiont_material_parent) }
        {
        }

        Request<SymbiontMaterial> symbiont_material_parent {};
    };
}

#endif
