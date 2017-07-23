#include "model.hpp"

namespace ontology
{
    Model::Model()
    {
        // constructor.
        this->number_of_objects = 0;
        this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
    }

    Model::~Model()
    {
        // destructor.
    }

    int32_t Model::get_number_of_children()
    {
        return this->number_of_objects;
    }

    int32_t Model::get_number_of_descendants()
    {
        return -1;
    }
}
