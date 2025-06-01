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

#include "glyph_object_creation.hpp"
#include "generic_entity_factory.hpp"
#include "scene.hpp"
#include "vector_font.hpp"
#include "text_3d.hpp"
#include "glyph_object.hpp"
#include "request.hpp"
#include "glyph_object_struct.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <ios>       // std::dec, std::hex
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string

namespace yli::ontology
{
    class Glyph;

    void create_glyph_objects(const std::string& text_string, Text3d& text_3d)
    {
        Scene* const scene_parent_of_text_3d = static_cast<Scene*>(text_3d.get_parent());

        const VectorFont* const vector_font_master_of_text_3d = text_3d.get_vector_font_master();

        if (vector_font_master_of_text_3d == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `create_glyph_objects`: `vector_font_master_of_text_3d` is `nullptr`!");
        }

        const char* text_pointer = text_string.c_str();

        while (*text_pointer != '\0')
        {
            std::optional<int32_t> unicode_value = yli::string::extract_unicode_value_from_string(text_pointer);

            if (!unicode_value)
            {
                throw std::runtime_error("ERROR: `create_glyph_objects`: exctracting Unicode value failed!");
            }

            Glyph* glyph_pointer = vector_font_master_of_text_3d->get_glyph_pointer(*unicode_value);

            if (glyph_pointer == nullptr)
            {
                // `nullptr`, so skip this character.
                std::cerr << "Error: no matching Glyph found for unicode_value 0x" << std::hex << *unicode_value << std::dec << "\n";
                continue;
            }

            std::cout << "Creating `GlyphObject` instance for unicode_value 0x" << std::hex << *unicode_value << std::dec << "\n";

            GlyphObjectStruct glyph_object_struct {
                    Request(scene_parent_of_text_3d),
                    Request(glyph_pointer),
                    Request(&text_3d) };
            glyph_object_struct.original_scale_vector = text_3d.original_scale_vector;
            glyph_object_struct.cartesian_coordinates = text_3d.location; // TODO: adjust this as needed.

            GenericEntityFactory& entity_factory = text_3d.get_application().get_generic_entity_factory();
            entity_factory.create_glyph_object(glyph_object_struct);
        }

        // TODO: Add support for Unicode strings.

        // TODO: go through `text_string`.

        // TODO: extract Unicode.
        //
        // TODO: If the Unicode exists in the hash map, create the corresponding `GlyphObject` instance.
        //       If not, continue from the next Unicode of `text_string`.
    }
}
