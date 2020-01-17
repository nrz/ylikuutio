// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "object.hpp"
#include "object_type.hpp"
#include "glyph.hpp"
#include "species.hpp"
#include "shapeshifter_sequence.hpp"
#include "model.hpp"
#include "text3D.hpp"
#include "object_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp> // glm::quat
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Entity;

        void Object::bind_to_parent()
        {
            if (this->object_type == yli::ontology::ObjectType::REGULAR)
            {
                // requirements for further actions in this block:
                // `this->species_parent` must not be `nullptr`.

                yli::ontology::Species* const species = this->species_parent;

                if (species == nullptr)
                {
                    std::cerr << "ERROR: `Object::bind_to_parent`: `species` is `nullptr`!\n";
                    return;
                }

                // get `childID` from `Species` and set pointer to this `Object`.
                species->bind_Object(this);
            }
            else if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
            {
                // requirements for further actions in this block:
                // `this->shapeshifter_sequence_parent` must not be `nullptr`.

                yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = this->shapeshifter_sequence_parent;

                if (shapeshifter_sequence == nullptr)
                {
                    std::cerr << "ERROR: `Object::bind_to_parent`: `shapeshifter_sequence` is `nullptr`!\n";
                    return;
                }

                // get `childID` from `ShapeshifterSequence` and set pointer to this `Object`.
                shapeshifter_sequence->bind_Object(this);
            }
            else if (this->object_type == yli::ontology::ObjectType::CHARACTER)
            {
                // requirements for further actions in this block:
                // `this->text3D_parent` must not be `nullptr`.

                yli::ontology::Text3D* const text3D = this->text3D_parent;

                if (text3D == nullptr)
                {
                    std::cerr << "ERROR: `Object::bind_to_parent`: `text3D` is `nullptr`!\n";
                    return;
                }

                // get `childID` from `Text3D` and set pointer to this `Object`.
                text3D->bind_Object(this);
            }
        }

        void Object::bind_to_new_parent(yli::ontology::Text3D* const new_parent)
        {
            // this method sets pointer to this `Object` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Text3D`.

            if (this->object_type == yli::ontology::ObjectType::CHARACTER)
            {
                // requirements for further actions in this block:
                // `this->text3D_parent` must not be `nullptr`.
                // `new_parent` must not be `nullptr`.

                yli::ontology::Text3D* const text3D = this->text3D_parent;

                if (text3D == nullptr)
                {
                    std::cerr << "ERROR: `Object::bind_to_new_parent`: `text3D` is `nullptr`!\n";
                    return;
                }

                if (new_parent == nullptr)
                {
                    std::cerr << "ERROR: `Object::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                    return;
                }

                // unbind from the old parent `Text3D`.
                text3D->unbind_Object(this->childID);

                // get `childID` from `Text3D` and set pointer to this `Object`.
                this->text3D_parent = static_cast<yli::ontology::Text3D*>(new_parent);
                this->text3D_parent->bind_Object(this);
            }
        }

        void Object::bind_to_new_parent(yli::ontology::Species* const new_parent)
        {
            // this method sets pointer to this `Object` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Species`.

            if (this->object_type == yli::ontology::ObjectType::REGULAR)
            {
                // requirements for further actions in this block:
                // `this->species_parent` must not be `nullptr`.
                // `new_parent` must not be `nullptr`.

                yli::ontology::Species* const species = this->species_parent;

                if (species == nullptr)
                {
                    std::cerr << "ERROR: `Object::bind_to_new_parent`: `species` is `nullptr`!\n";
                    return;
                }

                if (new_parent == nullptr)
                {
                    std::cerr << "ERROR: `Object::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                    return;
                }

                // unbind from the old parent `Species`.
                species->unbind_Object(this->childID);

                // get `childID` from `Species` and set pointer to this `Object`.
                this->species_parent = static_cast<yli::ontology::Species*>(new_parent);
                this->species_parent->bind_Object(this);
            }
        }

        void Object::bind_to_new_parent(yli::ontology::ShapeshifterSequence* const new_parent)
        {
            // this method sets pointer to this `Object` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `ShapeshifterSequence`.

            if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
            {
                // requirements for further actions in this block:
                // `this->shapeshifter_sequence_parent` must not be `nullptr`.
                // `new_parent` must not be `nullptr`.

                yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = this->shapeshifter_sequence_parent;

                if (shapeshifter_sequence == nullptr)
                {
                    std::cerr << "ERROR: `Object::bind_to_new_parent`: `shapeshifter_sequence` is `nullptr`!\n";
                    return;
                }

                if (new_parent == nullptr)
                {
                    std::cerr << "ERROR: `Object::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                    return;
                }

                // unbind from the old parent `ShapeshifterSequence`.
                shapeshifter_sequence->unbind_Object(this->childID);

                // get `childID` from `ShapeshifterSequence` and set pointer to this `Object`.
                this->shapeshifter_sequence_parent = static_cast<yli::ontology::ShapeshifterSequence*>(new_parent);
                this->shapeshifter_sequence_parent->bind_Object(this);
            }
        }

        void Object::bind_to_new_parent(yli::ontology::Entity* const new_parent)
        {
            // this method sets pointer to this `Object` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Species` or from the new `Text3D`.
            //
            // requirements:
            // `new_parent` must not be `nullptr`.

            yli::ontology::Species* const species_parent = dynamic_cast<yli::ontology::Species*>(new_parent);

            if (species_parent != nullptr)
            {
                this->bind_to_new_parent(species_parent);
                return;
            }

            yli::ontology::Text3D* const text3D_parent = dynamic_cast<yli::ontology::Text3D*>(new_parent);

            if (text3D_parent != nullptr)
            {
                this->bind_to_new_parent(text3D_parent);
                return;
            }

            std::cerr << "ERROR: `Object::bind_to_new_parent`: `new_parent` is neither `yli::ontology::Species*` nor `yli::ontology::Text3D*`!\n";
        }

        Object::~Object()
        {
            // destructor.
            std::cout << "Object with childID " << std::dec << this->childID << " will be destroyed.\n";

            // set pointer to this object to `nullptr`.
            if (this->object_type == yli::ontology::ObjectType::REGULAR)
            {
                // requirements for further actions in this block:
                // `this->species_parent` must not be `nullptr`.

                yli::ontology::Species* species = this->species_parent;

                if (species == nullptr)
                {
                    std::cerr << "ERROR: `Object::~Object`: `species` is `nullptr`!\n";
                    return;
                }

                species->unbind_Object(this->childID);
            }
            else if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
            {
                // requirements for further actions in this block:
                // `this->species_parent` must not be `nullptr`.

                yli::ontology::ShapeshifterSequence* shapeshifter_sequence = this->shapeshifter_sequence_parent;

                if (shapeshifter_sequence == nullptr)
                {
                    std::cerr << "ERROR: `Object::~Object`: `shapeshifter_sequence` is `nullptr`!\n";
                    return;
                }

                shapeshifter_sequence->unbind_Object(this->childID);
            }
            else if (this->object_type == yli::ontology::ObjectType::CHARACTER)
            {
                if (this->glyph != nullptr)
                {
                    std::string unicode_string = this->glyph->get_unicode_char_pointer();
                    std::cout << "Object with childID " << std::dec << this->childID << " (Unicode: \"" << unicode_string << "\") will be destroyed.\n";
                }

                // requirements for further actions in this block:
                // `this->text3D_parent` must not be `nullptr`.

                yli::ontology::Text3D* text3D = this->text3D_parent;

                if (text3D == nullptr)
                {
                    std::cerr << "ERROR: `Object::~Object`: `text3D` is `nullptr`!\n";
                    return;
                }

                text3D->unbind_Object(this->childID);
            }
        }

        void Object::render()
        {
            // render this `Object`.

            if (this->should_be_rendered)
            {
                this->prerender();

                if (this->object_type == yli::ontology::ObjectType::REGULAR)
                {
                    this->render_this_object(static_cast<yli::ontology::Shader*>(this->species_parent->get_parent()->get_parent()));
                }
                else if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
                {
                    // TODO.
                }
                else if (this->object_type == yli::ontology::ObjectType::CHARACTER)
                {
                    this->render_this_object(static_cast<yli::ontology::Shader*>(this->glyph->get_parent()->get_parent()->get_parent()));
                }

                this->postrender();
            }
        }

        void Object::render_this_object(yli::ontology::Shader* const shader_pointer)
        {
            if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
            {
                // TODO: implement rendering for `SHAPESHIFTER`!
                // Meanwhile this block just exists to exit this function.
                return;
            }

            this->model_matrix = glm::mat4(1.0f);

            if (this->object_type == yli::ontology::ObjectType::REGULAR)
            {
                const std::string model_file_format = this->species_parent->get_model_file_format();

                if (model_file_format == "fbx" || model_file_format == "FBX")
                {
                    // Only FBX objects need initial rotation.
                    this->model_matrix = glm::rotate(this->model_matrix, this->initial_rotate_angle, this->initial_rotate_vector);
                }
            }

            this->model_matrix = glm::scale(this->model_matrix, this->original_scale_vector);
            glm::vec3 euler_angles { this->vertical_angle, this->horizontal_angle, 0.0f };
            glm::quat my_quaternion = glm::quat(euler_angles);
            glm::mat4 rotation_matrix = glm::mat4_cast(my_quaternion);
            this->model_matrix = rotation_matrix * this->model_matrix;
            this->model_matrix[3][0] = this->cartesian_coordinates.x;
            this->model_matrix[3][1] = this->cartesian_coordinates.y;
            this->model_matrix[3][2] = this->cartesian_coordinates.z;

            this->MVP_matrix = this->universe->get_projection_matrix() * this->universe->get_view_matrix() * this->model_matrix;

            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform.
            glUniformMatrix4fv(shader_pointer->get_matrixID(), 1, GL_FALSE, &this->MVP_matrix[0][0]);
            glUniformMatrix4fv(shader_pointer->get_model_matrixID(), 1, GL_FALSE, &this->model_matrix[0][0]);

            yli::ontology::Model* parent_model = nullptr;

            if (this->object_type == yli::ontology::ObjectType::REGULAR)
            {
                parent_model = this->species_parent;
            }
            else if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
            {
                // TODO: set `parent_model` so that it points to the correct `ShapeshifterForm` for the current frame!
            }
            else if (this->object_type == yli::ontology::ObjectType::CHARACTER)
            {
                parent_model = this->glyph;
            }

            uint32_t vertexbuffer = parent_model->get_vertexbuffer();
            uint32_t vertex_position_modelspaceID = parent_model->get_vertex_position_modelspaceID();
            uint32_t uvbuffer = parent_model->get_uvbuffer();
            uint32_t vertexUVID = parent_model->get_vertexUVID();
            uint32_t normalbuffer = parent_model->get_normalbuffer();
            uint32_t vertex_normal_modelspaceID = parent_model->get_vertex_normal_modelspaceID();
            uint32_t elementbuffer = parent_model->get_elementbuffer();
            uint32_t indices_size = parent_model->get_indices().size();

            // 1st attribute buffer: vertices.
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    vertex_position_modelspaceID, // The attribute we want to configure
                    3,                           // size
                    GL_FLOAT,                    // type
                    GL_FALSE,                    // normalized?
                    0,                           // stride
                    (void*) 0                    // array buffer offset
                    );

            // 2nd attribute buffer: UVs.
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glVertexAttribPointer(
                    vertexUVID, // The attribute we want to configure
                    2,          // size : U+V => 2
                    GL_FLOAT,   // type
                    GL_FALSE,   // normalized?
                    0,          // stride
                    (void*) 0   // array buffer offset
                    );

            // 3rd attribute buffer: normals.
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
            if (this->object_type == yli::ontology::ObjectType::REGULAR)
            {
                return this->species_parent;
            }
            else if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
            {
                return this->shapeshifter_sequence_parent;
            }
            else if (this->object_type == yli::ontology::ObjectType::CHARACTER)
            {
                return this->text3D_parent;
            }

            return nullptr;
        }

        std::size_t Object::get_number_of_children() const
        {
            return 0; // `Object` has no children.
        }

        std::size_t Object::get_number_of_descendants() const
        {
            return 0; // `Object` has no children.
        }
    }
}
