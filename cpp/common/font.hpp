#ifndef __FONT_HPP_INCLUDED
#define __FONT_HPP_INCLUDED

#include <iostream>
#include <queue>     // std::queue

#include "globals.hpp"
#include "model_common_functions.hpp"
#include "model_templates.hpp"
#include "texture.hpp"

namespace model
{
    class Texture;

    class Font
    {
        public:
            // constructor.
            Font(FontStruct font_struct);

            // destructor.
            ~Font();

            // this method sets a glyph pointer.
            void set_glyph_pointer(GLuint childID, void* parent_pointer);

            // this method sets pointer to this species to NULL, sets `parent_pointer` according to the input, and requests a new `childID` from the new texture.
            void bind_to_new_parent(model::Texture *new_texture_pointer);

            // The rest fields are created in the constructor.
            GLuint image_width;
            GLuint image_height;

            model::Texture *parent_pointer;       // pointer to the texture.

            template<class T1>
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);

        private:
            void bind_to_parent();

            // this method renders all objects of this species.
            void render();

            std::string font_file_format;          // type of the model file, eg. `"bmp"`.
            std::string font_filename;             // filename of the model file.
            GLuint childID;                        // species ID, returned by `model::Texture->get_speciesID()`.
            GLuint lightID;                        // light ID, returned by `glGetUniformLocation(programID, "LightPosition_worldspace");`.
            const char *char_font_file_format;
            const char *char_font_filename;

            std::vector<void*> glyph_pointer_vector;
            std::queue<GLuint> free_glyphID_queue;
    };
}

#endif
