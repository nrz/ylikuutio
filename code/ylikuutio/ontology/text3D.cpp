#include "text3D.hpp"
#include "vector_font.hpp"
#include "object.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        class Object;

        void Text3D::bind_to_parent()
        {
            // get `childID` from `VectorFont` and set pointer to this `Text3D`.
            this->parent->bind_text3D(this);
        }

        Text3D::~Text3D()
        {
            // destructor.
            std::cout << "This 3D text (\"" << this->text_string << "\", childID " << std::dec << this->childID << ") will be destroyed.\n";

            // destroy all objects of this `Text3D`.
            std::cout << "All objects (" << this->object_pointer_vector.size() << " pieces) of this 3D text will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Object*>(this->object_pointer_vector, &this->number_of_objects);

            this->parent->set_text3D_pointer(this->childID, nullptr);
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
            return 0; // TODO; write the code!
        }

        void Text3D::set_object_pointer(const std::size_t childID, yli::ontology::Object* const child_pointer)
        {
            yli::hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, &this->number_of_objects);
        }
    }
}
