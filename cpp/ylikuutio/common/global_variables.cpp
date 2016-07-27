#include "global_variables.hpp"

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

// Global variables.

// Variables related to the window.
GLFWwindow* window;
uint32_t window_width = 1600;
uint32_t window_height = 900;

// Variables related to the camera.
glm::vec3 camera_position;
glm::mat4 ProjectionMatrix;
glm::mat4 ViewMatrix;
GLfloat aspect_ratio = (GLfloat) window_width / window_height;
GLfloat initialFoV;

// Variables related to the console.
console::Console* global_console_pointer = nullptr;

// Variables related to the fonts and texts used.
uint32_t text_size = 40;
uint32_t font_size = 16;

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
bool hasMouseEverMoved;
bool is_invert_mouse_in_use;
bool is_flight_mode_in_use;
bool is_first_turbo_pressed;
bool is_second_turbo_pressed;

// Variables related to physics.
GLfloat gravity = 9.81f / 60.0f;
GLfloat fallSpeed = gravity;

// Variables related to timing of events.
double lastTime;
double currentTime;
float deltaTime;
uint32_t max_FPS = 60;

// Variables related to the current `Scene`.
double earth_radius;
bool testing_spherical_world_in_use = false;
bool is_world_loaded; // no more than one world object can be loaded. TODO: check that no more than one world is loaded!
bool is_world_spherical;

// Variables related to debug & testing keys.
bool is_key_I_released;
bool is_key_F_released;
bool is_key_F1_released;
bool in_help_mode = true;
