#include "symbiosis.hpp"
#include "shader.hpp"
#include "symbiosis_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace ontology
{
    void Symbiosis::bind_to_parent()
    {
        // get `childID` from `Shader` and set pointer to this `Symbiosis`.
        hierarchy::bind_child_to_parent<ontology::Symbiosis*>(this, this->parent_pointer->symbiosis_pointer_vector, this->parent_pointer->free_symbiosisID_queue);
    }

    Symbiosis::Symbiosis(SymbiosisStruct symbiosis_struct)
    {
        // constructor.

        // get `childID` from `Shader` and set pointer to this `Symbiosis`.
        this->bind_to_parent();
    }

    Symbiosis::~Symbiosis()
    {
        // destructor.
    }

    int32_t Symbiosis::get_number_of_children()
    {
        return -1;
    }

    int32_t Symbiosis::get_number_of_descendants()
    {
        return -1;
    }
}
