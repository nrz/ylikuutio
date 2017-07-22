#include "model.hpp"

namespace ontology
{
    Model::Model()
    {
        // constructor.
        this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
    }

    Model::~Model()
    {
        // destructor.
    }

    int32_t Model::get_number_of_children()
    {
        return 0;
    }

    int32_t Model::get_number_of_descendants()
    {
        return 0;
    }
}
