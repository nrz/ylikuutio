// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_MOVABLE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MOVABLE_HPP_INCLUDED

#include "entity.hpp"
#include "generic_master_module.hpp"
#include "apprentice_module.hpp"
#include "cartesian_coordinates_module.hpp"
#include "orientation_module.hpp"
#include "rigid_body_module.hpp"
#include "movable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN
#include <optional> // std::optional
#include <vector>   // std::vector

// `Movable` is a mixin class, not intended to be instantiated.
//
// So far there are 4 kinds of `Movable`s implemented:
// `Object`    - child of `Species`.
// `Holobiont` - child of `Symbiosis`.
// `Biont`     - child of `Holobiont`.
// `Camera`    - non-material `Movable`, child of `Scene`.
//
// `Text3d`, child of `VectorFont`, is not implemented yet.

namespace yli::core
{
    class Application;
}

namespace yli::input
{
    enum class InputMethod;
}

namespace yli::ontology
{
    class GenericMasterModule;
    class Universe;
    class Brain;

    class Movable : public Entity
    {
        public:
            // Set pointer to `movable` to `nullptr`, set brain according to the input,
            // and request a new apprenticeID from `new_brain`.
            static std::optional<yli::data::AnyValue> bind_to_new_brain(
                    Movable& movable,
                    Brain& new_brain) noexcept;

            static std::optional<yli::data::AnyValue> unbind_from_brain(
                    Movable& movable) noexcept;

        protected:
            Movable(
                    yli::core::Application& application,
                    Universe& universe,
                    const MovableStruct& movable_struct,
                    GenericMasterModule* const brain_master_module);

        public:
            Movable(const Movable&) = delete;            // Delete copy constructor.
            Movable& operator=(const Movable&) = delete; // Delete copy assignment.

            virtual ~Movable() = default;

            const glm::vec3& get_cartesian_coordinates() const;
            void set_cartesian_coordinates(const glm::vec3& cartesian_coordinates);
            float get_roll() const;
            void set_roll(const float roll);
            float get_yaw() const;
            void set_yaw(const float yaw);
            float get_pitch() const;
            void set_pitch(const float pitch);
            float get_azimuth() const;
            void set_azimuth(const float azimuth);
            float get_scale() const;
            void set_scale(const float scale);

            // Public callbacks (to be called from AI scripts written in YliLisp).
            // These are the functions that are available for AI scripts.
            // Ylikuutio will support scripting of game agents using YliLisp.
            // Ylikuutio can be used for all kinds of games. However, there is
            // more support for some kinds of games needing such callbacks.
            // In particular, Ylikuutio supports simulations of real-life phenomena.
            // TODO: implement public AI callbacks!

            // Command callbacks.

            // Set target towards which to move.
            static void set_dest(Movable* const movable, const float x, const float y, const float z);

            // Get x coordinate of `movable`.
            static float get_x(const Movable* const movable);

            // Get y coordinate of `movable`.
            static float get_y(const Movable* const movable);

            // Get z destination coordinate of `movable`.
            static float get_z(const Movable* const movable);

            // Get x destination coordinate of `movable`.
            static float get_dest_x(const Movable* const movable);

            // Get y destination coordinate of `movable`.
            static float get_dest_y(const Movable* const movable);

            // Get z coordinate of `movable`.
            static float get_dest_z(const Movable* const movable);

            // Allied-movable-centric path and map information callbacks.

            // This method returns `true` if destination is visible, `false` otherwise.
            // destination may be visible directly (line of sight) or eg. by radar (without line of sight).
            static bool is_visible(const float x, const float y, const float z);

            // This method returns `true` if destination is visible with a line of sight for any own `Movable`, `false` otherwise.
            static bool is_line_of_sight_for_any(const float x, const float y, const float z);

            // This method returns `true` if destination is visible with a line of sight for any own `Movable`, `false` otherwise.
            static bool is_line_of_sight(const Movable* const movable, const float x, const float y, const float z);

            // This method returns `true` if there is any known ground path between `Movable` and (x, y, z),  `false` otherwise.
            static bool is_ground_path_known(const Movable* const movable, const float x, const float y, const float z);

            // This method returns `true` if there is any known rail path between `Movable` and (x, y, z),  `false` otherwise.
            static bool is_rail_path_known(const Movable* const movable, const float x, const float y, const float z);

            // This method returns `true` if there is known air path between movables, `false` otherwise.
            static bool is_air_path_known(const Movable* const movable, const float x, const float y, const float z);

            // This method returns `true` if there is known ballistic path between `Movable` and (x, y, z), `false` otherwise.
            static bool is_ballistic_path_known(const Movable* const movable, const float x, const float y, const float z);

            // This method returns `true` if there may be ballistic path between movables, `false` otherwise.
            static bool may_have_ballistic_path(const Movable* const movable, const float x, const float y, const float z);

            // These functions return the coordinates of the farthest point.
            static float get_closest_visible_ground_dest_x_towards(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            static float get_closest_visible_ground_dest_y_towards(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            static float get_closest_visible_ground_dest_z_towards(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            // This method returns `true` if complete path is visible, `false` otherwise.
            static bool is_complete_ground_path_visible(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            static bool is_complete_rail_path_visible(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            static bool is_complete_air_path_visible(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            static bool is_complete_ballistic_path_visible(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            // These methods return the coordinates of the point closest to `movable` from which there is known ballistic path to (x, y, z).
            static float get_nearest_known_ballistic_launch_site_x(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            static float get_nearest_known_ballistic_launch_site_y(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            static float get_nearest_known_ballistic_launch_site_z(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            // These methods return the coordinates of the point closest to `movable` from which there may be a ballistic path to (x, y, z).
            static float get_nearest_possible_ballistic_launch_site_x(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            static float get_nearest_possible_ballistic_launch_site_y(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            static float get_nearest_possible_ballistic_launch_site_z(
                    const Movable* const movable,
                    const float x,
                    const float y,
                    const float z);

            // This method returns `true` if there is known line of sight between (x1, y1, z1) and (x2, y2, z2).

            // Coordinate-centric path and map information callbacks.
            // The conditions for returning `true` match the conditions of the corresponding allied-movable-centric callbacks.

            static bool is_line_of_sight_between_from(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static bool may_have_line_of_sight_between(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static bool is_ground_path_known_between(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static bool is_rail_path_known_between(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static bool is_air_path_known_between(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static bool is_ballistic_path_known(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static bool may_have_ballistic_path_between(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static float get_nearest_known_ballistic_launch_site_x(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static float get_nearest_known_ballistic_launch_site_y(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static float get_nearest_known_ballistic_launch_site_z(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static float get_nearest_possible_ballistic_launch_site_x(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static float get_nearest_possible_ballistic_launch_site_y(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static float get_nearest_possible_ballistic_launch_site_z(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static float get_closest_visible_dest_x_towards(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static float get_closest_visible_dest_y_towards(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            static float get_closest_visible_dest_z_towards(
                    const float x1,
                    const float y1,
                    const float z1,
                    const float x2,
                    const float y2,
                    const float z2);

            // Callbacks for looping through movables.
            static void* get_first_allied_movable(Movable& movable);       // point `allied_iterator` to the first movable, `nullptr` if N/A.
            static void* get_next_allied_movable(Movable& movable);        // advance `allied_iterator`, `nullptr` if N/A.
            static void* get_first_other_allied_movable(Movable& movable); // point `allied_other_iterator` to the first other movable, `nullptr` if N/A.
            static void* get_next_other_allied_movable(Movable& movable);  // advance `allied_other_iterator`, `nullptr` if N/A.
            static void* get_first_opponent_movable(Movable& movable);     // point `opponent_iterator` to the first opponent, `nullptr` if N/A.
            static void* get_next_opponent_movable(Movable& movable);      // advance `opponent_iterator`, `nullptr` if N/A.

            // Public callbacks end here.

        private:
            void create_coordinate_and_angle_variables();

        public:
            ApprenticeModule apprentice_of_brain;

        private:
            RigidBodyModule rigid_body_module;

        public:
            std::vector<glm::vec3> initial_rotate_vectors;
            std::vector<float> initial_rotate_angles;

            glm::vec3 original_scale_vector { glm::vec3(1.0f, 1.0f, 1.0f) };

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            CartesianCoordinatesModule location;

            glm::vec3 dest_cartesian_coordinates;                  // cartesian destination coordinates.

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 direction { glm::vec3(NAN, NAN, NAN) };

            glm::vec3 right { glm::vec3(NAN, NAN, NAN) };          // note: can not be set directly using console.
            glm::vec3 up { glm::vec3(NAN, NAN, NAN) };             // note: can not be set directly using console.

            OrientationModule orientation;

            float scale { 1.0f };
            float speed { 1.0f };

            // The rest fields are created in the constructor.
            glm::mat4 model_matrix { glm::mat4(1.0f) };            // model matrix (initialized with dummy value).
            glm::mat4 mvp_matrix { glm::mat4(1.0f) };              // model view projection matrix (initialized with dummy value).

            GLuint movable_uniform_block { 0 };

            yli::input::InputMethod input_method;                  // If `input_method` is `KEYBOARD`, then keypresses control this `Movable`.
                                                                   // If `input_method` is `AI`, then the chosen `Brain` controls this `Movable`.
    };
}

#endif
