// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h>
#endif

#include "globals.hpp"

glm::mat4 ProjectionMatrix;
glm::vec3 position;
GLfloat gravity = 9.81f / 60.0f;
bool inFlightmode;
GLfloat fallSpeed = gravity;
SphericalCoordinatesStruct spherical_position;
double horizontalAngle;
double verticalAngle;
GLfloat initialFoV;
double earth_radius;

bool hasMouseEverMoved;
bool is_invert_mouse_in_use;
bool is_key_I_released;
bool is_world_loaded; // no more than one world object can be loaded. TODO: check that no more than one world is loaded!
bool is_world_spherical;
