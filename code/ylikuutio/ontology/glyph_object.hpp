// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_GLYPH_OBJECT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GLYPH_OBJECT_HPP_INCLUDED

#include "child_module.hpp"
#include "apprentice_module.hpp"
#include "movable.hpp"

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
    class Scene;
    struct GlyphObjectStruct;

    class GlyphObject final : public Movable
    {
        public:
            GlyphObject(
                    yli::core::Application& application,
                    Universe& universe,
                    const GlyphObjectStruct& glyph_object_struct,
                    GenericParentModule* const scene_parent_module,
                    GenericMasterModule* const glyph_master_module,
                    GenericMasterModule* const text_3d_master_module);

            GlyphObject(const GlyphObject&) = delete;            // Delete copy constructor.
            GlyphObject &operator=(const GlyphObject&) = delete; // Delete copy assignment.

            virtual ~GlyphObject() = default;

            Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            Scene* get_scene() const override;

            ChildModule child_of_scene;
            ApprenticeModule apprentice_of_glyph;
            ApprenticeModule apprentice_of_text_3d;
    };
}

#endif
