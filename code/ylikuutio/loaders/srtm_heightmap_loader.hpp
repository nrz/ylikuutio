#ifndef __SRTM_HEIGHTMAP_LOADER_HPP_INCLUDED
#define __SRTM_HEIGHTMAP_LOADER_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace loaders
    {
        bool load_SRTM_terrain(
                const std::string& image_path,
                const float latitude,
                const float longitude,
                const float planet_radius,
                const float divisor,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals,
                const std::size_t x_step,
                const std::size_t z_step,
                const std::string& triangulation_type);
    }
}

#endif
