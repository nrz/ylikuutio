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

#include "vector_font.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "pipeline.hpp"
#include "material.hpp"
#include "text_3d.hpp"
#include "generic_entity_factory.hpp"
#include "family_templates.hpp"
#include "request.hpp"
#include "vector_font_struct.hpp"
#include "glyph_struct.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <ios>       // std::dec
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Text3d;
    class Glyph;

    std::optional<yli::data::AnyValue> VectorFont::bind_to_new_material_parent(
            VectorFont& vector_font,
            Material& new_parent)
    {
        // Set pointer to `vector_font` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const Material* const material_parent = static_cast<Material*>(vector_font.get_parent());

        if (material_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `VectorFont::bind_to_new_material_parent`: `material_parent` is `nullptr`!");
        }

        if (new_parent.has_child(vector_font.local_name))
        {
            std::cerr << "ERROR: `VectorFont::bind_to_new_material_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        vector_font.child_of_material.unbind_and_bind_to_new_parent(&new_parent.parent_of_vector_fonts);
        return std::nullopt;
    }

    // This method returns a pointer to `Glyph` that matches the given `unicode_value`,
    // and `nullptr` if this `VectorFont` does not contain such a `Glyph`.
    Glyph* VectorFont::get_glyph_pointer(const int32_t unicode_value) const
    {
        if (this->unicode_glyph_map.count(unicode_value) == 1)
        {
            return this->unicode_glyph_map.at(unicode_value);
        }

        // No matching `Glyph` found!
        return nullptr;
    }

    VectorFont::VectorFont(
            yli::core::Application& application,
            Universe& universe,
            const VectorFontStruct& vector_font_struct,
            GenericParentModule* const material_parent_module)
        : Entity(application, universe, vector_font_struct),
        child_of_material(material_parent_module, *this),
        parent_of_glyphs(
                *this,
                this->registry,
                "glyphs"),
        master_of_text_3ds(
                *this,
                &this->registry,
                "text_3ds"),
        font_file_format      { vector_font_struct.font_file_format },
        font_filename         { vector_font_struct.font_filename },
        vertex_scaling_factor { vector_font_struct.vertex_scaling_factor }
    {
        this->can_be_erased         = true;
        bool font_loading_result    = false;

        if (this->font_file_format == "svg" || this->font_file_format == "SVG")
        {
            // TODO: implement SVG font loading!
        }

        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::VectorFont*";
        this->can_be_erased = true;

        // Requirements for further actions:
        // `this->parent` must not be `nullptr`.

        Material* const material_parent = static_cast<Material*>(this->get_parent());

        if (material_parent == nullptr)
        {
            std::cerr << "ERROR: `VectorFont::VectorFont`: `material_parent` is `nullptr`!\n";
            return;
        }

        if (font_loading_result)
        {
            // OK, `VectorFont` loading was successful.
            // Create each `Glyph` and bind them to `VectorFont`.

            std::cout << "Number of glyphs to be created: " << this->glyph_vertex_data.size() << "\n";

            for (std::size_t glyph_i = 0; glyph_i < this->glyph_vertex_data.size(); glyph_i++)
            {
                const char* unicode_char_pointer = this->unicode_strings.at(glyph_i).c_str();
                const char* temp_unicode_char_pointer = unicode_char_pointer;

                std::optional<int32_t> unicode_value = yli::string::extract_unicode_value_from_string(temp_unicode_char_pointer);

                if (!unicode_value.has_value())
                {
                    std::cerr << "ERROR: `VectorFont::VectorFont`: exctracting Unicode value failed!\n";
                    continue;
                }

                if (*unicode_value >= 0xd800 && *unicode_value <= 0xdfff)
                {
                    // Invalid Unicode, skip to next `Glyph`.
                    std::cerr << std::dec << "Error: invalid Unicode: " << *unicode_value << "\n";
                    continue;
                }

                GlyphStruct glyph_struct {
                        Request(this),
                        Request(material_parent) };
                glyph_struct.glyph_vertex_data = &this->glyph_vertex_data.at(glyph_i);
                glyph_struct.glyph_name_pointer = this->glyph_names.at(glyph_i).c_str();
                glyph_struct.unicode_char_pointer = unicode_char_pointer;

                std::string glyph_name_string = glyph_struct.glyph_name_pointer;
                std::string unicode_string = glyph_struct.unicode_char_pointer;
                std::cout << "Creating Glyph \"" << glyph_name_string << "\", Unicode: \"" << unicode_string << "\"\n";

                GenericEntityFactory& entity_factory = this->get_application().get_generic_entity_factory();
                Glyph* glyph = entity_factory.create_glyph(glyph_struct);

                // So that each `Glyph` can be referred to,
                // we need a hash map that points from Unicode string to `Glyph`.
                this->unicode_glyph_map[*unicode_value] = glyph;
            }
        }

    }

    void VectorFont::render(const Scene* const target_scene)
    {
        if (!this->should_render) [[unlikely]]
        {
            return;
        }

        yli::render::RenderSystem& render_system = this->universe.get_render_system();

        Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene)
        {
            // Different `Scene`s, do not render.
            return;
        }

        const Scene* const new_target_scene = (target_scene != nullptr ? target_scene : scene);

        render_system.render_glyphs(this->parent_of_glyphs, new_target_scene);
    }

    Entity* VectorFont::get_parent() const
    {
        return this->child_of_material.get_parent();
    }

    Scene* VectorFont::get_scene() const
    {
        Entity* const material_parent = this->get_parent();

        if (material_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `VectorFont::get_scene`: `material_parent` is `nullptr`!");
        }

        return material_parent->get_scene();
    }

    Pipeline* VectorFont::get_pipeline() const
    {
        const Material* const material_parent = static_cast<Material*>(this->get_parent());

        if (material_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `VectorFont::get_pipeline`: `material_parent` is `nullptr`!");
        }

        return material_parent->get_pipeline();
    }

    std::size_t VectorFont::get_number_of_children() const
    {
        return this->parent_of_glyphs.get_number_of_children();
    }

    std::size_t VectorFont::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_glyphs.child_pointer_vector);
    }
}
