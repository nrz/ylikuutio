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

#include "globals.hpp"

extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#ifndef __COMMON_GLOBALS_HPP_INCLUDED
#define __COMMON_GLOBALS_HPP_INCLUDED
#include "common/globals.hpp"
#endif

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

namespace controls
{
    glm::mat4 getViewMatrix()
    {
        return ViewMatrix;
    }

    glm::mat4 getProjectionMatrix()
    {
        return ProjectionMatrix;
    }

    GLfloat speed = 5.0f; // 5 units / second
    GLfloat turbo_factor = 5.0f;
    GLfloat twin_turbo_factor = 1000.0f;
    GLfloat mouseSpeed = 0.005f;

    void computeMatricesFromInputs()
    {
        // glfwGetTime is called only once, the first time this function is called
        static double lastTime = glfwGetTime();

        // Compute time difference between current and last frame
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);

        // Get mouse position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Reset mouse position for next frame
        glfwSetCursorPos(window, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

        if (hasMouseEverMoved || (abs(xpos) > 0.0001) || (abs(ypos) > 0.0001))
        {
            hasMouseEverMoved = true;

            // Compute new orientation
            horizontalAngle += mouseSpeed * GLfloat(WINDOW_WIDTH/2 - xpos);

            if (is_invert_mouse_in_use)
            {
                // invert mouse.
                verticalAngle   -= mouseSpeed * GLfloat(WINDOW_HEIGHT/2 - ypos);
            }
            else
            {
                // don't invert mouse.
                verticalAngle   += mouseSpeed * GLfloat(WINDOW_HEIGHT/2 - ypos);
            }
        }

        // Direction : Spherical coordinates to Cartesian coordinates conversion
        glm::vec3 direction(
                cos(verticalAngle) * sin(horizontalAngle),
                sin(verticalAngle),
                cos(verticalAngle) * cos(horizontalAngle)
                );

        // Right vector
        glm::vec3 right = glm::vec3(
                sin(horizontalAngle - PI/2.0f),
                0,
                cos(horizontalAngle - PI/2.0f)
                );

        // Up vector
        glm::vec3 up = glm::cross(right, direction);

        GLfloat temp_speed;

        // Turbo.
        if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
        {
            temp_speed = twin_turbo_factor * speed;
        }
        else if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
        {
            temp_speed = turbo_factor * speed;
        }
        else
        {
            temp_speed = speed;
        }

        // Move forward
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            position += direction * deltaTime * temp_speed;
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            position -= direction * deltaTime * temp_speed;
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            position += right * deltaTime * temp_speed;
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            position -= right * deltaTime * temp_speed;
        }

        // Move up.
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            position.y += deltaTime * temp_speed;
        }

        // Move down.
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            position.y -= deltaTime * temp_speed;
        }

        // Move west.
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            position.x -= deltaTime * temp_speed;
        }

        // Move east.
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            position.x += deltaTime * temp_speed;
        }

        // Move north.
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        {
            position.z += deltaTime * temp_speed;
        }

        // Move south.
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            position.z -= deltaTime * temp_speed;
        }

        GLfloat FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        {
            if (is_key_I_released)
            {
                if (is_invert_mouse_in_use)
                {
                    is_invert_mouse_in_use = false;
                }
                else
                {
                    is_invert_mouse_in_use = true;
                }
            }
        }
        else
        {
            is_key_I_released = true;
        }

        earth_radius = EARTH_RADIUS;

        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 5000.0f + EARTH_RADIUS);
        // Camera matrix
        ViewMatrix = glm::lookAt(
                position,           // Camera is here
                position+direction, // and looks here : at the same position, plus "direction"
                up                  // Head is up (set to 0,-1,0 to look upside-down)
                );

        // For the next frame, the "last time" will be "now"
        lastTime = currentTime;
    }
}
