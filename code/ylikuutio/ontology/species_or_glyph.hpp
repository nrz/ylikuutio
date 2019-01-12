#ifndef __SPECIES_OR_GLYPH_HPP_INCLUDED
#define __SPECIES_OR_GLYPH_HPP_INCLUDED

#include "render_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

namespace yli
{
    namespace ontology
    {
        class Object;

        template<class T1>
            void render_species_or_glyph(T1 const species_or_glyph_pointer)
            {
                // Compute the MVP matrix from keyboard and mouse input.
                glUniform3f(
                        species_or_glyph_pointer->lightID,
                        species_or_glyph_pointer->light_position.x,
                        species_or_glyph_pointer->light_position.y,
                        species_or_glyph_pointer->light_position.z);

                // 1st attribute buffer : vertices.
                glEnableVertexAttribArray(species_or_glyph_pointer->vertex_position_modelspaceID);

                // 2nd attribute buffer : UVs.
                glEnableVertexAttribArray(species_or_glyph_pointer->vertexUVID);

                // 3rd attribute buffer : normals.
                glEnableVertexAttribArray(species_or_glyph_pointer->vertex_normal_modelspaceID);

                // render this `Species` or `Glyph` by calling `render()` function of each `Object`.
                yli::ontology::render_children<yli::ontology::Object*>(species_or_glyph_pointer->object_pointer_vector);

                glDisableVertexAttribArray(species_or_glyph_pointer->vertex_position_modelspaceID);
                glDisableVertexAttribArray(species_or_glyph_pointer->vertexUVID);
                glDisableVertexAttribArray(species_or_glyph_pointer->vertex_normal_modelspaceID);
            }
    }
}

#endif
