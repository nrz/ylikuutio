#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "quad_triangulation.hpp"

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
#include <vector>   // std::vector

namespace geometry
{
    void output_triangle_vertices(
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec2>& temp_UVs,
            std::vector<glm::vec3>& temp_normals,
            GLuint vertexIndex[3],
            GLuint uvIndex[3],
            GLuint normalIndex[3],
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals)
    {
        out_vertices.push_back(temp_vertices[vertexIndex[0]]);
        out_UVs.push_back(temp_UVs[uvIndex[0]]);
        out_normals.push_back(temp_normals[normalIndex[0]]);

        out_vertices.push_back(temp_vertices[vertexIndex[1]]);
        out_UVs.push_back(temp_UVs[uvIndex[1]]);
        out_normals.push_back(temp_normals[normalIndex[1]]);

        out_vertices.push_back(temp_vertices[vertexIndex[2]]);
        out_UVs.push_back(temp_UVs[uvIndex[2]]);
        out_normals.push_back(temp_normals[normalIndex[2]]);
    }
}
