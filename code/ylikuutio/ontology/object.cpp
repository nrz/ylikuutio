#include "object.hpp"
#include "glyph.hpp"
#include "species.hpp"
#include "model.hpp"
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

namespace yli
{
    namespace ontology
    {
        class Entity;

        void Object::bind_to_parent()
        {
            // get `childID` from `Species` or `Text3D` and set pointer to this `Object`.
            yli::ontology::Model* glyph_parent_model = this->glyph_parent;
            yli::ontology::Model* species_parent_model = this->species_parent;
            yli::ontology::Model* parent_model = (this->is_character ? glyph_parent_model : species_parent_model);
            parent_model->bind(this);
        }

        void Object::bind_to_new_parent(void* const new_parent)
        {
            // this method sets pointer to this `Object` to nullptr, sets `parent` according to the input,
            // and requests a new `childID` from the new `Species` or from the new `Glyph`.

            yli::ontology::Model* glyph_parent_model = this->glyph_parent;
            yli::ontology::Model* species_parent_model = this->species_parent;
            yli::ontology::Model* parent_model = (this->is_character ? glyph_parent_model : species_parent_model);

            // unbind from the old parent `Model`.
            parent_model->unbind(this->childID);

            if (this->is_character)
            {
                this->glyph_parent = static_cast<yli::ontology::Glyph*>(new_parent);
            }
            else
            {
                this->species_parent = static_cast<yli::ontology::Species*>(new_parent);
            }

            // get `childID` from `Model` and set pointer to this `Object`.
            parent_model->bind(this);
        }

        Object::~Object()
        {
            // destructor.

            // set pointer to this object to nullptr.
            if (this->is_character)
            {
                std::string unicode_string = this->glyph_parent->get_unicode_char_pointer();
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
                    this->render_this_object(static_cast<yli::ontology::Shader*>(this->glyph_parent->get_parent()->get_parent()->get_parent()));
                }
                else
                {
                    this->render_this_object(static_cast<yli::ontology::Shader*>(this->species_parent->get_parent()->get_parent()));
                }

                this->postrender();
            }
        }

        void Object::render_this_object(yli::ontology::Shader* const shader_pointer)
        {
            if (!this->has_entered)
            {
                this->model_matrix = glm::translate(glm::mat4(1.0f), this->cartesian_coordinates);

                if (!this->is_character)
                {
                    const std::string model_file_format = this->species_parent->get_model_file_format();

                    if (model_file_format.compare("fbx") == 0 || model_file_format.compare("FBX") == 0)
                    {
                        // Only FBX objects need initial rotation.
                        this->model_matrix = glm::rotate(this->model_matrix, this->initial_rotate_angle, this->initial_rotate_vector);
                    }
                }
                this->model_matrix = glm::scale(this->model_matrix, this->original_scale_vector);

                // store the new coordinates to be used in the next update.
                this->cartesian_coordinates = glm::vec3(this->model_matrix[3][0], this->model_matrix[3][1], this->model_matrix[3][2]);
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
                this->cartesian_coordinates = glm::vec3(this->model_matrix[3][0], this->model_matrix[3][1], this->model_matrix[3][2]);
            }

            this->MVP_matrix = this->universe->get_projection_matrix() * this->universe->get_view_matrix() * this->model_matrix;

            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform.
            glUniformMatrix4fv(shader_pointer->get_matrixID(), 1, GL_FALSE, &this->MVP_matrix[0][0]);
            glUniformMatrix4fv(shader_pointer->get_model_matrixID(), 1, GL_FALSE, &this->model_matrix[0][0]);

            yli::ontology::Model* glyph_parent_model = this->glyph_parent;
            yli::ontology::Model* species_parent_model = this->species_parent;
            yli::ontology::Model* parent_model = (this->is_character ? glyph_parent_model : species_parent_model);
            GLuint vertexbuffer = parent_model->get_vertexbuffer();
            GLuint vertex_position_modelspaceID = parent_model->get_vertex_position_modelspaceID();
            GLuint uvbuffer = parent_model->get_uvbuffer();
            GLuint vertexUVID = parent_model->get_vertexUVID();
            GLuint normalbuffer = parent_model->get_normalbuffer();
            GLuint vertex_normal_modelspaceID = parent_model->get_vertex_normal_modelspaceID();
            GLuint elementbuffer = parent_model->get_elementbuffer();
            GLuint indices_size = parent_model->get_indices().size();

            // 1st attribute buffer : vertices.
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    vertex_position_modelspaceID, // The attribute we want to configure
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
                    vertex_normal_modelspaceID, // The attribute we want to configure
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

        yli::ontology::Entity* Object::get_parent() const
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
    }
}
