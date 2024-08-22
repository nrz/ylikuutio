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

#ifndef YLIKUUTIO_ONTOLOGY_HOLOBIONT_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_HOLOBIONT_STRUCT_HPP_INCLUDED

#include "movable_struct.hpp"

// Include standard headers
#include <string> // std::string
#include <vector> // std::vector

namespace yli::ontology
{
    class Scene;
    class Brain;
    class Symbiosis;

    struct HolobiontStruct : public yli::ontology::MovableStruct
    {
        HolobiontStruct(
                yli::ontology::Scene& parent,
                yli::ontology::Symbiosis& symbiosis)
            : MovableStruct(nullptr, &parent),
            symbiosis { &symbiosis }
        {
        }

        HolobiontStruct(
                const std::string& parent,
                yli::ontology::Symbiosis& symbiosis)
            : MovableStruct(nullptr, parent),
            symbiosis { &symbiosis }
        {
        }

        HolobiontStruct(
                yli::ontology::Brain* const brain,
                const std::string& parent,
                yli::ontology::Symbiosis& symbiosis)
            : MovableStruct(brain, parent),
            symbiosis { &symbiosis }
        {
        }

        yli::ontology::Symbiosis* symbiosis { nullptr }; // pointer to the `Symbiosis`.

        std::vector<bool> should_render_bionts_vector;
    };
}

#endif
