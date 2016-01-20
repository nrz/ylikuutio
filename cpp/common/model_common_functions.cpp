#include "model_common_functions.hpp"
#include "species.hpp"

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

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>     // NAN
#include <vector>    // std::vector

namespace model
{
    void set_child_pointer(GLuint childID, void* child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue)
    {
        child_pointer_vector[childID] = child_pointer;

        if (child_pointer == NULL)
        {
            if (childID == child_pointer_vector.size() - 1)
            {
                // OK, this is the biggest childID of all childID's of this 'object'.
                // We can reduce the size of the child pointer vector at least by 1.
                while ((!child_pointer_vector.empty()) && (child_pointer_vector.back() == NULL))
                {
                    // Reduce the size of child pointer vector by 1.
                    child_pointer_vector.pop_back();
                }
            }
        }
    }

    GLuint get_childID(std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue)
    {
        GLuint childID;

        while (!free_childID_queue.empty())
        {
            // return the first (oldest) free childID.
            childID = free_childID_queue.front();
            free_childID_queue.pop();

            // check that the child index does not exceed current child pointer vector.
            if (childID < child_pointer_vector.size())
            {
                // OK, it does not exceed current child pointer vector.
                return childID;
            }
        }
        // OK, the queue is empty.
        // A new child index must be created.
        childID = child_pointer_vector.size();

        // child pointer vector must also be extended with an appropriate NULL pointer.
        child_pointer_vector.push_back(NULL);

        return childID;
    }

    GLfloat get_ground_level(
            model::Species* terrain_species,
            glm::vec3 position)
    {
        if (!terrain_species->is_world)
        {
            // if the current species is not a world species, no collision detection to the ground will be performed.
            return NAN;
        }

        if ((position.x < 0.0f) || (position.x > terrain_species->image_width))
        {
            // if the x coordinate is out of range, no collision detection to the ground will be performed.
            return NAN;
        }

        if ((position.z < 0.0f) || (position.z > terrain_species->image_height))
        {
            // if the z coordinate is out of range, no collision detection to the ground will be performed.
            return NAN;
        }

        // compute the indices of closest vertices.
        GLuint southwest_i = (GLuint) floor(position.z) * terrain_species->image_width + floor(position.x);
        GLuint southeast_i = (GLuint) floor(position.z) * terrain_species->image_width + ceil(position.x);
        GLuint northwest_i = (GLuint) ceil(position.z) * terrain_species->image_width + floor(position.x);
        GLuint northeast_i = (GLuint) ceil(position.z) * terrain_species->image_width + ceil(position.x);

        // read closest the heights of closest integer coordinates to be used in bilinear interpolation.
        GLfloat southwest_height = terrain_species->vertices[southwest_i].y;
        GLfloat southeast_height = terrain_species->vertices[southeast_i].y;
        GLfloat northwest_height = terrain_species->vertices[northwest_i].y;
        GLfloat northeast_height = terrain_species->vertices[northeast_i].y;

        // these are not actually means but interpolations.
        // the result of the interpolation is mean if and only if (ceil(x) - x == 0.5) & (x - floor(x) == 0.5) , likewise for the z coordinate.
        GLfloat south_mean;
        GLfloat north_mean;
        GLfloat mean;

        if ((position.x - floor(position.x) < 0.01f) || (ceil(position.x) - position.x < 0.01f))
        {
            // if the x coordinate is too close to integer, the height of the closest vertex is used instead.
            south_mean = southwest_height;
            north_mean = northwest_height;
        }
        else
        {
            // the height is computed using bilinear interpolation.
            south_mean = (GLfloat) ((ceil(position.x) - position.x) * southwest_height) + ((position.x - floor(position.x)) * southeast_height);
            north_mean = (GLfloat) ((ceil(position.x) - position.x) * northwest_height) + ((position.x - floor(position.x)) * northeast_height);
        }

        if ((position.z - floor(position.z) < 0.01f) || (ceil(position.z) - position.z < 0.01f))
        {
            // if the z coordinate is too close to integer, the mean is used instead of bilinear interpolation.
            mean = (south_mean + north_mean) / 2.0f;
        }
        else
        {
            // the height is computed using bilinear interpolation.
            mean = (GLfloat) ((ceil(position.z) - position.z) * south_mean) + ((position.z - floor(position.z)) * north_mean);
        }

        return mean;
    }

    GLfloat get_floor_level(
            model::Species* terrain_species,
            glm::vec3 position)
    {
        if (!terrain_species->is_world)
        {
            // if the current species is not a world species, no collision detection to the ground will be performed.
            return NAN;
        }

#define CHARACTER_RADIUS 1.0f
        GLfloat current_ground_level = get_ground_level(terrain_species, position);

        // Get ground level at current location and +/- 1.0f.
        glm::vec3 south_position = position;
        south_position.z -= (GLfloat) CHARACTER_RADIUS;
        GLfloat south_ground_level = get_ground_level(terrain_species, south_position);

        glm::vec3 west_position = position;
        west_position.x -= (GLfloat) CHARACTER_RADIUS;
        GLfloat west_ground_level = get_ground_level(terrain_species, west_position);

        glm::vec3 north_position = position;
        north_position.z += (GLfloat) CHARACTER_RADIUS;
        GLfloat north_ground_level = get_ground_level(terrain_species, north_position);

        glm::vec3 east_position = position;
        east_position.x += (GLfloat) CHARACTER_RADIUS;
        GLfloat east_ground_level = get_ground_level(terrain_species, east_position);

        glm::vec3 southwest_position = south_position;
        southwest_position.x -= (GLfloat) CHARACTER_RADIUS;
        GLfloat southwest_ground_level = get_ground_level(terrain_species, southwest_position);

        glm::vec3 southeast_position = south_position;
        southeast_position.x += (GLfloat) CHARACTER_RADIUS;
        GLfloat southeast_ground_level = get_ground_level(terrain_species, southeast_position);

        glm::vec3 northwest_position = north_position;
        northwest_position.x -= (GLfloat) CHARACTER_RADIUS;
        GLfloat northwest_ground_level = get_ground_level(terrain_species, northwest_position);

        glm::vec3 northeast_position = north_position;
        northeast_position.x += (GLfloat) CHARACTER_RADIUS;
        GLfloat northeast_ground_level = get_ground_level(terrain_species, northeast_position);

        GLfloat temp_max_between_southwest_and_southeast = fmax(southwest_ground_level, southeast_ground_level);
        GLfloat temp_max_south = fmax(temp_max_between_southwest_and_southeast, south_ground_level);
        GLfloat temp_max_between_northwest_and_northeast = fmax(northwest_ground_level, northeast_ground_level);
        GLfloat temp_max_north = fmax(temp_max_between_northwest_and_northeast, north_ground_level);
        GLfloat temp_max_between_south_and_north = fmax(temp_max_south, temp_max_north);
        GLfloat temp_max_between_west_and_east = fmax(west_ground_level, east_ground_level);
        GLfloat temp_max_around_character = fmax(temp_max_between_south_and_north, temp_max_between_west_and_east);
        return fmax(temp_max_around_character, current_ground_level);
    }
}
