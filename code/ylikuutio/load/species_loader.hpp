#ifndef __SPECIES_LOADER_HPP_INCLUDED
#define __SPECIES_LOADER_HPP_INCLUDED

#include "species_loader_struct.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace yli
{
    namespace load
    {
        bool load_species(
                const SpeciesLoaderStruct& species_loader_struct,
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
