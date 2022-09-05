// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#include "movable.hpp"
#include "apprentice_module.hpp"
#include "universe.hpp"
#include "variable.hpp"
#include "brain.hpp"
#include "scene.hpp"
#include "movable_variable_activation.hpp"
#include "movable_variable_read.hpp"
#include "movable_struct.hpp"
#include "variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/pi.hpp"
#include "code/ylikuutio/opengl/ubo_block_enums.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <optional> // std::optional

// `Movable` is a mixin class, not intended to be instantiated.

namespace yli::ontology
{
    std::optional<yli::data::AnyValue> Movable::bind_to_new_brain(yli::ontology::Movable& movable, yli::ontology::Brain& new_brain) noexcept
    {
        // Set pointer to `movable` to `nullptr`, set brain according to the input,
        // and request a new apprenticeID from `new_brain`.

        // Master and apprentice must belong to the same `Scene`,
        // if both belong to some `Scene`, and not `Ecosystem`.
        if (movable.get_scene() == new_brain.get_scene() ||
                movable.get_scene() == nullptr ||
                new_brain.get_scene() == nullptr)
        {
            movable.apprentice_of_brain.unbind_and_bind_to_new_generic_master_module(&new_brain.master_of_movables);
        }
        else
        {
            std::cerr << "ERROR: `Movable::bind_to_new_brain`: master and apprentice can not belong to different `Scene`s!\n";
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Movable::unbind_from_brain(yli::ontology::Movable& movable) noexcept
    {
        movable.apprentice_of_brain.unbind_and_bind_to_new_generic_master_module(nullptr);
        return std::nullopt;
    }

    Movable::Movable(yli::ontology::Universe& universe,
            const yli::ontology::MovableStruct& movable_struct,
            yli::ontology::GenericMasterModule* const brain_master)
        : Entity(universe, movable_struct),
        apprentice_of_brain(brain_master, this),
        rigid_body_module(movable_struct.rigid_body_module_struct, movable_struct.scene, this),
        initial_rotate_vectors { movable_struct.initial_rotate_vectors },
        initial_rotate_angles { movable_struct.initial_rotate_angles },
        original_scale_vector { movable_struct.original_scale_vector },
        location(movable_struct.cartesian_coordinates),
        spherical_coordinates { movable_struct.spherical_coordinates },
        orientation(movable_struct.orientation.roll, movable_struct.orientation.yaw, movable_struct.orientation.pitch),
        input_method { movable_struct.input_method }
    {
        // constructor.

        if (this->universe.get_is_opengl_in_use())
        {
            // Uniform block for data related to this `Movable`.

            glGenBuffers(1, &this->movable_uniform_block);
            glBindBuffer(GL_UNIFORM_BUFFER, this->movable_uniform_block);
            glBufferData(GL_UNIFORM_BUFFER, yli::opengl::movable_ubo::MovableUboBlockOffsets::TOTAL_SIZE, nullptr, GL_STATIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        // Initialize speed, angular speed and maximum speed variables.
        // These are to be used from the `Brain` callbacks.

        this->create_coordinate_and_angle_variables();

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Movable*";
        this->can_be_erased = true;
    }

    const glm::vec3& Movable::get_cartesian_coordinates() const
    {
        return this->location.xyz;
    }

    void Movable::set_cartesian_coordinates(const glm::vec3& cartesian_coordinates)
    {
        this->location.xyz = cartesian_coordinates;
    }

    float Movable::get_roll() const
    {
        return this->orientation.roll;
    }

    void Movable::set_roll(const float roll)
    {
        this->orientation.roll = roll;
    }

    float Movable::get_yaw() const
    {
        return this->orientation.yaw;
    }

    void Movable::set_yaw(const float yaw)
    {
        this->orientation.yaw = yaw;
    }

    float Movable::get_pitch() const
    {
        return this->orientation.pitch;
    }

    void Movable::set_pitch(const float pitch)
    {
        this->orientation.pitch = pitch;
    }

    float Movable::get_azimuth() const
    {
        return 0.5f * pi - this->orientation.yaw;
    }

    void Movable::set_azimuth(const float azimuth)
    {
        this->orientation.yaw = 0.5f * pi - azimuth;
    }

    float Movable::get_scale() const
    {
        return this->scale;
    }

    void Movable::set_scale(const float scale)
    {
        this->scale = scale;
    }

    // Public callbacks (to be called from AI scripts written in YliLisp).

    void Movable::set_dest(yli::ontology::Movable* const movable, const float x, const float y, const float z)
    {
        // Set target towards which to move.
        movable->location.xyz = glm::vec3(x, y, z);
    }

    float Movable::get_x(const yli::ontology::Movable* const movable)
    {
        // Get x coordinate of `movable`.
        return movable->location.get_x();
    }

    float Movable::get_y(const yli::ontology::Movable* const movable)
    {
        // Get y coordinate of `movable`.
        return movable->location.get_y();
    }

    float Movable::get_z(const yli::ontology::Movable* const movable)
    {
        // Get z coordinate of `movable`.
        return movable->location.get_z();
    }

    float Movable::get_dest_x(const yli::ontology::Movable* const movable)
    {
        // Get x destination coordinate of `movable`.
        return movable->dest_cartesian_coordinates.x;
    }

    float Movable::get_dest_y(const yli::ontology::Movable* const movable)
    {
        // Get y destination coordinate of `movable`.
        return movable->dest_cartesian_coordinates.y;
    }

    float Movable::get_dest_z(const yli::ontology::Movable* const movable)
    {
        // Get z destination coordinate of `movable`.
        return movable->dest_cartesian_coordinates.z;
    }

    // Public callbacks end here.

    void Movable::create_coordinate_and_angle_variables()
    {
        float& float_x = this->location.xyz.x;
        float& float_y = this->location.xyz.y;
        float& float_z = this->location.xyz.z;

        yli::ontology::VariableStruct cartesian_coordinates_variable_struct;
        cartesian_coordinates_variable_struct.local_name = "cartesian";
        cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
        cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
        cartesian_coordinates_variable_struct.should_call_activate_callback_now = true;
        this->create_variable(cartesian_coordinates_variable_struct, yli::data::AnyValue(glm::vec3(float_x, float_y, float_z)));

        yli::ontology::VariableStruct x_variable_struct;
        x_variable_struct.local_name = "x";
        x_variable_struct.activate_callback = &yli::ontology::activate_x;
        x_variable_struct.read_callback = &yli::ontology::read_x;
        x_variable_struct.should_call_activate_callback_now = true;
        this->create_variable(x_variable_struct, yli::data::AnyValue(float_x));

        yli::ontology::VariableStruct y_variable_struct;
        y_variable_struct.local_name = "y";
        y_variable_struct.activate_callback = &yli::ontology::activate_y;
        y_variable_struct.read_callback = &yli::ontology::read_y;
        y_variable_struct.should_call_activate_callback_now = true;
        this->create_variable(y_variable_struct, yli::data::AnyValue(float_y));

        yli::ontology::VariableStruct z_variable_struct;
        z_variable_struct.local_name = "z";
        z_variable_struct.activate_callback = &yli::ontology::activate_z;
        z_variable_struct.read_callback = &yli::ontology::read_z;
        z_variable_struct.should_call_activate_callback_now = true;
        this->create_variable(z_variable_struct, yli::data::AnyValue(float_z));

        yli::ontology::VariableStruct roll_variable_struct;
        roll_variable_struct.local_name = "roll";
        roll_variable_struct.activate_callback = &yli::ontology::activate_roll;
        roll_variable_struct.read_callback = &yli::ontology::read_roll;
        roll_variable_struct.should_call_activate_callback_now = true;
        this->create_variable(roll_variable_struct, yli::data::AnyValue(this->orientation.roll));

        yli::ontology::VariableStruct yaw_variable_struct;
        yaw_variable_struct.local_name = "yaw";
        yaw_variable_struct.activate_callback = &yli::ontology::activate_yaw;
        yaw_variable_struct.read_callback = &yli::ontology::read_yaw;
        yaw_variable_struct.should_call_activate_callback_now = true;
        this->create_variable(yaw_variable_struct, yli::data::AnyValue(this->orientation.yaw));

        yli::ontology::VariableStruct pitch_variable_struct;
        pitch_variable_struct.local_name = "pitch";
        pitch_variable_struct.activate_callback = &yli::ontology::activate_pitch;
        pitch_variable_struct.read_callback = &yli::ontology::read_pitch;
        pitch_variable_struct.should_call_activate_callback_now = true;
        this->create_variable(pitch_variable_struct, yli::data::AnyValue(this->orientation.pitch));

        const float azimuth = 0.0f;
        yli::ontology::VariableStruct azimuth_variable_struct;
        azimuth_variable_struct.local_name = "azimuth";
        azimuth_variable_struct.activate_callback = &yli::ontology::activate_azimuth;
        azimuth_variable_struct.read_callback = &yli::ontology::read_azimuth;
        azimuth_variable_struct.should_call_activate_callback_now = false;
        this->create_variable(azimuth_variable_struct, yli::data::AnyValue(azimuth));

        const float scale = this->scale;
        yli::ontology::VariableStruct scale_variable_struct;
        scale_variable_struct.local_name = "scale";
        scale_variable_struct.activate_callback = &yli::ontology::activate_scale;
        scale_variable_struct.should_call_activate_callback_now = true;
        this->create_variable(scale_variable_struct, yli::data::AnyValue(scale));

        const float speed = this->speed;
        yli::ontology::VariableStruct speed_variable_struct;
        speed_variable_struct.local_name = "speed";
        speed_variable_struct.activate_callback = &yli::ontology::Variable::activate_speed;
        speed_variable_struct.should_call_activate_callback_now = true;
        this->create_variable(speed_variable_struct, yli::data::AnyValue(speed));
    }
}
