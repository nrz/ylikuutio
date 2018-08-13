#ifndef __TEXT3D_HPP_INCLUDED
#define __TEXT3D_HPP_INCLUDED

#include "movable.hpp"
#include "glyph_object_creation.hpp"
#include "vector_font.hpp"
#include "text3D_struct.hpp"
#include "object_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/common/globals.hpp"

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
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Entity;
        class Universe;
        class Object;

        class Text3D: public yli::ontology::Movable
        {
            public:
                void bind_object(yli::ontology::Object* const object);
                void unbind_object(const std::size_t childID);

                // this method deletes all glyph Objects of this `Text3D`,
                // sets pointer to this `Text3D` to nullptr,
                // sets `parent` according to the input (the new `VectorFont`),
                // requests a new `childID` from the new `VectorFont`,
                // and creates all glyph Objects of this `Text3D` with the font data.
                // Note: different fonts may provide glyphs for different Unicodes!
                void bind_to_new_parent(yli::ontology::VectorFont* const new_vector_font_pointer);

                // constructor.
                // TODO: `Text3D` constructor also creates each `Object`,
                // and binds each to its corresponding `Glyph` for rendering hierarchy,
                // and also binds each to this `Text3D` for ontological hierarchy.
                Text3D(yli::ontology::Universe* const universe, Text3DStruct& text3D_struct)
                    : yli::ontology::Movable(universe, text3D_struct.cartesian_coordinates)
                {
                    // constructor.
                    this->rotate_angle = NAN;
                    this->text_string = text3D_struct.text_string;
                    this->parent = text3D_struct.parent;

                    this->number_of_objects = 0;

                    // get childID from `VectorFont` and set pointer to this `Text3D`.
                    this->bind_to_parent();

                    std::cout << "Creating the glyph Objects for the string \"" << this->text_string << "\"\n";

                    // Let's create each glyph `Object` in a loop.

                    yli::ontology::create_glyph_objects(this->text_string, this);

                    this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
                    this->type = "yli::ontology::Text3D*";

                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~Text3D();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                friend class Object;
                friend void create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* text3D);
                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                std::string text_string;

                yli::ontology::VectorFont* parent; // pointer to `VectorFont`.

                glm::vec3 original_scale_vector;      // original scale vector.
                GLfloat rotate_angle;                 // rotate angle.
                glm::vec3 rotate_vector;              // rotate vector.
                glm::vec3 translate_vector;           // translate vector.

                std::vector<yli::ontology::Object*> object_pointer_vector;
                std::queue<std::size_t> free_objectID_queue;
                std::size_t number_of_objects;
        };
    }
}

#endif
