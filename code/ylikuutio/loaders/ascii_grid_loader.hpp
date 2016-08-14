#ifndef __ASCII_GRID_LOADER_HPP_INCLUDED
#define __ASCII_GRID_LOADER_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector


namespace loaders
{
    bool load_ascii_grid(
            std::string ascii_grid_file_name,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            std::string triangulation_type);
}

#endif
