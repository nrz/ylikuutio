#ifndef __ASCII_GRID_LOADER_HPP_INCLUDED
#define __ASCII_GRID_LOADER_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace load
    {
        bool load_ASCII_grid(
                const std::string& ascii_grid_filename,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals,
                std::size_t& image_width,
                std::size_t& image_height,
                const std::size_t x_step,
                const std::size_t z_step,
                const std::string& triangulation_type,
                const bool should_ylikuutio_use_real_texture_coordinates);
    }
}

#endif
