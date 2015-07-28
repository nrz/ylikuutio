#ifndef __GLOBALS_HPP_INCLUDED
#define __GLOBALS_HPP_INCLUDED

#include <string>
#include <vector>
#include <stdint.h> // uint32_t etc.

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

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH (1600.0f)
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT (900.0f)
#endif

#ifndef ASPECT_RATIO
#define ASPECT_RATIO (WINDOW_WIDTH / WINDOW_HEIGHT)
#endif

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef EARTH_RADIUS
#define EARTH_RADIUS 6371000.0f
#endif

#ifndef TEXT_SIZE
#define TEXT_SIZE 40
#endif

#ifndef FONT_SIZE
#define FONT_SIZE 16
#endif

#ifndef MAX_FPS
#define MAX_FPS 60
#endif

extern glm::vec3 position;
extern GLfloat gravity;
extern bool inFlightmode;
extern GLfloat fallSpeed;
extern double horizontalAngle;
extern double verticalAngle;
extern GLfloat initialFoV;
extern double earth_radius;
extern bool hasMouseEverMoved;
extern bool is_invert_mouse_in_use;
extern bool is_key_I_released;
extern bool is_world_loaded;                 // no more than one world object can be loaded. TODO: check that no more than one world is loaded!
extern bool is_world_spherical;

typedef struct
{
#ifdef __gnu_linux__
    void *world_pointer = NULL;              // pointer to the world (draw list).
#endif
#ifdef _WIN32
    void *world_pointer;                     // pointer to the world (draw list).
#endif
    std::string vertex_shader;               // filename of vertex shader.
    std::string fragment_shader;             // filename of fragment shader.
} ShaderStruct;

#ifdef __gnu_linux__
#define SHADERSTRUCT(x) \
ShaderStruct x
#endif
#ifdef _WIN32
#define SHADERSTRUCT(x) \
ShaderStruct x; x.world_pointer = NULL
#endif

typedef struct
{
#ifdef __gnu_linux__
    void *shader_pointer = NULL;             // pointer to the shader.
#endif
#ifdef _WIN32
    void *shader_pointer;                    // pointer to the shader.
#endif
    std::string texture_file_format;         // type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
    std::string texture_filename;            // filename of the model file.
    std::string image_path;
} TextureStruct;

#ifdef __gnu_linux__
#define TEXTURESTRUCT(x) \
TextureStruct x
#endif
#ifdef _WIN32
#define TEXTURESTRUCT(x) \
TextureStruct x; x.shader_pointer = NULL
#endif

typedef struct
{
    GLuint nodeID;
    void *graph_pointer = NULL;
    glm::vec3 coordinate_vector;
    std::vector<uint32_t> neighbor_nodeIDs;
} NodeStruct;

typedef struct
{
    glm::vec3 coordinate_vector;     // coordinate vector.
    GLfloat rotate_angle = NAN;      // rotate angle.
    glm::vec3 rotate_vector;         // rotate vector.
    glm::vec3 translate_vector;      // translate vector.
    glm::mat4 model_matrix;          // model matrix.
    glm::mat4 MVP_matrix;            // model view projection matrix.
    void *species_pointer = NULL;    // pointer to the species.
} ObjectStruct;

typedef struct
{
    // used for all files (for all species).
    void *texture_pointer = NULL;            // pointer to the texture object.
    std::string model_file_format;           // type of the model file. supported file formats so far: `"bmp"`/`"BMP"`, `"obj"`/`"OBJ"`.
                                             // TODO: add support for `"SRTM"`.
    std::string vertex_shader;               // filename of vertex shader.
    std::string fragment_shader;             // filename of fragment shader.
    glm::vec3 lightPos;                      // light position.
    std::vector<ObjectStruct> object_vector; // vector of individual objects of this species.
    bool is_world = false;                   // worlds currently do not rotate nor translate.
    std::string coordinate_system;           // used only for worlds (`is_world` == `true`). valid values: `"cartesian"`.
                                             // TODO: add support for `"spherical"`. `"spherical"` is used eg. in SRTM heightmaps.
    double world_radius = NAN;               // radius of sea level in meters. used only for worlds.

    // for `"bmp"` model files.
    std::string model_filename;              // filename of the model file.
    std::string color_channel;               // color channel to use for altitude data.
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

typedef struct
{
    double rho;
    double theta;
    double phi;
} SphericalCoordinatesStruct;

typedef struct
{
    double southern_latitude;
    double northern_latitude;
    double western_longitude;
    double eastern_longitude;
} SphericalWorldStruct;

extern SphericalCoordinatesStruct spherical_position;

#endif
