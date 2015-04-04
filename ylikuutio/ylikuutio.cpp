// Include standard headers
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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

GLFWwindow* window;

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

#include <glm/gtc/matrix_transform.hpp>
using namespace std;

#include "common/shader.hpp"
#include "common/texture.hpp"
#include "common/globals.hpp"
#include "common/controls.hpp"
#include "common/bmploader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/text2D.hpp"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define TEXT_SIZE 40
#define FONT_SIZE 16

#define PI 3.14159265359f

// model file format: obj/bmp/...
// std::string g_model_file_format = "bmp";
std::string g_model_file_format = "bmp";

// model filename.
// std::string g_model_filename = "cube.obj";
// std::string g_model_filename = "oma_icosphere.obj";
// std::string g_model_filename = "kirjainkuutio.obj";
// std::string g_model_filename = "noise1024x1024.bmp";
std::string g_model_filename = "noise256x256.bmp";
// std::string g_model_filename = "noise128x128.bmp";

// texture file format: bmp/...
std::string g_texture_file_format = "bmp";

// color channel to use for height data.
// std::string g_height_data_color_channel = "red";
// std::string g_height_data_color_channel = "green";
// std::string g_height_data_color_channel = "blue";
std::string g_height_data_color_channel = "mean"; // "all" is equivalent to "mean".

// texture filename.
// std::string_g_texture_filename = "kuutio-uv-numerot.bmp";
// std::string g_texture_filename = "punamusta.bmp";
std::string g_texture_filename = "GrassGreenTexture0002.bmp";

// font texture file format: bmp/...
std::string g_font_texture_file_format = "bmp";

// font texture filename.
// std::string g_font_texture_filename = "Holstein.DDS";
std::string g_font_texture_filename = "Holstein.bmp";

int main(void)
{
    // Initial position : on +Z
    position = glm::vec3(100, 100, 100);
    // Initial horizontal angle : toward -Z
    horizontalAngle = 0.0f;
    // Initial vertical angle : none
    verticalAngle = PI / 2;
    // Initial Field of View
    initialFoV = 45.0f;

    // Initialise GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW.\n";
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context.
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ylikuutio", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW.
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW.\n";
        return -1;
    }

    // Ensure we can capture the escape key being pressed below.
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPos(window, (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2));

    // Dark blue background.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test.
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one.
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera.
    glEnable(GL_CULL_FACE);

    // Create and compile our GLSL program from the shaders.
    // GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
    GLuint programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");

    // Get a handle for our "MVP" uniform.
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

    // Get a handle for our buffers.
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
    GLuint vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

    // Load the texture.
    GLuint Texture;

    const char *char_g_texture_file_format = g_texture_file_format.c_str();
    const char *char_g_texture_filename = g_texture_filename.c_str();

    if ((strcmp(char_g_texture_file_format, "bmp") == 0) || (strcmp(char_g_texture_file_format, "BMP") == 0))
    {
        Texture = loadBMP_custom(char_g_texture_filename);
    }
    else
    {
        std::cerr << "no texture was loaded!\n";
        std::cerr << "texture file format: " << g_texture_file_format << "\n";
        return -1;
    }

    // Get a handle for our "myTextureSampler" uniform.
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

    // Read the model file.
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.

    bool model_loading_result = false;

    const char *char_g_model_file_format = g_model_file_format.c_str();
    const char *char_g_model_filename = g_model_filename.c_str();
    if ((strcmp(char_g_model_file_format, "obj") == 0) || (strcmp(char_g_model_file_format, "OBJ") == 0))
    {
        model_loading_result = load_OBJ(char_g_model_filename, vertices, uvs, normals);
    }
    else if ((strcmp(char_g_model_file_format, "bmp") == 0) || (strcmp(char_g_model_file_format, "BMP") == 0))
    {
        const char *char_g_height_data_color_channel = g_height_data_color_channel.c_str();
        model_loading_result = load_BMP_world(char_g_model_filename, vertices, uvs, normals, g_height_data_color_channel);
    }
    else
    {
        std::cerr << "no model was loaded!\n";
        std::cerr << "model file format: " << g_model_file_format << "\n";
        return -1;
    }

    if (!model_loading_result)
    {
        std::cerr << "model loading failed!\n";
        std::cerr << "model file format: " << g_model_file_format << "\n";
        std::cerr << "model file name: " << g_model_filename << "\n";
    }

    std::cout << "number of vertices: " << vertices.size() << ".\n";
    std::cout << "number of UVs: " << uvs.size() << ".\n";
    std::cout << "number of normals: " << normals.size() << ".\n";

    std::vector<GLuint> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;
    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
    std::cout << "number of indexed vertices: " << indexed_vertices.size() << ".\n";
    std::cout << "number of indexed UVs: " << indexed_uvs.size() << ".\n";
    std::cout << "number of indexed normals: " << indexed_normals.size() << ".\n";

    // Load it into a VBO.
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    // Initialize our little text library with the Holstein font
    const char *char_g_font_texture_filename = g_font_texture_filename.c_str();
    const char *char_g_font_texture_file_format = g_font_texture_file_format.c_str();
    initText2D(WINDOW_WIDTH, WINDOW_HEIGHT, char_g_font_texture_filename, char_g_font_texture_file_format);

    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    bool ms_frame_text_ready = false;

    do
    {
        // Measure speed
        char ms_frame_text[256];
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0)
        {
            // If last printf() was more than 1 sec ago
            // printf and reset
            sprintf(ms_frame_text, "%.02f ms/frame; %.02f Hz", 1000.0f / ((double) nbFrames), 1000.0f / (1000.0f / ((double) nbFrames)));
            ms_frame_text_ready = true;
            nbFrames = 0;
            lastTime += 1.0;
        }
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader.
        glUseProgram(programID);

        // Compute the MVP matrix from keyboard and mouse input.
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

        glm::vec3 lightPos = glm::vec3(4, 4, 4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

        // Bind our texture in Texture Unit 0.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set our "myTextureSampler" sampler to user Texture Unit 0.
        glUniform1i(TextureID, 0);

        // 1st attribute buffer : vertices.
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                vertexPosition_modelspaceID,  // The attribute we want to configure
                3,                            // size
                GL_FLOAT,                     // type
                GL_FALSE,                     // normalized?
                0,                            // stride
                (void*) 0                     // array buffer offset
                );

        // 2nd attribute buffer : UVs.
        glEnableVertexAttribArray(vertexUVID);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                vertexUVID,                   // The attribute we want to configure
                2,                            // size : U+V => 2
                GL_FLOAT,                     // type
                GL_FALSE,                     // normalized?
                0,                            // stride
                (void*) 0                     // array buffer offset
                );

        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(vertexNormal_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
                vertexNormal_modelspaceID,    // The attribute we want to configure
                3,                            // size
                GL_FLOAT,                     // type
                GL_FALSE,                     // normalized?
                0,                            // stride
                (void*) 0                     // array buffer offset
                );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        // Draw the triangles !
        glDrawElements(
                GL_TRIANGLES,    // mode
                indices.size(),  // count
                GL_UNSIGNED_INT, // type
                (void*) 0        // element array buffer offset
                );

        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glDisableVertexAttribArray(vertexUVID);
        glDisableVertexAttribArray(vertexNormal_modelspaceID);

        PrintingStruct printing_struct;
        printing_struct.screen_width = WINDOW_WIDTH;
        printing_struct.screen_height = WINDOW_HEIGHT;
        printing_struct.text_size = TEXT_SIZE;
        printing_struct.font_size = FONT_SIZE;
        printing_struct.char_font_texture_file_format = "bmp";

        char coordinates_text[256];
        sprintf(coordinates_text, "(%.2f,%.2f,%.2f) (%.2f,%.2f)", position.x, position.y, position.z, horizontalAngle, verticalAngle);

        char time_text[256];
        sprintf(time_text, "%.2f sec", glfwGetTime(), position.x, position.y, position.z);

        printing_struct.x = 0;
        printing_struct.y = 0;
        printing_struct.text = coordinates_text;
        printing_struct.horizontal_alignment = "left";
        printing_struct.vertical_alignment = "bottom";
        printText2D(printing_struct);

        printing_struct.x = 0;
        printing_struct.y = WINDOW_HEIGHT;
        printing_struct.text = time_text;
        printing_struct.horizontal_alignment = "left";
        printing_struct.vertical_alignment = "top";
        printText2D(printing_struct);

        if (ms_frame_text_ready)
        {
            printing_struct.x = WINDOW_WIDTH;
            printing_struct.y = WINDOW_HEIGHT;
            printing_struct.text = ms_frame_text;
            printing_struct.horizontal_alignment = "right";
            printing_struct.vertical_alignment = "top";
            printText2D(printing_struct);
        }

        // Swap buffers.
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while ((glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
            && (glfwWindowShouldClose(window) == 0));

    // Cleanup VBO, shader and texture.
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &Texture);

    // Delete the text's VBO, the shader and the texture
    cleanupText2D();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
