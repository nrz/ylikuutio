#ifndef __COMPUTE_TASK_STRUCT_HPP_INCLUDED
#define __COMPUTE_TASK_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits

namespace yli
{
    namespace ontology
    {
        class Shader;
    }
}

typedef struct ComputeTaskStruct
{
    ComputeTaskStruct()
        : parent(nullptr),
        compute_taskID(std::numeric_limits<std::size_t>::max()), // `std::numeric_limits<std::size_t>::max()` means that `compute_taskID` is not defined.
        texture_width(0),
        texture_height(0)
    {
        // constructor.
    }

    yli::ontology::Shader* parent; // pointer to the `Shader`.
    std::size_t compute_taskID;
    std::size_t texture_width;
    std::size_t texture_height;
} TextureStruct;

#endif
