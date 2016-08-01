#ifndef __SPECIES_HPP_INCLUDED
#define __SPECIES_HPP_INCLUDED

#include "model.hpp"
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
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace ontology
{
    class Material;

    class Species: public ontology::Model
    {
        public:
            // constructor.
            Species(SpeciesStruct species_struct);

            // destructor.
            ~Species();

            // this method sets pointer to this species to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new texture.
            void bind_to_new_parent(ontology::Material* new_material_pointer);

            // this method sets a object pointer.
            void set_object_pointer(uint32_t childID, ontology::Object* child_pointer);

            // this method gets a object ID and removes it from the `free_objectID_queue` if it was popped from the queue.
            uint32_t get_objectID();

            bool is_world;                           // worlds currently do not rotate nor translate.

            std::string color_channel;               // color channel in use: `"red"`, `"green"`, `"blue"`, `"mean"` or `"all"`.
            glm::vec3 light_position;                // light position.

            friend class Object;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue);
            template<class T1>
                friend void render_species_or_glyph(T1 species_or_glyph_pointer);
            template<class T1>
                friend void render_this_object(ontology::Object* object_pointer, ontology::Shader* shader_pointer);
            friend GLfloat get_ground_level(ontology::Species* terrain_species, glm::vec3 position);

        private:
            void bind_to_parent();

            // this method renders all objects of this species.
            void render();

            ontology::Material* parent_pointer;         // pointer to the material.

            std::string model_file_format;           // type of the model file, eg. `"bmp"`.
            std::string model_filename;              // filename of the model file.

            const char* char_model_file_format;
            const char* char_model_filename;

            std::string triangulation_type;

            uint32_t image_width;
            uint32_t image_height;
    };
}

#endif
