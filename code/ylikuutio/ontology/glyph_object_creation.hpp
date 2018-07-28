#ifndef __GLYPH_OBJECT_CREATION_HPP_INCLUDED
#define __GLYPH_OBJECT_CREATION_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Text3D;

        void create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* const text3D);
    }
}

#endif
