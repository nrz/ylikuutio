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

#ifndef YLIKUUTIO_ONTOLOGY_TEXT_3D_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_TEXT_3D_HPP_INCLUDED

#include "movable.hpp"
#include "child_module.hpp"
#include "generic_master_module.hpp"
#include "glyph_object_creation.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <string>   // std::string

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;
    class Pipeline;
    class Object;
    class VectorFont;
    struct Text3dStruct;

    class Text3d final : public Movable
    {
        public:
            // Disable all character `Object`s of `text_3d`,
            // set `parent` according to the input, request a new childID
            // from the `new_parent`, and create and enable the needed
            // character `Object`s of `text_3d`.
            // TODO: implement creation and enabling the character `Object`s!
            // Note: different fonts may provide glyphs for different Unicode code points!
            static std::optional<yli::data::AnyValue> bind_to_new_vector_font_parent(
                    Text3d& text_3d,
                    VectorFont& new_parent);

            Text3d(
                    yli::core::Application& application,
                    Universe& universe,
                    const Text3dStruct& text_3d_struct,
                    GenericParentModule* const vector_font_parent_module,
                    GenericMasterModule* const brain_master_module);

            ~Text3d() = default;

            Text3d(const Text3d&) = delete;            // Delete copy constructor.
            Text3d& operator=(const Text3d&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            friend class Object;
            friend void create_glyph_objects(const std::string& text_string, Text3d& text_3d);

            ChildModule child_of_vector_font;
            GenericMasterModule master_of_objects;

            Scene* get_scene() const override;

            Pipeline* get_pipeline() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            std::string text_string;
    };
}

#endif
