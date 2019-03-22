#ifndef __SYMBIOSIS_STRUCT_HPP_INCLUDED
#define __SYMBIOSIS_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Shader;
    }
}

typedef struct SymbiosisStruct
{
    SymbiosisStruct()
        : triangulation_type("bilinear_interpolation"),
        light_position(glm::vec3(0.0f, 0.0f, 0.0f)),
        parent(nullptr),
        vram_buffer_in_use(true)
    {
        // constructor.
    }

    std::string model_filename;     // filename of the symbiosis model file.
    std::string model_file_format;  // type of the symbiosis model file.
    std::string triangulation_type; // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.
    glm::vec3 light_position;       // light position.
    yli::ontology::Shader* parent;  // pointer to the `Shader`.
    bool vram_buffer_in_use;
} SymbiosisStruct;

#endif
