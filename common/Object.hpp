#ifndef __OBJECT_HPP_INCLUDED
#define __OBJECT_HPP_INCLUDED

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
#include "Species.hpp"

namespace model
{
    class Object
    {
        public:
            // constructor.
            Object(ObjectStruct object_struct);

            std::string model_file_format;         // type of the model file, eg. `"bmp"`.
            std::string model_filename;            // filename of the model file.
            std::string texture_file_format;       // type of the model file, eg. `"bmp"`.
            std::string texture_filename;          // filename of the model file.
            std::string color_channel;             // filename of fragment shader.
            glm::mat4 model_matrix;                // model matrix.
            glm::vec3 translate_vector;            // translate vector.
            glm::mat4 MVP_matrix;                  // model view projection matrix.

            // The rest fields are created in the constructor.
            std::vector<glm::vec3> vertices;       // vertices of the object.
            std::vector<glm::vec2> UVs;            // UVs of the object.
            std::vector<glm::vec3> normals;        // normals of the object. not used at the moment.
            GLuint programID;                      // shaders' programID, returned by `LoadShaders`.
            GLuint lightID;                        // light ID, returned by `glGetUniformLocation(programID, "LightPosition_worldspace");`.
            GLuint textureID;                      // texture ID, returned by `glGetUniformLocation(programID, "myTextureSampler");`.

        private:
            const char *char_model_file_format;
            const char *char_model_filename;
            const char *char_texture_file_format;
            const char *char_texture_filename;
    };
}

#endif
