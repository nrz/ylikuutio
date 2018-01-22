#include "symbiont_species.hpp"
#include "vboindexer.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "symbiont_material.hpp"
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
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace ontology
{
    void SymbiontSpecies::bind_to_parent()
    {
        // get `childID` from `SymbiontMaterial` and set pointer to this `SymbiontSpecies`.
        this->symbiont_material_parent->bind(this);
    }

    SymbiontSpecies::~SymbiontSpecies()
    {
        // destructor.
        std::cout << "SymbiontSpecies with childID " << std::dec << this->childID << " will be destroyed.\n";

        glDeleteBuffers(1, &this->normalbuffer);
        glDeleteBuffers(1, &this->elementbuffer);

        // set pointer to this symbiont_species to nullptr.
        this->symbiont_material_parent->set_symbiont_species_pointer(this->childID, nullptr);
    }

    void SymbiontSpecies::render()
    {
        this->prerender();

        // render this `SymbiontSpecies`.
        ontology::render_species_or_glyph<ontology::SymbiontSpecies*>(this);

        this->postrender();
    }

    ontology::Entity* SymbiontSpecies::get_parent() const
    {
        return this->symbiont_material_parent;
    }

    void SymbiontSpecies::set_object_pointer(const int32_t childID, ontology::Object* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, &this->number_of_objects);
    }

    void SymbiontSpecies::set_name(const std::string& name)
    {
        ontology::set_name(name, this);
    }

    int32_t SymbiontSpecies::get_indices_size() const
    {
        return this->indices.size();
    }

    GLuint SymbiontSpecies::get_lightID() const
    {
        return this->lightID;
    }
}
