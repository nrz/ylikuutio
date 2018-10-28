#ifndef __TEXT2D_HPP_INCLUDED
#define __TEXT2D_HPP_INCLUDED

#include "entity.hpp"
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
        class Font2D;

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
                    this->x = text_struct.x;
                    this->y = text_struct.y;
                    this->text_size = text_struct.text_size;
                    this->font_size = text_struct.font_size;
                }

                // destructor.
                virtual ~Text2D();

                void render();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                yli::ontology::Font2D* parent;

                std::string text;
                std::string horizontal_alignment;
                std::string vertical_alignment;
                std::size_t x;
                std::size_t y;
                std::size_t text_size;
                std::size_t font_size;
        };
    }
}

#endif
