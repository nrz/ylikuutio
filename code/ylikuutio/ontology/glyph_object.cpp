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

#include "glyph_object.hpp"
#include "scene.hpp"
#include "glyph_object_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;
    class Universe;

    Entity* GlyphObject::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    GlyphObject::GlyphObject(
            yli::core::Application& application,
            Universe& universe,
            const GlyphObjectStruct& glyph_object_struct,
            GenericParentModule* const scene_parent_module,
            GenericMasterModule* const glyph_master_module,
            GenericMasterModule* const text_3d_master_module)
        : Movable(
                application,
                universe,
                glyph_object_struct,
                nullptr),
        child_of_scene(scene_parent_module, *this),
        apprentice_of_glyph(glyph_master_module, this),
        apprentice_of_text_3d(text_3d_master_module, this)
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::GlyphObject*";
    }

    std::size_t GlyphObject::get_number_of_children() const
    {
        return 0;
    }

    std::size_t GlyphObject::get_number_of_descendants() const
    {
        return 0;
    }

    Scene* GlyphObject::get_scene() const
    {
        return this->child_of_scene.get_scene();
    }
}
