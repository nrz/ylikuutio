// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include "cartesian_coordinates_module.hpp"
#include "orientation_module.hpp"
#include "pipeline.hpp"
#include "scene.hpp"
#include "species.hpp"
#include "text_3d.hpp"
#include "generic_entity_factory.hpp"
#include "request.hpp"
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
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;

    std::optional<yli::data::AnyValue> Object::bind_to_new_scene_parent(
            Object& object,
            Scene& new_parent)
    {
        // Set pointer to `object` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const Scene* const old_scene_parent = object.get_scene();

        if (old_scene_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Object::bind_to_new_scene_parent`: `old_scene_parent` is `nullptr`!");
        }

        if (&new_parent == old_scene_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(object.local_name))
        {
            std::cerr << "ERROR: `Object::bind_to_new_scene_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        object.apprentice_of_species.unbind_from_any_master_belonging_to_other_scene(new_parent);
        object.child_of_scene.unbind_and_bind_to_new_parent(&new_parent.parent_of_objects);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Object::bind_to_new_species_master(
            Object& object,
            Species& new_species) noexcept
    {
        // Set pointer to `object` to `nullptr`, set mesh according to the input,
        // and request a new apprenticeID from `new_species`.

        // Master and apprentice must belong to the same `Scene`,
        // if both belong to some `Scene`, and not `Ecosystem`.
        if (object.get_scene() == new_species.get_scene() ||
                object.get_scene() == nullptr ||
                new_species.get_scene() == nullptr)
        {
            object.apprentice_of_species.unbind_and_bind_to_new_generic_master_module(
                    &new_species.master_of_objects);
        }
        else
        {
            std::cerr << "ERROR: `Object::bind_to_new_species_master`: master and apprentice can not belong to different `Scene`s!\n";
        }

        return std::nullopt;
    }

    Object::Object(
            yli::core::Application& application,
            Universe& universe,
            const ObjectStruct& object_struct,
            GenericParentModule* const scene_parent_module,
            GenericMasterModule* const brain_master_module,
            GenericMasterModule* const species_master_module)
        : Movable(
                application,
                universe,
                object_struct,
                brain_master_module),
        child_of_scene(scene_parent_module, *this),
        apprentice_of_species(species_master_module, this)
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Object*";
        this->can_be_erased = true;
    }

    Entity* Object::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    void Object::render(const Scene* const target_scene)
    {
        // render this `Object`.

        if (!this->should_render) [[unlikely]]
        {
            return;
        }

        Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene) [[unlikely]]
        {
            // Different `Scene`s, do not render.
            return;
        }

        this->render_this_object(this->get_pipeline());
    }

    void Object::render_this_object(Pipeline* const pipeline)
    {
        if (this->universe.get_render_system() == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Object::render_this_object`: `this->universe.get_render_system()` is `nullptr`!");
        }

        if (pipeline == nullptr) [[unlikely]]
        {
            return;
        }

        this->model_matrix = glm::mat4(1.0f);

        Species* const species = static_cast<Species*>(this->apprentice_of_species.get_master());

        if (species == nullptr) [[unlikely]]
        {
            return;
        }

        if (this->initial_rotate_vectors.size() == this->initial_rotate_angles.size()) [[likely]]
        {
            for (std::size_t i = 0; i < this->initial_rotate_vectors.size() && i < this->initial_rotate_angles.size(); i++)
            {
                this->model_matrix = glm::rotate(this->model_matrix, this->initial_rotate_angles[i], this->initial_rotate_vectors[i]);
            }
        }

        this->model_matrix = glm::scale(this->model_matrix, this->scale * this->original_scale_vector);
        glm::vec3 euler_angles { this->orientation.roll, -this->orientation.pitch, this->orientation.yaw };
        glm::quat my_quaternion = glm::quat(euler_angles);
        glm::mat4 rotation_matrix = glm::mat4_cast(my_quaternion);
        this->model_matrix = rotation_matrix * this->model_matrix;
        this->model_matrix[3][0] = this->location.get_x();
        this->model_matrix[3][1] = this->location.get_y();
        this->model_matrix[3][2] = this->location.get_z();

        this->mvp_matrix = this->universe.get_projection_matrix() * this->universe.get_view_matrix() * this->model_matrix;

        if (this->universe.get_is_opengl_in_use()) [[likely]]
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

        MeshModule* master_model = nullptr;

        Species* const master_species = static_cast<Species*>(this->apprentice_of_species.get_master());

        if (master_species != nullptr)
        {
            master_model = &master_species->mesh;
        }

        if (this->universe.get_is_opengl_in_use() && master_model != nullptr) [[likely]]
        {
            const GLuint vao                             = master_model->get_vao();
            const GLuint vertex_buffer                   = master_model->get_vertex_buffer();
            const uint32_t vertex_position_modelspace_id = master_model->get_vertex_position_modelspace_id();
            const GLuint uvbuffer                        = master_model->get_uvbuffer();
            const uint32_t vertex_uv_id                  = master_model->get_vertex_uv_id();
            const GLuint normalbuffer                    = master_model->get_normalbuffer();
            const uint32_t vertex_normal_modelspace_id   = master_model->get_vertex_normal_modelspace_id();
            const GLuint elementbuffer                   = master_model->get_elementbuffer();
            const uint32_t indices_size                  = master_model->get_indices_size();

            glBindVertexArray(vao);

            // 1st attribute buffer: vertices.
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            glVertexAttribPointer(
                    vertex_position_modelspace_id, // The attribute we want to configure
                    3,                             // size
                    GL_FLOAT,                      // type
                    GL_FALSE,                      // normalized?
                    0,                             // stride
                    nullptr                        // array buffer offset
                    );
            yli::opengl::enable_vertex_attrib_array(vertex_position_modelspace_id);

            // 2nd attribute buffer: UVs.
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glVertexAttribPointer(
                    vertex_uv_id, // The attribute we want to configure
                    2,            // size : U+V => 2
                    GL_FLOAT,     // type
                    GL_FALSE,     // normalized?
                    0,            // stride
                    nullptr       // array buffer offset
                    );
            yli::opengl::enable_vertex_attrib_array(vertex_uv_id);

            // 3rd attribute buffer: normals.
            glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
            glVertexAttribPointer(
                    vertex_normal_modelspace_id, // The attribute we want to configure
                    3,                           // size
                    GL_FLOAT,                    // type
                    GL_FALSE,                    // normalized?
                    0,                           // stride
                    nullptr                      // array buffer offset
                    );
            yli::opengl::enable_vertex_attrib_array(vertex_normal_modelspace_id);

            // Index buffer.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

            // Draw the triangles!
            glDrawElements(
                    GL_TRIANGLES,    // mode
                    indices_size,    // count
                    GL_UNSIGNED_INT, // type
                    nullptr          // element array buffer offset
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

    Scene* Object::get_scene() const
    {
        return static_cast<Scene*>(this->child_of_scene.get_parent());
    }

    Pipeline* Object::get_pipeline() const
    {
        if (const auto* const species = static_cast<Species*>(this->apprentice_of_species.get_master()); species != nullptr) [[likely]]
        {
            return species->get_pipeline();
        }

        throw std::runtime_error("ERROR: `Object::get_pipeline`: `species` is `nullptr`!");
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

    std::optional<yli::data::AnyValue> Object::with_parent_name_x_y_z(
            Scene& parent,
            Species& species,
            const std::string& object_name,
            const std::string& x,
            const std::string& y,
            const std::string& z)
    {
        return Object::with_parent_name_x_y_z_yaw_pitch(parent, species, object_name, x, y, z, "0.0", "0.0");
    }

    std::optional<yli::data::AnyValue> Object::with_parent_name_x_y_z_yaw_pitch(
            Scene& parent,
            Species& species,
            const std::string& object_name,
            const std::string& x,
            const std::string& y,
            const std::string& z,
            const std::string& yaw,
            const std::string& pitch)
    {
        return Object::with_parent_name_x_y_z_roll_yaw_pitch(parent, species, object_name, x, y, z, "0.0", yaw, pitch);
    }

    std::optional<yli::data::AnyValue> Object::with_parent_name_x_y_z_roll_yaw_pitch(
            Scene& parent,
            Species& species,
            const std::string& object_name,
            const std::string& x,
            const std::string& y,
            const std::string& z,
            const std::string& roll,
            const std::string& yaw,
            const std::string& pitch)
    {
        GenericEntityFactory& entity_factory = parent.get_application().get_generic_entity_factory();

        yli::data::AnyValue x_any_value("float", x);
        yli::data::AnyValue y_any_value("float", y);
        yli::data::AnyValue z_any_value("float", z);
        yli::data::AnyValue roll_any_value("float", roll);
        yli::data::AnyValue yaw_any_value("float", yaw);
        yli::data::AnyValue pitch_any_value("float", pitch);

        if (!std::holds_alternative<float>(x_any_value.data))
        {
            std::cerr << "ERROR: `Object::with_parent_name_x_y_z_yaw_pitch`: invalid value for `x`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(y_any_value.data))
        {
            std::cerr << "ERROR: `Object::with_parent_name_x_y_z_yaw_pitch`: invalid value for `y`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(z_any_value.data))
        {
            std::cerr << "ERROR: `Object::with_parent_name_x_y_z_yaw_pitch`: invalid value for `z`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(roll_any_value.data))
        {
            std::cerr << "ERROR: `Object::with_parent_name_x_y_z_roll_pitch`: invalid value for `roll`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(yaw_any_value.data))
        {
            std::cerr << "ERROR: `Object::with_parent_name_x_y_z_yaw_pitch`: invalid value for `yaw`!\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<float>(pitch_any_value.data))
        {
            std::cerr << "ERROR: `Object::with_parent_name_x_y_z_yaw_pitch`: invalid value for `pitch`!\n";
            return std::nullopt;
        }

        float float_x = std::get<float>(x_any_value.data);
        float float_y = std::get<float>(y_any_value.data);
        float float_z = std::get<float>(z_any_value.data);
        float float_roll = std::get<float>(roll_any_value.data);
        float float_yaw = std::get<float>(yaw_any_value.data);
        float float_pitch = std::get<float>(pitch_any_value.data);

        ObjectStruct object_struct { Request<Scene>(&parent) };
        object_struct.species_master = Request(&species);
        object_struct.cartesian_coordinates = CartesianCoordinatesModule(float_x, float_y, float_z);
        object_struct.orientation = OrientationModule(float_roll, float_yaw, float_pitch);
        object_struct.local_name = object_name;
        entity_factory.create_object(object_struct);
        return std::nullopt;
    }

    // Public callbacks end here.
}
