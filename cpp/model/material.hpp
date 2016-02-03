#ifndef __TEXTURE_HPP_INCLUDED
#define __TEXTURE_HPP_INCLUDED

#include "cpp/common/globals.hpp"
#include "shader.hpp"
#include "cpp/common/hierarchy.hpp"
#include "model_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <iostream>  // std::cout, std::cin, std::cerr
#include <string>    // std::string
#include <vector>    // std::vector
#include <queue>     // std::queue
#include <string.h>

namespace model
{
    class Species;
    class Object;

    class Material
    {
        public:
            // constructor.
            Material(MaterialStruct material_struct);

            // destructor.
            ~Material();

            // this method sets pointer to this shader to NULL, sets `parent_pointer` according to the input, and requests a new `childID` from the new shader.
            void bind_to_new_parent(model::Shader *new_shader_pointer);

            friend class Shader;
            friend class Font;
            friend class Glyph;
            friend class Species;
            friend class Object;
            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);
            template<class T1, class T2>
                friend void bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<void*> &old_child_pointer_vector, std::queue<GLuint> &old_free_childID_queue);

        private:
            // this method renders all species using this texture.
            void render();

            // this method sets a species pointer.
            void set_species_pointer(GLuint childID, void* parent_pointer);

            // this method sets a font pointer.
            void set_font_pointer(GLuint childID, void* parent_pointer);

            // this method sets a world species pointer.
            void set_terrain_species_pointer(model::Species* terrain_species_pointer);

            model::Shader *parent_pointer;         // pointer to the shader.

            void bind_to_parent();

            model::Species* terrain_species_pointer; // pointer to world species (used in collision detection).

            GLuint texture;                        // Material, returned by `load_DDS_texture` or `load_BMP_texture`.
            GLuint openGL_textureID;               // texture ID, returned by `glGetUniformLocation(programID, "myTextureSampler");`.

            std::vector<void*> species_pointer_vector;
            std::vector<void*> font_pointer_vector;
            std::queue<GLuint> free_speciesID_queue;
            std::queue<GLuint> free_fontID_queue;

            std::string texture_file_format;       // type of the model file, eg. `"bmp"`.
            std::string texture_filename;          // filename of the model file.
            GLuint childID;                      // texture ID, returned by `Shader::get_textureID`.
            const char* char_texture_file_format;
            const char* char_texture_filename;
    };
}

#endif
