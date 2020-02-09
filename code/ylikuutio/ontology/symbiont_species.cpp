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
#include "symbiont_material.hpp"
#include "biont.hpp"
#include "species_or_glyph.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace ontology
    {
        class Entity;

        void SymbiontSpecies::bind_Biont(yli::ontology::Biont* const biont)
        {
            // `SymbiontSpecies` is not the ontological parent of `Biont`,
            // as `Holobiont` is the ontological parent of `Biont`.
            // The relationship between `SymbiontSpecies` and `Biont`
            // is purely only for rendering.
            //
            // To avoid potential problems in the future, follow this order:
            // 1. bind `Biont` to its `Holobiont` parent.
            // 2. bind `Biont` to its corresponding `SymbiontSpecies`.
            // 3. do stuff
            // 4. unbind `Biont` from its `SymbiontSpecies`.
            // 5. unbind `Biont` from its `Holobiont` parent.
            //
            // get `childID` from `SymbiontSpecies` and set pointer to `biont`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Biont*>(
                    biont,
                    this->biont_pointer_vector,
                    this->free_biontID_queue,
                    this->number_of_bionts);
        }

        void SymbiontSpecies::unbind_Biont(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->biont_pointer_vector,
                    this->number_of_bionts);
        }

        void SymbiontSpecies::bind_to_parent()
        {
            // requirements:
            // `this->symbiont_material_parent` must not be `nullptr`.
            yli::ontology::SymbiontMaterial* const symbiont_material = this->symbiont_material_parent;

            if (symbiont_material == nullptr)
            {
                std::cerr << "ERROR: `SymbiontSpecies::bind_to_parent`: `symbiont_material` is `nullptr`!\n";
                return;
            }

            // get `childID` from `SymbiontMaterial` and set pointer to this `SymbiontSpecies`.
            symbiont_material->parent_of_symbiont_species.bind_child(this);
        }

        SymbiontSpecies::~SymbiontSpecies()
        {
            // destructor.
            std::cout << "`SymbiontSpecies` with childID " << std::dec << this->childID << " will be destroyed.\n";

            if (this->opengl_in_use)
            {
                glDeleteBuffers(1, &this->normalbuffer);
                glDeleteBuffers(1, &this->elementbuffer);
            }

            // requirements for further actions:
            // `this->symbiont_material_parent` must not be `nullptr`.

            yli::ontology::SymbiontMaterial* const symbiont_material = this->symbiont_material_parent;

            // set pointer to this `SymbiontSpecies` to `nullptr`.
            if (symbiont_material == nullptr)
            {
                std::cerr << "ERROR: `SymbiontSpecies::~SymbiontSpecies`: `symbiont_material` is `nullptr`!\n";
                return;
            }

            symbiont_material->parent_of_symbiont_species.unbind_child(this->childID);
        }

        void SymbiontSpecies::render()
        {
            if (this->opengl_in_use)
            {
                this->prerender();

                // render this `SymbiontSpecies`.
                yli::ontology::render_species_or_glyph<yli::ontology::SymbiontSpecies*>(this);

                this->postrender();
            }
        }

        yli::ontology::Entity* SymbiontSpecies::get_parent() const
        {
            return this->symbiont_material_parent;
        }

        std::size_t SymbiontSpecies::get_indices_size() const
        {
            return this->indices.size();
        }

        GLint SymbiontSpecies::get_lightID() const
        {
            return this->lightID;
        }
    }
}
