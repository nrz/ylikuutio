#ifndef __GLOBALS_HPP_INCLUDED
#define __GLOBALS_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

extern glm::vec3 position;
extern float horizontalAngle;
extern float verticalAngle;
extern float initialFoV;

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
