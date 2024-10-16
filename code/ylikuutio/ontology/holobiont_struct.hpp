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

    struct HolobiontStruct : public MovableStruct
    {
        HolobiontStruct(
                Scene& parent,
                Symbiosis& symbiosis_master)
            : MovableStruct(nullptr, &parent),
            symbiosis_master { &symbiosis_master }
        {
        }

        HolobiontStruct(
                const std::string& parent,
                Symbiosis& symbiosis_master)
            : MovableStruct(nullptr, parent),
            symbiosis_master { &symbiosis_master }
        {
        }

        HolobiontStruct(
                Brain* const brain,
                const std::string& parent,
                Symbiosis& symbiosis_master)
            : MovableStruct(brain, parent),
            symbiosis_master { &symbiosis_master }
        {
        }

        Symbiosis* symbiosis_master { nullptr };

        std::vector<bool> should_render_bionts_vector;
    };
}

#endif
