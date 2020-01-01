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

#ifndef __MOVABLE_HPP_INCLUDED
#define __MOVABLE_HPP_INCLUDED

#include "entity.hpp"
#include "movable_struct.hpp"
#include "code/ylikuutio/common/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <limits>   // std::numeric_limits
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <vector>   // std::vector

// `Movable` is a mixin class, not intended to be instantiated.
//
// So far there are 4 kinds of `Movable`s implemented:
// `Object`    - child of `Species`.
// `Holobiont` - child of `Symbiosis`.
// `Biont`     - child of `Holobiont`.
// `Camera`    - non-material `Movable`, child of `Scene`.
//
// `Text3D`, child of `VectorFont`, is not implemented yet.

namespace yli
{
    namespace input
    {
        enum class InputMethod;
    }

    namespace ontology
    {
        class Universe;
        class Brain;
        class Waypoint;

        class Movable: public yli::ontology::Entity
        {
            public:
                void bind_to_Brain();
                void unbind_from_Brain();

                // This method sets pointer to this `Movable` to `nullptr`, sets `brain` according to the input, and requests a new `movableID` from the new `Brain`.
                void bind_to_new_Brain(yli::ontology::Brain* const new_brain);

                // constructor.
                Movable(yli::ontology::Universe* const universe, const yli::ontology::MovableStruct& movable_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->brain                       = movable_struct.brain;
                    this->movableID                   = std::numeric_limits<std::size_t>::max(); // uninitialized.
                    this->cartesian_coordinates.x     = movable_struct.cartesian_coordinates.x;
                    this->cartesian_coordinates.y     = movable_struct.cartesian_coordinates.y;
                    this->cartesian_coordinates.z     = movable_struct.cartesian_coordinates.z;
                    this->spherical_coordinates.rho   = movable_struct.spherical_coordinates.rho;
                    this->spherical_coordinates.theta = movable_struct.spherical_coordinates.theta;
                    this->spherical_coordinates.phi   = movable_struct.spherical_coordinates.phi;
                    this->horizontal_angle            = movable_struct.horizontal_angle;
                    this->vertical_angle              = movable_struct.vertical_angle;

                    // Initialize speed, angular speed and maximum speed variables.
                    // These are to be used from the `Brain` callbacks.
                    this->speed                       = 0.0f;
                    this->angular_speed               = 0.0f;
                    this->max_land_speed              = 0.0f;
                    this->max_land_angular_speed      = 0.0f;
                    this->land_acceleration           = 0.0f;
                    this->land_deceleration           = 0.0f;
                    this->max_rail_speed              = 0.0f;
                    this->rail_acceleration           = 0.0f;
                    this->rail_deceleration           = 0.0f;
                    this->max_water_speed             = 0.0f;
                    this->max_water_angular_speed     = 0.0f;
                    this->water_acceleration          = 0.0f;
                    this->water_deceleration          = 0.0f;
                    this->max_air_speed               = 0.0f;
                    this->max_air_angular_speed       = 0.0f;
                    this->air_acceleration            = 0.0f;
                    this->air_deceleration            = 0.0f;

                    this->model_matrix                = glm::mat4(1.0f); // identity matrix (dummy value).
                    this->MVP_matrix                  = glm::mat4(1.0f); // identity matrix (dummy value).

                    float float_x                     = this->cartesian_coordinates.x;
                    float float_y                     = this->cartesian_coordinates.y;
                    float float_z                     = this->cartesian_coordinates.z;

                    yli::config::SettingMaster* const setting_master = this->get_setting_master();

                    yli::config::SettingStruct cartesian_coordinates_setting_struct(std::make_shared<yli::common::AnyValue>(new glm::vec3(float_x, float_y, float_z)));
                    cartesian_coordinates_setting_struct.name = "cartesian_coordinates";
                    cartesian_coordinates_setting_struct.activate_callback = &yli::config::SettingMaster::activate_cartesian_coordinates;
                    cartesian_coordinates_setting_struct.read_callback = &yli::config::SettingMaster::read_cartesian_coordinates;
                    cartesian_coordinates_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `setting_master->create_Setting(cartesian_coordinates_setting_struct);` ...\n";
                    setting_master->create_Setting(cartesian_coordinates_setting_struct);

                    yli::config::SettingStruct x_setting_struct(std::make_shared<yli::common::AnyValue>(float_x));
                    x_setting_struct.name = "x";
                    x_setting_struct.activate_callback = &yli::config::SettingMaster::activate_x;
                    x_setting_struct.read_callback = &yli::config::SettingMaster::read_x;
                    x_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `setting_master->create_Setting(x_setting_struct);` ...\n";
                    setting_master->create_Setting(x_setting_struct);

                    yli::config::SettingStruct y_setting_struct(std::make_shared<yli::common::AnyValue>(float_y));
                    y_setting_struct.name = "y";
                    y_setting_struct.activate_callback = &yli::config::SettingMaster::activate_y;
                    y_setting_struct.read_callback = &yli::config::SettingMaster::read_y;
                    y_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `setting_master->create_Setting(y_setting_struct);` ...\n";
                    setting_master->create_Setting(y_setting_struct);

                    yli::config::SettingStruct z_setting_struct(std::make_shared<yli::common::AnyValue>(float_z));
                    z_setting_struct.name = "z";
                    z_setting_struct.activate_callback = &yli::config::SettingMaster::activate_z;
                    z_setting_struct.read_callback = &yli::config::SettingMaster::read_z;
                    z_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `setting_master->create_Setting(z_setting_struct);` ...\n";
                    setting_master->create_Setting(z_setting_struct);

                    yli::config::SettingStruct horizontal_angle_setting_struct(std::make_shared<yli::common::AnyValue>(this->horizontal_angle));
                    horizontal_angle_setting_struct.name = "horizontal_angle";
                    horizontal_angle_setting_struct.activate_callback = &yli::config::SettingMaster::activate_horizontal_angle;
                    horizontal_angle_setting_struct.read_callback = &yli::config::SettingMaster::read_horizontal_angle;
                    horizontal_angle_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `setting_master->create_Setting(horizontal_angle_setting_struct);` ...\n";
                    setting_master->create_Setting(horizontal_angle_setting_struct);

                    yli::config::SettingStruct vertical_angle_setting_struct(std::make_shared<yli::common::AnyValue>(this->vertical_angle));
                    vertical_angle_setting_struct.name = "vertical_angle";
                    vertical_angle_setting_struct.activate_callback = &yli::config::SettingMaster::activate_vertical_angle;
                    vertical_angle_setting_struct.read_callback = &yli::config::SettingMaster::read_vertical_angle;
                    vertical_angle_setting_struct.should_ylikuutio_call_activate_callback_now = true;
                    std::cout << "Executing `setting_master->create_Setting(vertical_angle_setting_struct);` ...\n";
                    setting_master->create_Setting(vertical_angle_setting_struct);

                    this->bind_to_Brain();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Movable*";
                    this->can_be_erased = true;
                }

                Movable(const Movable&) = delete;            // Delete copy constructor.
                Movable &operator=(const Movable&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Movable();

                const glm::vec3& get_cartesian_coordinates() const;
                void set_cartesian_coordinates(const glm::vec3& cartesian_coordinates);
                const float get_horizontal_angle() const;
                void set_horizontal_angle(const float horizontal_angle);
                const float get_vertical_angle() const;
                void set_vertical_angle(const float vertical_angle);

                // Public callbacks (to be called from AI scripts written in s7).
                // These are the functions that are available for AI scripts.
                // Ylikuutio will support scripting of game agents using s7.
                // Ylikuutio can be used for all kinds of games. However, there is
                // more support for some kinds of games needing such callbacks.
                // In particular, Ylikuutio supports simulations of real-life phenomena.
                // TODO: implement public AI callbacks!

                // Command callbacks.

                // Set target towards which to move.
                static void set_dest(yli::ontology::Movable* const movable, const float x, const float y, const float z);

                // Set target towards which to move.
                static void set_spherical_dest(yli::ontology::Movable* const movable, const float rho, const float theta, const float phi);

                // Get x coordinate of `object`.
                static float get_x(const yli::ontology::Movable* const movable);

                // Get y coordinate of `object`.
                static float get_y(const yli::ontology::Movable* const movable);

                // Get z destination coordinate of `object`.
                static float get_z(const yli::ontology::Movable* const movable);

                // Get rho coordinate of `object`.
                static float get_rho(const yli::ontology::Movable* const movable);

                // Get theta coordinate of `object`.
                static float get_theta(const yli::ontology::Movable* const movable);

                // Get phi destination coordinate of `object`.
                static float get_phi(const yli::ontology::Movable* const movable);

                // Get x destination coordinate of `object`.
                static float get_dest_x(const yli::ontology::Movable* const movable);

                // Get y destination coordinate of `object`.
                static float get_dest_y(const yli::ontology::Movable* const movable);

                // Get z coordinate of `object`.
                static float get_dest_z(const yli::ontology::Movable* const movable);

                // Get rho destination coordinate of `object`.
                static float get_dest_rho(const yli::ontology::Movable* const movable);

                // Get theta destination coordinate of `object`.
                static float get_dest_theta(const yli::ontology::Movable* const movable);

                // Get phi destination destination coordinate of `object`.
                static float get_dest_phi(const yli::ontology::Movable* const movable);

                // Public callbacks end here.

                // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
                glm::vec3 cartesian_coordinates;                       // cartesian coordinates.

                // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
                yli::common::SphericalCoordinatesStruct spherical_coordinates;      // spherical coordinates.

                glm::vec3 dest_cartesian_coordinates;                  // cartesian destination coordinates.
                yli::common::SphericalCoordinatesStruct dest_spherical_coordinates; // spherical destination coordinates.

                // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
                glm::vec3 direction;

                glm::vec3 right;                                       // note: can not be set directly using console.
                glm::vec3 up;                                          // note: can not be set directly using console.

                double horizontal_angle;
                double vertical_angle;

                float speed;                                           // m/s
                float angular_speed;                                   // 1/s
                float max_land_speed;                                  // m/s
                float max_land_angular_speed;                          // 1/s
                float land_acceleration;                               // m/s^2
                float land_deceleration;                               // m/s^2
                float max_rail_speed;                                  // m/s. By the way, there is no angular speed for railways.
                float rail_acceleration;                               // m/s^2
                float rail_deceleration;                               // m/s^2
                float max_water_speed;                                 // m/s
                float max_water_angular_speed;                         // 1/s
                float water_acceleration;                              // m/s^2
                float water_deceleration;                              // m/s^2
                float max_air_speed;                                   // m/s
                float max_air_angular_speed;                           // 1/s
                float air_acceleration;                                // m/s^2
                float air_deceleration;                                // m/s^2
                std::vector<yli::ontology::Waypoint*> waypoints;       // Used for actual waypoints. `Brain` can use these freely.
                std::vector<yli::ontology::Waypoint*> control_points;  // Used as B-spline/Bézier/etc. control points. `Brain` can use these freely.

                // The rest fields are created in the constructor.
                glm::mat4 model_matrix;                                // model matrix.
                glm::mat4 MVP_matrix;                                  // model view projection matrix.

                friend class Brain;

            private:
                yli::input::InputMethod input_method;                  // If `input_method` is `KEYBOARD`, then keypresses control this `Movable`.
                                                                       // If `input_method` is `AI`, then the chosen `Brain` controls this `Movable`.
                yli::ontology::Brain* brain;                           // Different kind of controls can be implemented as `Brain`s, e.g. train control systems.
                std::size_t movableID;
        };
    }
}

#endif
