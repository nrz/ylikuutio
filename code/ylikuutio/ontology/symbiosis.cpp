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
        this->parent->bind_symbiosis(this);
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
        // unbind from the old parent `Shader`.
        this->parent->unbind_symbiosis(this->childID);

        // get `childID` from `Shader` and set pointer to this `Symbiosis`.
        this->parent = new_shader_pointer;
        this->parent->bind_symbiosis(this);
    }
}
