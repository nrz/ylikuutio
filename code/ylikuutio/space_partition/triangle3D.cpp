#include "triangle3D.hpp"

namespace space_partition
{
    void Triangle3D::bind_to_parent()
    {
        // get `childID` from the `Chunk` and set pointer to this `Triangle3D`.
        hierarchy::bind_child_to_parent<space_partition::Triangle3D*>(this, this->parent_pointer->triangle3D_pointer_vector, this->parent_pointer->free_triangle3D_ID_queue, &this->parent_pointer->number_of_triangle3Ds);
    }

    Triangle3D::Triangle3D()
    {
        // constructor.
    }

    Triangle3D::~Triangle3D()
    {
        // destructor.
    }

    void Triangle3D::bind_to_new_parent(space_partition::Chunk* new_chunk_pointer)
    {
        // this method sets pointer to this `Triangle3D` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Chunk`.
        hierarchy::bind_child_to_new_parent<space_partition::Triangle3D*, space_partition::Chunk*>(this, new_chunk_pointer, this->parent_pointer->triangle3D_pointer_vector, this->parent_pointer->free_triangle3D_ID_queue, &this->parent_pointer->number_of_triangle3Ds);
    }
}
