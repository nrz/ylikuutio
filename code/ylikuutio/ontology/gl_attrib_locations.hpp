#ifndef __GL_ATTRIB_LOCATIONS_HPP_INCLUDED
#define __GL_ATTRIB_LOCATIONS_HPP_INCLUDED

namespace yli
{
    namespace ontology
    {
        class Shader;
        class Glyph;

        void store_gl_attrib_locations(yli::ontology::Shader* const shader, yli::ontology::Glyph* const glyph);
    }
}

#endif
