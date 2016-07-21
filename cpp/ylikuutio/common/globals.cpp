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

uint32_t window_width = 1600;
uint32_t window_height = 900;
uint32_t text_size = 40;
uint32_t font_size = 16;
uint32_t max_FPS = 60;
GLfloat aspect_ratio = (GLfloat) window_width / window_height;
glm::mat4 ProjectionMatrix;
glm::mat4 ViewMatrix;
glm::vec3 position;
GLfloat gravity = 9.81f / 60.0f;
bool is_flight_mode_in_use;
bool in_help_mode = true;
GLfloat fallSpeed = gravity;
SphericalCoordinatesStruct spherical_position;
double horizontalAngle;
double verticalAngle;
GLfloat initialFoV;
double earth_radius;

bool hasMouseEverMoved;
bool is_invert_mouse_in_use;
bool is_key_I_released;
bool is_key_F_released;
bool is_key_F1_released;
bool is_world_loaded; // no more than one world object can be loaded. TODO: check that no more than one world is loaded!
bool is_world_spherical;
bool testing_spherical_world_in_use = false;

GLfloat speed = 5.0f; // 5 units / second

GLfloat turbo_factor;
GLfloat twin_turbo_factor;

GLfloat mouseSpeed = 0.005f;

glm::vec3 camera_position;
