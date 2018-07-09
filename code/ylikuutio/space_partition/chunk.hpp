#ifndef __CHUNK_HPP_INCLUDED
#define __CHUNK_HPP_INCLUDED

#include "chunk_master.hpp"
#include "code/ylikuutio/ontology/model.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

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
    class Chunk: yli::ontology::Model
    {
        public:
            // constructor.
            Chunk(yli::ontology::Universe* universe, space_partition::ChunkMaster* const parent)
                : Model(universe)
            {
                // constructor.
                this->is_original = true;

                this->parent = parent;

                // get `childID` from `ChunkMaster` and set pointer to this `Chunk`.
                this->bind_to_parent();

                this->type = "space_partition::Chunk*";
            }

            // destructor.
            virtual ~Chunk();

            glm::vec3 light_position;            // light position.

            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);
            template<class T1>
                friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

        private:
            void bind_to_parent();

            void render();

            space_partition::ChunkMaster* parent;  // pointer to `ChunkMaster`.

            bool is_original; // If `Chunk` is original, if can be reconstructed using `get_content_callback`.
    };
}

#endif
