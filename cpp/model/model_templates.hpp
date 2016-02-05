#ifndef __MODEL_TEMPLATES_HPP_INCLUDED
#define __MODEL_TEMPLATES_HPP_INCLUDED

#include "cpp/common/hierarchy.hpp"

// Include standard headers
#include <vector>    // std::vector

namespace model
{
    void set_child_pointer(uint32_t childID, void* child_pointer, std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);
    uint32_t get_childID(std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);

    template<class T1>
        void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue)
        {
            // get childID from the parent, because every child deserves a unique ID!
            child_pointer->childID = get_childID(child_pointer_vector, free_childID_queue);
            // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
            set_child_pointer(child_pointer->childID, child_pointer, child_pointer_vector, free_childID_queue);
        }

    template <class T1, class T2>
        void bind_child_to_new_parent(
                T1 child_pointer,
                T2 new_parent_pointer,
                std::vector<void*> &old_child_pointer_vector,
                std::queue<uint32_t> &old_free_childID_queue)
        {
            // set pointer to this child to nullptr in the old parent.
            set_child_pointer(child_pointer->childID, nullptr, old_child_pointer_vector, old_free_childID_queue);
            // set the new parent pointer.
            child_pointer->parent_pointer = new_parent_pointer;
            // bind to the new parent.
            child_pointer->bind_to_parent();
        }

    template<class T1>
        void delete_children(std::vector<void*> &child_pointer_vector)
        {
            for (uint32_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                delete static_cast<T1>(child_pointer_vector[child_i]);
            }
        }

    template<class T1>
        void render_children(std::vector<void*> &child_pointer_vector)
        {
            for (uint32_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                T1 child_pointer;
                child_pointer = static_cast<T1>(child_pointer_vector[child_i]);

                if (child_pointer != nullptr)
                {
                    child_pointer->render();
                }
            }
        }
}

#endif
