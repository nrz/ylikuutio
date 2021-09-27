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

#ifndef __YLIKUUTIO_ONTOLOGY_MOVABLE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MOVABLE_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_master_module.hpp"
#include "apprentice_module.hpp"
#include "rigid_body_module.hpp"
#include "movable_struct.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
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

namespace yli::input
{
    enum class InputMethod;
}

namespace yli::ontology
{
    class ParentModule;
    class GenericMasterModule;
    class Universe;
    class Brain;
    class Waypoint;

    class Movable: public yli::ontology::Entity
    {
        public:
            void bind_to_new_brain(yli::ontology::Brain* const new_brain);

            Movable(yli::ontology::Universe* const universe,
                    const yli::ontology::MovableStruct& movable_struct,
                    yli::ontology::ParentModule* const parent_module,
                    yli::ontology::GenericMasterModule* const generic_master_module)
                : Entity(universe, movable_struct),
                child(parent_module, this),
                apprentice_of_brain(generic_master_module, this),
                rigid_body_module(movable_struct.rigid_body_module_struct, movable_struct.scene, this),
                initial_rotate_vectors { movable_struct.initial_rotate_vectors },
                initial_rotate_angles { movable_struct.initial_rotate_angles },
                original_scale_vector { movable_struct.original_scale_vector },
                cartesian_coordinates { movable_struct.cartesian_coordinates },
                spherical_coordinates { movable_struct.spherical_coordinates },
                yaw { movable_struct.yaw },
                pitch { movable_struct.pitch },
                input_method { movable_struct.input_method }
            {
                // constructor.

                // Initialize speed, angular speed and maximum speed variables.
                // These are to be used from the `Brain` callbacks.

                this->create_coordinate_and_angle_variables();

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Movable*";
                this->can_be_erased = true;
            }

            Movable(const Movable&) = delete;            // Delete copy constructor.
            Movable& operator=(const Movable&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Movable();

            yli::ontology::Entity* get_parent() const override;

            const glm::vec3& get_cartesian_coordinates() const;
            void set_cartesian_coordinates(const glm::vec3& cartesian_coordinates);
            float get_yaw() const;
            void set_yaw(const float yaw);
            float get_pitch() const;
            void set_pitch(const float pitch);
            float get_azimuth() const;
            void set_azimuth(const float azimuth);

            // Public callbacks (to be called from AI scripts written in YliLisp).
            // These are the functions that are available for AI scripts.
            // Ylikuutio will support scripting of game agents using YliLisp.
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

            // Allied-object-centric path and map information callbacks.

            // This method returns `true` if destination is visible, `false` otherwise.
            // destination may be visible directly (line of sight) or eg. by radar (without line of sight).
            static bool is_visible(const float x, const float y, const float z);

            // This method returns `true` if destination is visible with a line of sight for any own `Object`, `false` otherwise.
            static bool is_line_of_sight_for_any(const float x, const float y, const float z);

            // This method returns `true` if destination is visible with a line of sight for any own `Object`, `false` otherwise.
            static bool is_line_of_sight(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // This method returns `true` if there is any known ground path between `Object` and (x, y, z),  `false` otherwise.
            static bool is_ground_path_known(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // This method returns `true` if there is any known rail path between `Object` and (x, y, z),  `false` otherwise.
            static bool is_rail_path_known(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // This method returns `true` if there is known air path between objects, `false` otherwise.
            static bool is_air_path_known(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // This method returns `true` if there is known ballistic path between `Object` and (x, y, z), `false` otherwise.
            static bool is_ballistic_path_known(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // This method returns `true` if there may be ballistic path between objects, `false` otherwise.
            static bool may_have_ballistic_path(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // These functions return the coordinates of the farthest point.
            static float get_closest_visible_ground_dest_x_towards(const yli::ontology::Object* const object, const float x, const float y, const float z);
            static float get_closest_visible_ground_dest_y_towards(const yli::ontology::Object* const object, const float x, const float y, const float z);
            static float get_closest_visible_ground_dest_z_towards(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // This method returns `true` if complete path is visible, `false` otherwise.
            static bool is_complete_ground_path_visible(const yli::ontology::Object* const object, const float x, const float y, const float z);
            static bool is_complete_rail_path_visible(const yli::ontology::Object* const object, const float x, const float y, const float z);
            static bool is_complete_air_path_visible(const yli::ontology::Object* const object, const float x, const float y, const float z);
            static bool is_complete_ballistic_path_visible(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // These methods return the coordinates of the point closest to `object` from which there is known ballistic path to (x, y, z).
            static float get_nearest_known_ballistic_launch_site_x(const yli::ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_known_ballistic_launch_site_y(const yli::ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_known_ballistic_launch_site_z(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // These methods return the coordinates of the point closest to `object` from which there may be a ballistic path to (x, y, z).
            static float get_nearest_possible_ballistic_launch_site_x(const yli::ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_possible_ballistic_launch_site_y(const yli::ontology::Object* const object, const float x, const float y, const float z);
            static float get_nearest_possible_ballistic_launch_site_z(const yli::ontology::Object* const object, const float x, const float y, const float z);

            // This method returns `true` if there is known line of sight between (x1, y1, z1) and (x2, y2, z2).

            // Coordinate-centric path and map information callbacks.
            // The conditions for returning `true` match the conditions of the corresponding allied-object-centric callbacks.

            static bool is_line_of_sight_between_from(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool may_have_line_of_sight_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_ground_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_rail_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_air_path_known_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool is_ballistic_path_known(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static bool may_have_ballistic_path_between(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            static float get_nearest_known_ballistic_launch_site_x(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_known_ballistic_launch_site_y(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_known_ballistic_launch_site_z(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            static float get_nearest_possible_ballistic_launch_site_x(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_possible_ballistic_launch_site_y(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_nearest_possible_ballistic_launch_site_z(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            static float get_closest_visible_dest_x_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_closest_visible_dest_y_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);
            static float get_closest_visible_dest_z_towards(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2);

            // Callbacks for looping through objects.
            static void* get_first_allied_object(yli::ontology::Object* object);       // point `allied_iterator` to the first object, `nullptr` if N/A.
            static void* get_next_allied_object(yli::ontology::Object* object);        // advance `allied_iterator`, `nullptr` if N/A.
            static void* get_first_other_allied_object(yli::ontology::Object* object); // point `allied_other_iterator` to the first other object, `nullptr` if N/A.
            static void* get_next_other_allied_object(yli::ontology::Object* object);  // advance `allied_other_iterator`, `nullptr` if N/A.
            static void* get_first_opponent_object(yli::ontology::Object* object);     // point `opponent_iterator` to the first opponent, `nullptr` if N/A.
            static void* get_next_opponent_object(yli::ontology::Object* object);      // advance `opponent_iterator`, `nullptr` if N/A.

            // Public callbacks end here.

        private:
            void create_coordinate_and_angle_variables();

            friend class yli::ontology::Brain;
            friend class yli::ontology::GenericMasterModule;

            template<class T1>
                friend void yli::hierarchy::bind_apprentice_to_master(T1 apprentice_pointer, std::vector<T1>& apprentice_pointer_vector, std::queue<std::size_t>& free_apprenticeID_queue, std::size_t& number_of_apprenticeren);

        protected:
            yli::ontology::ChildModule child;

        public:
            yli::ontology::ApprenticeModule apprentice_of_brain;

        private:
            yli::ontology::RigidBodyModule rigid_body_module;

        public:
            std::vector<glm::vec3> initial_rotate_vectors;
            std::vector<float> initial_rotate_angles;

            glm::vec3 original_scale_vector { glm::vec3(1.0f, 1.0f, 1.0f) };

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            glm::vec3 cartesian_coordinates;                       // cartesian coordinates.

            // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
            yli::data::SphericalCoordinatesStruct spherical_coordinates;      // spherical coordinates.

            glm::vec3 dest_cartesian_coordinates;                  // cartesian destination coordinates.
            yli::data::SphericalCoordinatesStruct dest_spherical_coordinates; // spherical destination coordinates.

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 direction { glm::vec3(NAN, NAN, NAN) };

            glm::vec3 right { glm::vec3(NAN, NAN, NAN) };          // note: can not be set directly using console.
            glm::vec3 up { glm::vec3(NAN, NAN, NAN) };             // note: can not be set directly using console.

            float yaw                     { 0.0f };
            float pitch                   { 0.0f };
            float speed                   { 0.0f };                // m/s
            float angular_speed           { 0.0f };                // 1/s
            float max_land_speed          { 0.0f };                // m/s
            float max_land_angular_speed  { 0.0f };                // 1/s
            float land_acceleration       { 0.0f };                // m/s^2
            float land_deceleration       { 0.0f };                // m/s^2
            float max_rail_speed          { 0.0f };                // m/s. By the way, there is no angular speed for railways.
            float rail_acceleration       { 0.0f };                // m/s^2
            float rail_deceleration       { 0.0f };                // m/s^2
            float max_water_speed         { 0.0f };                // m/s
            float max_water_angular_speed { 0.0f };                // 1/s
            float water_acceleration      { 0.0f };                // m/s^2
            float water_deceleration      { 0.0f };                // m/s^2
            float max_air_speed           { 0.0f };                // m/s
            float max_air_angular_speed   { 0.0f };                // 1/s
            float air_acceleration        { 0.0f };                // m/s^2
            float air_deceleration        { 0.0f };                // m/s^2
            std::vector<yli::ontology::Waypoint*> waypoints;       // Used for actual waypoints. `Brain` can use these freely.
            std::vector<yli::ontology::Waypoint*> control_points;  // Used as B-spline/Bézier/etc. control points. `Brain` can use these freely.

            // The rest fields are created in the constructor.
            glm::mat4 model_matrix { glm::mat4(1.0f) };            // model matrix (initialized with dummy value).
            glm::mat4 mvp_matrix { glm::mat4(1.0f) };              // model view projection matrix (initialized with dummy value).


            yli::input::InputMethod input_method;                  // If `input_method` is `KEYBOARD`, then keypresses control this `Movable`.
                                                                   // If `input_method` is `AI`, then the chosen `Brain` controls this `Movable`.
    };
}

#endif
