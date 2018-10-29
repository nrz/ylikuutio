#ifndef __FONT2D_HPP_INCLUDED
#define __FONT2D_HPP_INCLUDED

#include "entity.hpp"
#include "text_struct.hpp"
#include "code/ylikuutio/load/shader_loader.hpp"
#include "code/ylikuutio/load/texture_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cstddef>   // std::size_t
#include <string>    // std::string
#include <queue>     // std::queue
#include <vector>    // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;
        class Text2D;

        class Font2D: public yli::ontology::Entity
        {
            public:
                void bind_text2D(yli::ontology::Text2D* const text2D);
                void unbind_text2D(const std::size_t childID);

                // constructor.
                Font2D(
                        yli::ontology::Universe* const universe,
                        std::size_t screen_width,
                        std::size_t screen_height,
                        std::size_t text_size,
                        std::size_t font_size,
                        const std::string& texture_filename,
                        const std::string& font_texture_file_format)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent = universe;
                    this->screen_width = screen_width;
                    this->screen_height = screen_height;
                    this->font_texture_file_format = font_texture_file_format;
                    this->text_size = text_size;
                    this->font_size = font_size;

                    this->number_of_text2Ds = 0;

                    // get `childID` from `Universe` and set pointer to this `Font2D`.
                    this->bind_to_parent();

                    // Initialize class members with some dummy values.
                    this->vertexbuffer                     = 0;
                    this->uvbuffer                         = 0;
                    this->programID                        = 0;
                    this->vertex_position_in_screenspaceID = 0;
                    this->vertexUVID                       = 0;
                    this->Text2DUniformID                  = 0;
                    this->screen_width_uniform_ID          = 0;
                    this->screen_height_uniform_ID         = 0;
                    this->image_width                      = 0;
                    this->image_height                     = 0;
                    this->image_size                       = 0;

                    // Initialize texture
                    if (this->font_texture_file_format == "bmp" || this->font_texture_file_format == "BMP")
                    {
                        if (!yli::load::load_BMP_texture(texture_filename, this->image_width, this->image_height, this->image_size, this->texture))
                        {
                            std::cerr << "ERROR: loading BMP texture failed!\n";
                        }
                    }
                    else if (this->font_texture_file_format == "dds" || this->font_texture_file_format == "DDS")
                    {
                        if (!yli::load::load_DDS_texture(texture_filename, this->image_width, this->image_height, this->image_size, this->texture))
                        {
                            std::cerr << "ERROR: loading DDS texture failed!\n";
                        }
                    }
                    else
                    {
                        std::cerr << "ERROR: invalid font texture file format: " << this->font_texture_file_format << "\n";
                        std::cerr << "supported font texture file formats: bmp, BMP, dds, DDS.\n";
                        this->texture = 0;
                        return;
                    }

                    // Initialize VBO
                    glGenBuffers(1, &this->vertexbuffer);
                    glGenBuffers(1, &this->uvbuffer);

                    // Initialize Shader
                    this->programID = yli::load::load_shaders("TextVertexShader.vertexshader", "TextVertexShader.fragmentshader");

                    // Get a handle for our buffers
                    this->vertex_position_in_screenspaceID = glGetAttribLocation(this->programID, "vertexPosition_screenspace");
                    this->vertexUVID = glGetAttribLocation(this->programID, "vertexUV");

                    // Initialize uniforms' IDs
                    this->Text2DUniformID = glGetUniformLocation(this->programID, "myTextureSampler");

                    // Initialize uniform window width.
                    this->screen_width_uniform_ID = glGetUniformLocation(this->programID, "screen_width");
                    glUniform1i(this->screen_width_uniform_ID, this->screen_width);

                    // Initialize uniform window height.
                    this->screen_height_uniform_ID = glGetUniformLocation(this->programID, "screen_height");
                    glUniform1i(this->screen_height_uniform_ID, this->screen_height);

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Font2D*";
                }

                // destructor.
                virtual ~Font2D();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                std::size_t get_text_size() const;
                std::size_t get_font_size() const;
                const std::string& get_font_texture_file_format() const;
                GLuint get_programID() const;

                void prepare_to_print() const;

                void render();

                void print_text2D(
                        std::size_t x,
                        std::size_t y,
                        std::size_t text_size,
                        std::size_t font_size,
                        const std::string text,
                        const std::string font_texture_file_format,
                        const std::string horizontal_alignment,
                        const std::string vertical_alignment) const;

                void print_text2D(const TextStruct& text_struct) const;

                void print_text2D(
                        std::size_t x,
                        std::size_t y,
                        std::size_t text_size,
                        std::size_t font_size,
                        const std::string text,
                        const std::string font_texture_file_format) const;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Universe* parent; // pointer to the `Universe`.

                std::vector<yli::ontology::Text2D*> text2D_pointer_vector;
                std::queue<std::size_t> free_text2D_ID_queue;
                std::size_t number_of_text2Ds;

                GLuint texture;      // Texture containing the glyphs, reterned by `load_BMP_texture` or `load_DDS_texture` (used for `glGenTextures` etc.).
                GLuint vertexbuffer; // Buffer containing the vertices
                GLuint uvbuffer;     // Buffer containing the UVs
                GLuint programID;    // The `programID` of the shader used to display the text, returned by `load_shaders`.
                GLuint vertex_position_in_screenspaceID; // Location of the program's `vertexPosition_screenspace` attribute.
                GLuint vertexUVID;                       // Location of the program's `vertexUV` attribute.
                GLuint Text2DUniformID;                  // Location of the program's texture attribute.
                GLuint screen_width_uniform_ID;          // Location of the program's window width uniform.
                GLuint screen_height_uniform_ID;         // Location of the program's window height uniform.

                std::string font_texture_file_format;

                std::size_t screen_width;
                std::size_t screen_height;
                std::size_t image_width;
                std::size_t image_height;
                std::size_t image_size;
                std::size_t text_size;
                std::size_t font_size;
        };
    }
}

#endif
