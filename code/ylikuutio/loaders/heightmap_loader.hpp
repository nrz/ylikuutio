#ifndef __HEIGHTMAP_LOADER_HPP_INCLUDED
#define __HEIGHTMAP_LOADER_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    bool load_BMP_world(
            std::string image_path,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            uint32_t &image_width,
            uint32_t &image_height,
            std::string color_channel,
            std::string triangulation_type);

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

    bool load_LASF_data(
            std::string laser_scaling_file_name,
            std::vector<glm::vec3>& laser_points);
}

#endif
