#ifndef __TRIANGULATION_MACROS_CPP_INCLUDED
#define __TRIANGULATION_MACROS_CPP_INCLUDED

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace geometry
{
    inline GLuint get_y(
            GLuint* vertex_data,
            uint32_t x,
            uint32_t z,
            uint32_t image_width)
    {
        // This function returns the altitude value based on x & z coordinates.
        // This works only for a raw heightmap data (for a 2D array of altitudes).
        GLuint* vertex_pointer;
        vertex_pointer = vertex_data + z * image_width + x;
        return *vertex_pointer;
    }

    // for bilinear interpolation, southeast-northwest edges, and southwest-northeast edges.
    inline GLuint southwest(uint32_t current_vertex_i, uint32_t image_width)
    {
        return current_vertex_i - image_width - 1;
    }
    inline GLuint southeast(uint32_t current_vertex_i, uint32_t image_width)
    {
        return current_vertex_i - image_width;
    }
    inline GLuint northwest(uint32_t current_vertex_i, uint32_t image_width)
    {
        return current_vertex_i - 1;
    }
    inline GLuint northeast(uint32_t current_vertex_i, uint32_t image_width)
    {
        return current_vertex_i;
    }
}

// for bilinear interpolation.
inline GLuint center(uint32_t current_interpolated_vertex_i)
{
    return current_interpolated_vertex_i;
}

// for bilinear interpolation.
#define SOUTHWEST_Y (geometry::get_y(input_vertex_pointer, x - 1, z - 1, image_width))
#define SOUTHEAST_Y (geometry::get_y(input_vertex_pointer, x, z - 1, image_width))
#define NORTHWEST_Y (geometry::get_y(input_vertex_pointer, x - 1, z, image_width))
#define NORTHEAST_Y (geometry::get_y(input_vertex_pointer, x, z, image_width))
#define CENTER_Y ((SOUTHWEST_Y + SOUTHEAST_Y + NORTHWEST_Y + NORTHEAST_Y) / 4)

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
