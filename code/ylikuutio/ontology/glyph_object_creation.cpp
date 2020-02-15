// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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
#include "universe.hpp"
#include "vector_font.hpp"
#include "text3D.hpp"
#include "object.hpp"
#include "object_type.hpp"
#include "object_struct.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Glyph;

        void create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* const text3D)
        {
            if (text3D == nullptr)
            {
                return;
            }

            yli::ontology::VectorFont* const vector_font = static_cast<yli::ontology::VectorFont*>(text3D->get_parent());

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

                yli::ontology::ObjectStruct object_struct;
                object_struct.glyph = glyph_pointer;
                object_struct.text3D_parent = text3D;
                object_struct.original_scale_vector = text3D->original_scale_vector;
                object_struct.rotate_angle = text3D->rotate_angle;
                object_struct.object_type = yli::ontology::ObjectType::CHARACTER;
                object_struct.cartesian_coordinates = text3D->cartesian_coordinates; // TODO: adjust this as needed.
                object_struct.rotate_vector = text3D->rotate_vector;

                yli::ontology::EntityFactory* const entity_factory = text3D->universe->get_entity_factory();

                if (entity_factory != nullptr)
                {
                    entity_factory->create_Object(object_struct);
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
}
