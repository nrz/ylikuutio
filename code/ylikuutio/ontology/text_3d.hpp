// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;
    class Pipeline;
    class Object;
    class VectorFont;
    struct Text3DStruct;

    class Text3D final : public yli::ontology::Movable
    {
        public:
            // Disable all character `Object`s of `text_3d`,
            // set `parent` according to the input, request a new childID
            // from the `new_parent`, and create and enable the needed
            // character `Object`s of `text_3d`.
            // TODO: implement creation and enabling the character `Object`s!
            // Note: different fonts may provide glyphs for different Unicode code points!
            static std::optional<yli::data::AnyValue> bind_to_new_vector_font_parent(
                    yli::ontology::Text3D& text_3d,
                    yli::ontology::VectorFont& new_parent) noexcept;

            Text3D(
                    yli::ontology::Universe& universe,
                    const yli::ontology::Text3DStruct& text_3d_struct,
                    yli::ontology::GenericParentModule* const vector_font_parent_module,
                    yli::ontology::GenericMasterModule* const generic_master_module);

            Text3D(const Text3D&) = delete;            // Delete copy constructor.
            Text3D& operator=(const Text3D&) = delete; // Delete copy assignment.

            // destructor.
            ~Text3D() = default;

            yli::ontology::Entity* get_parent() const override;

            friend class yli::ontology::Object;
            friend void yli::ontology::create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* text_3d);

            yli::ontology::ChildModule child_of_vector_font;
            yli::ontology::GenericMasterModule master_of_objects;

            yli::ontology::Scene* get_scene() const override;

            yli::ontology::Pipeline* get_pipeline() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            std::string text_string;
    };
}

#endif
