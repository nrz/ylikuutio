#ifndef __GL_ATTRIB_LOCATIONS_HPP_INCLUDED
#define __GL_ATTRIB_LOCATIONS_HPP_INCLUDED

namespace ontology
{
    class Shader;
    class Glyph;

    void store_gl_attrib_locations(ontology::Shader* const shader, ontology::Glyph* const glyph);
}

#endif
