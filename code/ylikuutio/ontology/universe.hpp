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

#ifndef __YLIKUUTIO_ONTOLOGY_UNIVERSE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_UNIVERSE_HPP_INCLUDED

#include "entity.hpp"
#include "generic_parent_module.hpp"
#include "framebuffer_module.hpp"
#include "entity_factory.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/time/time.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include Bullet
#include <btBulletDynamicsCommon.h>

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <cstddef>       // std::size_t
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr
#include <optional>      // std::optional
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <vector>        // std::vector

namespace yli::audio
{
    class AudioSystem;
}

namespace yli::data
{
    class AnyValue;
}

namespace yli::input
{
    class InputSystem;
    enum class InputMethod;
}

namespace yli::render
{
    class RenderSystem;
    struct RenderStruct;
}

namespace yli::ontology
{
    class Scene;
    class Camera;
    class Console;

    struct UniverseStruct;

    class Universe: public yli::ontology::Entity
    {
        public:
            void bind_entity(yli::ontology::Entity* const entity);
            void unbind_entity(const std::size_t entityID);

            explicit Universe(const yli::ontology::UniverseStruct& universe_struct);

            Universe(const Universe&) = delete;            // Delete copy constructor.
            Universe& operator=(const Universe&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Universe();

            // This method contains the main loop.
            void start_simulation();

            // This method requests exit.
            void request_exit();

            // This method processes the physics.
            void do_physics();

            // Intentional actors (AIs and keyboard controlled ones).
            void act();

            // This method renders according to the data given in `render_struct`.
            void render(const yli::render::RenderStruct& render_struct);

            // This method renders the active `Scene` of this `Universe`.
            void render();

            // This method renders the active `Scene` of this `Universe`.
            void render_without_changing_depth_test();

            // This method sets the active `Scene`.
            void set_active_scene(yli::ontology::Scene* const scene);

            yli::ontology::Camera* get_active_camera() const;

            // This method sets the active `Camera`.
            // Setting the active `Camera` does not change the active `Scene`!
            void set_active_camera(yli::ontology::Camera* const camera) const;

            yli::ontology::Console* get_active_console() const;
            void set_active_console(yli::ontology::Console* const console);

            yli::input::InputMethod get_input_method() const;

            yli::render::GraphicsApiBackend get_graphics_api_backend() const;
            bool get_is_opengl_in_use() const;
            bool get_is_vulkan_in_use() const;
            bool get_is_software_rendering_in_use() const;
            bool get_is_headless() const;
            bool get_is_silent() const;
            bool get_is_physical() const;

            std::string eval_string(const std::string& my_string) const;

            yli::render::RenderSystem* get_render_system() const;
            yli::audio::AudioSystem* get_audio_system() const;
            yli::input::InputSystem* get_input_system() const;

            btDefaultCollisionConfiguration* get_collision_configuration() const;
            btCollisionDispatcher* get_dispatcher() const;
            btBroadphaseInterface* get_overlapping_pair_cache() const;
            btSequentialImpulseConstraintSolver* get_solver() const;

            yli::ontology::GenericParentModule& get_parent_of_ecosystems();
            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_ecosystems() const;
            std::size_t get_number_of_scenes() const;

            yli::ontology::Scene* get_active_scene() const;

            yli::ontology::Entity* get_parent() const override;

            [[nodiscard]] bool create_window();
            [[nodiscard]] bool setup_context();
            [[nodiscard]] bool create_window_and_setup_context();
            void set_swap_interval(const int32_t interval);
            void restore_onscreen_rendering() const;
            void set_opengl_background_color() const;
            void adjust_opengl_viewport() const;

            bool get_is_exit_requested() const;

            // This method returns current `window`.
            SDL_Window* get_window() const;

            // This method returns current `window_width`.
            uint32_t get_window_width() const;

            // This method sets `window_width`.
            void set_window_width(const uint32_t window_width);

            // This method returns current `window_height`.
            uint32_t get_window_height() const;

            // This method sets `window_height`.
            void set_window_height(const uint32_t window_height);

            // This method returns current `text_size`.
            uint32_t get_text_size() const;

            // This method returns current `font_size`.
            uint32_t get_font_size() const;

            // This method computes the new delta time and returns it.
            float compute_delta_time();

            // This method returns the last computed delta time.
            float get_delta_time() const;

            // This method stores `current_time_before_reading_keyboard` into `last_time_before_reading_keyboard`.
            void finalize_delta_time_loop();

            // This method returns current `max_fps`.
            uint32_t get_max_fps() const;
            float get_last_time_to_display_fps() const;
            float get_last_time_for_display_sync() const;
            int32_t get_number_of_frames() const;

            void increment_last_time_to_display_fps();
            void update_last_time_for_display_sync();
            void increment_number_of_frames();
            void reset_number_of_frames();

            yli::ontology::EntityFactory* get_entity_factory() const override;

            const glm::mat4& get_projection_matrix() const;
            void set_projection_matrix(const glm::mat4& projection_matrix);

            const glm::mat4& get_view_matrix() const;
            void set_view_matrix(const glm::mat4& view_matrix);

            float get_aspect_ratio() const;
            float get_initial_fov() const;

            // Public callbacks.

            // Public `Entity` create callbacks.

            // Public `Entity` delete callbacks.

            static std::optional<yli::data::AnyValue> delete_entity(
                    yli::ontology::Universe& universe,
                    yli::ontology::Entity& entity);

            // Public `Entity` naming callbacks.

            static std::optional<yli::data::AnyValue> set_global_name_for_entity(
                    yli::ontology::Entity& entity,
                    const std::string& new_value);

            static std::optional<yli::data::AnyValue> set_local_name_for_entity(
                    yli::ontology::Entity& entity,
                    const std::string& new_value);

            // Public `Entity` activate callbacks.

            static std::optional<yli::data::AnyValue> activate_entity(yli::ontology::Entity& entity);

            // Public YliLisp-related callbacks.

            static std::optional<yli::data::AnyValue> eval(
                    yli::ontology::Console& console,
                    yli::ontology::Universe& universe,
                    const std::vector<std::string>& command_parameters);

            // Public data printing callbacks.

            static std::optional<yli::data::AnyValue> info0(
                    const yli::ontology::Universe& universe,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> info1(
                    const yli::ontology::Universe& universe,
                    yli::ontology::Console& console,
                    const yli::ontology::Entity& entity);

            static std::optional<yli::data::AnyValue> print_entities(
                    const yli::ontology::Universe& universe,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> print_parent(
                    const yli::ontology::Universe&,
                    yli::ontology::Console& console,
                    const yli::ontology::Entity& entity);

            // Other public callbacks.

            static std::optional<yli::data::AnyValue> screenshot(
                    yli::ontology::Universe& universe,
                    const std::string& filename);

            // Public callbacks end here.

            // Ylikuutio version.
            static const std::string version;

            // Variables related to location and orientation.

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            glm::vec3 current_camera_cartesian_coordinates { glm::vec3(NAN, NAN, NAN) }; // Dummy coordinates.

            // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
            yli::data::SphericalCoordinatesStruct current_camera_spherical_coordinates;

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 current_camera_direction;

            glm::vec3 current_camera_right; // note: `right` can not be set directly using console.
            glm::vec3 current_camera_up;    // note: `up` can not be set directly using console.

            float current_camera_roll  { NAN };
            float current_camera_yaw   { NAN };
            float current_camera_pitch { NAN };

            // 'can toggle'-type of boolean keypress control variables
            // should all be stored in the `Universe` to avoid locking.
            bool can_toggle_invert_mouse { false };
            bool can_toggle_flight_mode  { false };
            bool can_toggle_help_mode    { false };

            bool is_invert_mouse_in_use  { false };
            bool is_first_turbo_pressed  { false };
            bool is_second_turbo_pressed { false };
            bool is_exit_requested       { false };

            // Variables related to the current `Scene`.
            bool testing_spherical_terrain_in_use { false };

            // Variables related to `Console`s.
            bool in_console { false };

            // Variables related to help mode.
            bool in_help_mode            { true };
            bool can_display_help_screen { true };

            float background_red   { NAN };
            float background_green { NAN };
            float background_blue  { NAN };
            float background_alpha { NAN };

            yli::ontology::GenericParentModule parent_of_ecosystems;
            yli::ontology::GenericParentModule parent_of_scenes;
            yli::ontology::GenericParentModule parent_of_font_2ds;
            yli::ontology::GenericParentModule parent_of_consoles;
            yli::ontology::GenericParentModule parent_of_any_value_entities;
            yli::ontology::GenericParentModule parent_of_callback_engine_entities;

            yli::ontology::FramebufferModule framebuffer_module;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            void create_should_be_rendered_variable();

            bool compute_and_update_matrices_from_inputs();

            std::unique_ptr<yli::ontology::EntityFactory> entity_factory { std::make_unique<yli::ontology::EntityFactory>(*this) };

            std::vector<yli::ontology::Entity*> entity_pointer_vector;
            std::queue<std::size_t> free_entityID_queue;
            std::size_t number_of_entities { 0 };

            yli::ontology::Scene* active_scene     { nullptr };
            yli::ontology::Console* active_console { nullptr };

            std::unique_ptr<yli::render::RenderSystem> render_system { nullptr }; // pointer to `RenderSystem`.
            std::unique_ptr<yli::audio::AudioSystem> audio_system    { nullptr }; // pointer to `AudioSystem`.
            std::unique_ptr<yli::input::InputSystem> input_system    { nullptr }; // pointer to `InputSystem`.

            // Bullet variables.
            std::unique_ptr<btDefaultCollisionConfiguration> collision_configuration { std::make_unique<btDefaultCollisionConfiguration>() };
            std::unique_ptr<btCollisionDispatcher> dispatcher                        { std::make_unique<btCollisionDispatcher>(this->collision_configuration.get()) };
            std::unique_ptr<btBroadphaseInterface> overlapping_pair_cache            { std::make_unique<btDbvtBroadphase>() };
            std::unique_ptr<btSequentialImpulseConstraintSolver> solver              { std::make_unique<btSequentialImpulseConstraintSolver>() };

            const std::string application_name;

            const yli::render::GraphicsApiBackend graphics_api_backend;
            const std::vector<SDL_DisplayMode> display_modes;
            const uint32_t n_displays;
            const bool is_silent;
            const bool is_physical;
            bool is_fullscreen;
            bool is_desktop_fullscreen;

            // variables related to the window.
            SDL_Window* window { nullptr };
            uint32_t window_width;
            uint32_t window_height;
            std::string window_title { "Ylikuutio " + yli::ontology::Universe::version };

            int32_t mouse_x;
            int32_t mouse_y;

        public:
            float speed;
            float turbo_factor;
            float twin_turbo_factor;
            float mouse_speed;

        private:
            bool has_mouse_ever_moved { false };

            // Variables related to graphics.
            float znear;
            float zfar;

            // variables related to `Camera` (projection).
            glm::mat4 current_camera_projection_matrix { glm::mat4(1.0f) }; // Identity matrix (dummy value).
            glm::mat4 current_camera_view_matrix       { glm::mat4(1.0f) }; // Identity matrix (dummy value).
            float aspect_ratio;          // At the moment all `Camera`s use the same aspect ratio.
            float initial_fov { 60.0f }; // At the moment all `Camera`s use the same FoV.

            // variables related to the fonts and texts used.
            uint32_t text_size;
            uint32_t font_size;

            // variables related to timing of events.
            uint32_t max_fps;
            float last_time_to_display_fps   { yli::time::get_time() };
            float last_time_for_display_sync { yli::time::get_time() };
            float delta_time                 { NAN };
            int32_t number_of_frames         { 0 };

            // `std::numeric_limits<std::size_t>::max()` means that `last_time_before_reading_keyboard` is not defined.
            uint32_t last_time_before_reading_keyboard    { std::numeric_limits<uint32_t>::max() };

            // `std::numeric_limits<std::size_t>::max()` means that `current_time_before_reading_keyboard` is not defined.
            uint32_t current_time_before_reading_keyboard { std::numeric_limits<uint32_t>::max() };
    };
}

#endif
