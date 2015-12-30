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

    bool triangulate_quads(
            TriangulateQuadsStruct triangulate_quads_struct,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals);
}

#endif
