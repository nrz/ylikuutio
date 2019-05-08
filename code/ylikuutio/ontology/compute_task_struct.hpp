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
        n_index_characters(4),
        format(GL_RGB),
        internal_format(GL_INVALID_ENUM),
        type(GL_UNSIGNED_BYTE),
        should_ylikuutio_save_intermediate_results(false),
        should_ylikuutio_flip_texture(true),
        preiterate_callback(nullptr),
        postiterate_callback(nullptr)
    {
        // constructor.
    }

    std::string texture_file_format; // Type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
    std::string texture_filename;    // Filename of the model file.
    std::string output_filename;     // Filename of the output file.
    yli::ontology::Shader* parent; // pointer to the `Shader`.
    std::shared_ptr<yli::callback_system::CallbackEngine> end_condition_callback_engine;
    std::size_t n_max_iterations;
    std::size_t compute_taskID;
    std::size_t texture_width;
    std::size_t texture_height;
    std::size_t n_index_characters;  // For intermediate results' filenames.
    GLenum format;
    GLenum internal_format;
    GLenum type;
    bool should_ylikuutio_save_intermediate_results;
    bool should_ylikuutio_flip_texture;
    PreIterateCallback preiterate_callback;
    PostIterateCallback postiterate_callback;
} TextureStruct;

#endif
