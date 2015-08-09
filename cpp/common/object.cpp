#include "object.hpp"
#include "glyph.hpp"
#include "species.hpp"

namespace model
{
    void Object::bind_to_parent()
    {
        if (this->is_character)
        {
            model::Glyph* parent_pointer;
            parent_pointer = static_cast<model::Glyph*>(this->parent_pointer);
            model::bind_child_to_parent<model::Object*>(this, parent_pointer->object_pointer_vector, parent_pointer->free_objectID_queue);
        }
        else
        {
            model::Species* parent_pointer;
            parent_pointer = static_cast<model::Species*>(this->parent_pointer);
            model::bind_child_to_parent<model::Object*>(this, parent_pointer->object_pointer_vector, parent_pointer->free_objectID_queue);
        }
    }

    Object::Object(ObjectStruct object_struct)
    {
        // constructor.
        this->coordinate_vector     = object_struct.coordinate_vector;
        this->original_scale_vector = object_struct.original_scale_vector;
        this->rotate_angle          = object_struct.rotate_angle;
        this->rotate_vector         = object_struct.rotate_vector;
        this->translate_vector      = object_struct.translate_vector;
        this->has_entered           = false;
        this->parent_pointer        = static_cast<model::Species*>(object_struct.parent_pointer);
        this->is_character          = object_struct.is_character;

        // get childID from the Species and set pointer to this object.
        this->bind_to_parent();

        bool model_loading_result = false;
    }

    Object::~Object()
    {
        // destructor.
        std::cout << "Object with childID " << this->childID << " will be destroyed.\n";

        // set pointer to this object to NULL.
        if (this->is_character)
        {
            model::Glyph* parent_pointer;
            parent_pointer = static_cast<model::Glyph*>(this->parent_pointer);
            parent_pointer->set_object_pointer(this->childID, NULL);
        }
        else
        {
            model::Glyph* parent_pointer;
            parent_pointer = static_cast<model::Glyph*>(this->parent_pointer);
            parent_pointer->set_object_pointer(this->childID, NULL);
        }
    }

    void Object::render()
    {
        model::Shader* shader_pointer;

        if (this->is_character)
        {
            shader_pointer = static_cast<model::Glyph*>(this->parent_pointer)->parent_pointer->parent_pointer->parent_pointer;
            model::render_this_object<model::Glyph*>(this, shader_pointer);
        }
        else
        {
            shader_pointer = static_cast<model::Species*>(this->parent_pointer)->parent_pointer->parent_pointer;
            model::render_this_object<model::Species*>(this, shader_pointer);
        }
    }

    void Object::bind_to_new_parent(void* new_parent_pointer)
    {
        if (this->is_character)
        {
            model::Glyph* parent_pointer;
            parent_pointer = static_cast<model::Glyph*>(this->parent_pointer);
            model::bind_child_to_new_parent<model::Object*, model::Glyph*>(this, static_cast<model::Glyph*>(new_parent_pointer), parent_pointer->object_pointer_vector, parent_pointer->free_objectID_queue);
        }
        else
        {
            model::Species* parent_pointer;
            parent_pointer = static_cast<model::Species*>(this->parent_pointer);
            model::bind_child_to_new_parent<model::Object*, model::Species*>(this, static_cast<model::Species*>(new_parent_pointer), parent_pointer->object_pointer_vector, parent_pointer->free_objectID_queue);
        }
    }
}
