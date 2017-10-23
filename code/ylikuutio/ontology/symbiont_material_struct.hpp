#ifndef __SYMBIONT_MATERIAL_STRUCT_HPP_INCLUDED
#define __SYMBIONT_MATERIAL_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace ontology
{
    class Universe;
    class Symbiosis;
}

typedef struct SymbiontMaterialStruct
{
    SymbiontMaterialStruct(
            const ontology::Universe* universe,
            const ontology::Symbiosis* parent,
            const std::string texture_file_format,
            const std::string texture_filename,
            const std::string image_path)
        : universe(nullptr), parent(nullptr)
    {
        // constructor.
    }
    ontology::Universe* universe;          // pointer to the `Scene` object.
    ontology::Symbiosis* parent;           // pointer to `Symbiosis` object.
    const std::string texture_file_format; // type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
    const std::string texture_filename;    // filename of the model file.
    const std::string image_path;
} SymbiontMaterialStruct;

#endif
