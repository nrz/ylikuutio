#include "object.hpp"
#include "glyph.hpp"
#include "species.hpp"
#include "object_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace ontology
{
    class Entity;

    void Object::bind_to_parent()
    {
        // get `childID` from `Species` or `Glyph` and set pointer to this `Object`.

        if (this->is_character)
        {
            ontology::Text3D* parent;
            parent = this->text3D_parent;
            // for ontological hierarchy (rendering hierarchy does not use `childID`).
            // get `childID` from `Glyph` and set pointer to this `Object`.
            hierarchy::bind_child_to_parent<ontology::Object*>(this, parent->object_pointer_vector, parent->free_objectID_queue, &parent->number_of_objects);
        }
        else
        {
            ontology::Species* parent;
            parent = this->species_parent;
            // for ontological hierarchy (rendering hierarchy does not use `childID`).
            // get `childID` from `Species` and set pointer to this `Object`.
            hierarchy::bind_child_to_parent<ontology::Object*>(this, parent->object_pointer_vector, parent->free_objectID_queue, &parent->number_of_objects);
        }
    }

    Object::~Object()
    {
        // destructor.

        // set pointer to this object to nullptr.
        if (this->is_character)
        {
            std::string unicode_string = this->glyph_parent->unicode_char_pointer;
            std::cout << "Object with childID " << std::dec << this->childID << " (Unicode: \"" << unicode_string << "\") will be destroyed.\n";
            this->text3D_parent->set_object_pointer(this->childID, nullptr);
        }
        else
        {
            std::cout << "Object with childID " << std::dec << this->childID << " will be destroyed.\n";
            this->species_parent->set_object_pointer(this->childID, nullptr);
        }
    }

    void Object::act()
    {
        // TODO: act according to this game/simulation object's programming.
    }

    void Object::render()
    {
        // render this `Object`.

        if (this->should_ylikuutio_render_this_object)
        {
            this->prerender();

            ontology::Shader* shader_pointer;

            if (this->is_character)
            {
                shader_pointer = this->glyph_parent->parent->parent->parent;
                ontology::render_this_object<ontology::Glyph*>(this, shader_pointer);
            }
            else
            {
                shader_pointer = this->species_parent->parent->parent;
                ontology::render_this_object<ontology::Species*>(this, shader_pointer);
            }

            this->postrender();
        }
    }

    ontology::Entity* Object::get_parent()
    {
        if (this->is_character)
        {
            return this->glyph_parent;
        }
        else
        {
            return this->species_parent;
        }
    }

    int32_t Object::get_number_of_children()
    {
        return 0;
    }

    int32_t Object::get_number_of_descendants()
    {
        return 0;
    }

    void Object::bind_to_new_parent(void* const new_parent)
    {
        // this method sets pointer to this `Object` to nullptr, sets `parent` according to the input,
        // and requests a new `childID` from the new `Species` or from the new `Glyph`.

        if (this->is_character)
        {
            ontology::Glyph* parent;
            parent = this->glyph_parent;
            // set pointer to this child to nullptr in the old parent.
            ontology::Object* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(this->childID, dummy_child_pointer, glyph_parent->object_pointer_vector, glyph_parent->free_objectID_queue, &glyph_parent->number_of_objects);
            // set the new parent pointer.
            this->glyph_parent = static_cast<ontology::Glyph*>(new_parent);
            // bind to the new parent.
            this->bind_to_parent();
        }
        else
        {
            ontology::Species* parent;
            parent = this->species_parent;
            // set pointer to this child to nullptr in the old parent.
            ontology::Object* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(this->childID, dummy_child_pointer, species_parent->object_pointer_vector, species_parent->free_objectID_queue, &species_parent->number_of_objects);
            // set the new parent pointer.
            this->species_parent = static_cast<ontology::Species*>(new_parent);
            // bind to the new parent.
            this->bind_to_parent();
        }
    }

    void Object::set_name(const std::string& name)
    {
        ontology::set_name(name, this);
    }

    // Public callbacks (to be called from AI scripts written in Chibi-Scheme).

    void Object::set_dest(ontology::Object* const object, const float x, const float y, const float z)
    {
        // Set target towards which to move.
        object->dest_vector = glm::vec3(x, y, z);
    }

    float Object::get_x(const ontology::Object* const object)
    {
        // Get x coordinate of `object`.
        return object->coordinate_vector.x;
    }

    float Object::get_y(const ontology::Object* const object)
    {
        // Get y coordinate of `object`.
        return object->coordinate_vector.x;
    }

    float Object::get_z(const ontology::Object* const object)
    {
        // Get z coordinate of `object`.
        return object->coordinate_vector.x;
    }

    float Object::get_dest_x(const ontology::Object* const object)
    {
        // Get x destination coordinate of `object`.
        return object->dest_vector.x;
    }

    float Object::get_dest_y(const ontology::Object* const object)
    {
        // Get y destination coordinate of `object`.
        return object->dest_vector.x;
    }

    float Object::get_dest_z(const ontology::Object* const object)
    {
        // Get z destination coordinate of `object`.
        return object->dest_vector.x;
    }

    // Public callbacks end here.
}
