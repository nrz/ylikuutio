#ifndef __HEIGHTMAP_LOADER_HPP_INCLUDED
#define __HEIGHTMAP_LOADER_HPP_INCLUDED

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>
#include <vector>   // std::vector

namespace model
{
    bool load_BMP_world(
            std::string image_path,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals,
            GLuint &image_width,
            GLuint &image_height,
            std::string color_channel);

    bool load_SRTM_world(
            std::string image_path,
            double latitude,
            double longitude,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals);
}

#endif
