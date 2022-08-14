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

#include "glyph_object_creation.hpp"
#include "entity_factory.hpp"
#include "vector_font.hpp"
#include "text_3d.hpp"
#include "object.hpp"
#include "object_type.hpp"
#include "object_struct.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class Glyph;

    void create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* const text_3d)
    {
        if (text_3d == nullptr)
        {
            return;
        }

        const yli::ontology::VectorFont* const vector_font = static_cast<yli::ontology::VectorFont*>(text_3d->get_parent());

        if (vector_font == nullptr)
        {
            return;
        }

        const char* text_pointer = text_string.c_str();

        while (*text_pointer != '\0')
        {
            int32_t unicode_value = yli::string::extract_unicode_value_from_string(text_pointer);
            yli::ontology::Glyph* glyph_pointer = vector_font->get_glyph_pointer(unicode_value);

            if (glyph_pointer == nullptr)
            {
                // `nullptr`, so skip this character.
                std::cerr << "Error: no matching Glyph found for unicode_value 0x" << std::hex << unicode_value << std::dec << "\n";
                continue;
            }

            std::cout << "Creating the glyph Object for unicode_value 0x" << std::hex << unicode_value << std::dec << "\n";

            yli::ontology::ObjectStruct object_struct(text_3d->get_scene());
            object_struct.mesh_master = text_3d;
            object_struct.glyph = glyph_pointer;
            object_struct.original_scale_vector = text_3d->original_scale_vector;
            object_struct.cartesian_coordinates = text_3d->cartesian_coordinates; // TODO: adjust this as needed.

            yli::ontology::EntityFactory* const entity_factory = text_3d->get_entity_factory();

            if (entity_factory != nullptr)
            {
                entity_factory->create_object(object_struct);
            }
        }

        // TODO: Add support for Unicode strings.

        // TODO: go through `text_string`.

        // TODO: extract Unicode.
        //
        // TODO: If the Unicode exists in the hash map, create the corresponding glyph `Object`.
        //       If not, continue from the next Unicode of `text_string`.
    }
}
