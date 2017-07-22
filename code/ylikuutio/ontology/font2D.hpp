#ifndef __FONT2D_HPP_INCLUDED
#define __FONT2D_HPP_INCLUDED

#include "entity.hpp"
#include "entity_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <string>    // std::string

namespace ontology
{
    class Universe;

    class Font2D: public ontology::Entity
    {
        public:
            // constructor.
            Font2D(
                    ontology::Universe* universe_pointer,
                    GLuint screen_width,
                    GLuint screen_height,
                    std::string texture_filename,
                    std::string font_texture_file_format);

            // destructor.
            ~Font2D();

            int32_t get_number_of_children() override;

            int32_t get_number_of_descendants() override;

            void printText2D(
                    GLuint screen_width,
                    GLuint screen_height,
                    GLuint x,
                    GLuint y,
                    GLuint text_size,
                    GLuint font_size,
                    const char* text_char,
                    const char* char_font_texture_file_format,
                    const char* horizontal_alignment,
                    const char* vertical_alignment);

            void printText2D(PrintingStruct printing_struct);

            void printText2D(
                    GLuint screen_width,
                    GLuint screen_height,
                    GLuint x,
                    GLuint y,
                    GLuint text_size,
                    GLuint font_size,
                    const char* text_char,
                    const char* char_font_texture_file_format);

            void set_name(std::string name);

            template<class T1>
                friend void set_name(std::string name, T1 entity);

        private:
            GLuint texture;      // Texture containing the glyphs, reterned by `load_BMP_texture` or `load_DDS_texture` (used for `glGenTextures` etc.).
            GLuint vertexbuffer; // Buffer containing the vertices
            GLuint uvbuffer;     // Buffer containing the UVs
            GLuint programID;    // The `programID` of the shader used to display the text, returned by `load_shaders`.
            GLuint vertex_position_in_screenspaceID; // Location of the program's `vertexPosition_screenspace` attribute.
            GLuint vertexUVID;                       // Location of the program's `vertexUV` attribute.
            GLuint Text2DUniformID;                  // Location of the program's texture attribute.
            GLuint screen_width_uniform_ID;          // Location of the program's window width uniform.
            GLuint screen_height_uniform_ID;         // Location of the program's window height uniform.

            ontology::Universe* universe_pointer;
    };
}

#endif
