#ifndef __MATERIAL_STRUCT_HPP_INCLUDED
#define __MATERIAL_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Shader;
        class Symbiosis;
    }
}

namespace ofbx
{
    // OpenFBX.
    struct Texture;
}

typedef struct MaterialStruct
{
    MaterialStruct()
        : shader(nullptr),
        symbiosis(nullptr),
        ofbx_texture(nullptr),
        is_symbiont_material(false)
    {
        // constructor.
    }

    std::string texture_file_format;     // Type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
    std::string texture_filename;        // Filename of the model file.
    yli::ontology::Shader* shader;       // Pointer to `Shader`.
    yli::ontology::Symbiosis* symbiosis; // Pointer to `Symbiosis`.
    const ofbx::Texture* ofbx_texture;   // For `SymbiontMaterial`s.
    bool is_symbiont_material;
} MaterialStruct;

#endif
