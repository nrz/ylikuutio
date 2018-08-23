#ifndef __LAS_LOADER_HPP_INCLUDED
#define __LAS_LOADER_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace load
    {
        bool load_LASF_data(
                const std::string laser_scaling_file_name,
                std::vector<glm::vec3>& laser_points);
    }
}

#endif
