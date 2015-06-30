#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

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

// Include matrix_transform.hpp .
#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#include "common/shader.hpp"
#include "common/texture.hpp"
#include "common/controls.hpp"
#include "common/model.hpp"
#include "common/vboindexer.hpp"
#include "common/text2D.hpp"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define TEXT_SIZE 40
#define FONT_SIZE 16

#define MAX_FPS 60

// font texture file format: bmp/...
std::string g_font_texture_file_format = "bmp";

// font texture filename.
// std::string g_font_texture_filename = "Holstein.DDS";
std::string g_font_texture_filename = "Holstein.bmp";

std::vector<model::Object> object_vector;

int main(void)
{
    // Initial position : on +Z
    position = glm::vec3(1.5f, 0.0f, 3.75f);
    // Initial horizontal angle : toward -Z
    horizontalAngle = -3.0f;
    // Initial vertical angle : none
    // verticalAngle = PI / 2;
    verticalAngle = 0.0f;
    // Initial Field of View
    initialFoV = 45.0f;

    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Several models", NULL, NULL);
    if (window == NULL)
    {
        fprintf (stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPos(window, (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2));

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // Create the world, store it in `my_world`.
    model::World *my_world = new model::World();

    // Create the shader, store it in 'my_shader`.
    ShaderStruct shader_struct;
    shader_struct.world_pointer = my_world;
    shader_struct.vertex_shader = "StandardShading.vertexshader";
    shader_struct.fragment_shader = "StandardShading.fragmentshader";
    model::Shader *my_shader = new model::Shader(shader_struct);

    // Create the species, store it in `suzanne_species`.
    SpeciesStruct species_struct;
    species_struct.shader_pointer = my_shader;
    species_struct.model_file_format = "obj";
    species_struct.model_filename = "suzanne.obj";
    species_struct.texture_file_format = "dds";
    species_struct.texture_filename = "uvmap.DDS";
    species_struct.vertex_shader = "StandardShading.vertexshader";
    species_struct.fragment_shader = "StandardShading.fragmentshader";
    species_struct.lightPos = glm::vec3(4, 4, 4);
    model::Species *suzanne_species = new model::Species(species_struct);

    // Create suzanne1, store it in `suzanne1`.
    ObjectStruct object_struct1;
    object_struct1.species_pointer = suzanne_species;
    object_struct1.coordinate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    model::Object *suzanne1 = new model::Object(object_struct1);

    // Create suzanne2, store it in `suzanne2`.
    ObjectStruct object_struct2;
    object_struct2.species_pointer = suzanne_species;
    object_struct2.coordinate_vector = glm::vec3(-1.0f, 0.0f, 0.0f);
    object_struct2.translate_vector = glm::vec3(0.1f, 0.0f, 0.0f);
    model::Object *suzanne2 = new model::Object(object_struct2);

    // Initialize our little text library with the Holstein font
    const char *char_g_font_texture_filename = g_font_texture_filename.c_str();
    const char *char_g_font_texture_file_format = g_font_texture_file_format.c_str();
    text2D::initText2D(WINDOW_WIDTH, WINDOW_HEIGHT, char_g_font_texture_filename, char_g_font_texture_file_format);

    // For speed computation
    double lastTime = glfwGetTime();
    double last_time_for_display_sync = glfwGetTime();
    int nbFrames = 0;

    do
    {
        // Measure speed
        double currentTime = glfwGetTime();

        if (currentTime - last_time_for_display_sync >= (1.0f / MAX_FPS))
        {
            last_time_for_display_sync = glfwGetTime();

            nbFrames++;

            if (currentTime - lastTime >= 1.0)
            {
                // If last `printf()` was more than 1 sec ago,
                // `printf` and reset.
                printf("%f ms/frame\n", 1000.0f/double(nbFrames));
                nbFrames = 0;
                lastTime += 1.0;
            }

            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render the world.
            my_world->render();

            glDisableVertexAttribArray(suzanne_species->vertexPosition_modelspaceID);
            glDisableVertexAttribArray(suzanne_species->vertexUVID);
            glDisableVertexAttribArray(suzanne_species->vertexNormal_modelspaceID);

            PrintingStruct printing_struct;
            printing_struct.screen_width = WINDOW_WIDTH;
            printing_struct.screen_height = WINDOW_HEIGHT;
            printing_struct.text_size = TEXT_SIZE;
            printing_struct.font_size = FONT_SIZE;
            printing_struct.char_font_texture_file_format = "bmp";

            char coordinates_text[256];
            sprintf(coordinates_text, "(%.2f,%.2f,%.2f) (%.2f,%.2f)", position.x, position.y, position.z, horizontalAngle, verticalAngle);

            // print cartesian coordinates on bottom left corner.
            printing_struct.x = 0;
            printing_struct.y = 0;
            printing_struct.text = coordinates_text;
            printing_struct.horizontal_alignment = "left";
            printing_struct.vertical_alignment = "bottom";
            text2D::printText2D(printing_struct);

            // Swap buffers
            glfwSwapBuffers(window);
        }

        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0);

    delete my_world;

    // Delete the text's VBO, the shader and the texture
    text2D::cleanupText2D();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
