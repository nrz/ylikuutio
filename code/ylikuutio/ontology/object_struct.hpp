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

#ifndef YLIKUUTIO_ONTOLOGY_OBJECT_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_OBJECT_STRUCT_HPP_INCLUDED

#include "movable_struct.hpp"
#include "request.hpp"

// Include standard headers
#include <utility> // std::move

namespace yli::ontology
{
    class Scene;
    class Brain;
    class Species;

    struct ObjectStruct : public MovableStruct
    {
        explicit ObjectStruct(Request<Scene>&& scene_parent)
            : MovableStruct(std::move(scene_parent))
        {
        }

        ObjectStruct(
                Request<Scene>&& scene_parent,
                Request<Brain>&& brain_master)
            : MovableStruct(std::move(scene_parent), std::move(brain_master))
        {
        }

        ObjectStruct(
                Request<Scene>&& scene_parent,
                Request<Species>&& species_master)
            : MovableStruct(std::move(scene_parent)),
            species_master { std::move(species_master) }
        {
        }

        ObjectStruct(
                Request<Scene>&& scene_parent,
                Request<Brain>&& brain_master,
                Request<Species>&& species_master)
            : MovableStruct(std::move(scene_parent), std::move(brain_master)),
            species_master { std::move(species_master) }
        {
        }

        Request<Species> species_master {};
    };
}

#endif
