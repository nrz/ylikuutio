#include "text3D.hpp"
#include "vector_font.hpp"
#include "object.hpp"
#include "object_struct.hpp"
#include "text3D_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace ontology
{
    void Text3D::bind_to_parent()
    {
        // get `childID` from `VectorFont` and set pointer to this `Text3D`.
        hierarchy::bind_child_to_parent<ontology::Text3D*>(this, this->parent_pointer->text3D_pointer_vector, this->parent_pointer->free_text3D_ID_queue, &this->parent_pointer->number_of_text3Ds);
    }

    // constructor.
    // TODO: `Text3D` constructor also creates each `Object`,
    // and binds each to its corresponding `Glyph` for rendering hierarchy,
    // and also binds each to this `Text3D` for ontological hierarchy.
    Text3D::Text3D(const Text3DStruct text3D_struct)
    {
        // constructor.
        this->text_string = text3D_struct.text_string;
        this->parent_pointer = text3D_struct.parent_pointer;
        this->universe_pointer = this->parent_pointer->universe_pointer;

        this->number_of_objects = 0;

        // get childID from `VectorFont` and set pointer to this `Text3D`.
        this->bind_to_parent();

        std::cout << "Creating the glyph Objects for the string \"" << this->text_string << "\"\n";

        // Let's create each glyph `Object` in a loop.

        const char* text_pointer = this->text_string.c_str();

        while (*text_pointer != '\0')
        {
            int32_t unicode_value = string::extract_unicode_value_from_string(text_pointer);
            ontology::Glyph* glyph_pointer = this->parent_pointer->get_glyph_pointer(unicode_value);

            if (!glyph_pointer)
            {
                // nullptr, so skip this character.
                std::cerr << "Error: no matching Glyph found for unicode_value 0x" << std::hex << unicode_value << "\n";
                continue;
            }

            std::cout << "Creating the glyph Object for unicode_value 0x" << std::hex << unicode_value << "\n";

            ObjectStruct object_struct;
            object_struct.glyph_parent_pointer = glyph_pointer;
            object_struct.text3D_parent_pointer = this;
            object_struct.original_scale_vector = this->original_scale_vector;
            object_struct.rotate_angle = this->rotate_angle;
            object_struct.is_character = true;
            object_struct.coordinate_vector = this->coordinate_vector; // TODO: adjust this as needed.
            object_struct.rotate_vector = this->rotate_vector;
            ontology::Object* object = new ontology::Object(object_struct);
        }

        // TODO: Add support for Unicode strings.

        // TODO: go through `text_string`.

        // TODO: extract Unicode.
        //
        // TODO: If the Unicode exists in the hash map, create the corresponding glyph `Object`.
        //       If not, continue from the next Unicode of `text_string`.

        this->child_vector_pointers_vector.push_back(&this->object_pointer_vector);
    }

    Text3D::~Text3D()
    {
        // destructor.
        std::cout << "This 3D text (\"" << this->text_string << "\", childID " << std::dec << this->childID << ") will be destroyed.\n";

        // destroy all objects of this `Text3D`.
        std::cout << "All objects (" << this->object_pointer_vector.size() << " pieces) of this 3D text will be destroyed.\n";
        hierarchy::delete_children<ontology::Object*>(this->object_pointer_vector, &this->number_of_objects);

        this->parent_pointer->set_text3D_pointer(this->childID, nullptr);

        if (!this->name.empty() && this->universe_pointer != nullptr)
        {
            delete this->universe_pointer->entity_anyvalue_map[this->name];
            this->universe_pointer->entity_anyvalue_map[this->name] = nullptr;
        }
    }

    int32_t Text3D::get_number_of_children()
    {
        return this->number_of_objects;
    }

    int32_t Text3D::get_number_of_descendants()
    {
        return -1;
    }

    void Text3D::set_object_pointer(const uint32_t childID, ontology::Object* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue, &this->number_of_objects);
    }

    void Text3D::set_name(const std::string name)
    {
        ontology::set_name(name, this);
    }
}
