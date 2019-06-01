#ifndef __SPECIES_OR_GLYPH_HPP_INCLUDED
#define __SPECIES_OR_GLYPH_HPP_INCLUDED

#include "object.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

namespace yli
{
    namespace ontology
    {
        template<class T1>
            void render_species_or_glyph(T1 const species_or_glyph_pointer)
            {
                // Compute the MVP matrix from keyboard and mouse input.
                glUniform3f(
                        species_or_glyph_pointer->lightID,
                        species_or_glyph_pointer->light_position.x,
                        species_or_glyph_pointer->light_position.y,
                        species_or_glyph_pointer->light_position.z);

                // 1st attribute buffer: vertices.
                yli::opengl::enable_vertex_attrib_array(species_or_glyph_pointer->vertex_position_modelspaceID);

                // 2nd attribute buffer: UVs.
                yli::opengl::enable_vertex_attrib_array(species_or_glyph_pointer->vertexUVID);

                // 3rd attribute buffer: normals.
                yli::opengl::enable_vertex_attrib_array(species_or_glyph_pointer->vertex_normal_modelspaceID);

                // Render this `Species` or `Glyph` by calling `render()` function of each `Object`.
                yli::ontology::render_children<yli::ontology::Object*>(species_or_glyph_pointer->object_pointer_vector);

                yli::opengl::disable_vertex_attrib_array(species_or_glyph_pointer->vertex_position_modelspaceID);
                yli::opengl::disable_vertex_attrib_array(species_or_glyph_pointer->vertexUVID);
                yli::opengl::disable_vertex_attrib_array(species_or_glyph_pointer->vertex_normal_modelspaceID);
            }
    }
}

#endif
