#ifndef __SPECIES_HPP_INCLUDED
#define __SPECIES_HPP_INCLUDED

#include "material.hpp"
#include "ground_level.hpp"
#include "render_templates.hpp"
#include "species_or_glyph.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

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
#include <string>    // std::string
#include <vector>    // std::vector
#include <queue>     // std::queue

namespace model
{
    class Material;

    class Species
    {
        public:
            // constructor.
            Species(SpeciesStruct species_struct);

            // destructor.
            ~Species();

            // this method sets pointer to this species to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new texture.
            void bind_to_new_parent(model::Material *new_texture_pointer);

            // this method sets a object pointer.
            void set_object_pointer(uint32_t childID, void* parent_pointer);

            // this method gets a object ID and removes it from the `free_objectID_queue` if it was popped from the queue.
            uint32_t get_objectID();

            bool is_world;                           // worlds currently do not rotate nor translate.

            std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
            glm::vec3 light_position;                // light position.

            friend class Object;
            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<void*> &old_child_pointer_vector, std::queue<uint32_t> &old_free_childID_queue);
            template<class T1>
                friend void render_species_or_glyph(T1 species_or_glyph_pointer);
            template<class T1>
                friend void render_this_object(model::Object* object_pointer, model::Shader* shader_pointer);
            friend GLfloat get_ground_level(model::Species* terrain_species, glm::vec3 position);

        private:
            void bind_to_parent();

            // this method renders all objects of this species.
            void render();

            std::string model_file_format;           // type of the model file, eg. `"bmp"`.
            std::string model_filename;              // filename of the model file.
            uint32_t childID;                        // species ID, returned by `model::Material->get_speciesID()`.
            GLuint lightID;                          // light ID, returned by `glGetUniformLocation(programID, "LightPosition_worldspace");`.
            const char* char_model_file_format;
            const char* char_model_filename;

            std::vector<void*> object_pointer_vector;
            std::queue<uint32_t> free_objectID_queue;

            std::string triangulation_type;

            uint32_t image_width;
            uint32_t image_height;

            model::Material *parent_pointer;         // pointer to the texture.

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
