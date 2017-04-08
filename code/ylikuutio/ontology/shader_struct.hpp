#ifndef __SHADER_STRUCT_HPP_INCLUDED
#define __SHADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace ontology
{
    class Scene;
}

typedef struct ShaderStruct
{
    ShaderStruct()
        : parent_pointer(nullptr)
    {
        // constructor.
    }
    ontology::Scene* parent_pointer; // pointer to the scene (draw list).
    std::string vertex_shader;       // filename of vertex shader.
    std::string fragment_shader;     // filename of fragment shader.
} ShaderStruct;

#endif
