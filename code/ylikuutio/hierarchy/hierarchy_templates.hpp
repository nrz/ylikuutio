#ifndef __HIERARCHY_TEMPLATES_HPP_INCLUDED
#define __HIERARCHY_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <queue>     // std::queue
#include <stdint.h>  // uint32_t etc.
#include <vector>    // std::vector

namespace hierarchy
{
    template<class T1>
        void set_child_pointer(uint32_t childID, T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue)
        {
            child_pointer_vector[childID] = child_pointer;

            if (child_pointer == nullptr)
            {
                if (childID == child_pointer_vector.size() - 1)
                {
                    // OK, this is the biggest childID of all childID's of this 'object'.
                    // We can reduce the size of the child pointer vector at least by 1.
                    while ((!child_pointer_vector.empty()) && (child_pointer_vector.back() == nullptr))
                    {
                        // Reduce the size of child pointer vector by 1.
                        child_pointer_vector.pop_back();
                    }
                }
            }
        }

    template<class T1>
        uint32_t get_childID(std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue)
        {
            // This function is called eg. from `bind_child_to_parent`,
            // so that child instance gets an appropriate `childID`.
            uint32_t childID;

            while (!free_childID_queue.empty())
            {
                // return the first (oldest) free childID.
                childID = free_childID_queue.front();
                free_childID_queue.pop();

                // check that the child index does not exceed current child pointer vector.
                if (childID < child_pointer_vector.size())
                {
                    // OK, it does not exceed current child pointer vector.
                    return childID;
                }
            }
            // OK, the queue is empty.
            // A new child index must be created.
            childID = child_pointer_vector.size();

            // child pointer vector must also be extended with an appropriate nullptr pointer.
            child_pointer_vector.push_back(nullptr);

            return childID;
        }

    template<class T1>
        void bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue)
        {
            // If a class' instances have parents, this function must be
            // called in the constructor. The call must be done only once
            // in each constructor, usually after setting
            // `this->parent_pointer`. So, get `childID` from the parent,
            // because every child deserves a unique ID!
            child_pointer->childID = get_childID(child_pointer_vector, free_childID_queue);
            // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
            set_child_pointer(child_pointer->childID, child_pointer, child_pointer_vector, free_childID_queue);
        }

    template <class T1, class T2>
        void bind_child_to_new_parent(
                T1 child_pointer,
                T2 new_parent_pointer,
                std::vector<T1>& old_child_pointer_vector,
                std::queue<uint32_t>& old_free_childID_queue)
        {
            // Set pointer to this child to `nullptr` in the old parent.
            T1 dummy_child_pointer = nullptr;
            set_child_pointer(child_pointer->childID, dummy_child_pointer, old_child_pointer_vector, old_free_childID_queue);
            // set the new parent pointer.
            child_pointer->parent_pointer = new_parent_pointer;
            // bind to the new parent.
            child_pointer->bind_to_parent();
        }

    template<class T1>
        void delete_children(std::vector<T1>& child_pointer_vector)
        {
            for (uint32_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                delete child_pointer_vector[child_i];
            }
        }
}

#endif
