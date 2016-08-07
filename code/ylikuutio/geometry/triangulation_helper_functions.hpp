#ifndef __TRIANGULATION_MACROS_HPP_INCLUDED
#define __TRIANGULATION_MACROS_HPP_INCLUDED

#include "code/ylikuutio/common/globals.hpp"

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
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    // for bilinear interpolation.
    enum BilinearDirections { SSW, WSW, WNW, NNW, NNE, ENE, ESE, SSE };

    inline GLuint get_y(
            uint32_t* vertex_data,
            uint32_t x,
            uint32_t z,
            uint32_t image_width);

    inline GLuint southwest(uint32_t current_vertex_i, uint32_t image_width);
    inline GLuint southeast(uint32_t current_vertex_i, uint32_t image_width);
    inline GLuint northwest(uint32_t current_vertex_i, uint32_t image_width);
    inline GLuint northeast(uint32_t current_vertex_i, uint32_t image_width);
    inline GLuint center(uint32_t current_interpolated_vertex_i);

    inline uint32_t southwest_y(uint32_t x, uint32_t z, uint32_t* input_vertex_pointer, uint32_t image_width);
    inline uint32_t southeast_y(uint32_t x, uint32_t z, uint32_t* input_vertex_pointer, uint32_t image_width);
    inline uint32_t northwest_y(uint32_t x, uint32_t z, uint32_t* input_vertex_pointer, uint32_t image_width);
    inline uint32_t northeast_y(uint32_t x, uint32_t z, uint32_t* input_vertex_pointer, uint32_t image_width);
    inline uint32_t center_y(uint32_t x, uint32_t z, uint32_t* input_vertex_pointer, uint32_t image_width);

    // for bilinear interpolation.
    glm::vec3 get_face_normal(
            std::vector<glm::vec3>& face_normal_data,
            uint32_t x,
            uint32_t z,
            BilinearDirections compass_point_code,
            uint32_t image_width);

    void interpolate_vertices_using_bilinear_interpolation(
            BilinearInterpolationStruct bilinear_interpolation_struct,
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec2>& temp_UVs);

    // for bilinear interpolation.
    // These `inline` functions exist to avoid need to remember
    // the array order when calling `geometry::get_face_normal`.
    inline glm::vec3 s_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, uint32_t x, uint32_t z, uint32_t image_width);
    inline glm::vec3 w_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, uint32_t x, uint32_t z, uint32_t image_width);
    inline glm::vec3 n_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, uint32_t x, uint32_t z, uint32_t image_width);
    inline glm::vec3 e_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, uint32_t x, uint32_t z, uint32_t image_width);
}

#endif
