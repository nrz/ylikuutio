#include "model.hpp"

namespace ontology
{
    Model::Model()
    {
        // constructor.

        // Initialize class members with some dummy values.
        this->childID = -1;
        this->lightID = 0;
        this->vertexPosition_modelspaceID = 0;
        this->vertexUVID = 0;
        this->vertexNormal_modelspaceID = 0;
        this->vertexbuffer = 0;
        this->uvbuffer = 0;
        this->normalbuffer = 0;
        this->elementbuffer = 0;

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
