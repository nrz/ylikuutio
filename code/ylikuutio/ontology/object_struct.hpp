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
    class Brain;
    class Scene;
    class Species;
    class ShapeshifterSequence;
    class Glyph;
    class Text3D;

    struct ObjectStruct : public yli::ontology::MovableStruct
    {
        explicit ObjectStruct(yli::ontology::Scene* const parent)
        {
            this->scene = parent;
        }

        ObjectStruct(
                yli::ontology::Brain* const brain,
                yli::ontology::Scene* const parent)
            : MovableStruct(brain, parent)
        {
        }

        ObjectStruct(
                yli::ontology::Brain* const brain,
                const std::string& scene,
                yli::ontology::Species* const species)
            : MovableStruct(brain, scene),
            mesh_master { species }
        {
        }

        ObjectStruct(
                const std::string& scene,
                yli::ontology::Species* const species)
            : MovableStruct(nullptr, scene),
            mesh_master { species }
        {
        }

        ObjectStruct(
                yli::ontology::Scene* const parent,
                std::variant<
                std::monostate,
                yli::ontology::Species*,
                yli::ontology::ShapeshifterSequence*,
                yli::ontology::Text3D*>
                mesh_master)
            : MovableStruct(nullptr, parent),
            mesh_master { mesh_master }
        {
        }

        ObjectStruct(
                yli::ontology::Brain* const brain,
                yli::ontology::Scene* const parent,
                std::variant<
                std::monostate,
                yli::ontology::Species*,
                yli::ontology::ShapeshifterSequence*,
                yli::ontology::Text3D*>
                mesh_master)
            : MovableStruct(brain, parent),
            mesh_master { mesh_master }
        {
        }

        std::variant<std::monostate, yli::ontology::Species*, yli::ontology::ShapeshifterSequence*, yli::ontology::Text3D*> mesh_master {};
        yli::ontology::Glyph* glyph { nullptr }; // pointer to the `Glyph` (not a parent!).
    };
}

#endif
