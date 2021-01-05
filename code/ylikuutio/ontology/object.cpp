// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include "material.hpp"
#include "species.hpp"
#include "shapeshifter_sequence.hpp"
#include "model.hpp"
#include "text3D.hpp"
#include "entity_factory.hpp"
#include "object_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
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
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;
    class Shader;

    void Object::bind_to_new_parent(yli::ontology::Species* const new_parent)
    {
        // this method sets pointer to this `Object` to `nullptr`, sets `parent` according to the input,
        // and requests a new `childID` from the new `Species`.

        if (this->object_type == yli::ontology::ObjectType::REGULAR)
        {
            // requirements for further actions in this block:
            // `this->species_parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.

            yli::ontology::Entity* const species = this->child.get_parent();

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

            if (new_parent->has_child(this->local_name))
            {
                std::cerr << "ERROR: `Object::bind_to_new_parent`: local name is already in use!\n";
                return;
            }

            // unbind from the old parent `Species`.
            this->child.unbind_child();

            // get `childID` from `Species` and set pointer to this `Object`.
            this->child.set_parent_module_and_bind_to_new_parent(&new_parent->parent_of_objects);
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

            yli::ontology::Entity* const shapeshifter_sequence = this->child.get_parent();

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

            if (new_parent->has_child(this->local_name))
            {
                std::cerr << "ERROR: `Object::bind_to_new_parent`: local name is already in use!\n";
                return;
            }

            // unbind from the old parent `ShapeshifterSequence`.
            this->child.unbind_child();

            // get `childID` from `ShapeshifterSequence` and set pointer to this `Object`.
            this->child.set_parent_module_and_bind_to_new_parent(&new_parent->parent_of_objects);
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

            yli::ontology::Entity* const text3D = this->child.get_parent();

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

            if (new_parent->has_child(this->local_name))
            {
                std::cerr << "ERROR: `Object::bind_to_new_parent`: local name is already in use!\n";
                return;
            }

            // unbind from the old parent `Text3D`.
            this->child.unbind_child();

            // get `childID` from `Text3D` and set pointer to this `Object`.
            this->child.set_parent_module_and_bind_to_new_parent(&new_parent->parent_of_objects);
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
        std::cout << "`Object` with childID " << std::dec << this->childID << " will be destroyed.\n";
    }

    yli::ontology::Glyph* Object::get_glyph() const
    {
        return this->glyph;
    }

    void Object::render()
    {
        // render this `Object`.

        if (this->should_be_rendered)
        {
            this->prerender();

            if (this->object_type == yli::ontology::ObjectType::REGULAR)
            {
                yli::ontology::Species* const species = static_cast<yli::ontology::Species*>(this->child.get_parent());

                if (species == nullptr)
                {
                    return;
                }

                yli::ontology::Material* const material = static_cast<yli::ontology::Material*>(species->get_parent());

                if (material == nullptr)
                {
                    return;
                }

                yli::ontology::Shader* const shader = static_cast<yli::ontology::Shader*>(material->get_parent());
                this->render_this_object(shader);
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
            yli::ontology::Species* const species = static_cast<yli::ontology::Species*>(this->child.get_parent());

            if (species == nullptr)
            {
                return;
            }

            const std::string model_file_format = species->get_model_file_format();

            if (this->initial_rotate_vectors.size() == this->initial_rotate_angles.size())
            {
                for (std::size_t i = 0; i < this->initial_rotate_vectors.size() && i < this->initial_rotate_angles.size(); i++)
                {
                    this->model_matrix = glm::rotate(this->model_matrix, this->initial_rotate_angles[i], this->initial_rotate_vectors[i]);
                }
            }
        }

        this->model_matrix = glm::scale(this->model_matrix, this->original_scale_vector);
        glm::vec3 euler_angles { 0.0f, this->yaw, this->pitch };
        glm::quat my_quaternion = glm::quat(euler_angles);
        glm::mat4 rotation_matrix = glm::mat4_cast(my_quaternion);
        this->model_matrix = rotation_matrix * this->model_matrix;
        this->model_matrix[3][0] = this->cartesian_coordinates.x;
        this->model_matrix[3][1] = this->cartesian_coordinates.y;
        this->model_matrix[3][2] = this->cartesian_coordinates.z;

        this->mvp_matrix = this->universe->get_projection_matrix() * this->universe->get_view_matrix() * this->model_matrix;

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform.
        glUniformMatrix4fv(shader_pointer->get_matrix_id(), 1, GL_FALSE, &this->mvp_matrix[0][0]);
        glUniformMatrix4fv(shader_pointer->get_model_matrix_id(), 1, GL_FALSE, &this->model_matrix[0][0]);

        yli::ontology::Model* parent_model = nullptr;

        if (this->object_type == yli::ontology::ObjectType::REGULAR)
        {
            parent_model = static_cast<yli::ontology::Species*>(this->child.get_parent());
        }
        else if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
        {
            // TODO: set `parent_model` so that it points to the correct `ShapeshifterForm` for the current frame!
        }
        else if (this->object_type == yli::ontology::ObjectType::CHARACTER)
        {
            parent_model = this->glyph;
        }

        GLuint vertexbuffer                    = parent_model->get_vertexbuffer();
        uint32_t vertex_position_modelspace_id = parent_model->get_vertex_position_modelspace_id();
        GLuint uvbuffer                        = parent_model->get_uvbuffer();
        uint32_t vertex_uv_id                  = parent_model->get_vertex_uv_id();
        GLuint normalbuffer                    = parent_model->get_normalbuffer();
        uint32_t vertex_normal_modelspace_id   = parent_model->get_vertex_normal_modelspace_id();
        GLuint elementbuffer                   = parent_model->get_elementbuffer();
        uint32_t indices_size                  = parent_model->get_indices().size();

        // 1st attribute buffer: vertices.
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                vertex_position_modelspace_id, // The attribute we want to configure
                3,                           // size
                GL_FLOAT,                    // type
                GL_FALSE,                    // normalized?
                0,                           // stride
                (void*) 0                    // array buffer offset
                );

        // 2nd attribute buffer: UVs.
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                vertex_uv_id, // The attribute we want to configure
                2,          // size : U+V => 2
                GL_FLOAT,   // type
                GL_FALSE,   // normalized?
                0,          // stride
                (void*) 0   // array buffer offset
                );

        // 3rd attribute buffer: normals.
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
                vertex_normal_modelspace_id, // The attribute we want to configure
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

    std::size_t Object::get_number_of_children() const
    {
        return 0; // `Object` has no children.
    }

    std::size_t Object::get_number_of_descendants() const
    {
        return 0; // `Object` has no children.
    }

    // Public callbacks.

    std::shared_ptr<yli::data::AnyValue> Object::create_object_with_parent_name_x_y_z(
            yli::ontology::Species* const parent,
            std::shared_ptr<std::string> object_name,
            std::shared_ptr<std::string> x,
            std::shared_ptr<std::string> y,
            std::shared_ptr<std::string> z)
    {
        if (parent == nullptr || object_name == nullptr || x == nullptr || y == nullptr || z == nullptr)
        {
            return nullptr;
        }

        yli::ontology::EntityFactory* const entity_factory = parent->get_entity_factory();

        if (entity_factory == nullptr)
        {
            return nullptr;
        }

        yli::data::AnyValue x_any_value("float", *x);
        yli::data::AnyValue y_any_value("float", *y);
        yli::data::AnyValue z_any_value("float", *z);

        if (!std::holds_alternative<float>(x_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z`: invalid value for `x`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(y_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z`: invalid value for `y`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(z_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z`: invalid value for `z`!\n";
            return nullptr;
        }

        float float_x = std::get<float>(x_any_value.data);
        float float_y = std::get<float>(y_any_value.data);
        float float_z = std::get<float>(z_any_value.data);

        yli::ontology::ObjectStruct object_struct;
        object_struct.cartesian_coordinates = glm::vec3(float_x, float_y, float_z);
        object_struct.species_parent = parent;
        object_struct.local_name = *object_name;
        entity_factory->create_object(object_struct);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Object::create_object_with_parent_name_x_y_z_yaw_pitch(
            yli::ontology::Species* const parent,
            std::shared_ptr<std::string> object_name,
            std::shared_ptr<std::string> x,
            std::shared_ptr<std::string> y,
            std::shared_ptr<std::string> z,
            std::shared_ptr<std::string> yaw,
            std::shared_ptr<std::string> pitch)
    {
        if (parent == nullptr || object_name == nullptr || x == nullptr || y == nullptr || z == nullptr || yaw == nullptr || pitch == nullptr)
        {
            return nullptr;
        }

        yli::ontology::EntityFactory* const entity_factory = parent->get_entity_factory();

        if (entity_factory == nullptr)
        {
            return nullptr;
        }

        yli::data::AnyValue x_any_value("float", *x);
        yli::data::AnyValue y_any_value("float", *y);
        yli::data::AnyValue z_any_value("float", *z);
        yli::data::AnyValue yaw_any_value("float", *yaw);
        yli::data::AnyValue pitch_any_value("float", *pitch);

        if (!std::holds_alternative<float>(x_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `x`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(y_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `y`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(z_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `z`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(yaw_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `yaw`!\n";
            return nullptr;
        }

        if (!std::holds_alternative<float>(pitch_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `pitch`!\n";
            return nullptr;
        }

        float float_x = std::get<float>(x_any_value.data);
        float float_y = std::get<float>(y_any_value.data);
        float float_z = std::get<float>(z_any_value.data);
        float float_yaw = std::get<float>(yaw_any_value.data);
        float float_pitch = std::get<float>(pitch_any_value.data);

        yli::ontology::ObjectStruct object_struct;
        object_struct.cartesian_coordinates = glm::vec3(float_x, float_y, float_z);
        object_struct.yaw = float_yaw;
        object_struct.pitch = float_pitch;
        object_struct.species_parent = parent;
        object_struct.local_name = *object_name;
        entity_factory->create_object(object_struct);
        return nullptr;
    }

    // Public callbacks end here.
}
