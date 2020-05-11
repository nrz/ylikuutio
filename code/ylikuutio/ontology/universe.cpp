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

#include "universe.hpp"
#include "entity.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "console.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
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

// Include standard headers
#include <cstddef>       // std::size_t
#include <ios>           // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <string>        // std::string
#include <utility>       // std::pair
#include <vector>        // std::vector

namespace yli::common
{
    class AnyValue;
}

namespace yli::config
{
    class Setting;
}

namespace yli::input
{
    class InputMaster;
}

namespace yli::ontology
{
    class Font2D;

    const std::string Universe::version = "0.0.6";

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
        // Setting the active `Camera` does not change the active `Scene`!

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
            this->parent_of_any_struct_entities.get_number_of_children() +
            this->parent_of_callback_engine_entities.get_number_of_children();
    }

    std::size_t Universe::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_worlds.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_font2Ds.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_consoles.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_any_value_entities.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_any_struct_entities.child_pointer_vector) +
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
        universe->universe->adjust_opengl_viewport();
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

    bool Universe::is_entity(const std::string& name) const
    {
        return this->entity_map.count(name) == 1;
    }

    yli::ontology::Entity* Universe::get_entity(const std::string& name) const
    {
        if (this->entity_map.count(name) != 1)
        {
            return nullptr;
        }
        return this->entity_map.at(name);
    }

    std::string Universe::get_entity_names() const
    {
        std::string entity_names = "";

        std::vector<std::string> keys;
        keys.reserve(this->entity_map.size());

        for (auto it : this->entity_map)
        {
            if (!entity_names.empty())
            {
                entity_names += " ";
            }
            std::string key = static_cast<std::string>(it.first);
            entity_names += key;
        }

        return entity_names;
    }

    void Universe::add_entity(const std::string& name, yli::ontology::Entity* const entity)
    {
        if (this->entity_map.count(name) == 0)
        {
            this->entity_map[name] = entity;
        }
    }

    void Universe::erase_entity(const std::string& name)
    {
        if (this->entity_map.count(name) == 1)
        {
            if (this->entity_map[name]->get_can_be_erased())
            {
                this->entity_map.erase(name);
            }
        }
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
        if (this->angelscript_master == nullptr)
        {
            return "";
        }

        return this->angelscript_master->eval_string(my_string);
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
}
