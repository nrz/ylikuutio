#ifndef __TEXTURE_HPP_INCLUDED
#define __TEXTURE_HPP_INCLUDED

#include "entity.hpp"
#include "shader.hpp"
#include "material_struct.hpp"
#include "render_templates.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace space_partition
{
    class ChunkMaster;
}

namespace ontology
{
    class Species;
    class Object;
    class VectorFont;

    class Material: public ontology::Entity
    {
        public:
            // constructor.
            Material(const MaterialStruct material_struct);

            // destructor.
            virtual ~Material();

            // this method sets pointer to this `Material` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Shader`.
            void bind_to_new_parent(ontology::Shader* const new_shader_pointer);

            void set_name(const std::string& name);

            friend class Shader;
            friend class VectorFont;
            friend class Glyph;
            friend class Species;
            friend class Object;
            friend class space_partition::ChunkMaster;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void set_name(std::string name, T1 entity);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, int32_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, int32_t* old_number_of_children);

        private:
            void bind_to_parent();

            // this method renders all `Species` using this `Material`.
            void render();

            int32_t get_number_of_children() override;

            int32_t get_number_of_descendants() override;

            // this method sets `Species` pointer.
            void set_species_pointer(const int32_t childID, ontology::Species* const child_pointer);

            // this method sets `VectorFont` pointer.
            void set_vector_font_pointer(const int32_t childID, ontology::VectorFont* const child_pointer);

            // this method sets `ChunkMaster` pointer.
            void set_chunk_master_pointer(const int32_t childID, space_partition::ChunkMaster* const child_pointer);

            // this method sets a terrain `Species` pointer.
            void set_terrain_species_pointer(ontology::Species* const terrain_species_pointer);

            ontology::Shader* parent_pointer;      // pointer to `Shader`.

            ontology::Species* terrain_species_pointer; // pointer to terrain `Species` (used in collision detection).

            GLuint texture;                        // Texture of this `Material`, returned by `load_BMP_texture` or `load_DDS_texture` (used for `glGenTextures` etc.).
            GLuint openGL_textureID;               // texture ID, returned by `glGetUniformLocation(programID, "myTextureSampler");`.

            std::vector<ontology::Species*> species_pointer_vector;
            std::vector<ontology::VectorFont*> vector_font_pointer_vector;
            std::vector<space_partition::ChunkMaster*> chunk_master_pointer_vector;
            std::queue<int32_t> free_speciesID_queue;
            std::queue<int32_t> free_vector_fontID_queue;
            std::queue<int32_t> free_chunk_masterID_queue;
            int32_t number_of_species;
            int32_t number_of_vector_fonts;
            int32_t number_of_chunk_masters;

            std::string texture_file_format;       // type of the model file, eg. `"bmp"`.
            std::string texture_filename;          // filename of the model file.
            const char* char_texture_file_format;
            const char* char_texture_filename;
    };
}

#endif
