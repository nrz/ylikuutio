#ifndef __GLOBAL_VARIABLES_HPP_INCLUDED
#define __GLOBAL_VARIABLES_HPP_INCLUDED

#include "globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Global variables.

// Variables related to the camera.
extern glm::vec3 camera_position;
extern glm::mat4 ProjectionMatrix;
extern glm::mat4 ViewMatrix;
extern GLfloat initialFoV;

// Variables related to the console.
extern console::Console* global_console_pointer;

// Variables related to the fonts and texts used.
extern uint32_t text_size;
extern uint32_t font_size;

// Variable related to voluntary movement.
extern glm::vec3 position;
extern glm::vec3 direction;
extern glm::vec3 right;
extern glm::vec3 up;
extern SphericalCoordinatesStruct spherical_position;
extern double horizontalAngle;
extern double verticalAngle;
extern GLfloat speed;
extern GLfloat turbo_factor;
extern GLfloat twin_turbo_factor;
extern GLfloat mouseSpeed;
extern bool hasMouseEverMoved;
extern bool can_toggle_invert_mouse;
extern bool is_invert_mouse_in_use;
extern bool can_toggle_flight_mode;
extern bool is_flight_mode_in_use;
extern bool is_first_turbo_pressed;
extern bool is_second_turbo_pressed;

// Variables related to physics.
extern GLfloat gravity;
extern GLfloat fallSpeed;

// Variables related to the current `Scene`.
extern bool testing_spherical_world_in_use;

// Variables related to debug & testing keys.
extern bool is_key_I_released;
extern bool is_key_F_released;

// Variables related to help mode.
extern bool in_help_mode;
extern bool can_toggle_help_mode;
extern bool can_display_help_screen;

#endif
