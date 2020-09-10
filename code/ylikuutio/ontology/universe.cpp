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

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef __STDC_FORMAT_MACROS
// For MinGW.
#define __STDC_FORMAT_MACROS
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

#include "entity.hpp"
#include "variable.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "text2D.hpp"
#include "camera.hpp"
#include "console.hpp"
#include "entity_variable_activation.hpp"
#include "entity_variable_read.hpp"
#include "variable_struct.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/audio/audio_master.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/callback/callback_magic_numbers.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/input/input_master.hpp"
#include "code/ylikuutio/input/input_mode.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/time/time.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include "SDL.h"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

// Include Bullet
#include <btBulletDynamicsCommon.h>

// Include standard headers
#include <cstddef>       // std::size_t
#include <iomanip>       // std::setfill, std::setprecision, std::setw
#include <ios>           // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <variant>       // std::holds_alternative, std::variant

namespace yli::data
{
    class AnyValue;
}

namespace yli::input
{
    class InputMaster;
}

namespace yli::ontology
{
    class Font2D;
    class Variable;

    const std::string Universe::version = "0.0.8";

    void Universe::bind_entity(yli::ontology::Entity* const entity)
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

    void Universe::unbind_entity(const std::size_t entityID)
    {
        yli::hierarchy::unbind_child_from_parent(
                entityID,
                this->entity_pointer_vector,
                this->free_entityID_queue,
                this->number_of_entities);
    }

    Universe::~Universe()
    {
        // destructor.
        std::cout << "This `Universe` will be destroyed.\n";

        if (!this->is_headless && this->is_framebuffer_initialized)
        {
            glDeleteTextures(1, &this->texture);
            glDeleteRenderbuffers(1, &this->renderbuffer);
            glDeleteFramebuffers(1, &this->framebuffer);
        }

        SDL_Quit();
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
        if (this->active_font2D == nullptr)
        {
            return;
        }

        if (this->entity_factory == nullptr)
        {
            return;
        }

        yli::ontology::Font2D* const font2D = this->active_font2D;

        // Create angles and cartesian coordinates text, on bottom left corner.
        yli::ontology::TextStruct angles_and_coordinates_text_struct;
        angles_and_coordinates_text_struct.font2D_parent = font2D;
        angles_and_coordinates_text_struct.screen_width = this->window_width;
        angles_and_coordinates_text_struct.screen_height = this->window_height;
        angles_and_coordinates_text_struct.x = 0;
        angles_and_coordinates_text_struct.y = 0;
        angles_and_coordinates_text_struct.text_size = this->text_size;
        angles_and_coordinates_text_struct.font_size = this->font_size;
        angles_and_coordinates_text_struct.font_texture_file_format = "bmp";
        angles_and_coordinates_text_struct.horizontal_alignment = "left";
        angles_and_coordinates_text_struct.vertical_alignment = "bottom";
        yli::ontology::Text2D* angles_and_coordinates_text2D = dynamic_cast<yli::ontology::Text2D*>(this->entity_factory->create_text2d(angles_and_coordinates_text_struct));

        if (angles_and_coordinates_text2D == nullptr)
        {
            return;
        }

        // Create spherical coordinates text, on second line from the bottom left.
        yli::ontology::TextStruct spherical_coordinates_text_struct;
        spherical_coordinates_text_struct.font2D_parent = font2D;
        spherical_coordinates_text_struct.screen_width = this->window_width;
        spherical_coordinates_text_struct.screen_height = this->window_height;
        spherical_coordinates_text_struct.x = 0;
        spherical_coordinates_text_struct.y = 2 * this->text_size;
        spherical_coordinates_text_struct.text_size = this->text_size;
        spherical_coordinates_text_struct.font_size = this->font_size;
        spherical_coordinates_text_struct.horizontal_alignment = "left";
        spherical_coordinates_text_struct.vertical_alignment = "bottom";
        yli::ontology::Text2D* spherical_coordinates_text2D = dynamic_cast<yli::ontology::Text2D*>(this->entity_factory->create_text2d(spherical_coordinates_text_struct));

        if (spherical_coordinates_text2D == nullptr)
        {
            return;
        }

        // Create time data text, on top left corner.
        yli::ontology::TextStruct time_text_struct;
        time_text_struct.font2D_parent = font2D;
        time_text_struct.screen_width = this->window_width;
        time_text_struct.screen_height = this->window_height;
        time_text_struct.x = 0;
        time_text_struct.y = this->window_height;
        time_text_struct.text_size = this->text_size;
        time_text_struct.font_size = this->font_size;
        time_text_struct.font_texture_file_format = "bmp";
        time_text_struct.horizontal_alignment = "left";
        time_text_struct.vertical_alignment = "top";
        yli::ontology::Text2D* time_text2D = dynamic_cast<yli::ontology::Text2D*>(this->entity_factory->create_text2d(time_text_struct));

        if (time_text2D == nullptr)
        {
            return;
        }

        // Create help text.
        yli::ontology::TextStruct help_text_struct;
        help_text_struct.font2D_parent = font2D;
        help_text_struct.screen_width = this->window_width;
        help_text_struct.screen_height = this->window_height;
        help_text_struct.x = 0;
        help_text_struct.y = this->window_height - (3 * this->text_size);
        help_text_struct.text_size = this->text_size;
        help_text_struct.font_size = this->font_size;
        help_text_struct.font_texture_file_format = "bmp";
        help_text_struct.horizontal_alignment = "left";
        help_text_struct.vertical_alignment = "top";
        yli::ontology::Text2D* help_text2D = dynamic_cast<yli::ontology::Text2D*>(this->entity_factory->create_text2d(help_text_struct));

        if (help_text2D == nullptr)
        {
            return;
        }

        // Print frame rate data on top right corner.
        yli::ontology::TextStruct frame_rate_text_struct;
        frame_rate_text_struct.font2D_parent = font2D;
        frame_rate_text_struct.screen_width = this->window_width;
        frame_rate_text_struct.screen_height = this->window_height;
        frame_rate_text_struct.x = this->window_width;
        frame_rate_text_struct.y = this->window_height;
        frame_rate_text_struct.text_size = this->text_size;
        frame_rate_text_struct.font_size = this->font_size;
        frame_rate_text_struct.font_texture_file_format = "bmp";
        frame_rate_text_struct.horizontal_alignment = "right";
        frame_rate_text_struct.vertical_alignment = "top";
        yli::ontology::Text2D* frame_rate_text2D = dynamic_cast<yli::ontology::Text2D*>(entity_factory->create_text2d(frame_rate_text_struct));

        if (frame_rate_text2D == nullptr)
        {
            return;
        }

        SDL_Event sdl_event;
        yli::sdl::flush_sdl_event_queue();

        // This method contains the main simulation loop.
        bool has_mouse_focus = true;

        while (!this->is_exit_requested && this->input_master != nullptr)
        {
            const float current_time_in_main_loop = yli::time::get_time();

            if (current_time_in_main_loop - this->last_time_for_display_sync >= (1.0f / this->max_fps))
            {
                this->update_last_time_for_display_sync();

                this->increment_number_of_frames();

                while (current_time_in_main_loop - this->last_time_to_display_fps >= 1.0f)
                {
                    // If last `std::stringstream` here was more than 1 sec ago,
                    // std::stringstream` and reset number of frames.
                    if (frame_rate_text2D != nullptr && this->number_of_frames > 0)
                    {
                        std::stringstream ms_frame_text_stringstream;
                        ms_frame_text_stringstream << std::fixed << std::setprecision(2) <<
                            1000.0f / static_cast<float>(this->number_of_frames) << " ms/frame; " <<
                            this->number_of_frames << " Hz";
                        std::string ms_frame_text = ms_frame_text_stringstream.str();
                        frame_rate_text2D->change_string(ms_frame_text);
                        this->reset_number_of_frames();
                    }

                    // `last_time_to_display_fps` needs to be incremented to avoid infinite loop.
                    this->increment_last_time_to_display_fps();

                    // Update audio also (in case the sound has reached the end).
                    if (audio_master != nullptr)
                    {
                        audio_master->update();
                    }
                }

                // Clear the screen.
                if (!this->is_headless)
                {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }

                this->compute_delta_time();

                this->mouse_x = this->window_width / 2;
                this->mouse_y = this->window_height / 2;

                const yli::input::InputMode* const input_mode = input_master->get_active_input_mode();

                if (input_mode == nullptr)
                {
                    return;
                }

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

                        yli::callback::CallbackEngine* const callback_engine = input_mode->get_keypress_callback_engine(scancode);

                        if (callback_engine != nullptr)
                        {
                            const std::shared_ptr<yli::data::AnyValue> any_value = callback_engine->execute(nullptr);

                            if (any_value != nullptr &&
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

                        yli::callback::CallbackEngine* const callback_engine = input_mode->get_keyrelease_callback_engine(scancode);

                        if (callback_engine == nullptr)
                        {
                            continue;
                        }

                        const std::shared_ptr<yli::data::AnyValue> any_value = callback_engine->execute(nullptr);

                        if (any_value != nullptr &&
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
                        this->current_camera_yaw += this->mouse_speed * static_cast<float>(this->window_width / 2 - xpos);
                        this->current_camera_yaw = remainder(this->current_camera_yaw, (2.0f * PI));

                        if (this->is_invert_mouse_in_use)
                        {
                            // Invert mouse.
                            this->current_camera_vertical_angle -= this->mouse_speed * static_cast<float>(this->window_height / 2 - ypos);
                        }
                        else
                        {
                            // Don't invert mouse.
                            this->current_camera_vertical_angle += this->mouse_speed * static_cast<float>(this->window_height / 2 - ypos);
                        }

                        this->current_camera_vertical_angle = remainder(this->current_camera_vertical_angle, (2.0f * PI));
                    }
                }

                // Direction: spherical coordinates to cartesian coordinates conversion.
                this->current_camera_direction = glm::vec3(
                        cos(this->current_camera_vertical_angle) * sin(this->current_camera_yaw + 0.5f * PI),
                        sin(this->current_camera_vertical_angle),
                        cos(this->current_camera_vertical_angle) * cos(this->current_camera_yaw + 0.5f * PI));

                // Right vector.
                this->current_camera_right = glm::vec3(
                        sin(this->current_camera_yaw),
                        0,
                        cos(this->current_camera_yaw));

                // Up vector.
                this->current_camera_up = glm::cross(this->current_camera_right, this->current_camera_direction);

                if (!this->in_console)
                {
                    const uint8_t* const current_key_states = SDL_GetKeyboardState(nullptr);
                    const std::vector<yli::callback::CallbackEngine*>* const continuous_keypress_callback_engines = input_mode->get_continuous_keypress_callback_engines();
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
                            yli::callback::CallbackEngine* const callback_engine = continuous_keypress_callback_engines->at(i);

                            if (callback_engine == nullptr)
                            {
                                continue;
                            }

                            const std::shared_ptr<yli::data::AnyValue> any_value = callback_engine->execute(nullptr);

                            if (any_value != nullptr &&
                                    std::holds_alternative<uint32_t>(any_value->data) &&
                                    std::get<uint32_t>(any_value->data) == EXIT_PROGRAM_MAGIC_NUMBER)
                            {
                                this->request_exit();
                            }
                        }
                    }
                }

                // Gravity etc. physical phenomena.
                this->do_physics();

                // Intentional actors (AIs and keyboard controlled ones).
                this->act();

                if (angles_and_coordinates_text2D != nullptr)
                {
                    std::stringstream angles_and_coordinates_stringstream;
                    angles_and_coordinates_stringstream << std::fixed << std::setprecision(2) <<
                        this->current_camera_yaw << "," <<
                        this->current_camera_vertical_angle << " rad; " <<
                        RADIANS_TO_DEGREES(this->current_camera_yaw) << "," <<
                        RADIANS_TO_DEGREES(this->current_camera_vertical_angle) << " deg\n" <<
                        "(" <<
                        this->current_camera_cartesian_coordinates.x << "," <<
                        this->current_camera_cartesian_coordinates.y << "," <<
                        this->current_camera_cartesian_coordinates.z << ")";
                    const std::string angles_and_coordinates_string = angles_and_coordinates_stringstream.str();
                    angles_and_coordinates_text2D->change_string(angles_and_coordinates_string);
                }

                if (time_text2D != nullptr)
                {
                    std::stringstream time_stringstream;
                    time_stringstream << std::fixed << std::setprecision(2) << yli::time::get_time() << " sec";
                    const std::string time_string = time_stringstream.str();
                    time_text2D->change_string(time_string);
                }

                const std::string on_string = "on";
                const std::string off_string = "off";

                if (help_text2D != nullptr)
                {
                    if (this->in_help_mode && this->can_display_help_screen)
                    {
                        std::stringstream help_text_stringstream;
                        yli::ontology::Scene* const scene = this->active_scene;
                        help_text_stringstream <<
                            (this->application_name.empty() ? "Ylikuutio" : this->application_name) << " " << yli::ontology::Universe::version << "\n"
                            "\n"
                            "arrow keys\n"
                            "space jump\n"
                            "enter duck\n"
                            "F1 help mode\n"
                            "`  enter console\n"
                            "I  invert mouse (" << (this->is_invert_mouse_in_use ? on_string : off_string) << ")\n"
                            "F  flight mode (" << (scene == nullptr || scene->get_is_flight_mode_in_use() ? on_string : off_string) << ")\n"
                            "Ctrl      turbo\n" <<
                            "Ctrl+Ctrl extra turbo\n" <<
                            "for debugging:\n" <<
                            "G  grass texture\n" <<
                            "O  orange fur texture\n" <<
                            "P  pink geometric tiles texture\n" <<
                            "T  terrain species\n" <<
                            "A  suzanne species\n";
                        const std::string help_text_string = help_text_stringstream.str();
                        help_text2D->change_string(help_text_string);
                    }
                    else
                    {
                        help_text2D->change_string("");
                    }
                }

                if (spherical_coordinates_text2D != nullptr)
                {
                    if (this->testing_spherical_terrain_in_use)
                    {
                        std::stringstream spherical_coordinates_stringstream;
                        spherical_coordinates_stringstream << std::fixed << std::setprecision(2) <<
                            "rho:" << this->current_camera_spherical_coordinates.rho <<
                            "theta:" << this->current_camera_spherical_coordinates.theta <<
                            "phi:" << this->current_camera_spherical_coordinates.phi;
                        std::string spherical_coordinates_string = spherical_coordinates_stringstream.str();
                        spherical_coordinates_text2D->change_string(spherical_coordinates_string);
                    }
                    else
                    {
                        spherical_coordinates_text2D->change_string("");
                    }
                }

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

    void Universe::render()
    {
        if (this->is_headless || !this->should_be_rendered)
        {
            return;
        }

        this->prerender();

        if (this->active_scene != nullptr)
        {
            // Render this `Universe` by calling `render()` function of the active `World`.
            this->active_scene->render();
        }

        yli::opengl::disable_depth_test();

        if (this->active_console != nullptr)
        {
            // Render the active `Console` (including current input).
            this->active_console->render();
        }

        // Render `Font2D`s of this `Universe` by calling `render()` function of each `Font2D`.
        yli::ontology::render_children<yli::ontology::Entity*>(this->parent_of_font2Ds.child_pointer_vector);

        yli::opengl::enable_depth_test();

        // Swap buffers.
        SDL_GL_SwapWindow(this->get_window());

        this->postrender();
    }

    void Universe::render_without_changing_depth_test()
    {
        if (this->is_headless || !this->should_be_rendered)
        {
            return;
        }

        this->prerender();

        if (this->active_scene != nullptr)
        {
            // Render this `Universe` by calling `render()` function of the active `World`.
            this->active_scene->render();
        }

        if (this->active_console != nullptr)
        {
            // Render the active `Console` (including current input).
            this->active_console->render();
        }

        // Render `Font2D`s of this `Universe` by calling `render()` function of each `Font2D`.
        yli::ontology::render_children<yli::ontology::Entity*>(this->parent_of_font2Ds.child_pointer_vector);

        // Swap buffers.
        SDL_GL_SwapWindow(this->get_window());

        this->postrender();
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

    yli::ontology::Font2D* Universe::get_active_font2D() const
    {
        return this->active_font2D;
    }

    void Universe::set_active_font2D(yli::ontology::Font2D* const font2D)
    {
        this->active_font2D = font2D;
    }

    void Universe::set_active_camera(yli::ontology::Camera* const camera) const
    {
        // Variable the active `Camera` does not change the active `Scene`!

        yli::ontology::Scene* const scene = static_cast<yli::ontology::Scene*>(camera->get_parent());

        if (scene == nullptr)
        {
            return; // `camera` has no parent.
        }

        scene->set_active_camera(camera);
    }

    yli::ontology::Console* Universe::get_active_console() const
    {
        return this->active_console;
    }

    void Universe::set_active_console(yli::ontology::Console* const console)
    {
        this->active_console = console;
    }

    yli::input::InputMethod Universe::get_input_method() const
    {
        if (this->input_master == nullptr)
        {
            return yli::input::InputMethod::KEYBOARD;
        }

        return this->input_master->get_input_method();
    }

    bool Universe::get_is_headless() const
    {
        return this->is_headless;
    }

    std::size_t Universe::get_number_of_worlds() const
    {
        return this->parent_of_worlds.get_number_of_children();
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

    std::size_t Universe::get_number_of_children() const
    {
        return this->parent_of_worlds.get_number_of_children() +
            this->parent_of_font2Ds.get_number_of_children() +
            this->parent_of_consoles.get_number_of_children() +
            this->parent_of_any_value_entities.get_number_of_children() +
            this->parent_of_callback_engine_entities.get_number_of_children();
    }

    std::size_t Universe::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_worlds.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_font2Ds.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_consoles.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_any_value_entities.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_callback_engine_entities.child_pointer_vector);
    }

    void Universe::create_context()
    {
        this->context = yli::sdl::create_context(this->window);
    }

    void Universe::make_context_current()
    {
        if (this->context != nullptr)
        {
            yli::sdl::make_context_current(this->window, *this->context);
        }
    }

    void Universe::set_swap_interval(const int32_t interval)
    {
        yli::sdl::set_swap_interval(static_cast<int>(interval));
    }

    void Universe::restore_onscreen_rendering() const
    {
        // Bind the default framebuffer for on-screen rendering.
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Set background color for the default framebuffer.
        universe->set_opengl_background_color();

        // Clear the default framebuffer.
        glClear(GL_COLOR_BUFFER_BIT);

        // Adjust viewport for the default framebuffer.
        universe->adjust_opengl_viewport();
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
                this->window_height <= std::numeric_limits<GLsizei>::max())
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

        if (this->active_console != nullptr)
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

        if (this->active_console != nullptr)
        {
            this->active_console->adjust_n_rows();
        }
    }

    uint32_t Universe::get_framebuffer_width() const
    {
        return this->framebuffer_width;
    }

    void Universe::set_framebuffer_width(const uint32_t framebuffer_width)
    {
        this->framebuffer_width = framebuffer_width;
    }

    uint32_t Universe::get_framebuffer_height() const
    {
        return this->framebuffer_height;
    }

    void Universe::set_framebuffer_height(const uint32_t framebuffer_height)
    {
        this->framebuffer_height = framebuffer_height;
    }

    std::size_t Universe::get_text_size() const
    {
        return this->text_size;
    }

    std::size_t Universe::get_font_size() const
    {
        return this->font_size;
    }

    float Universe::compute_delta_time()
    {
        // `std::numeric_limits<std::size_t>::max()` means that `last_time_before_reading_keyboard` is not defined.
        if (this->last_time_before_reading_keyboard == std::numeric_limits<uint32_t>::max())
        {
            // `SDL_GetTicks()` is called here only once, the first time this function is called.
            this->last_time_before_reading_keyboard = SDL_GetTicks();
        }

        this->current_time_before_reading_keyboard = SDL_GetTicks();

        this->delta_time = static_cast<float>(current_time_before_reading_keyboard - last_time_before_reading_keyboard);
        return this->delta_time;
    }

    float Universe::get_delta_time() const
    {
        return this->delta_time;
    }

    void Universe::finalize_delta_time_loop()
    {
        this->last_time_before_reading_keyboard = this->current_time_before_reading_keyboard;
    }

    std::size_t Universe::get_max_fps() const
    {
        return this->max_fps;
    }

    float Universe::get_last_time_to_display_fps() const
    {
        return this->last_time_to_display_fps;
    }

    float Universe::get_last_time_for_display_sync() const
    {
        return this->last_time_for_display_sync;
    }

    int32_t Universe::get_number_of_frames() const
    {
        return this->number_of_frames;
    }

    void Universe::increment_last_time_to_display_fps()
    {
        this->last_time_to_display_fps += 1.0f;
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

    yli::ontology::EntityFactory* Universe::get_entity_factory() const
    {
        if (this->entity_factory == nullptr)
        {
            return nullptr;
        }

        return this->entity_factory.get();
    }

    std::string Universe::eval_string(const std::string& my_string) const
    {
        return "TODO: eval";
    }

    yli::audio::AudioMaster* Universe::get_audio_master() const
    {
        if (this->audio_master == nullptr)
        {
            return nullptr;
        }

        return this->audio_master.get();
    }

    yli::input::InputMaster* Universe::get_input_master() const
    {
        if (this->input_master == nullptr)
        {
            return nullptr;
        }

        return this->input_master.get();
    }

    btDefaultCollisionConfiguration* Universe::get_collision_configuration() const
    {
        if (this->collision_configuration == nullptr)
        {
            return nullptr;
        }

        return this->collision_configuration.get();
    }

    btCollisionDispatcher* Universe::get_dispatcher() const
    {
        if (this->dispatcher == nullptr)
        {
            return nullptr;
        }

        return this->dispatcher.get();
    }

    btBroadphaseInterface* Universe::get_overlapping_pair_cache() const
    {
        if (this->overlapping_pair_cache == nullptr)
        {
            return nullptr;
        }

        return this->overlapping_pair_cache.get();
    }

    btSequentialImpulseConstraintSolver* Universe::get_solver() const
    {
        if (this->solver == nullptr)
        {
            return nullptr;
        }

        return this->solver.get();
    }

    const glm::mat4& Universe::get_projection_matrix() const
    {
        return this->current_camera_projection_matrix;
    }

    void Universe::set_projection_matrix(const glm::mat4& projection_matrix)
    {
        this->current_camera_projection_matrix = projection_matrix;
    }

    const glm::mat4& Universe::get_view_matrix() const
    {
        return this->current_camera_view_matrix;
    }

    void Universe::set_view_matrix(const glm::mat4& view_matrix)
    {
        this->current_camera_view_matrix = view_matrix;
    }

    float Universe::get_aspect_ratio() const
    {
        return this->aspect_ratio;
    }

    float Universe::get_initialFoV() const
    {
        return this->initialFoV;
    }

    bool Universe::compute_and_update_matrices_from_inputs()
    {
        if (this->testing_spherical_terrain_in_use)
        {
            // Compute spherical coordinates.
            this->current_camera_spherical_coordinates.rho = sqrt(
                    (this->current_camera_cartesian_coordinates.x * this->current_camera_cartesian_coordinates.x) +
                    (this->current_camera_cartesian_coordinates.y * this->current_camera_cartesian_coordinates.y) +
                    (this->current_camera_cartesian_coordinates.z * this->current_camera_cartesian_coordinates.z));
            this->current_camera_spherical_coordinates.theta = RADIANS_TO_DEGREES(atan2(sqrt(
                            (this->current_camera_cartesian_coordinates.x * this->current_camera_cartesian_coordinates.x) +
                            (this->current_camera_cartesian_coordinates.y * this->current_camera_cartesian_coordinates.y)),
                        this->current_camera_cartesian_coordinates.z));
            this->current_camera_spherical_coordinates.phi = RADIANS_TO_DEGREES(atan2(
                        this->current_camera_cartesian_coordinates.y,
                        this->current_camera_cartesian_coordinates.x));
        }

        glm::vec3 camera_cartesian_coordinates;
        camera_cartesian_coordinates.x = this->current_camera_cartesian_coordinates.x;
        camera_cartesian_coordinates.y = this->current_camera_cartesian_coordinates.y;
        camera_cartesian_coordinates.z = this->current_camera_cartesian_coordinates.z;

        // Compute the projection matrix.
        this->current_camera_projection_matrix = glm::perspective(
                DEGREES_TO_RADIANS(this->initialFoV),
                this->aspect_ratio,
                this->znear,
                this->zfar);

        // Compute the view matrix.
        this->current_camera_view_matrix = glm::lookAt(
                camera_cartesian_coordinates,                                  // Camera coordinates.
                camera_cartesian_coordinates + this->current_camera_direction, // Camera looks here: at the same position, plus "current_camera_direction".
                this->current_camera_up);                                      // Head is up (set to 0,-1,0 to look upside-down).

        return true;
    }

    void Universe::create_should_be_rendered_variable()
    {
        // Create `Variable` `should_be_rendered` here because it can't be done in `Entity` constructor.
        yli::ontology::VariableStruct should_be_rendered_variable_struct(std::make_shared<yli::data::AnyValue>(this->should_be_rendered));
        should_be_rendered_variable_struct.local_name = "should_be_rendered";
        should_be_rendered_variable_struct.activate_callback = &yli::ontology::activate_should_be_rendered;
        should_be_rendered_variable_struct.read_callback = &yli::ontology::read_should_be_rendered;
        should_be_rendered_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `this->create_variable(should_be_rendered_variable_struct);` ...\n";
        this->create_variable(should_be_rendered_variable_struct);
    }
}
