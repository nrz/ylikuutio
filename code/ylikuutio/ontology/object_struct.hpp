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

// Include standard headers
#include <string>  // std::string
#include <variant> // std::monostate, std::variant

namespace yli::ontology
{
    class Scene;
    class Brain;
    class Species;
    class ShapeshifterSequence;
    class Glyph;
    class Text3d;

    struct ObjectStruct : public MovableStruct
    {
        explicit ObjectStruct(Scene* const scene_parent)
            : MovableStruct(nullptr, scene_parent)
        {
        }

        ObjectStruct(
                Brain* const brain,
                Scene* const scene_parent)
            : MovableStruct(brain, scene_parent)
        {
        }

        ObjectStruct(
                Brain* const brain,
                const std::string& scene_parent,
                Species* const species)
            : MovableStruct(brain, scene_parent),
            mesh_master { species }
        {
        }

        ObjectStruct(
                const std::string& scene_parent,
                Species* const species)
            : MovableStruct(nullptr, scene_parent),
            mesh_master { species }
        {
        }

        ObjectStruct(
                Scene* const scene_parent,
                std::variant<
                std::monostate,
                Species*,
                ShapeshifterSequence*,
                Text3d*>
                mesh_master)
            : MovableStruct(nullptr, scene_parent),
            mesh_master { mesh_master }
        {
        }

        ObjectStruct(
                Brain* const brain,
                Scene* const scene_parent,
                std::variant<
                std::monostate,
                Species*,
                ShapeshifterSequence*,
                Text3d*>
                mesh_master)
            : MovableStruct(brain, scene_parent),
            mesh_master { mesh_master }
        {
        }

        std::variant<std::monostate, Species*, ShapeshifterSequence*, Text3d*> mesh_master {};
        Glyph* glyph { nullptr };
    };
}

#endif
