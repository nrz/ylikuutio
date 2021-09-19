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

#include "glyph.hpp"
#include "universe.hpp"
#include "object.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/render/render_master.hpp"
#include "code/ylikuutio/render/render_species_or_glyph.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli::ontology
{
    class Scene;

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

    yli::ontology::Entity* Glyph::get_parent() const
    {
        return this->child_of_vector_font.get_parent();
    }

    yli::ontology::Scene* Glyph::get_scene() const
    {
        yli::ontology::Entity* const parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    std::size_t Glyph::get_number_of_children() const
    {
        return 0; // `Glyph` has no children.
    }

    std::size_t Glyph::get_number_of_descendants() const
    {
        return 0; // `Glyph` has no children.
    }

    void Glyph::render()
    {
        if (!this->should_be_rendered || !this->opengl_in_use || this->universe == nullptr)
        {
            return;
        }

        yli::render::RenderMaster* const render_master = this->universe->get_render_master();

        if (render_master == nullptr)
        {
            return;
        }

        this->prerender();
        render_master->render_glyph(this);
        this->postrender();
    }

    const char* Glyph::get_unicode_char_pointer() const
    {
        return this->unicode_char_pointer;
    }
}
