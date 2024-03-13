// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "text_3d.hpp"
#include "vector_font.hpp"
#include "text_3d_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Entity;
    class Scene;
    class Pipeline;

    std::optional<yli::data::AnyValue> Text3D::bind_to_new_vector_font_parent(
            yli::ontology::Text3D& text_3d,
            yli::ontology::VectorFont& new_parent)
    {
        // Disable all character `Object`s of `text_3d`,
        // set `parent` according to the input, request a new childID
        // from the `new_parent`, and create and enable the needed
        // character `Object`s of `text_3d`.
        // TODO: implement creation and enabling the character `Object`s!
        // Note: different fonts may provide glyphs for different Unicode code points!

        const yli::ontology::Entity* const vector_font_parent = text_3d.get_parent();

        if (vector_font_parent == nullptr)
        {
            throw std::runtime_error("ERROR: `Text3D::bind_to_new_vector_font_parent`: `vector_font_parent` is `nullptr`!");
        }

        if (new_parent.has_child(text_3d.local_name))
        {
            std::cerr << "ERROR: `Text3D::bind_to_new_vector_font_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        text_3d.child_of_vector_font.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_text_3ds);

        return std::nullopt;
    }

    Text3D::Text3D(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::Text3DStruct& text_3d_struct,
            yli::ontology::GenericParentModule* const vector_font_parent_module,
            yli::ontology::GenericMasterModule* const brain_master_module)
        : Movable(
                application,
                universe,
                text_3d_struct,
                brain_master_module),
        child_of_vector_font(vector_font_parent_module, *this),
        master_of_objects(this, &this->registry, "objects")
    {
        // constructor.

        // TODO: `Text3D` constructor also creates each `Object`,
        // and binds each to its corresponding `Glyph` for rendering hierarchy,
        // and also binds each to this `Text3D` for ontological hierarchy.

        this->text_string = text_3d_struct.text_string;

        // Let's create each glyph `Object` in a loop.

        yli::ontology::create_glyph_objects(this->text_string, this);

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Text3D*";
        this->can_be_erased = true;
    }

    yli::ontology::Entity* Text3D::get_parent() const
    {
        return this->child_of_vector_font.get_parent();
    }

    yli::ontology::Scene* Text3D::get_scene() const
    {
        const yli::ontology::Entity* const parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    yli::ontology::Pipeline* Text3D::get_pipeline() const
    {
        const yli::ontology::VectorFont* const vector_font = static_cast<yli::ontology::VectorFont*>(this->get_parent());

        if (vector_font != nullptr)
        {
            return vector_font->get_pipeline();
        }

        return nullptr;
    }

    std::size_t Text3D::get_number_of_children() const
    {
        return 0; // `Text3D` has no children.
    }

    std::size_t Text3D::get_number_of_descendants() const
    {
        return 0; // `Text3D` has no children.
    }
}
