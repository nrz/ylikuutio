#ifndef __MATERIAL_STRUCT_HPP_INCLUDED
#define __MATERIAL_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace ofbx
{
    // OpenFBX.
    struct Texture;
}

namespace ontology
{
    class Shader;
    class Symbiosis;
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
    ontology::Shader* shader;         // pointer to `Shader`.
    ontology::Symbiosis* symbiosis;   // pointer to `Symbiosis`.
    std::string texture_file_format;  // type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
    std::string texture_filename;     // filename of the model file.
    std::string image_path;
    bool is_symbiont_material;
    const ofbx::Texture* ofbx_texture; // For `SymbiontMaterial`s.
} MaterialStruct;

#endif
