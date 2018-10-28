#ifndef __TEXT2D_HPP_INCLUDED
#define __TEXT2D_HPP_INCLUDED

#include "entity.hpp"
#include "font2D.hpp"
#include "text_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace yli
{
    namespace ontology
    {
        class Universe;

        class Text2D: public yli::ontology::Entity
        {
            public:
                void bind_to_parent();

                // this method sets pointer to this `Text2D` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Font2D`.
                void bind_to_new_parent(yli::ontology::Font2D* const new_parent);

                // constructor.
                Text2D(yli::ontology::Universe* const universe, const TextStruct& text_struct)
                    : Entity(universe)
                {
                    this->parent = text_struct.font2D_parent;
                    this->text = text_struct.text;
                    this->horizontal_alignment = text_struct.horizontal_alignment;
                    this->vertical_alignment = text_struct.vertical_alignment;
                    this->screen_height = text_struct.screen_height;
                    this->screen_width = text_struct.screen_width;
                    this->x = text_struct.x;
                    this->y = text_struct.y;
                    this->text_size = text_struct.text_size;
                    this->font_size = text_struct.font_size;

                    // get `childID` from `Font2D` and set pointer to this `Text2D`.
                    this->bind_to_parent();

                    // Initialize class members with some dummy values.
                    this->vertexbuffer                     = 0;
                    this->uvbuffer                         = 0;
                    this->programID                        = 0;
                    this->vertex_position_in_screenspaceID = 0;
                    this->vertexUVID                       = 0;

                    // Initialize VBO
                    glGenBuffers(1, &this->vertexbuffer);
                    glGenBuffers(1, &this->uvbuffer);

                    // Get a handle for our buffers
                    this->vertex_position_in_screenspaceID = glGetAttribLocation(this->parent->get_programID(), "vertexPosition_screenspace");
                    this->vertexUVID = glGetAttribLocation(this->parent->get_programID(), "vertexUV");

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Text2D*";
                }

                // destructor.
                virtual ~Text2D();

                void render();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                void change_string(const std::string& text);

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                yli::ontology::Font2D* parent;

                GLuint vertexbuffer; // Buffer containing the vertices
                GLuint uvbuffer;     // Buffer containing the UVs
                GLuint programID;    // The `programID` of the shader used to display the text, returned by `load_shaders`.
                GLuint vertex_position_in_screenspaceID; // Location of the program's `vertexPosition_screenspace` attribute.
                GLuint vertexUVID;                       // Location of the program's `vertexUV` attribute.

                std::string text;
                std::string horizontal_alignment;
                std::string vertical_alignment;
                std::size_t screen_width;
                std::size_t screen_height;
                std::size_t x;
                std::size_t y;
                std::size_t text_size;
                std::size_t font_size;
        };
    }
}

#endif
