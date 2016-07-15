#ifndef __MODEL_HPP_INCLUDED
#define __MODEL_HPP_INCLUDED

// #include "material.hpp"
// #include "ground_level.hpp"
// #include "render_templates.hpp"
// #include "species_or_glyph.hpp"
// #include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

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

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Material;

    class Model
    {
        public:
            // constructor.
            Model();

            // destructor.
            ~Model();

            // this method sets a object pointer.
            void set_object_pointer(uint32_t childID, void* parent_pointer);

            // this method gets a object ID and removes it from the `free_objectID_queue` if it was popped from the queue.
            uint32_t get_objectID();

            std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
            glm::vec3 light_position;                // light position.

            uint32_t childID;                        // species ID, returned by `ontology::Material->get_speciesID()`.
            GLuint lightID;                          // light ID, returned by `glGetUniformLocation(programID, "LightPosition_worldspace");`.

            std::vector<void*> object_pointer_vector;
            std::queue<uint32_t> free_objectID_queue;

            std::string triangulation_type;

            GLuint vertexPosition_modelspaceID;
            GLuint vertexUVID;
            GLuint vertexNormal_modelspaceID;

            std::vector<glm::vec3> vertices;         // vertices of the object.
            std::vector<glm::vec2> UVs;              // UVs of the object.
            std::vector<glm::vec3> normals;          // normals of the object.

            std::vector<uint32_t> indices;           // the deleted vertices will be reused (though it is not required, if there's enough memory).
            std::vector<glm::vec3> indexed_vertices;
            std::vector<glm::vec2> indexed_UVs;
            std::vector<glm::vec3> indexed_normals;

            GLuint vertexbuffer;
            GLuint uvbuffer;
            GLuint normalbuffer;
            GLuint elementbuffer;
    };
}

#endif
