#ifndef TEXT2D_HPP
#define TEXT2D_HPP

#include "globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace text2D
{
    void initText2D(
            GLuint screen_width,
            GLuint screen_height,
            const char* texturePath,
            const char* char_font_texture_file_format);

    void printText2D(
            GLuint screen_width,
            GLuint screen_height,
            GLuint x,
            GLuint y,
            GLuint text_size,
            GLuint font_size,
            const char* text,
            const char* char_font_texture_file_format,
            const char* horizontal_alignment,
            const char* vertical_alignment);

    void printText2D(PrintingStruct printing_struct);

    void printText2D(
            GLuint screen_width,
            GLuint screen_height,
            GLuint x,
            GLuint y,
            GLuint text_size,
            GLuint font_size,
            const char* text,
            const char* char_font_texture_file_format);

    void cleanupText2D();
}

#endif
