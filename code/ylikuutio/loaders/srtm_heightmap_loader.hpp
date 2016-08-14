#ifndef __SRTM_HEIGHTMAP_LOADER_HPP_INCLUDED
#define __SRTM_HEIGHTMAP_LOADER_HPP_INCLUDED

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
    bool load_SRTM_world(
            std::string image_path,
            float latitude,
            float longitude,
            float world_radius,
            float divisor,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            std::string triangulation_type);
}

#endif
