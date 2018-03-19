#ifndef __GROUND_LEVEL_HPP_INCLUDED
#define __GROUND_LEVEL_HPP_INCLUDED

#include "species.hpp"

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

namespace ontology
{
    GLfloat get_ground_level(ontology::Species* const terrain_species, glm::vec3& position);
    GLfloat get_floor_level(ontology::Species* const terrain_species, glm::vec3& position);
}

#endif
