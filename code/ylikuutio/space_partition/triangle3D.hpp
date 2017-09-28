#ifndef __TRIANGLE3D_HPP_INCLUDED
#define __TRIANGLE3D_HPP_INCLUDED

#include "chunk.hpp"

namespace space_partition
{
    class Triangle3D
    {
        public:
            // constructor.
            Triangle3D();

            // destructor.
            ~Triangle3D();

            // this method sets pointer to this `Triangle3D` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Chunk`.
            void bind_to_new_parent(space_partition::Chunk* new_chunk_pointer);

            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

        private:
            void bind_to_parent();

            space_partition::Chunk* parent_pointer;      // pointer to the `Chunk`.

            int32_t childID;                             // `Triangle3D` ID, returned by `space_partition::Chunk->get_triangle3D_ID()`.
    };
}

#endif
