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

#include "text_3d.hpp"
#include "scene.hpp"
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
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;
    class Pipeline;

    std::optional<yli::data::AnyValue> Text3d::bind_to_new_scene_parent(
            Text3d& text_3d,
            Scene& new_parent)
    {
        // Disable all `GlyphObject`s of `text_3d`,
        // set `parent` according to the input, request a new childID
        // from the `new_parent`, and create and enable the needed
        // `GlyphObject`s of `text_3d`.
        // TODO: implement creation and enabling the `GlyphObject`s!
        // Note: different fonts may provide glyphs for different Unicode code points!

        const Entity* const scene_parent = text_3d.get_parent();

        if (scene_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Text3d::bind_to_new_scene_parent`: `scene_parent` is `nullptr`!");
        }

        if (new_parent.has_child(text_3d.local_name))
        {
            std::cerr << "ERROR: `Text3d::bind_to_new_scene_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        text_3d.child_of_scene.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_text_3ds);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Text3d::bind_to_new_vector_font_master(
            Text3d& text_3d,
            VectorFont& new_master)
    {
        // Disable all `GlyphObject`s of `text_3d`,
        // set `master` according to the input, request a new apprenticeID
        // from the `new_master`, and create and enable the needed
        // `GlyphObject`s of `text_3d`.
        // TODO: implement creation and enabling the `GlyphObject`s!
        // Note: different fonts may provide glyphs for different Unicode code points!

        VectorFont* const vector_font_master = text_3d.get_vector_font_master();

        if (vector_font_master == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Text3d::bind_to_new_vector_font_master`: `vector_font_master` is `nullptr`!");
        }

        if (new_master.has_child(text_3d.local_name))
        {
            std::cerr << "ERROR: `Text3d::bind_to_new_vector_font_master`: local name is already in use!\n";
            return std::nullopt;
        }

        text_3d.apprentice_of_vector_font.unbind_and_bind_to_new_generic_master_module(
                &new_master.master_of_text_3ds);

        return std::nullopt;
    }

    Text3d::Text3d(
            yli::core::Application& application,
            Universe& universe,
            const Text3dStruct& text_3d_struct,
            GenericParentModule* const scene_parent_module,
            GenericMasterModule* const brain_master_module,
            GenericMasterModule* const vector_font_master_module)
        : Movable(
                application,
                universe,
                text_3d_struct,
                brain_master_module),
        child_of_scene(scene_parent_module, *this),
        apprentice_of_vector_font(vector_font_master_module, this),
        master_of_glyph_objects(*this, &this->registry, "glyph_objects")
    {
        // TODO: `Text3d` constructor also creates each `GlyphObject`,
        // and binds each to its corresponding `Glyph` for rendering hierarchy,
        // and also binds each to this `Text3d` for ontological hierarchy.

        this->text_string = text_3d_struct.text_string;

        // Let's create each `GlyphObject` in a loop.

        create_glyph_objects(this->text_string, *this);

        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Text3d*";
        this->can_be_erased = true;
    }

    Entity* Text3d::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    Scene* Text3d::get_scene() const
    {
        return static_cast<Scene*>(this->get_parent());
    }

    Pipeline* Text3d::get_pipeline() const
    {
        const VectorFont* const vector_font_master = this->get_vector_font_master();

        if (vector_font_master == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Text3d::get_pipeline`: `vector_font_parent` is `nullptr`!");
        }

        return vector_font_master->get_pipeline();
    }

    VectorFont* Text3d::get_vector_font_master() const
    {
        return static_cast<VectorFont*>(this->apprentice_of_vector_font.get_master());
    }

    std::size_t Text3d::get_number_of_children() const
    {
        return 0; // `Text3d` has no children.
    }

    std::size_t Text3d::get_number_of_descendants() const
    {
        return 0; // `Text3d` has no children.
    }
}
