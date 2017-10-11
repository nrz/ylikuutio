#include "text3D.hpp"
#include "object.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace ontology
{
    class Object;

    void Text3D::bind_to_parent()
    {
        // get `childID` from `VectorFont` and set pointer to this `Text3D`.
        hierarchy::bind_child_to_parent<ontology::Text3D*>(this, this->parent_pointer->text3D_pointer_vector, this->parent_pointer->free_text3D_ID_queue, &this->parent_pointer->number_of_text3Ds);
    }

    Text3D::~Text3D()
    {
        // destructor.
        std::cout << "This 3D text (\"" << this->text_string << "\", childID " << std::dec << this->childID << ") will be destroyed.\n";

        // destroy all objects of this `Text3D`.
        std::cout << "All objects (" << this->object_pointer_vector.size() << " pieces) of this 3D text will be destroyed.\n";
        hierarchy::delete_children<ontology::Object*>(this->object_pointer_vector, &this->number_of_objects);

        this->parent_pointer->set_text3D_pointer(this->childID, nullptr);
    }

    ontology::Entity* Text3D::get_parent()
    {
        return this->parent_pointer;
    }

    int32_t Text3D::get_number_of_children()
    {
        return this->number_of_objects;
    }

    int32_t Text3D::get_number_of_descendants()
    {
        return -1;
    }

    void Text3D::set_object_pointer(const int32_t childID, ontology::Object* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, &this->number_of_objects);
    }

    void Text3D::set_name(const std::string& name)
    {
        ontology::set_name(name, this);
    }
}
