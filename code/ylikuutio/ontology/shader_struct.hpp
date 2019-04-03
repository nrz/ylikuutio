#ifndef __SHADER_STRUCT_HPP_INCLUDED
#define __SHADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Scene;
    }
}

typedef struct ShaderStruct
{
    ShaderStruct()
        : parent(nullptr),
        number_of_textures(0),
        is_gpgpu_shader(false)
    {
        // constructor.
    }

    std::string vertex_shader;    // filename of vertex shader.
    std::string fragment_shader;  // filename of fragment shader.
    yli::ontology::Scene* parent; // pointer to the `Scene`.
    std::size_t number_of_textures; // Number of textures (for GPGPU `Shader`s).
    bool is_gpgpu_shader;         // TODO: GPGPU `Shader`s are not rendered on screen but their result textures can be used by `Material`s.
} ShaderStruct;

#endif
