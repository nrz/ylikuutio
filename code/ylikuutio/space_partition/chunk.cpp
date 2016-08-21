#include "chunk.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species_or_glyph.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace space_partition
{
    void Chunk::bind_to_parent()
    {
        hierarchy::bind_child_to_parent<space_partition::Chunk*>(this, this->parent_pointer->chunk_pointer_vector, this->parent_pointer->free_chunkID_queue);
    }

    Chunk::Chunk()
    {
        // constructor.
    }

    Chunk::~Chunk()
    {
        // destructor.

        // set pointer to this `Chunk` to nullptr.
        this->parent_pointer->set_chunk_pointer(this->childID, nullptr);
    }

    void Chunk::render()
    {
        // ontology::render_species_or_glyph<space_partition::Chunk*>(this);
    }

    void Chunk::set_object_pointer(uint32_t childID, ontology::Object* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue);
    }

    void Chunk::bind_to_new_parent(ontology::Material* new_material_pointer)
    {
        hierarchy::bind_child_to_new_parent<space_partition::Chunk*, ontology::Material*>(this, new_material_pointer, this->parent_pointer->chunk_pointer_vector, this->parent_pointer->free_chunkID_queue);
    }
}
