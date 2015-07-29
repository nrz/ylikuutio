#ifndef __GLOBALS_HPP_INCLUDED
#define __GLOBALS_HPP_INCLUDED

// GCC (at least g++ 4.7.2) and Visual Studio 2015 do support
// setting default values of a struct using C++11 syntax.
// Clang 3.7.0 and Visual Studio 2013 do not support
// setting default values of a struct using C++11 syntax.
// Visual Studio 2013 fails to compile, whereas Clang-compiled
// executable with code with setting default values of a struct
// causes Segmentation fault upon execution of the program.
// Compilers that don't support setting default values of a struct
// are handled by setting the default values in a macro.
// http://stackoverflow.com/questions/16782103/initializing-default-values-in-a-struct/16783513#16783513
#ifdef __clang__
#elif defined(__GNUC__)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#elif defined(_WIN32)
#if (_MSC_VER >= 1900)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#endif
#endif

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
#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
    void *world_pointer = NULL;              // pointer to the world (draw list).
#else
    void *world_pointer;                     // pointer to the world (draw list).
#endif
    std::string vertex_shader;               // filename of vertex shader.
    std::string fragment_shader;             // filename of fragment shader.
} ShaderStruct;

#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#define SHADERSTRUCT(x) \
ShaderStruct x
#else
#define SHADERSTRUCT(x) \
ShaderStruct x; x.world_pointer = NULL
#endif

typedef struct
{
#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
    void *shader_pointer = NULL;             // pointer to the shader.
#else
    void *shader_pointer;                    // pointer to the shader.
#endif
    std::string texture_file_format;         // type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
    std::string texture_filename;            // filename of the model file.
    std::string image_path;
} TextureStruct;

#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#define TEXTURESTRUCT(x) \
TextureStruct x
#else
#define TEXTURESTRUCT(x) \
TextureStruct x; x.shader_pointer = NULL
#endif

typedef struct
{
    GLuint nodeID;
#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
    void *graph_pointer = NULL;
#else
    void *graph_pointer;
#endif
    glm::vec3 coordinate_vector;
    std::vector<uint32_t> neighbor_nodeIDs;
} NodeStruct;

#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#define NODESTRUCT(x) \
NodeStruct x
#else
#define NODESTRUCT(x) \
NodeStruct x; x.graph_pointer = NULL
#endif

typedef struct
{
#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
    void *species_pointer = NULL;                                  // pointer to the species.
    glm::vec3 original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f); // original scale vector.
    GLfloat rotate_angle = NAN;                                    // rotate angle.
#else
    void *species_pointer;           // pointer to the species.
    glm::vec3 original_scale_vector; // original scale vector.
    GLfloat rotate_angle;            // rotate angle.
#endif
    glm::vec3 coordinate_vector;     // coordinate vector.
    glm::vec3 rotate_vector;         // rotate vector.
    glm::vec3 translate_vector;      // translate vector.
    glm::mat4 model_matrix;          // model matrix.
    glm::mat4 MVP_matrix;            // model view projection matrix.
} ObjectStruct;

#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#define OBJECTSTRUCT(x) \
ObjectStruct x
#else
#define OBJECTSTRUCT(x) \
ObjectStruct x; x.species_pointer = NULL; x.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f); x.rotate_angle = NAN
#endif

typedef struct
{
    // used for all files (for all species).
#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
    void *texture_pointer = NULL;            // pointer to the texture object.
    bool is_world = false;                   // worlds currently do not rotate nor translate.
    double world_radius = NAN;               // radius of sea level in meters. used only for worlds.
#else
    void *texture_pointer;                   // pointer to the texture object.
    bool is_world;                           // worlds currently do not rotate nor translate.
    double world_radius;                     // radius of sea level in meters. used only for worlds.
#endif
    std::string model_file_format;           // type of the model file. supported file formats so far: `"bmp"`/`"BMP"`, `"obj"`/`"OBJ"`.
                                             // TODO: add support for `"SRTM"`.
    std::string vertex_shader;               // filename of vertex shader.
    std::string fragment_shader;             // filename of fragment shader.
    glm::vec3 lightPos;                      // light position.
    std::vector<ObjectStruct> object_vector; // vector of individual objects of this species.
    std::string coordinate_system;           // used only for worlds (`is_world` == `true`). valid values: `"cartesian"`.
                                             // TODO: add support for `"spherical"`. `"spherical"` is used eg. in SRTM heightmaps.

    // for `"bmp"` model files.
    std::string model_filename;              // filename of the model file.
    std::string color_channel;               // color channel to use for altitude data.
} SpeciesStruct;

#ifdef __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#define SPECIESSTRUCT(x) \
SpeciesStruct x
#else
#define SPECIESSTRUCT(x) \
SpeciesStruct x; x.texture_pointer = NULL; x.is_world = false; x.world_radius = NAN
#endif

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
