// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef __STDC_FORMAT_MACROS
// For MinGW.
#define __STDC_FORMAT_MACROS
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "universe.hpp"
#include "entity.hpp"
#include "callback_engine.hpp"
#include "scene.hpp"
#include "font_2d.hpp"
#include "text_2d.hpp"
#include "camera.hpp"
#include "input_mode.hpp"
#include "console.hpp"
#include "generic_entity_factory.hpp"
#include "entity_variable_activation.hpp"
#include "entity_variable_read.hpp"
#include "universe_struct.hpp"
#include "variable_struct.hpp"
#include "text_struct.hpp"
#include "family_templates.hpp"
#include "callback_magic_numbers.hpp"
#include "code/ylikuutio/audio/audio_system.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/geometry/degrees_to_radians.hpp"
#include "code/ylikuutio/geometry/radians_to_degrees.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/memory/generic_memory_system.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ubo_block_enums.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/graphics_api_backend.hpp"
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_system_struct.hpp"
#include "code/ylikuutio/render/render_templates.hpp"
#include "code/ylikuutio/render/render_struct.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/time/time.hpp"

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

// Include standard headers
#include <cmath>     // sqrt
#include <cstddef>   // std::size_t
#include <iomanip>   // std::setprecision
#include <ios>       // std::fixed
#include <iostream>  // std::cout, std::cerr
#include <limits>    // std::numeric_limits
#include <numbers>   // std::numbers::pi
#include <optional>  // std::optional
#include <sstream>   // std::stringstream
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <utility>   // std::move
#include <variant>   // std::holds_alternative
#include <vector>    // std::vector

namespace yli::memory
{
    class GenericMemoryAllocator;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Font2D;

    struct InputModeStruct;

    const std::string Universe::version = "0.0.10";

    void Universe::bind_entity(yli::ontology::Entity* const entity) noexcept
    {
        // no-op when called during initialization of the `Entity` base class of `Universe` itself.
        if (entity == this)
        {
            return;
        }

        // get `entityID` from `Universe` and set pointer to `entity`.

        // `entity` must not be `nullptr` (use `this` as the first argument).
        entity->entityID = yli::hierarchy::request_childID(this->entity_pointer_vector, this->free_entityID_queue);
        // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
        yli::hierarchy::set_child_pointer(entity->entityID, entity, this->entity_pointer_vector, this->free_entityID_queue, this->number_of_entities);
    }

    void Universe::unbind_entity(const std::size_t entityID) noexcept
    {
        yli::hierarchy::unbind_child_from_parent(
                entityID,
                this->entity_pointer_vector,
                this->free_entityID_queue,
                this->number_of_entities);
    }

    Universe::Universe(
            yli::core::Application& application,
            const yli::ontology::UniverseStruct& universe_struct)
        : Entity(application, *this, universe_struct), // `Universe` has no parent.
        parent_of_ecosystems(
                *this,
                this->registry,
                "ecosystems"),
        parent_of_scenes(
                *this,
                this->registry,
                "scenes"),
        parent_of_font_2ds(
                *this,
                this->registry,
                "font_2ds"),
        parent_of_input_modes(
                *this,
                this->registry,
                "input_modes"),
        parent_of_consoles(
                *this,
                this->registry,
                "consoles"),
        parent_of_console_callback_engines(
                *this,
                this->registry,
                "console_callback_engines"),
        framebuffer_module(universe_struct.framebuffer_module_struct),
        application_name      { universe_struct.application_name },
        graphics_api_backend  { yli::sdl::init_sdl(universe_struct.graphics_api_backend) },
        display_modes         { yli::sdl::get_display_modes(this->graphics_api_backend) },
        n_displays            { static_cast<uint32_t>(this->display_modes.size()) },
        is_silent             { !(this->get_is_opengl_in_use() || this->get_is_vulkan_in_use()) || universe_struct.is_silent },
        is_physical           { universe_struct.is_physical },
        is_fullscreen         { universe_struct.is_fullscreen },
        is_desktop_fullscreen { universe_struct.is_desktop_fullscreen },
        window_width          { universe_struct.window_width },
        window_height         { universe_struct.window_height },
        window_title          { universe_struct.window_title },
        mouse_x               { static_cast<int32_t>(this->window_width / 2) },
        mouse_y               { static_cast<int32_t>(this->window_height / 2) },
        speed                 { universe_struct.speed },
        turbo_factor          { universe_struct.turbo_factor },
        twin_turbo_factor     { universe_struct.twin_turbo_factor },
        mouse_speed           { universe_struct.mouse_speed },
        znear                 { universe_struct.znear },
        zfar                  { universe_struct.zfar },
        aspect_ratio          { static_cast<float>(this->window_width) / static_cast<float>(this->window_height) },
        text_size             { universe_struct.text_size },
        font_size             { universe_struct.font_size },
        max_fps               { universe_struct.max_fps }
    {
        // constructor.

        // call `set_global_name` here because it can't be done in `Entity` constructor.
        this->set_global_name(universe_struct.global_name);

        if (this->window_title.empty())
        {
            this->window_title = "Ylikuutio " + yli::ontology::Universe::version;
        }

        this->create_should_render_variable();

        if (this->graphics_api_backend == yli::render::GraphicsApiBackend::HEADLESS)
        {
            this->is_exit_requested = true;
        }
        else
        {
            yli::render::RenderSystemStruct render_system_struct;
            this->render_system = std::make_unique<yli::render::RenderSystem>(this, render_system_struct);
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Universe*";
    }

    Universe::~Universe()
    {
        // destructor.

        SDL_Quit();

        this->unbind_entity(this->entityID);

        if (!this->global_name.empty())
        {
            // OK, this `Universe` had a global name, so it's global name shall be erased.
            this->universe.erase_entity(this->global_name);
        }
    }

    void Universe::do_physics()
    {
        if (this->active_scene != nullptr)
        {
            this->active_scene->do_physics();
        }

        this->compute_and_update_matrices_from_inputs();
    }

    void Universe::act()
    {
        if (this->active_scene != nullptr)
        {
            this->active_scene->act();
        }
    }

    void Universe::start_simulation()
    {
        if (this->parent_of_font_2ds.get_number_of_children() == 0)
        {
            return;
        }

        yli::ontology::GenericEntityFactory& entity_factory = this->application.get_generic_entity_factory();

        yli::ontology::Font2D* const font_2d = static_cast<yli::ontology::Font2D*>(
                yli::hierarchy::get_first_child(
                    this->parent_of_font_2ds.child_pointer_vector,
                    this->parent_of_font_2ds.get_number_of_children()));

        if (font_2d == nullptr)
        {
            return;
        }

        // Create angles and cartesian coordinates text, on bottom left corner.
        yli::ontology::TextStruct angles_and_coordinates_text_struct;
        angles_and_coordinates_text_struct.parent = font_2d;
        angles_and_coordinates_text_struct.screen_width = this->window_width;
        angles_and_coordinates_text_struct.screen_height = this->window_height;
        angles_and_coordinates_text_struct.x = 0;
        angles_and_coordinates_text_struct.y = 0;
        angles_and_coordinates_text_struct.text_size = this->text_size;
        angles_and_coordinates_text_struct.font_size = this->font_size;
        angles_and_coordinates_text_struct.font_texture_file_format = "png";
        angles_and_coordinates_text_struct.horizontal_alignment = "left";
        angles_and_coordinates_text_struct.vertical_alignment = "bottom";
        yli::ontology::Text2D* angles_and_coordinates_text_2d = entity_factory.create_text_2d(angles_and_coordinates_text_struct);

        if (angles_and_coordinates_text_2d == nullptr)
        {
            return;
        }

        // Create spherical coordinates text, on second line from the bottom left.
        yli::ontology::TextStruct spherical_coordinates_text_struct;
        spherical_coordinates_text_struct.parent = font_2d;
        spherical_coordinates_text_struct.screen_width = this->window_width;
        spherical_coordinates_text_struct.screen_height = this->window_height;
        spherical_coordinates_text_struct.x = 0;
        spherical_coordinates_text_struct.y = 2 * this->text_size;
        spherical_coordinates_text_struct.text_size = this->text_size;
        spherical_coordinates_text_struct.font_size = this->font_size;
        spherical_coordinates_text_struct.horizontal_alignment = "left";
        spherical_coordinates_text_struct.vertical_alignment = "bottom";
        yli::ontology::Text2D* spherical_coordinates_text_2d = entity_factory.create_text_2d(spherical_coordinates_text_struct);

        if (spherical_coordinates_text_2d == nullptr)
        {
            return;
        }

        // Create time data text, on top left corner.
        yli::ontology::TextStruct time_text_struct;
        time_text_struct.parent = font_2d;
        time_text_struct.screen_width = this->window_width;
        time_text_struct.screen_height = this->window_height;
        time_text_struct.x = 0;
        time_text_struct.y = this->window_height;
        time_text_struct.text_size = this->text_size;
        time_text_struct.font_size = this->font_size;
        time_text_struct.font_texture_file_format = "png";
        time_text_struct.horizontal_alignment = "left";
        time_text_struct.vertical_alignment = "top";
        yli::ontology::Text2D* time_text_2d = entity_factory.create_text_2d(time_text_struct);

        if (time_text_2d == nullptr)
        {
            return;
        }

        // Create help text.
        yli::ontology::TextStruct help_text_struct;
        help_text_struct.parent = font_2d;
        help_text_struct.screen_width = this->window_width;
        help_text_struct.screen_height = this->window_height;
        help_text_struct.x = 0;
        help_text_struct.y = this->window_height - (3 * this->text_size);
        help_text_struct.text_size = this->text_size;
        help_text_struct.font_size = this->font_size;
        help_text_struct.font_texture_file_format = "png";
        help_text_struct.horizontal_alignment = "left";
        help_text_struct.vertical_alignment = "top";
        yli::ontology::Text2D* help_text_2d = entity_factory.create_text_2d(help_text_struct);

        if (help_text_2d == nullptr)
        {
            return;
        }

        // Print frame rate data on top right corner.
        yli::ontology::TextStruct frame_rate_text_struct;
        frame_rate_text_struct.parent = font_2d;
        frame_rate_text_struct.screen_width = this->window_width;
        frame_rate_text_struct.screen_height = this->window_height;
        frame_rate_text_struct.x = this->window_width;
        frame_rate_text_struct.y = this->window_height;
        frame_rate_text_struct.text_size = this->text_size;
        frame_rate_text_struct.font_size = this->font_size;
        frame_rate_text_struct.font_texture_file_format = "png";
        frame_rate_text_struct.horizontal_alignment = "right";
        frame_rate_text_struct.vertical_alignment = "top";
        yli::ontology::Text2D* frame_rate_text_2d = entity_factory.create_text_2d(frame_rate_text_struct);

        if (frame_rate_text_2d == nullptr)
        {
            return;
        }

        SDL_Event sdl_event;
        yli::sdl::flush_sdl_event_queue();

        // This method contains the main simulation loop.
        bool has_mouse_focus = true;

        while (!this->is_exit_requested)
        {
            // The main simulation loop works in the following way:
            // 1. Read and process inputs.
            // 2. Process AI.
            // 3. Process physics.
            // 4. Update information about current location and orientation (for rendering).
            // 5. Render.
            const double current_time_in_main_loop = yli::time::get_time();

            if (current_time_in_main_loop - this->last_time_for_display_sync >= (1.0 / this->max_fps))
            {
                this->update_last_time_for_display_sync();

                this->increment_number_of_frames();

                while (current_time_in_main_loop - this->last_time_to_display_fps >= 1.0)
                {
                    // If last `std::stringstream` here was more than 1 sec ago,
                    // std::stringstream` and reset number of frames.
                    if (this->number_of_frames > 0)
                    {
                        std::stringstream ms_frame_text_stringstream;
                        ms_frame_text_stringstream << std::fixed << std::setprecision(2) <<
                            1000.0f / static_cast<float>(this->number_of_frames) << " ms/frame; " <<
                            this->number_of_frames << " Hz";
                        const std::string ms_frame_text = ms_frame_text_stringstream.str();
                        frame_rate_text_2d->change_string(ms_frame_text);
                        this->reset_number_of_frames();
                    }

                    // `last_time_to_display_fps` needs to be incremented to avoid infinite loop.
                    this->increment_last_time_to_display_fps();

                    // Update audio also (in case the sound has reached the end).
                    if (yli::audio::AudioSystem* const audio_system = this->get_audio_system(); audio_system != nullptr)
                    {
                        audio_system->update();
                    }
                }

                // Clear the screen.
                if (this->graphics_api_backend == yli::render::GraphicsApiBackend::OPENGL)
                {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }

                this->compute_delta_time();

                this->mouse_x = this->window_width / 2;
                this->mouse_y = this->window_height / 2;

                const yli::ontology::InputMode* const input_mode = this->parent_of_input_modes.get_active_input_mode();

                if (input_mode == nullptr)
                {
                    return;
                }

                // 1. Read and process inputs.
                // Poll all SDL events.
                while (SDL_PollEvent(&sdl_event))
                {
                    if (sdl_event.type == SDL_MOUSEMOTION)
                    {
                        this->mouse_x += sdl_event.motion.xrel; // horizontal motion relative to screen center.
                        this->mouse_y += sdl_event.motion.yrel; // vertical motion relative to screen center.
                    }
                    else if (sdl_event.type == SDL_KEYDOWN)
                    {
                        const uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                        yli::ontology::GenericCallbackEngine* const generic_callback_engine = input_mode->get_keypress_callback_engine(scancode);

                        if (generic_callback_engine != nullptr)
                        {
                            const std::optional<yli::data::AnyValue> any_value = generic_callback_engine->execute(yli::data::AnyValue());

                            if (any_value &&
                                    std::holds_alternative<uint32_t>(any_value->data) &&
                                    std::get<uint32_t>(any_value->data) == EXIT_PROGRAM_MAGIC_NUMBER)
                            {
                                this->request_exit();
                            }
                        }

                        yli::ontology::Console* const active_console = this->active_console;

                        if (active_console != nullptr)
                        {
                            active_console->process_key_event(sdl_event.key);
                        }
                    }
                    else if (sdl_event.type == SDL_KEYUP)
                    {
                        const uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                        yli::ontology::GenericCallbackEngine* const generic_callback_engine = input_mode->get_keyrelease_callback_engine(scancode);

                        if (generic_callback_engine == nullptr)
                        {
                            continue;
                        }

                        const std::optional<yli::data::AnyValue> any_value = generic_callback_engine->execute(yli::data::AnyValue());

                        if (any_value &&
                                std::holds_alternative<uint32_t>(any_value->data) &&
                                std::get<uint32_t>(any_value->data) == EXIT_PROGRAM_MAGIC_NUMBER)
                        {
                            this->request_exit();
                        }
                    }
                    else if (sdl_event.type == SDL_WINDOWEVENT)
                    {
                        if (sdl_event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                        {
                            has_mouse_focus = true;
                        }
                        else if (sdl_event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                        {
                            has_mouse_focus = false;
                        }
                    }
                    else if (sdl_event.type == SDL_QUIT)
                    {
                        this->request_exit();
                    }
                }

                // mouse position.
                const float xpos = static_cast<float>(this->mouse_x);
                const float ypos = static_cast<float>(this->mouse_y);

                // Reset mouse position for next frame.
                if (has_mouse_focus)
                {
                    yli::input::set_cursor_position(
                            this->window,
                            static_cast<float>(this->window_width) / 2,
                            static_cast<float>(this->window_height) / 2);

                    if (this->has_mouse_ever_moved || (std::abs(xpos) > 0.0001) || (std::abs(ypos) > 0.0001))
                    {
                        this->has_mouse_ever_moved = true;

                        // Compute new orientation.
                        this->update_yaw(xpos);
                        this->update_pitch(ypos);
                    }
                }

                {
                    const float roll = this->get_roll();
                    const float yaw = this->get_yaw();
                    const float pitch = this->get_pitch();

                    // Direction: spherical coordinates to cartesian coordinates conversion.
                    this->set_direction(glm::vec3(
                                cos(pitch) * sin(yaw + 0.5f * std::numbers::pi),
                                sin(pitch),
                                cos(pitch) * cos(yaw + 0.5f * std::numbers::pi)));

                    // Right vector.
                    this->set_right(glm::vec3(
                                sin(yaw),
                                sin(roll),
                                cos(yaw) * cos(roll)));

                    // Up vector.
                    this->set_up(glm::cross(this->get_right(), this->get_direction()));
                }

                if (!this->in_console)
                {
                    const uint8_t* const current_key_states = SDL_GetKeyboardState(nullptr);
                    const std::vector<yli::ontology::GenericCallbackEngine*>* const continuous_keypress_callback_engines = input_mode->get_continuous_keypress_callback_engines();
                    if (continuous_keypress_callback_engines == nullptr)
                    {
                        continue;
                    }

                    // Check for keypresses and call corresponding callbacks.
                    for (std::size_t i = 0; i < continuous_keypress_callback_engines->size(); i++)
                    {
                        bool is_pressed = false;

                        if (this->get_input_method() == yli::input::InputMethod::KEYBOARD)
                        {
                            if (current_key_states[i] == 1) // 1 = pressed, 0 = not pressed.
                            {
                                is_pressed = true;
                            }
                        }
                        else if (this->get_input_method() == yli::input::InputMethod::INPUT_FILE)
                        {
                            // TODO: implement optionally loading keyreleases from a file (do not execute `SDL_GetKeyboardState` in that case).
                            if (false)
                            {
                                is_pressed = true;
                            }
                        }
                        else
                        {
                            std::cerr << "ERROR: unsupported input method.\n";
                        }

                        if (is_pressed)
                        {
                            yli::ontology::GenericCallbackEngine* const generic_callback_engine = continuous_keypress_callback_engines->at(i);

                            if (generic_callback_engine == nullptr)
                            {
                                continue;
                            }

                            const std::optional<yli::data::AnyValue> any_value = generic_callback_engine->execute(yli::data::AnyValue());

                            if (any_value &&
                                    std::holds_alternative<uint32_t>(any_value->data) &&
                                    std::get<uint32_t>(any_value->data) == EXIT_PROGRAM_MAGIC_NUMBER)
                            {
                                this->request_exit();
                            }
                        }
                    }
                }

                // 2. Process AI.
                // Intentional actors (AIs and keyboard controlled ones).
                this->act();

                // 3. Process physics.
                // Gravity etc. physical phenomena.
                this->do_physics();

                // 4. Update information about current location and orientation (for rendering).

                if (angles_and_coordinates_text_2d != nullptr)
                {
                    std::stringstream angles_and_coordinates_stringstream;
                    angles_and_coordinates_stringstream << std::fixed << std::setprecision(2) <<
                        this->get_yaw() << "," <<
                        this->get_pitch() << " rad; " <<
                        yli::geometry::radians_to_degrees(this->get_yaw()) << "," <<
                        yli::geometry::radians_to_degrees(this->get_pitch()) << " deg\n" <<
                        "(" <<
                        this->get_x() << "," <<
                        this->get_y() << "," <<
                        this->get_z() << ")";
                    const std::string angles_and_coordinates_string = angles_and_coordinates_stringstream.str();
                    angles_and_coordinates_text_2d->change_string(angles_and_coordinates_string);
                }

                if (time_text_2d != nullptr)
                {
                    std::stringstream time_stringstream;
                    time_stringstream << std::fixed << std::setprecision(2) << yli::time::get_time() << " sec";
                    const std::string time_string = time_stringstream.str();
                    time_text_2d->change_string(time_string);
                }

                const std::string on_string = "on";
                const std::string off_string = "off";

                if (help_text_2d != nullptr)
                {
                    if (this->in_help_mode && this->can_display_help_screen)
                    {
                        yli::ontology::Scene* const scene = this->active_scene;
                        const std::string help_text_string =
                            (this->application_name.empty() ? "Ylikuutio" : this->application_name) + " " + yli::ontology::Universe::version + "\n"
                            "\n"
                            "arrow keys\n"
                            "space jump\n"
                            "enter duck\n"
                            "F1 help mode\n"
                            "`  enter console\n"
                            "I  invert mouse (" + (this->is_invert_mouse_in_use ? on_string : off_string) + ")\n"
                            "F  flight mode (" + (scene == nullptr || scene->get_is_flight_mode_in_use() ? on_string : off_string) + ")\n"
                            "Ctrl      turbo\n"
                            "Ctrl+Ctrl extra turbo\n"
                            "for debugging:\n"
                            "G  grass texture\n"
                            "O  orange fur texture\n"
                            "P  pink geometric tiles texture\n"
                            "T  terrain species\n"
                            "A  suzanne species\n";
                        help_text_2d->change_string(help_text_string);
                    }
                    else
                    {
                        help_text_2d->change_string("");
                    }
                }

                if (spherical_coordinates_text_2d != nullptr)
                {
                    if (this->testing_spherical_terrain_in_use)
                    {
                        std::stringstream spherical_coordinates_stringstream;
                        spherical_coordinates_stringstream << std::fixed << std::setprecision(2) <<
                            "rho:" << this->get_rho() <<
                            "theta:" << this->get_theta() <<
                            "phi:" << this->get_phi();
                        const std::string spherical_coordinates_string = spherical_coordinates_stringstream.str();
                        spherical_coordinates_text_2d->change_string(spherical_coordinates_string);
                    }
                    else
                    {
                        spherical_coordinates_text_2d->change_string("");
                    }
                }

                // 5. Render.
                // Render the `Universe`.
                this->render();

                this->finalize_delta_time_loop();
            }
        }
    }

    void Universe::request_exit()
    {
        this->is_exit_requested = true;
    }

    void Universe::render(const yli::render::RenderStruct& render_struct)
    {
        // Used `RenderSystem` rendering implementation depends of the graphics API.
        // Software rendering renders to a CPU memory region or to file.
        // TODO: implement Vulkan rendering!
        // TODO: implement software rendering!

        if (!this->should_render) [[unlikely]]
        {
            return;
        }

        if (this->render_system == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::render`: `this->render_system` is `nullptr`!");
        }

        if (this->get_active_camera() != nullptr) [[likely]]
        {
            if (this->get_is_opengl_in_use()) [[likely]]
            {
                // Send our view matrix to the uniform buffer object (UBO).
                glBindBuffer(GL_UNIFORM_BUFFER, this->get_active_camera()->get_camera_uniform_block());
                glBufferSubData(
                        GL_UNIFORM_BUFFER,
                        yli::opengl::camera_ubo::CameraUboBlockOffsets::V,
                        sizeof(glm::mat4),
                        glm::value_ptr(this->get_view_matrix())); // mat4
                glBindBuffer(GL_UNIFORM_BUFFER, 0);

                this->get_active_camera()->render();
            }
            else if (this->get_is_vulkan_in_use())
            {
                std::cerr << "ERROR: `Universe::render`: Vulkan is not supported yet!\n";
            }

            this->render_system->render(render_struct);
        }

        yli::opengl::print_opengl_errors("ERROR: `Universe::render`: OpenGL error detected!\n");
    }

    void Universe::render()
    {
        yli::render::RenderStruct render_struct;
        render_struct.scene = this->active_scene;
        render_struct.parent_of_font_2ds = &this->parent_of_font_2ds;
        render_struct.window = this->window;
        this->render(render_struct);
    }

    void Universe::render_without_changing_depth_test()
    {
        yli::render::RenderStruct render_struct;
        render_struct.scene = this->active_scene;
        render_struct.parent_of_font_2ds = &this->parent_of_font_2ds;
        render_struct.window = this->window;
        render_struct.should_change_depth_test = false;
        this->render(render_struct);
    }

    void Universe::set_active_scene(yli::ontology::Scene* const scene)
    {
        this->active_scene = scene;

        if (this->active_scene != nullptr)
        {
            this->turbo_factor = this->active_scene->get_turbo_factor();
            this->twin_turbo_factor = this->active_scene->get_twin_turbo_factor();
        }
    }

    yli::ontology::Camera* Universe::get_active_camera() const
    {
        if (this->active_scene != nullptr) [[likely]]
        {
            return this->active_scene->get_active_camera();
        }

        return nullptr; // No active `Scene`, so no active `Camera` either.
    }

    void Universe::set_active_camera(yli::ontology::Camera* const camera) const
    {
        // Changing the active `Camera` does not change the active `Scene`!

        yli::ontology::Scene* const scene_parent_of_camera = static_cast<yli::ontology::Scene*>(camera->get_parent());

        if (scene_parent_of_camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_active_camera`: `scene_parent_of_camera` is `nullptr`!");
        }

        scene_parent_of_camera->set_active_camera(camera);
    }

    const glm::vec3& Universe::get_xyz() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_xyz`: `camera` is `nullptr`!");
        }

        return camera->location.xyz;
    }

    void Universe::set_xyz(glm::vec3&& xyz)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_xyz`: `camera` is `nullptr`!");
        }

        camera->location.xyz = std::move(xyz);
    }

    void Universe::update_xyz(const glm::vec3& xyz)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::update_xyz`: `camera` is `nullptr`!");
        }

        camera->location.update_xyz(xyz);
    }

    float Universe::get_x() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_x`: `camera` is `nullptr`!");
        }

        return camera->location.xyz.x;
    }

    void Universe::set_x(const float x)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_x`: `camera` is `nullptr`!");
        }

        camera->location.xyz.x = x;
    }

    float Universe::get_y() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_y`: `camera` is `nullptr`!");
        }

        return camera->location.xyz.y;
    }

    void Universe::set_y(const float y)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_y`: `camera` is `nullptr`!");
        }

        camera->location.xyz.y = y;
    }

    float Universe::get_z() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_z`: `camera` is `nullptr`!");
        }

        return camera->location.xyz.z;
    }

    void Universe::set_z(const float z)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_z`: `camera` is `nullptr`!");
        }

        camera->location.xyz.z = z;
    }

    const yli::data::SphericalCoordinatesStruct& Universe::get_spherical() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_spherical`: `camera` is `nullptr`!");
        }

        return camera->spherical_coordinates;
    }

    void Universe::set_spherical(yli::data::SphericalCoordinatesStruct&& spherical_coordinates)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_spherical`: `camera` is `nullptr`!");
        }

        camera->spherical_coordinates = std::move(spherical_coordinates);
    }

    float Universe::get_rho() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_rho`: `camera` is `nullptr`!");
        }

        return camera->spherical_coordinates.rho;
    }

    void Universe::set_rho(const float rho)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_rho`: `camera` is `nullptr`!");
        }

        camera->spherical_coordinates.rho = rho;
    }

    float Universe::get_theta() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_theta`: `camera` is `nullptr`!");
        }

        return camera->spherical_coordinates.theta;
    }

    void Universe::set_theta(const float theta)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_theta`: `camera` is `nullptr`!");
        }

        camera->spherical_coordinates.theta = theta;
    }

    float Universe::get_phi() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_phi`: `camera` is `nullptr`!");
        }

        return camera->spherical_coordinates.phi;
    }

    void Universe::set_phi(const float phi)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_phi`: `camera` is `nullptr`!");
        }

        camera->spherical_coordinates.phi = phi;
    }

    const glm::vec3& Universe::get_direction() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_direction`: `camera` is `nullptr`!");
        }

        return camera->direction;
    }

    void Universe::set_direction(glm::vec3&& direction)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_rho`: `camera` is `nullptr`!");
        }

        camera->direction = std::move(direction);
    }

    const glm::vec3& Universe::get_right() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_right`: `camera` is `nullptr`!");
        }

        return camera->right;
    }

    void Universe::set_right(glm::vec3&& right)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_rho`: `camera` is `nullptr`!");
        }

        camera->right = std::move(right);
    }

    const glm::vec3& Universe::get_up() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_up`: `camera` is `nullptr`!");
        }

        return camera->up;
    }

    void Universe::set_up(glm::vec3&& up)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_rho`: `camera` is `nullptr`!");
        }

        camera->up = std::move(up);
    }

    float Universe::get_roll() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_roll`: `camera` is `nullptr`!");
        }

        return camera->get_roll();
    }

    void Universe::set_roll(const float roll)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_roll`: `camera` is `nullptr`!");
        }

        camera->set_roll(roll);
    }

    float Universe::get_yaw() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_yaw`: `camera` is `nullptr`!");
        }

        return camera->get_yaw();
    }

    void Universe::set_yaw(const float yaw)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_yaw`: `camera` is `nullptr`!");
        }

        camera->set_yaw(yaw);
    }

    void Universe::update_yaw(const float x_position)
    {
        const float temp_yaw = this->get_yaw() +
			this->mouse_speed * static_cast<float>(this->window_width / 2 - x_position);
        this->set_yaw(remainder(temp_yaw, (2.0f * std::numbers::pi)));
    }

    float Universe::get_pitch() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_pitch`: `camera` is `nullptr`!");
        }

        return camera->get_pitch();
    }

    void Universe::set_pitch(const float pitch)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_pitch`: `camera` is `nullptr`!");
        }

        camera->set_pitch(pitch);
    }

    void Universe::update_pitch(const float y_position)
    {
        const float temp_pitch = (this->is_invert_mouse_in_use) ?
            (this->get_pitch() - this->mouse_speed * static_cast<float>(this->window_height / 2 - y_position)) :
            (this->get_pitch() + this->mouse_speed * static_cast<float>(this->window_height / 2 - y_position));
        this->set_pitch(remainder(temp_pitch, (2.0f * std::numbers::pi)));
    }

    float Universe::get_azimuth() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_azimuth`: `camera` is `nullptr`!");
        }

        return camera->get_azimuth();
    }

    yli::ontology::Console* Universe::get_active_console() const
    {
        for (yli::ontology::Entity* console : this->parent_of_consoles.child_pointer_vector)
        {
            if (console == this->active_console)
            {
                return this->active_console;
            }
        }

        return nullptr;
    }

    void Universe::set_active_console(yli::ontology::Console* const console)
    {
        this->active_console = console;
    }

    yli::input::InputMethod Universe::get_input_method() const
    {
        return this->parent_of_input_modes.get_input_method();
    }

    yli::render::GraphicsApiBackend Universe::get_graphics_api_backend() const
    {
        return this->graphics_api_backend;
    }

    bool Universe::get_is_opengl_in_use() const
    {
        return this->graphics_api_backend == yli::render::GraphicsApiBackend::OPENGL;
    }

    bool Universe::get_is_vulkan_in_use() const
    {
        return this->graphics_api_backend == yli::render::GraphicsApiBackend::VULKAN;
    }

    bool Universe::get_is_software_rendering_in_use() const
    {
        return this->graphics_api_backend == yli::render::GraphicsApiBackend::SOFTWARE;
    }

    bool Universe::get_is_headless() const
    {
        return this->graphics_api_backend == yli::render::GraphicsApiBackend::HEADLESS;
    }

    bool Universe::get_is_silent() const
    {
        return this->is_silent;
    }

    bool Universe::get_is_physical() const
    {
        return this->is_physical;
    }

    std::size_t Universe::get_number_of_ecosystems() const
    {
        return this->parent_of_ecosystems.get_number_of_children();
    }

    std::size_t Universe::get_number_of_scenes() const
    {
        return this->parent_of_scenes.get_number_of_children();
    }

    yli::ontology::Scene* Universe::get_active_scene() const
    {
        return this->active_scene;
    }

    yli::ontology::Entity* Universe::get_parent() const
    {
        // `Universe` has no parent.
        return nullptr;
    }

    yli::ontology::GenericParentModule& Universe::get_parent_of_ecosystems()
    {
        return this->parent_of_ecosystems;
    }

    yli::ontology::Scene* Universe::get_scene() const
    {
        // `Universe` does not belong in any `Scene`.
        return nullptr;
    }

    std::size_t Universe::get_number_of_children() const
    {
        return this->parent_of_callback_engines.get_number_of_children() +
            this->parent_of_ecosystems.get_number_of_children() +
            this->parent_of_scenes.get_number_of_children() +
            this->parent_of_font_2ds.get_number_of_children() +
            this->parent_of_input_modes.get_number_of_children() +
            this->parent_of_consoles.get_number_of_children() +
            this->parent_of_console_callback_engines.get_number_of_children();
    }

    std::size_t Universe::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_callback_engines.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_ecosystems.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_scenes.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_font_2ds.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_input_modes.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_consoles.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_console_callback_engines.child_pointer_vector);
    }

    [[nodiscard]] bool Universe::create_window()
    {
        // Create the window only when OpenGL or Vulkan is in use.
        if (this->get_is_opengl_in_use() || this->get_is_vulkan_in_use()) [[likely]]
        {
            Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI;

            if (this->is_fullscreen)
            {
                flags |= SDL_WINDOW_FULLSCREEN;
            }

            if (this->is_desktop_fullscreen)
            {
                flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            }

            if (this->get_is_opengl_in_use()) [[likely]]
            {
                // Create a window.
                this->window = yli::sdl::create_window(
                        0,
                        0,
                        static_cast<int>(this->window_width),
                        static_cast<int>(this->window_height),
                        this->window_title.c_str(),
                        flags | SDL_WINDOW_OPENGL);
            }
            else if (this->get_is_vulkan_in_use())
            {
                // Create a window.
                this->window = yli::sdl::create_window(
                        0,
                        0,
                        static_cast<int>(this->window_width),
                        static_cast<int>(this->window_height),
                        this->window_title.c_str(),
                        flags | SDL_WINDOW_VULKAN);
            }

            if (this->window != nullptr) [[likely]]
            {
                std::cout << "SDL Window created successfully.\n";
                return true;
            }

            std::cerr << "ERROR: `Universe::create_window`: SDL Window could not be created!\n";
            return false;
        }

        return true;
    }

    [[nodiscard]] bool Universe::setup_context()
    {
        // Setup graphics context only when OpenGL or Vulkan is in use.
        if (this->get_is_opengl_in_use() || this->get_is_vulkan_in_use()) [[likely]]
        {
            if (!this->render_system->setup_context(this->window)) [[unlikely]]
            {
                // Setting up context failed.
                return false;
            }

            return true;
        }

        // No need to setup context.
        return true;
    }

    [[nodiscard]] bool Universe::create_window_and_setup_context()
    {
        // Create window and setup graphics context only when OpenGL or Vulkan is in use.
        if (this->get_is_opengl_in_use() || this->get_is_vulkan_in_use()) [[likely]]
        {
            if (!this->create_window()) [[unlikely]]
            {
                return false;
            }

            if (this->setup_context()) [[likely]]
            {
                return true;
            }

            return false;
        }

        // No need to create a window or to setup a context.
        return true;
    }

    void Universe::set_swap_interval(const int32_t interval)
    {
        if (!yli::sdl::set_swap_interval(static_cast<int>(interval))) [[unlikely]]
        {
            std::cerr << "ERROR: `Universe::set_swap_interval`: setting swap interval failed!\n";
        }
    }

    void Universe::restore_onscreen_rendering() const
    {
        // Bind the default framebuffer for on-screen rendering.
        yli::opengl::bind_gl_framebuffer(0);

        // Set background color for the default framebuffer.
        this->set_opengl_background_color();

        // Clear the default framebuffer.
        glClear(GL_COLOR_BUFFER_BIT);

        // Adjust viewport for the default framebuffer.
        this->adjust_opengl_viewport();
    }

    void Universe::set_opengl_background_color() const
    {
        yli::opengl::set_background_color(
                this->background_red,
                this->background_green,
                this->background_blue,
                this->background_alpha);
    }

    void Universe::adjust_opengl_viewport() const
    {
        if (this->window_width <= std::numeric_limits<GLsizei>::max() &&
                this->window_height <= std::numeric_limits<GLsizei>::max()) [[likely]]
        {
            glViewport(0, 0, this->window_width, this->window_height);
        }
    }

    bool Universe::get_is_exit_requested() const
    {
        return this->is_exit_requested;
    }

    SDL_Window* Universe::get_window() const
    {
        return this->window;
    }

    uint32_t Universe::get_window_width() const
    {
        return this->window_width;
    }

    void Universe::set_window_width(const uint32_t window_width)
    {
        this->window_width = window_width;
        this->adjust_opengl_viewport();

        if (this->active_console != nullptr) [[likely]]
        {
            this->active_console->adjust_n_columns();
        }
    }

    uint32_t Universe::get_window_height() const
    {
        return this->window_height;
    }

    void Universe::set_window_height(const uint32_t window_height)
    {
        this->window_height = window_height;
        this->adjust_opengl_viewport();

        if (this->active_console != nullptr) [[likely]]
        {
            this->active_console->adjust_n_rows();
        }
    }

    uint32_t Universe::get_text_size() const
    {
        return this->text_size;
    }

    uint32_t Universe::get_font_size() const
    {
        return this->font_size;
    }

    double Universe::compute_delta_time()
    {
        // `std::numeric_limits<std::size_t>::max()` means that `last_time_before_reading_keyboard` is not defined.
        if (this->last_time_before_reading_keyboard == std::numeric_limits<uint32_t>::max()) [[unlikely]]
        {
            // `SDL_GetTicks()` is called here only once, the first time this function is called.
            this->last_time_before_reading_keyboard = SDL_GetTicks();
        }

        this->current_time_before_reading_keyboard = SDL_GetTicks();

        this->delta_time = current_time_before_reading_keyboard - last_time_before_reading_keyboard;
        return this->delta_time;
    }

    double Universe::get_delta_time() const
    {
        return this->delta_time;
    }

    void Universe::finalize_delta_time_loop()
    {
        this->last_time_before_reading_keyboard = this->current_time_before_reading_keyboard;
    }

    uint32_t Universe::get_max_fps() const
    {
        return this->max_fps;
    }

    double Universe::get_last_time_to_display_fps() const
    {
        return this->last_time_to_display_fps;
    }

    double Universe::get_last_time_for_display_sync() const
    {
        return this->last_time_for_display_sync;
    }

    int32_t Universe::get_number_of_frames() const
    {
        return this->number_of_frames;
    }

    void Universe::increment_last_time_to_display_fps()
    {
        this->last_time_to_display_fps += 1.0;
    }

    void Universe::update_last_time_for_display_sync()
    {
        this->last_time_for_display_sync = yli::time::get_time();
    }

    void Universe::increment_number_of_frames()
    {
        this->number_of_frames++;
    }

    void Universe::reset_number_of_frames()
    {
        this->number_of_frames = 0;
    }

    std::string Universe::eval_string(const std::string& /* my_string */) const
    {
        return "TODO: eval";
    }

    yli::memory::GenericMemoryAllocator& Universe::get_generic_memory_allocator(const int type) const
    {
        return this->application.get_generic_memory_allocator(type);
    }

    yli::render::RenderSystem* Universe::get_render_system() const
    {
        if (this->render_system == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_render_system`: `this->render_system` is `nullptr`!");
        }

        return this->render_system.get();
    }

    yli::audio::AudioSystem* Universe::get_audio_system() const
    {
        if (yli::audio::AudioSystem* const audio_system = this->application.get_audio_system(); audio_system != nullptr) [[likely]]
        {
            return audio_system;
        }

        return nullptr;
    }

    const glm::mat4& Universe::get_projection_matrix() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_projection_matrix`: `camera` is `nullptr`!");
        }

        return camera->get_projection_matrix();
    }

    void Universe::set_projection_matrix(glm::mat4&& projection_matrix)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_projection_matrix`: `camera` is `nullptr`!");
        }

        camera->set_projection_matrix(std::move(projection_matrix));
    }

    const glm::mat4& Universe::get_view_matrix() const
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::get_view_matrix`: `camera` is `nullptr`!");
        }

        return camera->get_view_matrix();
    }

    void Universe::set_view_matrix(glm::mat4&& view_matrix)
    {
        yli::ontology::Camera* const camera = this->get_active_camera();

        if (camera == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Universe::set_view_matrix`: `camera` is `nullptr`!");
        }

        camera->set_view_matrix(std::move(view_matrix));
    }

    float Universe::get_aspect_ratio() const
    {
        return this->aspect_ratio;
    }

    float Universe::get_initial_fov() const
    {
        return this->initial_fov;
    }

    bool Universe::compute_and_update_matrices_from_inputs()
    {
        if (this->testing_spherical_terrain_in_use) [[unlikely]]
        {
            // Compute spherical coordinates.
            this->set_rho(sqrt(
                        (this->get_x() * this->get_x()) +
                        (this->get_y() * this->get_y()) +
                        (this->get_z() * this->get_z())));
            this->set_theta(yli::geometry::radians_to_degrees(atan2(sqrt(
                                (this->get_x() * this->get_x()) +
                                (this->get_y() * this->get_y())),
                            this->get_z())));
            this->set_phi(yli::geometry::radians_to_degrees(atan2(
                            this->get_y(),
                            this->get_x())));
        }

        glm::vec3 camera_cartesian_coordinates;
        camera_cartesian_coordinates.x = this->get_x();
        camera_cartesian_coordinates.y = this->get_y();
        camera_cartesian_coordinates.z = this->get_z();

        // Compute the projection matrix.
        this->set_projection_matrix(glm::perspective(
                    yli::geometry::degrees_to_radians(this->initial_fov),
                    this->aspect_ratio,
                    this->znear,
                    this->zfar));

        // Compute the view matrix.
        this->set_view_matrix(glm::lookAt(
                    camera_cartesian_coordinates,                                  // Camera coordinates.
                    camera_cartesian_coordinates + this->get_direction(),          // Camera looks here: at the same position, plus "current_camera_direction".
                    this->get_up()));                                              // Head is up (set to 0,-1,0 to look upside-down).

        return true;
    }

    void Universe::create_should_render_variable()
    {
        // Set the value of `should_render` here because it can't be done in `Entity` constructor.
        this->should_render = !this->get_is_headless();

        // Create `Variable` `should_render` here because it can't be done in `Entity` constructor.
        yli::ontology::VariableStruct should_render_variable_struct(*this, *this);
        should_render_variable_struct.is_variable_of_universe = true;
        should_render_variable_struct.local_name = "should_render";
        should_render_variable_struct.activate_callback = &yli::ontology::activate_should_render;
        should_render_variable_struct.read_callback = &yli::ontology::read_should_render;
        should_render_variable_struct.should_call_activate_callback_now = true;
        std::cout << "Executing `this->create_variable(should_render_variable_struct);` ...\n";
        this->create_variable(should_render_variable_struct, yli::data::AnyValue(this->should_render));
    }
}
