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

#include "symbiont_species.hpp"
#include "entity.hpp"
#include "universe.hpp"
#include "object.hpp"
#include "symbiont_material.hpp"
#include "biont.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_master.hpp"
#include "code/ylikuutio/render/render_species_or_glyph.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace yli::ontology
{
    class Entity;

    SymbiontSpecies::~SymbiontSpecies()
    {
        // destructor.
        std::cout << "`SymbiontSpecies` with childID " << std::dec << this->childID << " will be destroyed.\n";

        if (this->opengl_in_use)
        {
            glDeleteBuffers(1, &this->normalbuffer);
            glDeleteBuffers(1, &this->elementbuffer);
        }
    }

    std::size_t SymbiontSpecies::get_number_of_apprentices() const
    {
        return this->master_of_bionts.get_number_of_apprentices(); // `Biont`s belonging to `SymbiontSpecies` are its apprentices.
    }

    void SymbiontSpecies::render()
    {
        if (this->universe == nullptr)
        {
            return;
        }

        yli::render::RenderMaster* const render_master = this->universe->get_render_master();

        if (render_master == nullptr)
        {
            return;
        }

        this->prerender();
        render_master->render_symbiont_species(this);
        this->postrender();
    }

    std::size_t SymbiontSpecies::get_indices_size() const
    {
        return this->indices.size();
    }

    GLint SymbiontSpecies::get_light_id() const
    {
        return this->light_id;
    }
}
