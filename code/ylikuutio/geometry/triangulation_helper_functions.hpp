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

    void interpolate_vertices_using_bilinear_interpolation(
            BilinearInterpolationStruct bilinear_interpolation_struct,
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec2>& temp_UVs);
}

// for bilinear interpolation.
#define SSW_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, SSW, image_width))
#define WSW_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, WSW, image_width))
#define WNW_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, WNW, image_width))
#define NNW_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, NNW, image_width))
#define NNE_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, NNE, image_width))
#define ENE_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, ENE, image_width))
#define ESE_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, ESE, image_width))
#define SSE_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, SSE, image_width))

// for bilinear interpolation.
#define S_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, ENE, image_width))
#define W_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, NNE, image_width))
#define N_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, WSW, image_width))
#define E_FACE_NORMAL (geometry::get_face_normal(face_normal_vector_vec3, x, z, SSW, image_width))

// for southeast-northwest edges.
#define SSE_FACE_NORMAL_FOR_SE_NW (geometry::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, image_width))
#define WNW_FACE_NORMAL_FOR_SE_NW (geometry::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, image_width))
#define ESE_FACE_NORMAL_FOR_SE_NW (geometry::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, image_width))
#define NNW_FACE_NORMAL_FOR_SE_NW (geometry::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, image_width))
#define SW_FACE_NORMAL_FOR_SE_NW (geometry::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, image_width))
#define NE_FACE_NORMAL_FOR_SE_NW (geometry::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, image_width))

#endif
