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

#include "glyph.hpp"
#include "vector_font.hpp"
#include "species_or_glyph.hpp"
#include "object.hpp"
#include "glyph_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        Glyph::~Glyph()
        {
            // destructor.
            std::string glyph_name_string = this->glyph_name_pointer;
            std::string unicode_string = this->unicode_char_pointer;
            std::cout << "This `Glyph` (\"" << glyph_name_string << "\", Unicode: \"" << std::dec << unicode_string << "\") will be destroyed.\n";

            // Cleanup buffers.
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);
            glDeleteBuffers(1, &this->normalbuffer);
            glDeleteBuffers(1, &this->elementbuffer);
        }

        void Glyph::render()
        {
            if (this->opengl_in_use)
            {
                this->prerender();

                // render this `Glyph`.
                yli::ontology::render_species_or_glyph<yli::ontology::Glyph*>(this);

                this->postrender();
            }
        }

        const char* Glyph::get_unicode_char_pointer() const
        {
            return this->unicode_char_pointer;
        }
    }
}
