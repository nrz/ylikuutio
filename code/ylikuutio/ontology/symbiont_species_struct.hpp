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

#ifndef YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_STRUCT_HPP_INCLUDED

#include "model_struct.hpp"

namespace yli::ontology
{
    class Pipeline;
    class SymbiontMaterial;

    struct SymbiontSpeciesStruct final : public ModelStruct
    {
        SymbiontSpeciesStruct(
                Pipeline* const pipeline,
                SymbiontMaterial* const symbiont_material)
            : ModelStruct(pipeline, symbiont_material),
            symbiont_material { symbiont_material }
        {
        }

        SymbiontMaterial* const symbiont_material { nullptr };
    };
}

#endif
