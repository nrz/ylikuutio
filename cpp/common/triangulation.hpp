#ifndef __TRIANGULATION_HPP_INCLUDED
#define __TRIANGULATION_HPP_INCLUDED

#include "globals.hpp"

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
    // for bilinear interpolation.
    enum BilinearDirections { SSW, WSW, WNW, NNW, NNE, ENE, ESE, SSE };

    // for southeast-northwest edges.
    enum SoutheastNorthwestEdgesDirections { SSE_CODE_FOR_SE_NW, WNW_CODE_FOR_SE_NW, ESE_CODE_FOR_SE_NW, NNW_CODE_FOR_SE_NW, SW_CODE_FOR_SE_NW, NE_CODE_FOR_SE_NW };

    // for bilinear interpolation.
    glm::vec3 get_face_normal(
            std::vector<glm::vec3> &face_normal_data,
            uint32_t x,
            uint32_t z,
            BilinearDirections compass_point_code,
            uint32_t image_width);

    // for southeast-northwest edges.
    glm::vec3 get_face_normal_for_SE_NW(
            std::vector<glm::vec3> &face_normal_data,
            uint32_t x,
            uint32_t z,
            SoutheastNorthwestEdgesDirections compass_point_code,
            uint32_t image_width);

    inline GLuint get_y(
            GLuint* vertex_data,
            uint32_t x,
            uint32_t z,
            uint32_t image_width);

    glm::vec3 transform_planar_world_vertex_into_cartesian_vertex(
            glm::vec3 planar_world_vertex,
            double sphere_radius);

    uint32_t output_triangle_vertices(
            std::vector<glm::vec3> &temp_vertices,
            std::vector<glm::vec2> &temp_UVs,
            std::vector<glm::vec3> &temp_normals,
            GLuint vertexIndex[3],
            GLuint uvIndex[3],
            GLuint normalIndex[3],
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals,
            uint32_t triangle_i);

    bool triangulate_quads(
            TriangulateQuadsStruct triangulate_quads_struct,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals);
}

#endif
