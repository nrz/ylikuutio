#include "triangle3D.hpp"

namespace space_partition
{
    void Triangle3D::bind_to_parent()
    {
        // get `childID` from the `Chunk` and set pointer to this `Triangle3D`.
        hierarchy::bind_child_to_parent<space_partition::Triangle3D*>(this, this->parent_pointer->triangle3D_pointer_vector, this->parent_pointer->free_triangle3D_ID_queue);
    }

    Triangle3D::Triangle3D()
    {
        // constructor.
    }

    Triangle3D::~Triangle3D()
    {
        // destructor.
    }
}
