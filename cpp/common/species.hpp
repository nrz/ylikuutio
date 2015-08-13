#ifndef __SPECIES_HPP_INCLUDED
#define __SPECIES_HPP_INCLUDED

// Include standard headers
#include <vector>    // std::vector
#include <queue>     // std::queue

#include "texture.hpp"
#include "model_common_functions.hpp"
#include "model_templates.hpp"
#include "species_or_glyph.hpp"

namespace model
{
    class Texture;

    class Species
    {
        public:
            // constructor.
            Species(SpeciesStruct species_struct);

            // destructor.
            ~Species();

            // this method sets pointer to this species to NULL, sets `parent_pointer` according to the input, and requests a new `childID` from the new texture.
            void bind_to_new_parent(model::Texture *new_texture_pointer);

            // this method sets a object pointer.
            void set_object_pointer(GLuint childID, void* parent_pointer);

            // this method gets a object ID and removes it from the `free_objectID_queue` if it was popped from the queue.
            GLuint get_objectID();

            bool is_world;                           // worlds currently do not rotate nor translate.

            std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
            glm::vec3 light_position;                // light position.

            // The rest fields are created in the constructor.
            GLuint image_width;
            GLuint image_height;

            GLuint vertexPosition_modelspaceID;
            GLuint vertexUVID;
            GLuint vertexNormal_modelspaceID;

            std::vector<glm::vec3> vertices;         // vertices of the object.
            std::vector<glm::vec2> UVs;              // UVs of the object.
            std::vector<glm::vec3> normals;          // normals of the object.

            std::vector<GLuint> indices;             // the deleted vertices will be reused (though it is not required, if there's enough memory).
            std::vector<glm::vec3> indexed_vertices;
            std::vector<glm::vec2> indexed_UVs;
            std::vector<glm::vec3> indexed_normals;

            GLuint vertexbuffer;
            GLuint uvbuffer;
            GLuint normalbuffer;
            GLuint elementbuffer;

            model::Texture *parent_pointer;          // pointer to the texture.

            friend class Object;
            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);
            template<class T1, class T2>
                friend void bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<void*> &old_child_pointer_vector, std::queue<GLuint> &old_free_childID_queue);
            template<class T1>
                friend void render_species_or_glyph(T1 species_or_glyph_pointer);

        private:
            void bind_to_parent();

            // this method renders all objects of this species.
            void render();

            std::string model_file_format;           // type of the model file, eg. `"bmp"`.
            std::string model_filename;              // filename of the model file.
            GLuint childID;                          // species ID, returned by `model::Texture->get_speciesID()`.
            GLuint lightID;                          // light ID, returned by `glGetUniformLocation(programID, "LightPosition_worldspace");`.
            const char *char_model_file_format;
            const char *char_model_filename;
            const char *char_color_channel;

            std::vector<void*> object_pointer_vector;
            std::queue<GLuint> free_objectID_queue;
    };
}

#endif
