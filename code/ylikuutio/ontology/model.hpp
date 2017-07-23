#ifndef __MODEL_HPP_INCLUDED
#define __MODEL_HPP_INCLUDED

#include "entity.hpp"
#include "species_or_glyph.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

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

namespace space_partition
{
    class Chunk;
}

namespace ontology
{
    class Shader;
    class Material;
    class Species;
    class Object;

    class Model: public ontology::Entity
    {
        public:
            // constructor.
            Model();

            // destructor.
            ~Model();

            int32_t get_number_of_children() override;

            int32_t get_number_of_descendants() override;

            friend class Glyph;
            friend class Species;
            friend class Object;
            friend class space_partition::Chunk;
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue, int32_t* old_number_of_children);
            template<class T1>
                friend void render_species_or_glyph(T1 species_or_glyph_pointer);
            template<class T1>
                friend void render_this_object(ontology::Object* object_pointer, ontology::Shader* shader_pointer);
            friend GLfloat get_ground_level(ontology::Species* terrain_species, glm::vec3* position);

        private:
            // this method sets a object pointer.
            void set_object_pointer(uint32_t childID, ontology::Object* child_pointer);

            std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
            glm::vec3 light_position;                // light position.

            uint32_t childID;                        // species ID/text3D ID/glyph ID, set by corresponding `bind_to_parent()`.
            GLuint lightID;                          // light ID, returned by `glGetUniformLocation(programID, "LightPosition_worldspace");`.

            std::vector<ontology::Object*> object_pointer_vector;
            std::queue<uint32_t> free_objectID_queue;
            int32_t number_of_objects;

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
