#ifndef __TEXTURE_HPP_INCLUDED
#define __TEXTURE_HPP_INCLUDED

#include "code/ylikuutio/common/globals.hpp"
#include "shader.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

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
    class Chunk;
}

namespace ontology
{
    class Species;
    class Object;
    class VectorFont;

    class Material
    {
        public:
            // constructor.
            Material(MaterialStruct material_struct);

            // destructor.
            ~Material();

            // this method sets pointer to this shader to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new shader.
            void bind_to_new_parent(ontology::Shader* new_shader_pointer);

            friend class Shader;
            friend class VectorFont;
            friend class Glyph;
            friend class Species;
            friend class Object;
            friend class space_partition::Chunk;
            template<class T1>
                friend void render_children(std::vector<T1>& child_pointer_vector);
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue);

        private:
            // this method renders all species using this texture.
            void render();

            // this method sets `Species` pointer.
            void set_species_pointer(uint32_t childID, ontology::Species* child_pointer);

            // this method sets `VectorFont` pointer.
            void set_vector_font_pointer(uint32_t childID, ontology::VectorFont* child_pointer);

            // this method sets `Chunk` pointer.
            void set_chunk_pointer(uint32_t childID, space_partition::Chunk* child_pointer);

            // this method sets a world species pointer.
            void set_terrain_species_pointer(ontology::Species* terrain_species_pointer);

            ontology::Shader* parent_pointer;         // pointer to the shader.

            void bind_to_parent();

            ontology::Species* terrain_species_pointer; // pointer to world species (used in collision detection).

            GLuint texture;                        // Texture of this `Material`, returned by `load_BMP_texture` or `load_DDS_texture` (used for `glGenTextures` etc.).
            GLuint openGL_textureID;               // texture ID, returned by `glGetUniformLocation(programID, "myTextureSampler");`.

            std::vector<ontology::Species*> species_pointer_vector;
            std::vector<ontology::VectorFont*> vector_font_pointer_vector;
            std::vector<space_partition::Chunk*> chunk_pointer_vector;
            std::queue<uint32_t> free_speciesID_queue;
            std::queue<uint32_t> free_vector_fontID_queue;
            std::queue<uint32_t> free_chunkID_queue;

            std::string texture_file_format;       // type of the model file, eg. `"bmp"`.
            std::string texture_filename;          // filename of the model file.
            uint32_t childID;                      // texture ID, returned by `Shader::get_textureID`.
            const char* char_texture_file_format;
            const char* char_texture_filename;
    };
}

#endif
