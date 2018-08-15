#include "text3D.hpp"
#include "vector_font.hpp"
#include "object.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        class Object;

        void Text3D::bind_object(yli::ontology::Object* const object)
        {
            // get `childID` from `Text3d` and set pointer to `object`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Object*>(
                    object,
                    this->object_pointer_vector,
                    this->free_objectID_queue,
                    this->number_of_objects);
        }

        void Text3D::unbind_object(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->object_pointer_vector,
                    this->free_objectID_queue,
                    this->number_of_objects);
        }

        void Text3D::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::VectorFont* const vector_font = this->parent;

            if (vector_font == nullptr)
            {
                std::cerr << "ERROR: `Text3D::bind_to_parent`: `vector_font` is `nullptr`!\n";
                return;
            }

            // get `childID` from `VectorFont` and set pointer to this `Text3D`.
            vector_font->bind_text3D(this);
        }

        Text3D::~Text3D()
        {
            // destructor.
            std::cout << "This 3D text (\"" << this->text_string << "\", childID " << std::dec << this->childID << ") will be destroyed.\n";

            // destroy all objects of this `Text3D`.
            std::cout << "All objects (" << this->object_pointer_vector.size() << " pieces) of this 3D text will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Object*>(this->object_pointer_vector, this->number_of_objects);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::VectorFont* const vector_font = this->parent;

            if (vector_font == nullptr)
            {
                std::cerr << "ERROR: `Text3D::~Text3D`: `vector_font` is `nullptr`!\n";
                return;
            }

            vector_font->unbind_text3D(this->childID);
        }

        yli::ontology::Entity* Text3D::get_parent() const
        {
            return this->parent;
        }

        std::size_t Text3D::get_number_of_children() const
        {
            return this->number_of_objects;
        }

        std::size_t Text3D::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->object_pointer_vector);
        }
    }
}
