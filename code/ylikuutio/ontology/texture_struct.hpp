#ifndef __TEXTURE_STRUCT_HPP_INCLUDED
#define __TEXTURE_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t

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
    {
        // constructor.
    }

    yli::ontology::Shader* parent; // pointer to the `Shader`.
    std::size_t textureID;
    std::size_t texture_width;
    std::size_t texture_height;
} TextureStruct;

#endif
