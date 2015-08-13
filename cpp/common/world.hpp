#ifndef __WORLD_HPP_INCLUDED
#define __WORLD_HPP_INCLUDED

// Include standard headers
#include <iostream>
#include <vector>    // std::vector
#include <queue>     // std::queue

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

#include <iostream>
#include <vector>    // std::vector
#include <queue>     // std::queue
#include "globals.hpp"
#include "model_common_functions.hpp"
#include "model_templates.hpp"

namespace model
{
    class Shader;

    class World
    {
        public:
            // constructor.
            World();

            // destructor.
            ~World();

            // this method renders the entire world, one shader at a time.
            void render();

            friend class Shader;
            friend class Species;

        private:
            // this method sets a shader pointer.
            void set_shader_pointer(GLuint childID, void* parent_pointer);

            // this method sets a world species pointer.
            void set_world_species_pointer(void* world_species_pointer);

            void compute_matrices_from_inputs();

            void* world_species_pointer;              // pointer to world species (used in collision detection).

            std::vector<void*> shader_pointer_vector;
            std::queue<GLuint> free_shaderID_queue;
    };
}

#endif
