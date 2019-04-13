#ifndef __COMPUTE_TASK_STRUCT_HPP_INCLUDED
#define __COMPUTE_TASK_STRUCT_HPP_INCLUDED

#include "pre_iterate_callback.hpp"
#include "post_iterate_callback.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <memory>   // std::make_shared, std::shared_ptr

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
    }

    namespace ontology
    {
        class Shader;
    }
}

typedef struct ComputeTaskStruct
{
    ComputeTaskStruct()
        : parent(nullptr),
        end_condition_callback_engine(nullptr),
        n_max_iterations(1),                                     // By default execute GLSL shader exactly once (do not iterate further).
        compute_taskID(std::numeric_limits<std::size_t>::max()), // `std::numeric_limits<std::size_t>::max()` means that `compute_taskID` is not defined.
        texture_width(0),
        texture_height(0),
        format(GL_RGB),
        type(GL_UNSIGNED_BYTE),
        preiterate_callback(nullptr),
        postiterate_callback(nullptr)
    {
        // constructor.
    }

    yli::ontology::Shader* parent; // pointer to the `Shader`.
    std::shared_ptr<yli::callback_system::CallbackEngine> end_condition_callback_engine;
    std::size_t n_max_iterations;
    std::size_t compute_taskID;
    std::size_t texture_width;
    std::size_t texture_height;
    GLenum format;
    GLenum type;
    PreIterateCallback preiterate_callback;
    PostIterateCallback postiterate_callback;
} TextureStruct;

#endif
