#ifndef __FONT2D_HPP_INCLUDED
#define __FONT2D_HPP_INCLUDED

#include "entity.hpp"
#include "text_struct.hpp"
#include "code/ylikuutio/load/shader_loader.hpp"
#include "code/ylikuutio/load/texture_loader.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cstddef>   // std::size_t
#include <string>    // std::string

namespace yli
{
    namespace ontology
    {
        class Universe;

        class Font2D: public yli::ontology::Entity
        {
            public:
                // constructor.
                Font2D(
                        yli::ontology::Universe* const universe,
                        std::size_t screen_width,
                        std::size_t screen_height,
                        const std::string& texture_filename,
                        const std::string& font_texture_file_format)
                    : Entity(universe)
                {
                    // constructor.

                    // Initialize class members with some dummy values.
                    this->vertexbuffer                     = 0;
                    this->uvbuffer                         = 0;
                    this->programID                        = 0;
                    this->vertex_position_in_screenspaceID = 0;
                    this->vertexUVID                       = 0;
                    this->Text2DUniformID                  = 0;
                    this->screen_width_uniform_ID          = 0;
                    this->screen_height_uniform_ID         = 0;

                    // Initialize texture
                    if (font_texture_file_format == "bmp" || font_texture_file_format == "BMP")
                    {
                        if (!yli::load::load_BMP_texture(texture_filename, this->image_width, this->image_height, this->image_size, this->texture))
                        {
                            std::cerr << "ERROR: loading BMP texture failed!\n";
                        }
                    }
                    else if (font_texture_file_format == "dds" || font_texture_file_format == "DDS")
                    {
                        if (!yli::load::load_DDS_texture(texture_filename, this->image_width, this->image_height, this->image_size, this->texture))
                        {
                            std::cerr << "ERROR: loading DDS texture failed!\n";
                        }
                    }
                    else
                    {
                        std::cerr << "ERROR: invalid font texture file format: " << font_texture_file_format << "\n";
                        std::cerr << "supported font texture file formats: bmp, BMP, dds, DDS.\n";
                        this->texture = 0;
                        return;
                    }

                    // Initialize VBO
                    glGenBuffers(1, &vertexbuffer);
                    glGenBuffers(1, &uvbuffer);

                    // Initialize Shader
                    programID = yli::load::load_shaders("TextVertexShader.vertexshader", "TextVertexShader.fragmentshader");

                    // Get a handle for our buffers
                    vertex_position_in_screenspaceID = glGetAttribLocation(programID, "vertexPosition_screenspace");
                    vertexUVID = glGetAttribLocation(programID, "vertexUV");

                    // Initialize uniforms' IDs
                    Text2DUniformID = glGetUniformLocation(programID, "myTextureSampler");

                    // Initialize uniform window width.
                    screen_width_uniform_ID = glGetUniformLocation(programID, "screen_width");
                    glUniform1i(screen_width_uniform_ID, screen_width);

                    // Initialize uniform window height.
                    screen_height_uniform_ID = glGetUniformLocation(programID, "screen_height");
                    glUniform1i(screen_height_uniform_ID, screen_height);

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Font2D*";
                }

                // destructor.
                virtual ~Font2D();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                void printText2D(
                        std::size_t screen_width,
                        std::size_t screen_height,
                        std::size_t x,
                        std::size_t y,
                        std::size_t text_size,
                        std::size_t font_size,
                        const std::string text,
                        const std::string font_texture_file_format,
                        const std::string horizontal_alignment,
                        const std::string vertical_alignment) const;

                void printText2D(const TextStruct& text_struct);

                void printText2D(
                        std::size_t screen_width,
                        std::size_t screen_height,
                        std::size_t x,
                        std::size_t y,
                        std::size_t text_size,
                        std::size_t font_size,
                        const std::string text,
                        const std::string font_texture_file_format);

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

                std::size_t image_width;
                std::size_t image_height;
                std::size_t image_size;
        };
    }
}

#endif
