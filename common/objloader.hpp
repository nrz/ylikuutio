#ifndef OBJLOADER_H
#define OBJLOADER_H
bool load_OBJ(
        const char *path,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals
        );
#endif
