#ifndef TEXT2D_HPP
#define TEXT2D_HPP

#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace ontology
{
    class Font2D
    {
        public:
            // constructor.
            Font2D(
                    GLuint screen_width,
                    GLuint screen_height,
                    const char* texturePath,
                    const char* char_font_texture_file_format);

            // destructor.
            ~Font2D();

            void printText2D(
                    GLuint screen_width,
                    GLuint screen_height,
                    GLuint x,
                    GLuint y,
                    GLuint text_size,
                    GLuint font_size,
                    const char* text_char,
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
                    const char* text_char,
                    const char* char_font_texture_file_format);

        private:
            GLuint text2D_textureID;              // Material containing the font
            GLuint vertexbuffer;         // Buffer containing the vertices
            GLuint uvbuffer;             // Buffer containing the UVs
            GLuint programID;               // The `programID` of the shader used to display the text, returned by `LoadShaders`.
            GLuint vertexPosition_screenspaceID; // Location of the program's "vertexPosition_screenspace" attribute
            GLuint vertexUVID;                   // Location of the program's "vertexUV" attribute
            GLuint Text2DUniformID;              // Location of the program's texture attribute
            GLuint screen_width_uniform_ID;      // Location of the program's window width uniform.
            GLuint screen_height_uniform_ID;     // Location of the program's window height uniform.
    };
}

#endif
