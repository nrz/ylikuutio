#ifndef __CHUNK_HPP_INCLUDED
#define __CHUNK_HPP_INCLUDED

#include "chunk_master.hpp"
#include "code/ylikuutio/ontology/model.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Each `Chunk` contains `Triangle3D` objects.
// The `Chunk` in which a given `Triangle3D` belongs to is based on either
// on its center or its centroid. Each `Triangle3D` belongs to exactly one
// `Chunk`. Moving the vertices of the `Triangle3D` may move it to some
// other `Chunk` (to an adjacent `Chunk` or to a farther `Chunk`), as
// moving vertices moves the centroid and the center of the `Triangle3D`.
//
// The content of any `Chunk` can be based either on some predefined
// data (eg. height map data, laser scanning data etc.) or procedurally
// (eg. Perlin noise or some other fractal). The parent of `Chunk` objects
// is a `ChunkMaster` object, that has a callback for retrieving or
// producing the content, and also the code for dividing the content into
// appropriate `Chunk` objects.
//
// Centroid:
//
// Center:
//
// From rendering point of view, `Chunk` is like `Species`, with the
// exception that `Chunk` normally contains only 1 `Object`.

namespace space_partition
{
    class Chunk: ontology::Model
    {
        public:
            // constructor.
            Chunk();

            // destructor.
            ~Chunk();

            // this method sets a object pointer.
            void set_object_pointer(uint32_t childID, ontology::Object* child_pointer);

            // this method gets a object ID and removes it from the `free_objectID_queue` if it was popped from the queue.
            uint32_t get_objectID();

            glm::vec3 light_position;            // light position.

            friend class Object;
            template<class T1>
                friend void ontology::render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue);

        private:
            void bind_to_parent();

            void render();

            space_partition::ChunkMaster* parent_pointer;  // pointer to `ChunkMaster`.
    };
}

#endif
