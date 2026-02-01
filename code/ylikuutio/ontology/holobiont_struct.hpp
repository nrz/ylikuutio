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

#ifndef YLIKUUTIO_ONTOLOGY_HOLOBIONT_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_HOLOBIONT_STRUCT_HPP_INCLUDED

#include "movable_struct.hpp"
#include "request.hpp"

// Include standard headers
#include <utility> // std::move
#include <vector> // std::vector

namespace yli::ontology
{
    class Scene;
    class Brain;
    class Symbiosis;

    struct HolobiontStruct : public MovableStruct
    {
        HolobiontStruct(
                Request<Scene>&& scene_parent,
                Request<Symbiosis>&& symbiosis_master)
            : MovableStruct(std::move(scene_parent)),
            symbiosis_master { std::move(symbiosis_master) }
        {
        }

        HolobiontStruct(
                Request<Scene>&& scene_parent,
                Request<Brain>&& brain_master,
                Request<Symbiosis>&& symbiosis_master)
            : MovableStruct(std::move(scene_parent), std::move(brain_master)),
            symbiosis_master { std::move(symbiosis_master) }
        {
        }

        Request<Symbiosis> symbiosis_master {};

        std::vector<bool> should_render_bionts_vector;
    };
}

#endif
