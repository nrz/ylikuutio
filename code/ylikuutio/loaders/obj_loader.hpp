#ifndef __OBJLOADER_HPP_INCLUDED
#define __OBJLOADER_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli
{
    namespace loaders
    {
        bool load_OBJ(
                const std::string& obj_file_name,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals);
    }
}

#endif
