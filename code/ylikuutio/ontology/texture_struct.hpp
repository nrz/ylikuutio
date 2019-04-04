#ifndef __TEXTURE_STRUCT_HPP_INCLUDED
#define __TEXTURE_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits

namespace yli
{
    namespace ontology
    {
        class Shader;
    }
}

typedef struct TextureStruct
{
    TextureStruct()
        : parent(nullptr),
        textureID(std::numeric_limits<std::size_t>::max()), // `std::numeric_limits<std::size_t>::max()` means that `textureID` is not defined.
        texture_width(0),
        texture_height(0)
    {
        // constructor.
    }

    yli::ontology::Shader* parent; // pointer to the `Shader`.
    std::size_t textureID;
    std::size_t texture_width;
    std::size_t texture_height;
} TextureStruct;

#endif
