#ifndef __SPECIES_OR_GLYPH_HPP_INCLUDED
#define __SPECIES_OR_GLYPH_HPP_INCLUDED

#include "model_templates.hpp"

namespace model
{
    class Object;

    // template<typename T1>
    template<class T1>
        void render_species_or_glyph(T1 species_or_glyph_pointer)
        {
            // Compute the MVP matrix from keyboard and mouse input.
            glUniform3f(
                    species_or_glyph_pointer->lightID,
                    species_or_glyph_pointer->lightPos.x,
                    species_or_glyph_pointer->lightPos.y,
                    species_or_glyph_pointer->lightPos.z);

            // 1st attribute buffer : vertices.
            glEnableVertexAttribArray(species_or_glyph_pointer->vertexPosition_modelspaceID);

            // 2nd attribute buffer : UVs.
            glEnableVertexAttribArray(species_or_glyph_pointer->vertexUVID);

            // 3rd attribute buffer : normals.
            glEnableVertexAttribArray(species_or_glyph_pointer->vertexNormal_modelspaceID);

            // render Species by calling `render()` function of each Object.
            model::render_children<model::Object*>(species_or_glyph_pointer->object_pointer_vector);

            glDisableVertexAttribArray(species_or_glyph_pointer->vertexPosition_modelspaceID);
            glDisableVertexAttribArray(species_or_glyph_pointer->vertexUVID);
            glDisableVertexAttribArray(species_or_glyph_pointer->vertexNormal_modelspaceID);
        }
}

#endif
