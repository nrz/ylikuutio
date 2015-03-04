#include <vector>
#include <cstring>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "texture.hpp"
#include "text2D.hpp"

GLuint Text2DTextureID;              // Texture containing the font
GLuint Text2DVertexBufferID;         // Buffer containing the vertices
GLuint Text2DUVBufferID;             //                       UVs
GLuint Text2DShaderID;               // Program used to disaply the text
GLuint vertexPosition_screenspaceID; // Location of the program's "vertexPosition_screenspace" attribute
GLuint vertexUVID;                   // Location of the program's "vertexUV" attribute
GLuint Text2DUniformID;              // Location of the program's texture attribute
GLuint screen_width_uniform_ID;      // Location of the program's window width uniform.
GLuint screen_height_uniform_ID;     // Location of the program's window height uniform.

void initText2D(
        GLuint screen_width,
        GLuint screen_height,
        const char *texturePath,
        const char *char_font_texture_file_format)
{
    // Initialize texture
    if ((strcmp(char_font_texture_file_format, "bmp") == 0) || (strcmp(char_font_texture_file_format, "BMP") == 0))
    {
        Text2DTextureID = loadBMP_custom(texturePath);
    }
    else if ((strcmp(char_font_texture_file_format, "dds") == 0) || (strcmp(char_font_texture_file_format, "DDS") == 0))
    {
        Text2DTextureID = loadDDS(texturePath);
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

void printText2D(
        GLuint screen_width,
        GLuint screen_height,
        GLuint x,
        GLuint y,
        GLuint text_size,
        GLuint font_size,
        const char *text,
        const char *char_font_texture_file_format,
        const char *horizontal_alignment,
        const char *vertical_alignment)
{
    uint32_t length = strlen(text);

    // Fill buffers
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UVs;
    for (uint32_t i = 0; i < length; i++)
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

        if (strcmp(horizontal_alignment, "left") == 0)
        {
            vertex_up_left_x  = vertex_down_left_x  = x + (i * text_size);
            vertex_up_right_x = vertex_down_right_x = x + (i * text_size + text_size);
        }
        else if (strcmp(horizontal_alignment, "right") == 0)
        {
            vertex_up_left_x  = vertex_down_left_x  = x - (length * text_size) + (i * text_size);
            vertex_up_right_x = vertex_down_right_x = x - (length * text_size) + (i * text_size + text_size);
        }
        else if (strcmp(horizontal_alignment, "center") == 0)
        {
        }

        if (strcmp(vertical_alignment, "bottom") == 0)
        {
            vertex_down_left_y = vertex_down_right_y = y;
            vertex_up_left_y   = vertex_up_right_y   = y + text_size;
        }
        else if (strcmp(vertical_alignment, "top") == 0)
        {
        }
        else if (strcmp(vertical_alignment, "center") == 0)
        {
        }

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

        char character = text[i];
        float uv_x = (character % font_size) / (GLfloat) font_size;
        float uv_y;

        if ((strcmp(char_font_texture_file_format, "dds") == 0) || (strcmp(char_font_texture_file_format, "DDS") == 0))
        {
            uv_y = (character / font_size) / (GLfloat) font_size;
        }
        else if ((strcmp(char_font_texture_file_format, "bmp") == 0) || (strcmp(char_font_texture_file_format, "BMP") == 0))
        {
            // BMP is stored in the file beginning from the bottom line.
            uv_y = 1 - (character / font_size) / (GLfloat) font_size;
        }

        glm::vec2 uv_up_left    = glm::vec2(uv_x                 , uv_y);
        glm::vec2 uv_up_right   = glm::vec2(uv_x + (1.0f / (GLfloat) font_size), uv_y);
        glm::vec2 uv_down_right;
        glm::vec2 uv_down_left;
        if ((strcmp(char_font_texture_file_format, "dds") == 0) || (strcmp(char_font_texture_file_format, "DDS") == 0))
        {
            uv_down_right = glm::vec2(uv_x + (1.0f / (GLfloat) font_size), (uv_y + 1.0f / (GLfloat) font_size));
            uv_down_left  = glm::vec2(uv_x                               , (uv_y + 1.0f / (GLfloat) font_size));
        }
        else if ((strcmp(char_font_texture_file_format, "bmp") == 0) || (strcmp(char_font_texture_file_format, "BMP") == 0))
        {
            // BMP is stored in the file beginning from the bottom line.
            uv_down_right = glm::vec2(uv_x + (1.0f / (GLfloat) font_size), (uv_y - 1.0f / (GLfloat) font_size));
            uv_down_left  = glm::vec2(uv_x                               , (uv_y - 1.0f / (GLfloat) font_size));
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
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(Text2DUniformID, 0);

    // Set screen width.
    glUniform1i(screen_width_uniform_ID, screen_width);

    // Set screen height.
    glUniform1i(screen_height_uniform_ID, screen_height);

    // 1rst attribute buffer : vertices
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

void printText2D(
        GLuint screen_width,
        GLuint screen_height,
        GLuint x,
        GLuint y,
        GLuint text_size,
        GLuint font_size,
        const char *text,
        const char *char_font_texture_file_format)
{
    printText2D(screen_width, screen_height, x, y, text_size, font_size, text, char_font_texture_file_format, "left", "bottom");
}

void cleanupText2D()
{
    // Delete buffers
    glDeleteBuffers(1, &Text2DVertexBufferID);
    glDeleteBuffers(1, &Text2DUVBufferID);

    // Delete texture
    glDeleteTextures(1, &Text2DTextureID);

    // Delete shader
    glDeleteProgram(Text2DShaderID);
}
