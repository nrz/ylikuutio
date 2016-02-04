#include "hierarchy.hpp"

// Include standard headers
#include <cmath>     // NAN
#include <queue>     // std::queue
#include <stdint.h>  // uint32_t etc.
#include <vector>    // std::vector

namespace model
{
    void set_child_pointer(uint32_t childID, void* child_pointer, std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue)
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

    uint32_t get_childID(std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue)
    {
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
}
