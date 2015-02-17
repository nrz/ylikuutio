#ifndef BMPLOADER_H
#define BMPLOADER_H
bool load_BMP_world(
        const char *path,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals,
        std::string color_channel);
#endif
