#ifndef __MATERIAL_STRUCT_HPP_INCLUDED
#define __MATERIAL_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace ontology
{
    class Shader;
}

typedef struct MaterialStruct
{
    MaterialStruct()
        : parent(nullptr)
    {
        // constructor.
    }
    ontology::Shader* parent; // pointer to the shader.
    std::string texture_file_format;  // type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
    std::string texture_filename;     // filename of the model file.
    std::string image_path;
} MaterialStruct;

#endif
