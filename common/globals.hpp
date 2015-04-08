#ifndef __GLOBALS_HPP_INCLUDED
#define __GLOBALS_HPP_INCLUDED

#include <string>
#include <vector>

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h>
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

extern glm::vec3 position;
extern float horizontalAngle;
extern float verticalAngle;
extern float initialFoV;
extern bool hasMouseEverMoved;

typedef struct
{
    std::string texture_file_format;
    std::string image_path;
} TextureStruct;

typedef struct
{
    glm::mat4 model_matrix;          // model matrix.
    glm::vec3 translate_vector;      // translate vector.
    glm::mat4 MVP_matrix;            // model view projection matrix.
    void *species_ptr;               // pointer to the species.
} ObjectStruct;

typedef struct
{
    std::string model_file_format;           // type of the model file, eg. `"bmp"`.
    std::string model_filename;              // filename of the model file.
    std::string texture_file_format;         // type of the model file, eg. `"bmp"`.
    std::string texture_filename;            // filename of the model file.
    std::string vertex_shader;               // filename of vertex shader.
    std::string fragment_shader;             // filename of fragment shader.
    std::string color_channel;               // filename of fragment shader.
    std::vector<ObjectStruct> object_vector; // vector of individual objects of this species.
    glm::vec3 lightPos;                      // light position.
} SpeciesStruct;

typedef struct
{
    GLuint screen_width;
    GLuint screen_height;
    GLuint x;
    GLuint y;
    GLuint text_size;
    GLuint font_size;
    const char *text;
    const char *char_font_texture_file_format;
    const char *horizontal_alignment;
    const char *vertical_alignment;
} PrintingStruct;

#endif
