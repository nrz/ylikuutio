#ifndef __OBJLOADER_HPP_INCLUDED
#define __OBJLOADER_HPP_INCLUDED

namespace model
{
    bool load_OBJ(
            const char *path,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals);
}

#endif
