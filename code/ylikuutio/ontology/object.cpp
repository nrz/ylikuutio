#include "object.hpp"
#include "glyph.hpp"
#include "species.hpp"
#include "text3D.hpp"
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
#include <string>   // std::string

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

    void Object::render()
    {
        // render this `Object`.

        if (this->should_ylikuutio_render_this_object)
        {
            this->prerender();

            if (this->is_character)
            {
                this->render_this_object(this->glyph_parent->parent->parent->parent);
            }
            else
            {
                this->render_this_object(this->species_parent->parent->parent);
            }

            this->postrender();
        }
    }

    void Object::render_this_object(ontology::Shader* shader_pointer)
    {
        if (!this->has_entered)
        {
            this->model_matrix = glm::translate(glm::mat4(1.0f), *this->cartesian_coordinates);
            this->model_matrix = glm::scale(this->model_matrix, this->original_scale_vector);

            // store the new coordinates to be used in the next update.
            *this->cartesian_coordinates = glm::vec3(this->model_matrix[0][0], this->model_matrix[1][1], this->model_matrix[2][2]);
            this->has_entered = true;
        }
        else
        {
            // rotate.
            if (this->rotate_vector != glm::vec3(0.0f, 0.0f, 0.0f))
            {
                if (this->quaternions_in_use)
                {
                    // create `rotation_matrix` using quaternions.
                    glm::quat my_quaternion = glm::quat(DEGREES_TO_RADIANS(this->rotate_vector));
                    glm::mat4 rotation_matrix = glm::mat4_cast(my_quaternion);
                    this->model_matrix = rotation_matrix * this->model_matrix;
                }
                else
                {
                    this->model_matrix = glm::rotate(this->model_matrix, this->rotate_angle, this->rotate_vector);
                }
            }

            this->model_matrix = glm::translate(this->model_matrix, this->translate_vector);
            *this->cartesian_coordinates = glm::vec3(this->model_matrix[0][0], this->model_matrix[1][1], this->model_matrix[2][2]);
        }

        this->MVP_matrix = this->universe->get_projection_matrix() * this->universe->get_view_matrix() * this->model_matrix;

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform.
        glUniformMatrix4fv(shader_pointer->MatrixID, 1, GL_FALSE, &this->MVP_matrix[0][0]);
        glUniformMatrix4fv(shader_pointer->ModelMatrixID, 1, GL_FALSE, &this->model_matrix[0][0]);

        GLuint vertexbuffer;
        GLuint vertexPosition_modelspaceID;
        GLuint uvbuffer;
        GLuint vertexUVID;
        GLuint normalbuffer;
        GLuint vertexNormal_modelspaceID;
        GLuint elementbuffer;
        GLuint indices_size;

        if (this->is_character)
        {
            ontology::Glyph* parent_glyph = this->glyph_parent;
            vertexbuffer = parent_glyph->vertexbuffer;
            vertexPosition_modelspaceID = parent_glyph->vertexPosition_modelspaceID;
            uvbuffer = parent_glyph->uvbuffer;
            vertexUVID = parent_glyph->vertexUVID;
            normalbuffer = parent_glyph->normalbuffer;
            vertexNormal_modelspaceID = parent_glyph->vertexNormal_modelspaceID;
            elementbuffer = parent_glyph->elementbuffer;
            indices_size = parent_glyph->indices.size();
        }
        else
        {
            ontology::Species* parent_species = this->species_parent;
            vertexbuffer = parent_species->vertexbuffer;
            vertexPosition_modelspaceID = parent_species->vertexPosition_modelspaceID;
            uvbuffer = parent_species->uvbuffer;
            vertexUVID = parent_species->vertexUVID;
            normalbuffer = parent_species->normalbuffer;
            vertexNormal_modelspaceID = parent_species->vertexNormal_modelspaceID;
            elementbuffer = parent_species->elementbuffer;
            indices_size = parent_species->indices.size();
        }

        // 1st attribute buffer : vertices.
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                vertexPosition_modelspaceID, // The attribute we want to configure
                3,                           // size
                GL_FLOAT,                    // type
                GL_FALSE,                    // normalized?
                0,                           // stride
                (void*) 0                    // array buffer offset
                );

        // 2nd attribute buffer : UVs.
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                vertexUVID, // The attribute we want to configure
                2,          // size : U+V => 2
                GL_FLOAT,   // type
                GL_FALSE,   // normalized?
                0,          // stride
                (void*) 0   // array buffer offset
                );

        // 3rd attribute buffer : normals.
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
                vertexNormal_modelspaceID, // The attribute we want to configure
                3,                         // size
                GL_FLOAT,                  // type
                GL_FALSE,                  // normalized?
                0,                         // stride
                (void*) 0                  // array buffer offset
                );

        // Index buffer.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        // Draw the triangles!
        glDrawElements(
                GL_TRIANGLES,    // mode
                indices_size,    // count
                GL_UNSIGNED_INT, // type
                (void*) 0        // element array buffer offset
                );
    }

    ontology::Entity* Object::get_parent() const
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

    int32_t Object::get_number_of_children() const
    {
        return 0;
    }

    int32_t Object::get_number_of_descendants() const
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
}
