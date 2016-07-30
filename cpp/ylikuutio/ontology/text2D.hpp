#ifndef TEXT2D_HPP
#define TEXT2D_HPP

#include "cpp/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace text2D
{
    class Text2D
    {
        public:
            // constructor.
            Text2D(
                    GLuint screen_width,
                    GLuint screen_height,
                    const char* texturePath,
                    const char* char_font_texture_file_format);

            // destructor.
            ~Text2D();

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
            GLuint Text2DTextureID;              // Material containing the font
            GLuint Text2DVertexBufferID;         // Buffer containing the vertices
            GLuint Text2DUVBufferID;             // Buffer containing the UVs
            GLuint Text2DShaderID;               // Shader program used to display the text
            GLuint vertexPosition_screenspaceID; // Location of the program's "vertexPosition_screenspace" attribute
            GLuint vertexUVID;                   // Location of the program's "vertexUV" attribute
            GLuint Text2DUniformID;              // Location of the program's texture attribute
            GLuint screen_width_uniform_ID;      // Location of the program's window width uniform.
            GLuint screen_height_uniform_ID;     // Location of the program's window height uniform.
    };
}

#endif
