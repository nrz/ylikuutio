#include "model.hpp"

namespace ontology
{
    class Universe;

    Model::~Model()
    {
        // destructor.
    }

    int32_t Model::get_number_of_children() const
    {
        return this->number_of_objects;
    }

    int32_t Model::get_number_of_descendants() const
    {
        return -1;
    }
}
