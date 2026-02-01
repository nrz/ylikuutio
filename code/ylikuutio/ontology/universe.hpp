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

#ifndef YLIKUUTIO_ONTOLOGY_UNIVERSE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_UNIVERSE_HPP_INCLUDED

#include "entity.hpp"
#include "generic_parent_module.hpp"
#include "parent_of_input_modes_module.hpp"
#include "framebuffer_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/time/time.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>         // NAN
#include <cstddef>       // std::size_t
#include <limits>        // std::numeric_limits
#include <memory>        // std::unique_ptr
#include <optional>      // std::optional
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <vector>        // std::vector

namespace yli::audio
{
    class AudioSystem;
}

namespace yli::core
{
    class Application;
}

namespace yli::event
{
    class EventSystem;
}

namespace yli::input
{
    class InputSystem;
    enum class InputMethod;
}

namespace yli::memory
{
    class GenericMemoryAllocator;

    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
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
    struct InputModeStruct;

    class Universe final : public Entity
    {
        public:
            void bind_entity(Entity* const entity) noexcept;
            void unbind_entity(const std::size_t entityID) noexcept;

        private:
            Universe(
                    yli::core::Application& application,
                    const UniverseStruct& universe_struct);

            ~Universe();

        public:
            Universe(const Universe&) = delete;            // Delete copy constructor.
            Universe& operator=(const Universe&) = delete; // Delete copy assignment.

            // This method contains the main loop.
            void start_simulation();

            void update_mouse_x(const int32_t x_change);
            void update_mouse_y(const int32_t y_change);
            void gain_focus();
            void lose_focus();

            // This method requests exit.
            void request_exit();

            // This method processes the physics.
            void do_physics();

            // Intentional actors (AIs and keyboard controlled ones).
            void update();

            // This method renders according to the data given in `render_struct`.
            void render(const yli::render::RenderStruct& render_struct);

            // This method renders the active `Scene` of this `Universe`.
            void render();

            // This method renders the active `Scene` of this `Universe`.
            void render_without_changing_depth_test();

            // This method sets the active `Scene`.
            void set_active_scene(Scene* const scene);

            Camera* get_active_camera() const;

            // This method sets the active `Camera`.
            // Setting the active `Camera` does not change the active `Scene`!
            void set_active_camera(Camera* const camera) const;

            const glm::vec3& get_xyz() const;
            void set_xyz(glm::vec3&& xyz);
            void update_xyz(const glm::vec3& xyz);

            float get_x() const;
            void set_x(const float x);

            float get_y() const;
            void set_y(const float y);

            float get_z() const;
            void set_z(const float z);

            const glm::vec3& get_direction() const;
            void set_direction(glm::vec3&& direction);

            const glm::vec3& get_right() const;
            void set_right(glm::vec3&& right);

            const glm::vec3& get_up() const;
            void set_up(glm::vec3&& up);

            float get_roll() const;
            void set_roll(const float roll);

            float get_yaw() const;
            void set_yaw(const float yaw);
            void update_yaw(const float x_position);

            float get_pitch() const;
            void set_pitch(const float pitch);
            void update_pitch(const float y_position);

            float get_azimuth() const;

            Console* get_active_console() const;
            void set_active_console(Console* const console);

            yli::input::InputMethod get_input_method() const;

            yli::render::GraphicsApiBackend get_graphics_api_backend() const;
            bool get_is_opengl_in_use() const;
            bool get_is_vulkan_in_use() const;
            bool get_is_software_rendering_in_use() const;
            bool get_is_headless() const;
            bool get_is_silent() const;
            bool get_is_physical() const;

            std::string eval_string(const std::string& my_string) const;

            yli::memory::GenericMemoryAllocator& get_generic_memory_allocator(const int type) const;

            yli::event::EventSystem& get_event_system() const;
            yli::input::InputSystem& get_input_system() const;
            yli::render::RenderSystem& get_render_system() const;
            yli::audio::AudioSystem* get_audio_system() const;

            GenericParentModule& get_parent_of_ecosystems();
            Scene* get_scene() const override;
            std::size_t get_number_of_ecosystems() const;
            std::size_t get_number_of_scenes() const;

            Scene* get_active_scene() const;

            Entity* get_parent() const override;

            std::optional<SDL_DisplayMode> get_preferred_display_mode() const;
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

            // This method returns current `window_height`.
            uint32_t get_window_height() const;

            // This method returns current `text_size`.
            uint32_t get_text_size() const;

            // This method returns current `font_size`.
            uint32_t get_font_size() const;

            // This method computes the new delta time and returns it.
            double compute_delta_time();

            // This method returns the last computed delta time.
            double get_delta_time() const;

            // This method stores `current_time_before_reading_keyboard` into `last_time_before_reading_keyboard`.
            void finalize_delta_time_loop();

            // This method returns current `max_fps`.
            uint32_t get_max_fps() const;
            double get_last_time_to_display_fps() const;
            double get_last_time_for_display_sync() const;
            int32_t get_number_of_frames() const;

            void increment_last_time_to_display_fps();
            void update_last_time_for_display_sync();
            void increment_number_of_frames();
            void reset_number_of_frames();

            const glm::mat4& get_projection_matrix() const;
            void set_projection_matrix(glm::mat4&& projection_matrix);

            const glm::mat4& get_view_matrix() const;
            void set_view_matrix(glm::mat4&& view_matrix);

            float get_aspect_ratio() const;
            float get_initial_fov() const;

            // Public callbacks.

            // Public `Entity` create callbacks.

            // Public `Entity` delete callbacks.

            static std::optional<yli::data::AnyValue> delete_entity(
                    Universe& universe,
                    Entity& entity);

            // Public `Entity` naming callbacks.

            static std::optional<yli::data::AnyValue> set_global_name_for_entity(
                    Entity& entity,
                    const std::string& new_value);

            static std::optional<yli::data::AnyValue> set_local_name_for_entity(
                    Entity& entity,
                    const std::string& new_value);

            // Public `Entity` activate callbacks.

            static std::optional<yli::data::AnyValue> activate_entity(Entity& entity);

            // Public YliLisp-related callbacks.

            static std::optional<yli::data::AnyValue> eval(
                    Console& console,
                    Universe& universe,
                    const std::vector<std::string>& command_parameters);

            // Public data printing callbacks.

            static std::optional<yli::data::AnyValue> info0(
                    const Universe& universe,
                    Console& console);

            static std::optional<yli::data::AnyValue> info1(
                    const Universe& universe,
                    Console& console,
                    const Entity& entity);

            static std::optional<yli::data::AnyValue> print_entities(
                    const Universe& universe,
                    Console& console);

            static std::optional<yli::data::AnyValue> print_parent(
                    const Universe&,
                    Console& console,
                    const Entity& entity);

            // Other public callbacks.

            static std::optional<yli::data::AnyValue> screenshot(
                    Universe& universe,
                    const std::string& filename);

            // Public callbacks end here.

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            // Ylikuutio version.
            static const std::string version;

            // Variables related to location and orientation.

            // 'can toggle'-type of boolean keypress control variables
            // should all be stored in the `Universe` to avoid locking.
            bool can_toggle_invert_mouse { false };
            bool can_toggle_flight_mode  { false };
            bool can_toggle_help_mode    { false };

            bool is_invert_mouse_in_use  { false };
            bool is_first_turbo_pressed  { false };
            bool is_second_turbo_pressed { false };
            bool is_exit_requested       { false };

            // Variables related to `Console`s.
            bool in_console { false };

            // Variables related to help mode.
            bool in_help_mode            { true };
            bool can_display_help_screen { true };

            float background_red   { NAN };
            float background_green { NAN };
            float background_blue  { NAN };
            float background_alpha { NAN };

            GenericParentModule parent_of_ecosystems;
            GenericParentModule parent_of_scenes;
            GenericParentModule parent_of_audio_tracks;
            GenericParentModule parent_of_font_2ds;
            ParentOfInputModesModule parent_of_input_modes;
            GenericParentModule parent_of_consoles;

            FramebufferModule framebuffer_module;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            void create_should_render_variable();

            std::vector<Entity*> entity_pointer_vector;
            std::queue<std::size_t> free_entityID_queue;
            std::size_t number_of_entities { 0 };

            Scene* active_scene     { nullptr };
            Console* active_console { nullptr };

            std::unique_ptr<yli::render::RenderSystem> render_system { nullptr };

            const std::string application_name;

            const yli::render::GraphicsApiBackend graphics_api_backend;
            const std::vector<SDL_DisplayMode> display_modes;
            const uint32_t n_displays;

        public:
            const std::optional<SDL_DisplayMode> display_mode;

        private:
            const bool is_silent;
            const bool is_physical;
            bool is_fullscreen;

            // variables related to the window.
            SDL_Window* window { nullptr };
            uint32_t window_width;
            uint32_t window_height;
            std::string window_title { "Ylikuutio " + Universe::version };

            bool has_mouse_focus { true };
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
            float aspect_ratio;          // At the moment all `Camera`s use the same aspect ratio.
            float initial_fov { 60.0f }; // At the moment all `Camera`s use the same FoV.

            // variables related to the fonts and texts used.
            uint32_t text_size;
            uint32_t font_size;

            // variables related to timing of events.
            uint32_t max_fps;
            double last_time_to_display_fps   { yli::time::get_time() };
            double last_time_for_display_sync { yli::time::get_time() };
            double delta_time                 { NAN };
            int32_t number_of_frames          { 0 };

            // `std::numeric_limits<std::size_t>::max()` means that `last_time_before_reading_keyboard` is not defined.
            uint32_t last_time_before_reading_keyboard    { std::numeric_limits<uint32_t>::max() };

            // `std::numeric_limits<std::size_t>::max()` means that `current_time_before_reading_keyboard` is not defined.
            uint32_t current_time_before_reading_keyboard { std::numeric_limits<uint32_t>::max() };
    };
}

#endif
