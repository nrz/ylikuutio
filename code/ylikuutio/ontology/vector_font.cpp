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

#include "vector_font.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "pipeline.hpp"
#include "material.hpp"
#include "text_3d.hpp"
#include "generic_entity_factory.hpp"
#include "family_templates.hpp"
#include "model_struct.hpp"
#include "vector_font_struct.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/load/font_loader.hpp"
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
    class Text3D;
    class Glyph;

    std::optional<yli::data::AnyValue> VectorFont::bind_to_new_material_parent(
            yli::ontology::VectorFont& vector_font,
            yli::ontology::Material& new_parent)
    {
        // Set pointer to `vector_font` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Material* const material_parent = static_cast<yli::ontology::Material*>(vector_font.get_parent());

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
    yli::ontology::Glyph* VectorFont::get_glyph_pointer(const int32_t unicode_value) const
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
            yli::ontology::Universe& universe,
            const yli::ontology::VectorFontStruct& vector_font_struct,
            yli::ontology::GenericParentModule* const material_parent_module)
        : Entity(application, universe, vector_font_struct),
        child_of_material(material_parent_module, *this),
        parent_of_glyphs(
                *this,
                this->registry,
                application.get_memory_allocator(yli::data::Datatype::GLYPH),
                "glyphs"),
        parent_of_text_3ds(
                *this,
                this->registry,
                application.get_memory_allocator(yli::data::Datatype::TEXT_3D),
                "text_3ds"),
        font_file_format      { vector_font_struct.font_file_format },
        font_filename         { vector_font_struct.font_filename },
        vertex_scaling_factor { vector_font_struct.vertex_scaling_factor }
    {
        // constructor.

        this->can_be_erased         = true;
        bool font_loading_result    = false;

        if (this->font_file_format == "svg" || this->font_file_format == "SVG")
        {
            const bool is_debug_mode = true;

            font_loading_result = yli::load::load_svg_font(
                    this->font_filename,
                    this->glyph_vertex_data,
                    this->glyph_names,
                    this->unicode_strings,
                    is_debug_mode);
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::VectorFont*";
        this->can_be_erased = true;

        // Requirements for further actions:
        // `this->parent` must not be `nullptr`.

        yli::ontology::Material* const material_parent = static_cast<yli::ontology::Material*>(this->get_parent());

        if (material_parent == nullptr)
        {
            std::cerr << "ERROR: `VectorFont::VectorFont`: `material_parent` is `nullptr`!\n";
            return;
        }

        yli::ontology::Pipeline* const pipeline_parent_of_material = static_cast<yli::ontology::Pipeline*>(material_parent->get_parent());

        if (pipeline_parent_of_material == nullptr)
        {
            std::cerr << "ERROR: `VectorFont::VectorFont`: `pipeline_parent_of_material` is `nullptr`!\n";
            return;
        }

        yli::ontology::Scene* const scene = this->get_scene();

        if (scene == nullptr)
        {
            std::cerr << "ERROR: `VectorFont::VectorFont`: `scene` is `nullptr`!\n";
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

                int32_t unicode_value = yli::string::extract_unicode_value_from_string(temp_unicode_char_pointer);
                if (unicode_value >= 0xd800 && unicode_value <= 0xdfff)
                {
                    // Invalid Unicode, skip to next `Glyph`.
                    std::cerr << std::dec << "Error: invalid Unicode: " << unicode_value << "\n";
                    continue;
                }

                yli::ontology::ModelStruct model_struct;
                model_struct.parent = this;
                model_struct.pipeline = pipeline_parent_of_material;
                model_struct.material = material_parent;
                model_struct.glyph_vertex_data = &this->glyph_vertex_data.at(glyph_i);
                model_struct.glyph_name_pointer = this->glyph_names.at(glyph_i).c_str();
                model_struct.unicode_char_pointer = unicode_char_pointer;

                std::string glyph_name_string = model_struct.glyph_name_pointer;
                std::string unicode_string = model_struct.unicode_char_pointer;
                std::cout << "Creating Glyph \"" << glyph_name_string << "\", Unicode: \"" << unicode_string << "\"\n";

                yli::ontology::GenericEntityFactory& entity_factory = this->application.get_generic_entity_factory();
                yli::ontology::Glyph* glyph = entity_factory.create_glyph(model_struct);

                // So that each `Glyph` can be referred to,
                // we need a hash map that points from Unicode string to `Glyph`.
                this->unicode_glyph_map[unicode_value] = glyph;
            }
        }

    }

    void VectorFont::render(const yli::ontology::Scene* const target_scene)
    {
        if (!this->should_render) [[unlikely]]
        {
            return;
        }

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `VectorFont::render`: `render_system` is `nullptr`!");
        }

        yli::ontology::Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene)
        {
            // Different `Scene`s, do not render.
            return;
        }

        const yli::ontology::Scene* const new_target_scene = (target_scene != nullptr ? target_scene : scene);

        render_system->render_glyphs(this->parent_of_glyphs, new_target_scene);
    }

    yli::ontology::Entity* VectorFont::get_parent() const
    {
        return this->child_of_material.get_parent();
    }

    yli::ontology::Scene* VectorFont::get_scene() const
    {
        yli::ontology::Entity* const material_parent = this->get_parent();

        if (material_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `VectorFont::get_scene`: `material_parent` is `nullptr`!");
        }

        return material_parent->get_scene();
    }

    yli::ontology::Pipeline* VectorFont::get_pipeline() const
    {
        const yli::ontology::Material* const material_parent = static_cast<yli::ontology::Material*>(this->get_parent());

        if (material_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `VectorFont::get_pipeline`: `material_parent` is `nullptr`!");
        }

        return material_parent->get_pipeline();
    }

    std::size_t VectorFont::get_number_of_children() const
    {
        return this->parent_of_glyphs.get_number_of_children() +
            this->parent_of_text_3ds.get_number_of_children();
    }

    std::size_t VectorFont::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_glyphs.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_text_3ds.child_pointer_vector);
    }
}
