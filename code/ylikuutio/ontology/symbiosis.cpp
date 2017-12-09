#include "symbiosis.hpp"
#include "symbiont_material.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace ontology
{
    class Shader;
    class SymbiontMaterial;

    void Symbiosis::bind_to_parent()
    {
        // get `childID` from `Shader` and set pointer to this `Symbiosis`.
        hierarchy::bind_child_to_parent<ontology::Symbiosis*>(this, this->parent->symbiosis_pointer_vector, this->parent->free_symbiosisID_queue, &this->parent->number_of_symbioses);
    }

    Symbiosis::~Symbiosis()
    {
        // destructor.
    }

    void Symbiosis::render()
    {
        this->prerender();

        // render this `Symbiosis` by calling `render()` function of each `SymbiontMaterial`.
        ontology::render_children<ontology::SymbiontMaterial*>(this->symbiont_material_pointer_vector);

        this->postrender();
    }

    int32_t Symbiosis::get_number_of_children() const
    {
        return this->number_of_symbiont_materials;
    }

    int32_t Symbiosis::get_number_of_descendants() const
    {
        return -1;
    }

    void Symbiosis::set_symbiont_material_pointer(const int32_t childID, ontology::SymbiontMaterial* const child_pointer)
    {
        hierarchy::set_child_pointer(
                childID,
                child_pointer,
                this->symbiont_material_pointer_vector,
                this->free_symbiont_materialID_queue,
                &this->number_of_symbiont_materials);
    }

    void Symbiosis::bind_to_new_parent(ontology::Shader* const new_shader_pointer)
    {
        // this method sets pointer to this `Material` to nullptr, sets `parent` according to the input, and requests a new `childID` from the new `Shader`.
        hierarchy::bind_child_to_new_parent<ontology::Symbiosis*, ontology::Shader*>(this, new_shader_pointer, this->parent->symbiosis_pointer_vector, this->parent->free_symbiosisID_queue, &this->parent->number_of_symbioses);
    }
}
