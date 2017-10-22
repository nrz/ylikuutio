#include "symbiosis.hpp"
#include "shader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace ontology
{
    void Symbiosis::bind_to_parent()
    {
        // get `childID` from `Shader` and set pointer to this `Symbiosis`.
        hierarchy::bind_child_to_parent<ontology::Symbiosis*>(this, this->parent->symbiosis_pointer_vector, this->parent->free_symbiosisID_queue, &this->parent->number_of_symbioses);
    }

    Symbiosis::~Symbiosis()
    {
        // destructor.
    }

    int32_t Symbiosis::get_number_of_children()
    {
        return this->number_of_materials + this->number_of_species;
    }

    int32_t Symbiosis::get_number_of_descendants()
    {
        return -1;
    }
}
