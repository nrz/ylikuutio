#ifndef __BMPLOADER_HPP_INCLUDED
#define __BMPLOADER_HPP_INCLUDED

namespace model
{
    bool load_BMP_world(
            const char *image_path,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals,
            std::string color_channel);
}

#endif
