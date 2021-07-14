// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_VECTOR_FONT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_VECTOR_FONT_HPP_INCLUDED

#include "entity.hpp"
#include "parent_module.hpp"
#include "glyph.hpp"
#include "material.hpp"
#include "glyph_struct.hpp"
#include "vector_font_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/font_loader.hpp"
#include "code/ylikuutio/render/render_templates.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>       // std::size_t
#include <ios>           // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream>      // std::cout, std::cin, std::cerr
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <vector>        // std::vector
#include <unordered_map> // std::unordered_map

namespace yli::ontology
{
    class Universe;
    class Material;

    class VectorFont: public yli::ontology::Entity
    {
        public:
            // This method sets pointer to this `Species` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Material`.
            void bind_to_new_material_parent(yli::ontology::Material* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            VectorFont(yli::ontology::Universe* const universe, const yli::ontology::VectorFontStruct& vector_font_struct)
                : Entity(universe, vector_font_struct),
                parent_of_glyphs(this, &this->registry, "glyphs"),
                parent_of_text_3ds(this, &this->registry, "text_3ds")
            {
                // constructor.

                // TODO: `VectorFont` constructor also creates each `Glyph` and binds them to the `VectorFont`.

                this->font_file_format      = vector_font_struct.font_file_format;
                this->font_filename         = vector_font_struct.font_filename;
                this->vertex_scaling_factor = vector_font_struct.vertex_scaling_factor;
                this->parent                = vector_font_struct.parent;

                // Get `childID` from the `Material` and set pointer to this `VectorFont`.
                this->bind_to_parent();

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

                // Requirements for further actions:
                // `this->parent` must not be `nullptr`.

                yli::ontology::Material* const material = this->parent;

                if (material == nullptr)
                {
                    std::cerr << "ERROR: `VectorFont::VectorFont`: `material` is `nullptr`!\n";
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

                        yli::ontology::GlyphStruct glyph_struct;
                        glyph_struct.glyph_vertex_data = &this->glyph_vertex_data.at(glyph_i);
                        glyph_struct.glyph_name_pointer = this->glyph_names.at(glyph_i).c_str();
                        glyph_struct.unicode_char_pointer = unicode_char_pointer;
                        glyph_struct.universe = universe;
                        glyph_struct.shader = static_cast<yli::ontology::Shader*>(material->get_parent());
                        glyph_struct.parent = this;

                        std::string glyph_name_string = glyph_struct.glyph_name_pointer;
                        std::string unicode_string = glyph_struct.unicode_char_pointer;
                        std::cout << "Creating Glyph \"" << glyph_name_string << "\", Unicode: \"" << unicode_string << "\"\n";
                        yli::ontology::Glyph* glyph = new yli::ontology::Glyph(glyph_struct, &this->parent_of_glyphs);

                        // So that each `Glyph` can be referred to,
                        // we need a hash map that points from Unicode string to `Glyph`.
                        this->unicode_glyph_map[unicode_value] = glyph;
                    }
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::VectorFont*";
                this->can_be_erased = true;
            }

            VectorFont(const VectorFont&) = delete;            // Delete copy constructor.
            VectorFont& operator=(const VectorFont&) = delete; // Delete copy assignment.

            // destructor.
            // Destroying a `VectorFont` destroys also all `Text3D` entities, and after that all `Glyph` entities.
            virtual ~VectorFont();

            yli::ontology::Entity* get_parent() const override;

            // This method returns a pointer to `Glyph` that matches the given `unicode_value`,
            // and `nullptr` if this `VectorFont` does not contain such a `Glyph`.
            yli::ontology::Glyph* get_glyph_pointer(const int32_t unicode_value) const;

            // The rest fields are created in the constructor.

            yli::ontology::Material* parent; // Pointer to `Material`.

            template<class T1, class T2>
                friend void yli::render::render_children(const std::vector<T1>& child_pointer_vector);

            yli::ontology::ParentModule parent_of_glyphs;
            yli::ontology::ParentModule parent_of_text_3ds;

        private:
            void bind_to_parent();

            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // This method renders all `Glyph`s of this `VectorFont`.
            void render();

            std::string font_file_format; // Type of the model file, eg. `"png"`.
            std::string font_filename;    // Filename of the model file.
            float vertex_scaling_factor;

            std::vector<std::vector<std::vector<glm::vec2>>> glyph_vertex_data;
            std::vector<std::vector<glm::vec2>> glyph_UV_data;
            std::vector<std::vector<glm::vec2>> glyph_normal_data;
            std::vector<std::string> glyph_names;
            std::vector<std::string> unicode_strings;

            std::unordered_map<int32_t, yli::ontology::Glyph*> unicode_glyph_map;
    };
}

#endif
