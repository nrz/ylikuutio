#ifndef __ONTOLOGY_STRUCTS_HPP_INCLUDED
#define __ONTOLOGY_STRUCTS_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace ontology
{
    class VectorFont;
}

typedef struct GlyphStruct
{
    GlyphStruct()
        : glyph_vertex_data(nullptr), glyph_name_pointer(nullptr), unicode_char_pointer(nullptr), parent_pointer(nullptr), light_position(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        // constructor.
    }
    // used for all files (for all glyph).
    std::vector<std::vector<glm::vec2>>* glyph_vertex_data;
    const char* glyph_name_pointer;       // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
    const char* unicode_char_pointer;     // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
    ontology::VectorFont* parent_pointer; // pointer to the font object.
    glm::vec3 light_position;             // light position.
} GlyphStruct;

#endif
