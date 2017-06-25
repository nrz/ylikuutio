#include "global_variables.hpp"

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

// Variables related to the console.
// `global_console_pointer` can not be converted into a non-global
// variable, because the console object needs to be accessed from
// `void Console::charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods)`
// and as far as I know there is no way to pass `Universe*` pointer to `charmods_callback`
// without changing GLFW code, which I want to avoid, if possible.
console::Console* global_console_pointer = nullptr;

// Variable related to voluntary movement.
glm::vec3 position;
glm::vec3 direction;
glm::vec3 right;
glm::vec3 up;
SphericalCoordinatesStruct spherical_position;
double horizontalAngle;
double verticalAngle;
GLfloat speed = 5.0f; // 5 units / second
GLfloat turbo_factor;
GLfloat twin_turbo_factor;
GLfloat mouseSpeed = 0.005f;
bool hasMouseEverMoved = false;
bool can_toggle_invert_mouse = false;
bool is_invert_mouse_in_use = false;
bool can_toggle_flight_mode = false;
bool is_flight_mode_in_use = false;
bool is_first_turbo_pressed = false;
bool is_second_turbo_pressed = false;

// Variables related to physics.
GLfloat gravity = 9.81f / 60.0f;
GLfloat fallSpeed = gravity;

// Variables related to the current `Scene`.
bool testing_spherical_world_in_use = false;

// Variables related to debug & testing keys.
bool is_key_I_released;
bool is_key_F_released;

// Variables related to help mode.
bool in_help_mode = true;
bool can_toggle_help_mode = false;
bool can_display_help_screen = true;
