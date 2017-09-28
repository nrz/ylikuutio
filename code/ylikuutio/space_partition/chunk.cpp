#include "chunk.hpp"
#include "triangle3D.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species_or_glyph.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace space_partition
{
    void Chunk::bind_to_parent()
    {
        // get `childID` from the `ChunkMaster` and set pointer to this `Chunk`.
        hierarchy::bind_child_to_parent<space_partition::Chunk*>(this, this->parent_pointer->chunk_pointer_vector, this->parent_pointer->free_chunkID_queue, &this->parent_pointer->number_of_chunks);
    }

    Chunk::Chunk()
    {
        // constructor.
        this->is_original = true;
        this->number_of_triangle3Ds = 0;

        this->type = "space_partition::Chunk*";
    }

    Chunk::~Chunk()
    {
        // destructor.

        // set pointer to this `Chunk` to nullptr.
        this->parent_pointer->set_chunk_pointer(this->childID, nullptr);
    }

    void Chunk::render()
    {
        // Render this `Chunk`.
        // If any `Triangle3D` of the `Chunk` has changed,
        // the vertex data of the `Chunk` needs to be reconstructed
        // before rendering. Reconstruction (or concatenation) of
        // vertex data may also be necessary even if the vertices of
        // the `Triangle3D` objects of the `Chunk` are not modified, if
        // vertices of some other `Triangle3D` are modified so that
        // the center or centroid of that `Triangle3D` becomes part of
        // this `Chunk`.
    }

    void Chunk::set_triangle3D_pointer(int32_t childID, space_partition::Triangle3D* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->triangle3D_pointer_vector, this->free_triangle3D_ID_queue, &this->number_of_triangle3Ds);
    }
}
