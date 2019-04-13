#ifndef __CHUNK_HPP_INCLUDED
#define __CHUNK_HPP_INCLUDED

#include "model.hpp"
#include "chunk_struct.hpp"
#include "chunk_master.hpp"
#include "material.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::queue
#include <vector>  // std::vector

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

namespace yli
{
    namespace ontology
    {
        class Chunk: yli::ontology::Model
        {
            public:
                // constructor.
                Chunk(const ChunkStruct& chunk_struct)
                    : Model(chunk_struct.universe, chunk_struct.vram_buffer_in_use)
                {
                    // constructor.
                    this->is_original = true;

                    this->parent      = chunk_struct.parent;

                    // get `childID` from `ChunkMaster` and set pointer to this `Chunk`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "ontology::Chunk*";
                }

                Chunk(const Chunk&) = delete;            // Delete copy constructor.
                Chunk &operator=(const Chunk&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Chunk();

                glm::vec3 light_position;            // light position.

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                void render();

                yli::ontology::ChunkMaster* parent;  // pointer to the `ChunkMaster`.

                bool is_original;                    // If `Chunk` is original, if can be reconstructed using `get_content_callback`.
        };
    }
}

#endif
