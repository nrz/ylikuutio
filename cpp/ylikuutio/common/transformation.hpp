#ifndef __TRANSFORMATION_HPP_INCLUDED
#define __TRANSFORMATION_HPP_INCLUDED

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

namespace geometry
{
    glm::vec3 transform_planar_world_vertex_into_cartesian_vertex(
            glm::vec3 planar_world_vertex,
            double sphere_radius);

    void transform_coordinates_to_curved_surface(
            TransformationStruct transformation_struct,
            std::vector<glm::vec3> &temp_vertices);
}

#endif
