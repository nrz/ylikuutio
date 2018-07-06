#ifndef __GL_ATTRIB_LOCATIONS_HPP_INCLUDED
#define __GL_ATTRIB_LOCATIONS_HPP_INCLUDED

namespace ylikuutio
{
    namespace ontology
    {
        class Shader;
        class Glyph;

        void store_gl_attrib_locations(ylikuutio::ontology::Shader* const shader, ylikuutio::ontology::Glyph* const glyph);
    }
}

#endif
