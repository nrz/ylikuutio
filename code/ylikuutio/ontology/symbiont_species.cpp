#include "symbiont_species.hpp"
#include "vboindexer.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "symbiont_material.hpp"
#include "biont.hpp"
#include "object.hpp"
#include "species_or_glyph.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void SymbiontSpecies::bind_biont(yli::ontology::Biont* const biont)
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

        void SymbiontSpecies::unbind_biont(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->biont_pointer_vector,
                    this->free_biontID_queue,
                    this->number_of_bionts);
        }

        void SymbiontSpecies::bind_to_parent()
        {
            // get `childID` from `SymbiontMaterial` and set pointer to this `SymbiontSpecies`.
            this->symbiont_material_parent->bind_symbiont_species(this);
        }

        SymbiontSpecies::~SymbiontSpecies()
        {
            // destructor.
            std::cout << "SymbiontSpecies with childID " << std::dec << this->childID << " will be destroyed.\n";

            glDeleteBuffers(1, &this->normalbuffer);
            glDeleteBuffers(1, &this->elementbuffer);

            // set pointer to this `SymbiontSpecies` to `nullptr`.
            this->symbiont_material_parent->set_symbiont_species_pointer(this->childID, nullptr);
        }

        void SymbiontSpecies::render()
        {
            this->prerender();

            // render this `SymbiontSpecies`.
            yli::ontology::render_species_or_glyph<yli::ontology::SymbiontSpecies*>(this);

            this->postrender();
        }

        yli::ontology::Entity* SymbiontSpecies::get_parent() const
        {
            return this->symbiont_material_parent;
        }

        std::size_t SymbiontSpecies::get_indices_size() const
        {
            return this->indices.size();
        }

        GLuint SymbiontSpecies::get_lightID() const
        {
            return this->lightID;
        }
    }
}
