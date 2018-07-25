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
        : parent(nullptr), light_position(glm::vec3(0.0f, 0.0f, 0.0f)), triangulation_type("bilinear_interpolation"), vram_buffer_in_use(true)
    {
        // constructor.
    }
    yli::ontology::Shader* parent; // pointer to the `Scene` object.

    std::string model_file_format;    // type of the symbiosis model file.
    std::string model_filename;       // filename of the symbiosis model file.
    glm::vec3 light_position;         // light position.
    std::string triangulation_type;   // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.
    bool vram_buffer_in_use;
} SymbiosisStruct;

#endif
