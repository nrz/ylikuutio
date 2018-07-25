#ifndef __SPECIES_LOADER_HPP_INCLUDED
#define __SPECIES_LOADER_HPP_INCLUDED

#include "species_loader_struct.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace yli
{
    namespace loaders
    {
        bool load_species(
                SpeciesLoaderStruct& species_loader_struct,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals,
                std::vector<GLuint>& indices,
                std::vector<glm::vec3>& indexed_vertices,
                std::vector<glm::vec2>& indexed_UVs,
                std::vector<glm::vec3>& indexed_normals,
                GLuint* vertexbuffer,
                GLuint* uvbuffer,
                GLuint* normalbuffer,
                GLuint* elementbuffer,
                bool& vram_buffer_in_use,
                const bool is_debug_mode);
    }
}

#endif
