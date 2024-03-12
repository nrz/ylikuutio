// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include "universe.hpp"
#include "mesh_module.hpp"
#include "orientation_module.hpp"
#include "object_type.hpp"
#include "glyph.hpp"
#include "pipeline.hpp"
#include "scene.hpp"
#include "species.hpp"
#include "shapeshifter_sequence.hpp"
#include "text_3d.hpp"
#include "generic_entity_factory.hpp"
#include "object_struct.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_TYPE_PTR_HPP_INCLUDED
#define __GLM_GTC_TYPE_PTR_HPP_INCLUDED
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
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
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> Object::bind_to_new_scene_parent(
            yli::ontology::Object& object,
            yli::ontology::Scene& new_parent)
    {
        // Set pointer to `object` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Scene* const scene = static_cast<yli::ontology::Scene*>(object.get_parent());

        if (scene == nullptr)
        {
            throw std::runtime_error("ERROR: `Object::bind_to_new_scene_parent`: `scene` is `nullptr`!\n");
        }

        if (&new_parent == scene)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(object.local_name))
        {
            std::cerr << "ERROR: `Object::bind_to_new_scene_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        object.apprentice_of_mesh.unbind_from_any_master_belonging_to_other_scene(new_parent);
        object.child_of_scene.unbind_and_bind_to_new_parent(&new_parent.parent_of_objects);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Object::bind_to_new_species_master(
            yli::ontology::Object& object,
            yli::ontology::Species& new_species) noexcept
    {
        // Set pointer to `object` to `nullptr`, set mesh according to the input,
        // and request a new apprenticeID from `new_species`.

        if (object.object_type == yli::ontology::ObjectType::REGULAR)
        {
            // Master and apprentice must belong to the same `Scene`,
            // if both belong to some `Scene`, and not `Ecosystem`.
            if (object.get_scene() == new_species.get_scene() ||
                    object.get_scene() == nullptr ||
                    new_species.get_scene() == nullptr)
            {
                object.apprentice_of_mesh.unbind_and_bind_to_new_generic_master_module(
                        &new_species.master_of_objects);
            }
            else
            {
                std::cerr << "ERROR: `Object::bind_to_new_species_master`: master and apprentice can not belong to different `Scene`s!\n";
            }
        }
        else
        {
            std::cerr << "ERROR: `Object::bind_to_new_species_master`: only `REGULAR` type `Object`s can be bound to `Species`!\n";
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Object::bind_to_new_shapeshifter_sequence_master(
            yli::ontology::Object& object,
            yli::ontology::ShapeshifterSequence& new_shapeshifter_sequence) noexcept
    {
        // Set pointer to `object` to `nullptr`, set mesh according to the input,
        // and request a new apprenticeID from `new_shapeshifter_sequence`.

        if (object.object_type == yli::ontology::ObjectType::SHAPESHIFTER)
        {
            object.apprentice_of_mesh.unbind_and_bind_to_new_generic_master_module(
                    &new_shapeshifter_sequence.master_of_objects);
        }
        else
        {
            std::cerr << "ERROR: `Object::bind_to_new_shapeshifter_sequence_master`: only `SHAPESHIFTER` type `Object`s can be bound to `ShapeshifterSequence`!\n";
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Object::bind_to_new_text_3d_master(
            yli::ontology::Object& object,
            yli::ontology::Text3D& new_text_3d) noexcept
    {
        // Set pointer to `object` to `nullptr`, set mesh according to the input,
        // and request a new apprenticeID from `new_text_3d`.

        if (object.object_type == yli::ontology::ObjectType::CHARACTER)
        {
            object.apprentice_of_mesh.unbind_and_bind_to_new_generic_master_module(
                    &new_text_3d.master_of_objects);
        }
        else
        {
            std::cerr << "ERROR: `Object::bind_to_new_text_3d_master`: only `CHARACTER` type `Object`s can be bound to `Text3D`!\n";
        }

        return std::nullopt;
    }

    Object::Object(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::ObjectStruct& object_struct,
            yli::ontology::GenericParentModule* const scene_parent_module,
            yli::ontology::GenericMasterModule* const mesh_master_module,
            yli::ontology::GenericMasterModule* const brain_master_module)
        : Movable(
                application,
                universe,
                object_struct,
                brain_master_module),
        child_of_scene(scene_parent_module, *this),
        apprentice_of_mesh(mesh_master_module, this)
    {
        // constructor.

        if (std::holds_alternative<yli::ontology::Species*>(object_struct.mesh_master))
        {
            this->object_type = yli::ontology::ObjectType::REGULAR;
        }
        else if (std::holds_alternative<yli::ontology::ShapeshifterSequence*>(object_struct.mesh_master))
        {
            this->object_type = yli::ontology::ObjectType::SHAPESHIFTER;
        }
        else if (std::holds_alternative<yli::ontology::Text3D*>(object_struct.mesh_master))
        {
            this->object_type = yli::ontology::ObjectType::CHARACTER;
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Object*";
        this->can_be_erased = true;
    }

    yli::ontology::Entity* Object::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    void Object::render(const yli::ontology::Scene* const target_scene)
    {
        // render this `Object`.

        if (!this->should_be_rendered)
        {
            return;
        }

        yli::ontology::Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene)
        {
            // Different `Scene`s, do not render.
            return;
        }

        if (this->object_type == yli::ontology::ObjectType::REGULAR ||
                this->object_type == yli::ontology::ObjectType::CHARACTER)
        {
            this->render_this_object(this->get_pipeline());
        }
        else if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
        {
            // TODO.
        }
    }

    void Object::render_this_object(yli::ontology::Pipeline* const pipeline)
    {
        if (this->universe.get_render_system() == nullptr)
        {
            std::cerr << "ERROR: `Object::render_this_object`: `this->universe.get_render_system()` is `nullptr`!\n";
            return;
        }

        if (pipeline == nullptr)
        {
            return;
        }

        if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
        {
            // TODO: implement rendering for `SHAPESHIFTER`!
            // Meanwhile this block just exists to exit this function.
            return;
        }

        this->model_matrix = glm::mat4(1.0f);

        if (this->object_type == yli::ontology::ObjectType::REGULAR)
        {
            yli::ontology::Species* const species = static_cast<yli::ontology::Species*>(this->apprentice_of_mesh.get_master());

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

        this->model_matrix = glm::scale(this->model_matrix, this->scale * this->original_scale_vector);
        glm::vec3 euler_angles { this->orientation.roll, this->orientation.yaw, this->orientation.pitch };
        glm::quat my_quaternion = glm::quat(euler_angles);
        glm::mat4 rotation_matrix = glm::mat4_cast(my_quaternion);
        this->model_matrix = rotation_matrix * this->model_matrix;
        this->model_matrix[3][0] = this->location.get_x();
        this->model_matrix[3][1] = this->location.get_y();
        this->model_matrix[3][2] = this->location.get_z();

        this->mvp_matrix = this->universe.get_projection_matrix() * this->universe.get_view_matrix() * this->model_matrix;

        if (this->universe.get_is_opengl_in_use())
        {
            // Send our transformation to the uniform buffer object (UBO).
            glBindBuffer(GL_UNIFORM_BUFFER, this->movable_uniform_block);
            glBufferSubData(GL_UNIFORM_BUFFER, yli::opengl::movable_ubo::MovableUboBlockOffsets::MVP, sizeof(glm::mat4), glm::value_ptr(this->mvp_matrix)); // mat4
            glBufferSubData(GL_UNIFORM_BUFFER, yli::opengl::movable_ubo::MovableUboBlockOffsets::M, sizeof(glm::mat4), glm::value_ptr(this->model_matrix)); // mat4
            glBindBuffer(GL_UNIFORM_BUFFER, 0);

            glBindBufferBase(GL_UNIFORM_BUFFER, yli::opengl::UboBlockIndices::MOVABLE, this->movable_uniform_block);
        }
        else if (this->universe.get_is_vulkan_in_use())
        {
            throw std::runtime_error("ERROR: `Object::render_this_object`: Vulkan is not supported yet!");
        }

        yli::ontology::MeshModule* master_model = nullptr;

        if (this->object_type == yli::ontology::ObjectType::REGULAR)
        {
            yli::ontology::Species* const master_species = static_cast<yli::ontology::Species*>(this->apprentice_of_mesh.get_master());

            if (master_species != nullptr)
            {
                master_model = &master_species->mesh;
            }
        }
        else if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
        {
            // TODO: set `master_model` so that it points to the correct `ShapeshifterForm` for the current frame!
            throw std::runtime_error("ERROR: `Object::render_this_object`: shapeshifters are not implemented yet!");
        }
        else if (this->object_type == yli::ontology::ObjectType::CHARACTER)
        {
            yli::ontology::Glyph* const master_glyph = static_cast<yli::ontology::Glyph*>(this->apprentice_of_mesh.get_master());

            if (master_glyph != nullptr)
            {
                master_model = &master_glyph->mesh;
            }
            else
            {
                return;
            }
        }

        if (this->universe.get_is_opengl_in_use() && master_model != nullptr)
        {
            GLuint vao                             = master_model->get_vao();
            GLuint vertexbuffer                    = master_model->get_vertexbuffer();
            uint32_t vertex_position_modelspace_id = master_model->get_vertex_position_modelspace_id();
            GLuint uvbuffer                        = master_model->get_uvbuffer();
            uint32_t vertex_uv_id                  = master_model->get_vertex_uv_id();
            GLuint normalbuffer                    = master_model->get_normalbuffer();
            uint32_t vertex_normal_modelspace_id   = master_model->get_vertex_normal_modelspace_id();
            GLuint elementbuffer                   = master_model->get_elementbuffer();
            uint32_t indices_size                  = master_model->get_indices_size();

            glBindVertexArray(vao);

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
            yli::opengl::enable_vertex_attrib_array(vertex_position_modelspace_id);

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
            yli::opengl::enable_vertex_attrib_array(vertex_uv_id);

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
            yli::opengl::enable_vertex_attrib_array(vertex_normal_modelspace_id);

            // Index buffer.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

            // Draw the triangles!
            glDrawElements(
                    GL_TRIANGLES,    // mode
                    indices_size,    // count
                    GL_UNSIGNED_INT, // type
                    (void*) 0        // element array buffer offset
                    );

            yli::opengl::disable_vertex_attrib_array(vertex_position_modelspace_id);
            yli::opengl::disable_vertex_attrib_array(vertex_uv_id);
            yli::opengl::disable_vertex_attrib_array(vertex_normal_modelspace_id);
        }
        else if (this->universe.get_is_vulkan_in_use() && master_model != nullptr)
        {
            throw std::runtime_error("ERROR: `Object::render_this_object`: Vulkan is not supported yet!");
        }
    }

    yli::ontology::Scene* Object::get_scene() const
    {
        return static_cast<yli::ontology::Scene*>(this->child_of_scene.get_parent());
    }

    yli::ontology::Pipeline* Object::get_pipeline() const
    {
        if (this->object_type == yli::ontology::ObjectType::REGULAR)
        {
            if (const auto* const species = static_cast<yli::ontology::Species*>(this->apprentice_of_mesh.get_master()); species != nullptr) [[likely]]
            {
                return species->get_pipeline();
            }

            throw std::runtime_error("ERROR: `Object::get_pipeline`: `species` is `nullptr`!");
        }
        else if (this->object_type == yli::ontology::ObjectType::SHAPESHIFTER)
        {
            if (const auto* const shapeshifter_sequence =
                    static_cast<yli::ontology::ShapeshifterSequence*>(this->apprentice_of_mesh.get_master()); shapeshifter_sequence != nullptr) [[likely]]
            {
                return shapeshifter_sequence->get_pipeline();
            }

            throw std::runtime_error("ERROR: `Object::get_pipeline`: `shapeshifter_sequence` is `nullptr`!");
        }
        else if (this->object_type == yli::ontology::ObjectType::CHARACTER)
        {
            if (const auto* const text_3d = static_cast<yli::ontology::Text3D*>(this->apprentice_of_mesh.get_master()); text_3d != nullptr) [[likely]]
            {
                return text_3d->get_pipeline();
            }

            throw std::runtime_error("ERROR: `Object::get_pipeline`: `text_3d` is `nullptr`!");
        }

        throw std::runtime_error("ERROR: `Object::get_pipeline`: unknown object type!");
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

    std::optional<yli::data::AnyValue> Object::create_object_with_parent_name_x_y_z(
            yli::ontology::Scene& parent,
            yli::ontology::Species& species,
            const std::string& object_name,
            const std::string& x,
            const std::string& y,
            const std::string& z)
    {
        return yli::ontology::Object::create_object_with_parent_name_x_y_z_yaw_pitch(parent, species, object_name, x, y, z, "0.0", "0.0");
    }

    std::optional<yli::data::AnyValue> Object::create_object_with_parent_name_x_y_z_yaw_pitch(
            yli::ontology::Scene& parent,
            yli::ontology::Species& species,
            const std::string& object_name,
            const std::string& x,
            const std::string& y,
            const std::string& z,
            const std::string& yaw,
            const std::string& pitch)
    {
        return yli::ontology::Object::create_object_with_parent_name_x_y_z_roll_yaw_pitch(parent, species, object_name, x, y, z, "0.0", yaw, pitch);
    }

    std::optional<yli::data::AnyValue> Object::create_object_with_parent_name_x_y_z_roll_yaw_pitch(
            yli::ontology::Scene& parent,
            yli::ontology::Species& species,
            const std::string& object_name,
            const std::string& x,
            const std::string& y,
            const std::string& z,
            const std::string& roll,
            const std::string& yaw,
            const std::string& pitch)
    {
        yli::ontology::GenericEntityFactory& entity_factory = parent.get_application().get_generic_entity_factory();

        yli::data::AnyValue x_any_value("float", x);
        yli::data::AnyValue y_any_value("float", y);
        yli::data::AnyValue z_any_value("float", z);
        yli::data::AnyValue roll_any_value("float", roll);
        yli::data::AnyValue yaw_any_value("float", yaw);
        yli::data::AnyValue pitch_any_value("float", pitch);

        if (!std::holds_alternative<float>(x_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `x`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(y_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `y`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(z_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `z`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(roll_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_roll_pitch`: invalid value for `roll`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(yaw_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `yaw`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(pitch_any_value.data))
        {
            std::cerr << "ERROR: `Object::create_object_with_parent_name_x_y_z_yaw_pitch`: invalid value for `pitch`!\n";
            return std::nullopt;
        }

        float float_x = std::get<float>(x_any_value.data);
        float float_y = std::get<float>(y_any_value.data);
        float float_z = std::get<float>(z_any_value.data);
        float float_roll = std::get<float>(roll_any_value.data);
        float float_yaw = std::get<float>(yaw_any_value.data);
        float float_pitch = std::get<float>(pitch_any_value.data);

        yli::ontology::ObjectStruct object_struct(&parent);
        object_struct.mesh_master = &species;
        object_struct.cartesian_coordinates = glm::vec3(float_x, float_y, float_z);
        object_struct.orientation = yli::ontology::OrientationModule(float_roll, float_yaw, float_pitch);
        object_struct.local_name = object_name;
        entity_factory.create_object(object_struct);
        return std::nullopt;
    }

    // Public callbacks end here.
}
