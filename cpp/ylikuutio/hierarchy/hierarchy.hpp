#ifndef __MODEL_COMMON_FUNCTIONS_HPP_INCLUDED
#define __MODEL_COMMON_FUNCTIONS_HPP_INCLUDED

// Include standard headers
#include <stdint.h>  // uint32_t etc.
#include <vector>    // std::vector
#include <queue>     // std::queue

namespace model
{
    void set_child_pointer(uint32_t childID, void* child_pointer, std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);
    uint32_t get_childID(std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);
}

#endif
