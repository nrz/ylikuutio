#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "universe.hpp"
#include "scene.hpp"
#include "ground_level.hpp"
#include "render_templates.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "cpp/ylikuutio/common/global_variables.hpp"
#include "cpp/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

namespace ontology
{
    Universe::Universe()
    {
        // constructor.
    }

    Universe::~Universe()
    {
        // destructor.
        std::cout << "This world will be destroyed.\n";

        // destroy all scenes of this world.
        std::cout << "All scenes of this world will be destroyed.\n";
        hierarchy::delete_children<ontology::Scene*>(this->scene_pointer_vector);
    }

    void Universe::render()
    {
        this->compute_matrices_from_inputs();

        // render Universe by calling `render()` function of each Scene.
        ontology::render_children<ontology::Scene*>(this->scene_pointer_vector);
    }

    void Universe::set_scene_pointer(uint32_t childID, ontology::Scene* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->scene_pointer_vector, this->free_sceneID_queue);
    }

    void Universe::set_terrain_species_pointer(ontology::Species* terrain_species_pointer)
    {
        this->terrain_species_pointer = terrain_species_pointer;
    }

    void Universe::compute_matrices_from_inputs()
    {
        if (std::isnan(lastTime))
        {
            // `glfwGetTime()` is called here only once, the first time this function is called.
            lastTime = glfwGetTime();
        }

        // Compute time difference between current and last frame
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);

        // Get mouse position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Reset mouse position for next frame
        glfwSetCursorPos(window, window_width / 2, window_height / 2);

        if (hasMouseEverMoved || (abs(xpos) > 0.0001) || (abs(ypos) > 0.0001))
        {
            hasMouseEverMoved = true;

            // Compute new orientation
            horizontalAngle += mouseSpeed * GLfloat(window_width / 2 - xpos);
            horizontalAngle = remainder(horizontalAngle, (2.0f * PI));

            if (is_invert_mouse_in_use)
            {
                // invert mouse.
                verticalAngle   -= mouseSpeed * GLfloat(window_height / 2 - ypos);
            }
            else
            {
                // don't invert mouse.
                verticalAngle   += mouseSpeed * GLfloat(window_height / 2 - ypos);
            }
            verticalAngle = remainder(verticalAngle, (2.0f * PI));
        }

        // Direction : Spherical coordinates to Cartesian coordinates conversion
        glm::vec3 direction = glm::vec3(
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
            position.z -= deltaTime * temp_speed;
        }

        // Move south.
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            position.z += deltaTime * temp_speed;
        }

        // Help mode on.
        if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        {
            if (is_key_F1_released)
            {
                if (in_help_mode)
                {
                    in_help_mode = false;
                }
                else
                {
                    in_help_mode = true;
                }
                is_key_F1_released = false;
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE)
        {
            is_key_F1_released = true;
        }

        // Flight mode on.
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
            if (is_key_F_released)
            {
                is_flight_mode_in_use = (is_flight_mode_in_use ? false : true);
                fallSpeed = 0.0f;
                is_key_F_released = false;
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
        {
            is_key_F_released = true;
        }

        if (!is_flight_mode_in_use)
        {
            fallSpeed += gravity;
            position.y -= fallSpeed;
        }

        GLfloat FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        {
            if (is_key_I_released)
            {
                is_invert_mouse_in_use = (is_invert_mouse_in_use ? false : true);
                is_key_I_released = false;
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_RELEASE)
        {
            is_key_I_released = true;
        }

        // adjust position according to the ground.
        if (!is_flight_mode_in_use)
        {
            if (this->terrain_species_pointer != nullptr)
            {
                GLfloat ground_y = ontology::get_floor_level(static_cast<ontology::Species*>(this->terrain_species_pointer), position);

                if (!std::isnan(ground_y))
                {
                    if (position.y < ground_y)
                    {
                        position.y = ground_y;
                        fallSpeed = 0.0f;
                    }
                }
            }
        }

#ifdef TESTING_SPHERICAL_WORLD_IN_USE
        // compute spherical coordinates.
        spherical_position.rho = sqrt((position.x * position.x) + (position.y * position.y) + (position.z * position.z));
        spherical_position.theta = RADIANS_TO_DEGREES(atan2(sqrt((position.x * position.x) + (position.y * position.y)), position.z));
        spherical_position.phi = RADIANS_TO_DEGREES(atan2(position.y, position.x));
#endif

        earth_radius = EARTH_RADIUS;

        camera_position = position;
        camera_position.y += 2.0f;

        // Projection matrix : 45° Field of View, aspect ratio, display range : 0.1 unit <-> 100 units
        ProjectionMatrix = glm::perspective(FoV, aspect_ratio, 0.001f, 5000.0f + 2.0f * (GLfloat) earth_radius);
        // Camera matrix
        ViewMatrix = glm::lookAt(
                camera_position,           // Camera is here
                camera_position+direction, // and looks here : at the same position, plus "direction"
                up                         // Head is up (set to 0,-1,0 to look upside-down)
                );

        // For the next frame, the "last time" will be "now"
        lastTime = currentTime;
    }
}
