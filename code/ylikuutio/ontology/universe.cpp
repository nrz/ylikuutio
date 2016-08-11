#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

#include "universe.hpp"
#include "scene.hpp"
#include "ground_level.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/global_variables.hpp"
#include "code/ylikuutio/common/globals.hpp"

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
    Universe::Universe(float world_radius)
    {
        // constructor.
        this->world_radius = world_radius;
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
        if (!is_flight_mode_in_use)
        {
            fallSpeed += gravity;
            position.y -= fallSpeed;
        }

        GLfloat FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

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

        if (testing_spherical_world_in_use)
        {
            // compute spherical coordinates.
            spherical_position.rho = sqrt((position.x * position.x) + (position.y * position.y) + (position.z * position.z));
            spherical_position.theta = RADIANS_TO_DEGREES(atan2(sqrt((position.x * position.x) + (position.y * position.y)), position.z));
            spherical_position.phi = RADIANS_TO_DEGREES(atan2(position.y, position.x));
        }

        camera_position = position;
        camera_position.y += 2.0f;

        // Projection matrix : 45° Field of View, aspect ratio, display range : 0.1 unit <-> 100 units
        ProjectionMatrix = glm::perspective(FoV, aspect_ratio, 0.001f, 5000.0f + 2.0f * static_cast<GLfloat>(this->world_radius));
        // Camera matrix
        ViewMatrix = glm::lookAt(
                camera_position,           // Camera is here
                camera_position+direction, // and looks here : at the same position, plus "direction"
                up                         // Head is up (set to 0,-1,0 to look upside-down)
                );
    }
}
