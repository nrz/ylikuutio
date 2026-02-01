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

#ifndef YLIKUUTIO_ONTOLOGY_BIONT_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_BIONT_STRUCT_HPP_INCLUDED

#include "movable_struct.hpp"
#include "request.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <utility>  // std::move

namespace yli::ontology
{
    class Holobiont;
    class SymbiontSpecies;

    struct BiontStruct : public MovableStruct
    {
        BiontStruct(
                Request<Holobiont>&& holobiont_parent,
                Request<Scene>&& scene_master,
                Request<SymbiontSpecies>&& symbiont_species_master)
            : MovableStruct(std::move(scene_master)),
            holobiont_parent { std::move(holobiont_parent) },
            symbiont_species_master { std::move(symbiont_species_master) }
        {
        }

        Request<Holobiont> holobiont_parent              {};
        Request<SymbiontSpecies> symbiont_species_master {};
        std::size_t biontID { std::numeric_limits<std::size_t>::max() }; // `std::numeric_limits<std::size_t>::max()` means that `biontID` is not defined.
        bool should_render { true };
    };
}

#endif
