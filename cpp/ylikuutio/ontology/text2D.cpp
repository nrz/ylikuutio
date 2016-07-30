#include "text2D.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"

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

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

// Include standard headers
#include <vector>   // std::vector
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <stdint.h> // uint32_t etc.

namespace text2D
{
    Text2D::Text2D(
            GLuint screen_width,
            GLuint screen_height,
            const char* texturePath,
            const char* char_font_texture_file_format)
    {
        // constructor.

        // Initialize texture
        if ((std::strcmp(char_font_texture_file_format, "bmp") == 0) || (std::strcmp(char_font_texture_file_format, "BMP") == 0))
        {
            Text2DTextureID = texture::load_BMP_texture(texturePath);
        }
        else if ((std::strcmp(char_font_texture_file_format, "dds") == 0) || (std::strcmp(char_font_texture_file_format, "DDS") == 0))
        {
            Text2DTextureID = texture::load_DDS_texture(texturePath);
        }

        // Initialize VBO
        glGenBuffers(1, &Text2DVertexBufferID);
        glGenBuffers(1, &Text2DUVBufferID);

        // Initialize Shader
        Text2DShaderID = LoadShaders("TextVertexShader.vertexshader", "TextVertexShader.fragmentshader");

        // Get a handle for our buffers
        vertexPosition_screenspaceID = glGetAttribLocation(Text2DShaderID, "vertexPosition_screenspace");
        vertexUVID = glGetAttribLocation(Text2DShaderID, "vertexUV");

        // Initialize uniforms' IDs
        Text2DUniformID = glGetUniformLocation(Text2DShaderID, "myTextureSampler");

        // Initialize uniform window width.
        screen_width_uniform_ID = glGetUniformLocation(Text2DShaderID, "screen_width");
        glUniform1i(screen_width_uniform_ID, screen_width);

        // Initialize uniform window height.
        screen_height_uniform_ID = glGetUniformLocation(Text2DShaderID, "screen_height");
        glUniform1i(screen_height_uniform_ID, screen_height);
    }

    Text2D::~Text2D()
    {
        // destructor.

        // Delete buffers
        glDeleteBuffers(1, &Text2DVertexBufferID);
        glDeleteBuffers(1, &Text2DUVBufferID);

        // Delete texture
        glDeleteTextures(1, &Text2DTextureID);

        // Delete shader
        glDeleteProgram(Text2DShaderID);
    }

    void Text2D::printText2D(
            GLuint screen_width,
            GLuint screen_height,
            GLuint x,
            GLuint y,
            GLuint text_size,
            GLuint font_size,
            const char* text_char,
            const char* char_font_texture_file_format,
            const char* horizontal_alignment,
            const char* vertical_alignment)
    {
        // If horizontal alignment is `"left"`, each line begins from the same x coordinate.
        // If horizontal alignment is `"left"` and vertical alignment is `"top"`,
        // then there is no need to check the text beforehand for newlines.
        // Otherwise newlines need to be checked beforehand.
        //
        // If horizontal alignment is right, each line ends in the same x coordinate.
        // Newlines need to be checked beforehand.
        uint32_t length = std::strlen(text_char);

        // Count the number of lines.
        uint32_t number_of_lines = 1;

        uint32_t i = 0;

        while (i < length)
        {
            char character = text_char[i++];

            if (character == (char) '\\')
            {
                // OK, this character was backslash, so read the next character.
                character = text_char[i++];

                if (character == 'n')
                {
                    number_of_lines++;
                }
            }
        }

        GLuint current_left_x;
        GLuint current_top_y;

        if (std::strcmp(horizontal_alignment, "left") == 0)
        {
            current_left_x = x;
        }
        else if (std::strcmp(horizontal_alignment, "center") == 0)
        {
            current_left_x = x - 0.5f * length * text_size;
        }
        else if (std::strcmp(horizontal_alignment, "right") == 0)
        {
            current_left_x = x - length * text_size;
        }

        if (std::strcmp(vertical_alignment, "top") == 0)
        {
            current_top_y = y;
        }
        else if (std::strcmp(vertical_alignment, "center") == 0)
        {
            current_top_y = y + 0.5f * number_of_lines * text_size;
        }
        else if (std::strcmp(vertical_alignment, "bottom") == 0)
        {
            current_top_y = y + number_of_lines * text_size;
        }

        // Fill buffers
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> UVs;

        i = 0;

        while (i < length)
        {
            // Print to the right side of X (so far there is no check for input length).
            // Print up of Y.
            GLfloat vertex_up_left_x;
            GLfloat vertex_up_left_y;
            GLfloat vertex_up_right_x;
            GLfloat vertex_up_right_y;
            GLfloat vertex_down_left_x;
            GLfloat vertex_down_left_y;
            GLfloat vertex_down_right_x;
            GLfloat vertex_down_right_y;

            char character = text_char[i++];

            if (character == (char) '\\')
            {
                // OK, this character was backslash, so read the next character.
                character = text_char[i++];

                if (character == 'n')
                {
                    // jump to the beginning of the next line.
                    // `"left"` horizontal alignment and `"top"` vertical alignment are assumed.
                    // TODO: implement newline for other horizontal and vertical alignments too!
                    current_left_x = x;
                    current_top_y -= text_size;
                    continue;
                }
            }

            vertex_up_left_x = vertex_down_left_x = current_left_x;
            vertex_up_right_x = vertex_down_right_x = current_left_x + text_size;
            current_left_x += text_size;

            vertex_down_left_y = vertex_down_right_y = current_top_y - text_size;
            vertex_up_left_y = vertex_up_right_y = current_top_y;

            glm::vec2 vertex_up_left = glm::vec2(vertex_up_left_x, vertex_up_left_y);
            glm::vec2 vertex_up_right = glm::vec2(vertex_up_right_x, vertex_up_right_y);
            glm::vec2 vertex_down_left = glm::vec2(vertex_down_left_x, vertex_down_left_y);
            glm::vec2 vertex_down_right = glm::vec2(vertex_down_right_x, vertex_down_right_y);

            vertices.push_back(vertex_up_left);
            vertices.push_back(vertex_down_left);
            vertices.push_back(vertex_up_right);

            vertices.push_back(vertex_down_right);
            vertices.push_back(vertex_up_right);
            vertices.push_back(vertex_down_left);

            float uv_x = (character % font_size) / (GLfloat) font_size;
            float uv_y;

            if ((std::strcmp(char_font_texture_file_format, "dds") == 0) || (std::strcmp(char_font_texture_file_format, "DDS") == 0))
            {
                uv_y = (character / font_size) / (GLfloat) font_size;
            }
            else if ((std::strcmp(char_font_texture_file_format, "bmp") == 0) || (std::strcmp(char_font_texture_file_format, "BMP") == 0))
            {
                // BMP is stored in the file beginning from the bottom line.
                uv_y = 1 - (character / font_size) / (GLfloat) font_size;
            }

            glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
            glm::vec2 uv_up_right = glm::vec2(uv_x + (1.0f / (GLfloat) font_size), uv_y);
            glm::vec2 uv_down_right;
            glm::vec2 uv_down_left;

            if ((std::strcmp(char_font_texture_file_format, "dds") == 0) || (std::strcmp(char_font_texture_file_format, "DDS") == 0))
            {
                uv_down_right = glm::vec2(uv_x + (1.0f / (GLfloat) font_size), (uv_y + 1.0f / (GLfloat) font_size));
                uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / (GLfloat) font_size));
            }
            else if ((std::strcmp(char_font_texture_file_format, "bmp") == 0) || (std::strcmp(char_font_texture_file_format, "BMP") == 0))
            {
                // BMP is stored in the file beginning from the bottom line.
                uv_down_right = glm::vec2(uv_x + (1.0f / (GLfloat) font_size), (uv_y - 1.0f / (GLfloat) font_size));
                uv_down_left = glm::vec2(uv_x, (uv_y - 1.0f / (GLfloat) font_size));
            }
            UVs.push_back(uv_up_left);
            UVs.push_back(uv_down_left);
            UVs.push_back(uv_up_right);

            UVs.push_back(uv_down_right);
            UVs.push_back(uv_up_right);
            UVs.push_back(uv_down_left);
        }

        glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
        glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

        // Bind shader
        glUseProgram(Text2DShaderID);

        // Bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
        // Set our "myTextureSampler" sampler to user Material Unit 0
        glUniform1i(Text2DUniformID, 0);

        // Set screen width.
        glUniform1i(screen_width_uniform_ID, screen_width);

        // Set screen height.
        glUniform1i(screen_height_uniform_ID, screen_height);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(vertexPosition_screenspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
        glVertexAttribPointer(vertexPosition_screenspaceID, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(vertexUVID);
        glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
        glVertexAttribPointer(vertexUVID, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Draw call
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisable(GL_BLEND);

        glDisableVertexAttribArray(vertexPosition_screenspaceID);
        glDisableVertexAttribArray(vertexUVID);
    }

    void Text2D::printText2D(PrintingStruct printing_struct)
    {
        if (printing_struct.text.empty())
        {
            printText2D(
                    printing_struct.screen_width,
                    printing_struct.screen_height,
                    printing_struct.x,
                    printing_struct.y,
                    printing_struct.text_size,
                    printing_struct.font_size,
                    printing_struct.text_char,
                    printing_struct.char_font_texture_file_format,
                    printing_struct.horizontal_alignment,
                    printing_struct.vertical_alignment);
        }
        else
        {
            printText2D(
                    printing_struct.screen_width,
                    printing_struct.screen_height,
                    printing_struct.x,
                    printing_struct.y,
                    printing_struct.text_size,
                    printing_struct.font_size,
                    printing_struct.text.c_str(),
                    printing_struct.char_font_texture_file_format,
                    printing_struct.horizontal_alignment,
                    printing_struct.vertical_alignment);
        }
    }

    void Text2D::printText2D(
            GLuint screen_width,
            GLuint screen_height,
            GLuint x,
            GLuint y,
            GLuint text_size,
            GLuint font_size,
            const char* text_char,
            const char* char_font_texture_file_format)
    {
        printText2D(screen_width, screen_height, x, y, text_size, font_size, text_char, char_font_texture_file_format, "left", "bottom");
    }
}
