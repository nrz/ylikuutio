#ifndef __HIERARCHY_TEMPLATES_HPP_INCLUDED
#define __HIERARCHY_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace hierarchy
{
    template<class T1>
        void set_child_pointer(
                const int32_t childID,
                const T1 child_pointer,
                std::vector<T1>& child_pointer_vector,
                std::queue<int32_t>& free_childID_queue,
                int32_t* const number_of_children)
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

                // 1 child less.
                (*number_of_children)--;
            }
            else
            {
                // 1 child more.
                (*number_of_children)++;
            }
        }

    template<class T1>
        int32_t get_childID(std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue)
        {
            // This function is called eg. from `bind_child_to_parent`,
            // so that child instance gets an appropriate `childID`.
            int32_t childID;

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
        void bind_child_to_parent(
                const T1 child_pointer,
                std::vector<T1>& child_pointer_vector,
                std::queue<int32_t>& free_childID_queue,
                int32_t* const number_of_children)
        {
            // If a class' instances have parents, this function must be
            // called in the constructor. The call must be done only once
            // in each constructor, usually after setting
            // `this->parent`. So, get `childID` from the parent,
            // because every child deserves a unique ID!
            child_pointer->childID = get_childID(child_pointer_vector, free_childID_queue);
            // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
            set_child_pointer(child_pointer->childID, child_pointer, child_pointer_vector, free_childID_queue, number_of_children);
        }

    template<class T1>
        void bind_child_to_parent(
                const std::string child_name,
                std::unordered_map<std::string, T1>& child_hash_map,
                const T1 child_pointer,
                std::vector<T1>& child_pointer_vector,
                std::queue<int32_t>& free_childID_queue,
                int32_t* const number_of_children)
        {
            // If a class' instances have parents, this function must be
            // called in the constructor. The call must be done only once
            // in each constructor, usually after setting
            // `this->parent`. So, get `childID` from the parent,
            // because every child deserves a unique ID!

            if (!child_name.empty())
            {
                // if the child has a name, let the parent know it!
                child_hash_map[child_name] = child_pointer;
            }

            child_pointer->childID = get_childID(child_pointer_vector, free_childID_queue);
            // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
            set_child_pointer(child_pointer->childID, child_pointer, child_pointer_vector, free_childID_queue, number_of_children);
        }

    template <class T1, class T2>
        void bind_child_to_new_parent(
                const T1 child_pointer,
                const T2 new_parent,
                std::vector<T1>& old_child_pointer_vector,
                std::queue<int32_t>& old_free_childID_queue,
                int32_t* const old_number_of_children)
        {
            // Set pointer to this child to `nullptr` in the old parent.
            T1 dummy_child_pointer = nullptr;
            set_child_pointer(child_pointer->childID, dummy_child_pointer, old_child_pointer_vector, old_free_childID_queue, old_number_of_children);
            // set the new parent pointer.
            child_pointer->parent = new_parent;
            // bind to the new parent.
            child_pointer->bind_to_parent();
        }

    template<class T1>
        void delete_children(std::vector<T1>& child_pointer_vector, int32_t* const number_of_children)
        {
            for (uint32_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                delete child_pointer_vector[child_i];
            }

            *number_of_children = 0; // no children any more.
        }
}

#endif
