#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "species.hpp"
#include "object.hpp"
#include "vector_font.hpp"
#include "glyph.hpp"
#include "text3D.hpp"
#include "ground_level.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <unordered_map> // std::unordered_map

extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

namespace ontology
{
    Universe::Universe()
    {
        // constructor.
        this->world_radius = NAN; // world radius is NAN as long it doesn't get `set` by `SettingMaster`.
        this->setting_master_pointer = nullptr;
        this->console_pointer = nullptr;

        // Variables related to the window.
        this->window = nullptr;
        this->window_width = 1600; // default width.
        this->window_height = 900; // default height.

        // Variables related to the camera.
        this->aspect_ratio = static_cast<GLfloat>(this->window_width / this->window_height);
        this->initialFoV = 60.0f;

        this->text_size = 40; // default text size.
        this->font_size = 16; // default font size.

        this->max_FPS = 60; // default value max 60 frames per second.
        this->delta_time = NAN;
        this->last_time_before_reading_keyboard = NAN;
        this->current_time_before_reading_keyboard = NAN;

        this->has_mouse_ever_moved = false;
        this->can_toggle_invert_mouse = false;
        this->is_invert_mouse_in_use = false;
        this->can_toggle_flight_mode = false;
        this->is_flight_mode_in_use = false;
        this->is_first_turbo_pressed = false;
        this->is_second_turbo_pressed = false;

        this->speed = 5.0f; // 5.0 units / second
        this->mouse_speed = 0.005f;

        this->gravity = 9.81f / 60.0f;
        this->fall_speed = this->gravity;

        this->testing_spherical_world_in_use = false;
        this->is_key_I_released = true;
        this->is_key_F_released = true;
        this->in_help_mode = true;
        this->can_toggle_help_mode = false;
        this->can_display_help_screen = true;

        this->child_vector_pointers_vector.push_back(&this->scene_pointer_vector);
    }

    Universe::~Universe()
    {
        // destructor.
        std::cout << "This world will be destroyed.\n";

        // destroy all scenes of this world.
        std::cout << "All scenes of this world will be destroyed.\n";
        hierarchy::delete_children<ontology::Scene*>(this->scene_pointer_vector);

        std::cout << "The setting master of this universe will be destroyed.\n";
        delete this->setting_master_pointer;
    }

    void Universe::render()
    {
        if (!this->compute_matrices_from_inputs())
        {
            return;
        }

        // render this `Universe` by calling `render()` function of the active `Scene`.
        this->active_scene->render();
    }

    void Universe::set_active_scene(ontology::Scene* scene)
    {
        this->active_scene = scene;
    }

    void Universe::set_window(GLFWwindow* window)
    {
        this->window = window;
        glfwSetWindowUserPointer(this->window, this);
    }

    GLFWwindow* Universe::get_window()
    {
        return this->window;
    }

    uint32_t Universe::get_window_width()
    {
        return this->window_width;
    }

    uint32_t Universe::get_window_height()
    {
        return this->window_height;
    }

    uint32_t Universe::get_text_size()
    {
        return this->text_size;
    }

    uint32_t Universe::get_font_size()
    {
        return this->font_size;
    }

    float Universe::compute_delta_time()
    {
        if (std::isnan(this->last_time_before_reading_keyboard))
        {
            // `glfwGetTime()` is called here only once, the first time this function is called.
            this->last_time_before_reading_keyboard = glfwGetTime();
        }

        this->current_time_before_reading_keyboard = glfwGetTime();

        this->delta_time = static_cast<float>(current_time_before_reading_keyboard - last_time_before_reading_keyboard);
        return this->delta_time;
    }

    float Universe::get_delta_time()
    {
        return this->delta_time;
    }

    void Universe::finalize_delta_time_loop()
    {
        this->last_time_before_reading_keyboard = this->current_time_before_reading_keyboard;
    }

    uint32_t Universe::get_max_FPS()
    {
        return this->max_FPS;
    }

    bool Universe::set(std::string& setting_name, datatypes::AnyValue* setting_any_value)
    {
        this->setting_master_pointer->set(setting_name, setting_any_value);
    }

    config::Setting* Universe::get(std::string key)
    {
        return this->setting_master_pointer->get(key);
    }

    datatypes::AnyValue* Universe::get_value(std::string key)
    {
        return this->setting_master_pointer->get_value(key);
    }

    // Public callbacks.

    datatypes::AnyValue* Universe::delete_entity(
            console::Console* console,
            ontology::Universe* universe,
            std::vector<std::string>& command_parameters)
    {
        if (console == nullptr || universe == nullptr || command_parameters.size() == 0)
        {
            return nullptr;
        }

        config::SettingMaster* setting_master = universe->setting_master_pointer;

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string name = command_parameters[0];
            datatypes::AnyValue* any_value = universe->entity_anyvalue_map[name];

            if (any_value == nullptr)
            {
                return nullptr;
            }

            switch (any_value->type)
            {
                case (datatypes::datatype::UNIVERSE_POINTER):
                    // OK, this is an `Universe` to be deleted.
                    delete static_cast<ontology::Universe*>(any_value->universe_pointer);
                case (datatypes::datatype::SCENE_POINTER):
                    // OK, this is a `Scene` to be deleted.
                    delete static_cast<ontology::Scene*>(any_value->scene_pointer);
                case (datatypes::datatype::SHADER_POINTER):
                    // OK, this is a `Shader` to be deleted.
                    delete static_cast<ontology::Shader*>(any_value->shader_pointer);
                case (datatypes::datatype::MATERIAL_POINTER):
                    // OK, this is a `Material` to be deleted.
                    delete static_cast<ontology::Material*>(any_value->material_pointer);
                case (datatypes::datatype::SPECIES_POINTER):
                    // OK, this is a `Species` to be deleted.
                    delete static_cast<ontology::Species*>(any_value->species_pointer);
                case (datatypes::datatype::OBJECT_POINTER):
                    // OK, this is a `Object` to be deleted.
                    delete static_cast<ontology::Object*>(any_value->object_pointer);
                case (datatypes::datatype::VECTORFONT_POINTER):
                    // OK, this is a `VectorFont` to be deleted.
                    delete static_cast<ontology::VectorFont*>(any_value->vector_font_pointer);
                case (datatypes::datatype::GLYPH_POINTER):
                    // OK, this is a `Glyph` to be deleted.
                    delete static_cast<ontology::Glyph*>(any_value->glyph_pointer);
                case (datatypes::datatype::TEXT3D_POINTER):
                    // OK, this is a `Text3D` to be deleted.
                    delete static_cast<ontology::Text3D*>(any_value->text3D_pointer);
                default:
                    return nullptr;
            }
            delete any_value;
        }
        else
        {
            return nullptr;
        }
    }

    datatypes::AnyValue* Universe::info(
            console::Console* console,
            ontology::Universe* universe,
            std::vector<std::string>& command_parameters)
    {
        if (console == nullptr || universe == nullptr || command_parameters.size() == 0)
        {
            return nullptr;
        }

        config::SettingMaster* setting_master = universe->setting_master_pointer;

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string name = command_parameters[0];
            datatypes::AnyValue* any_value = universe->entity_anyvalue_map[name];

            if (any_value == nullptr)
            {
                return nullptr;
            }

            // OK, let's find out information about the entity.

            // TODO: get info about the entity.
            delete any_value;
            return nullptr;
        }
        else
        {
            return nullptr;
        }
    }

    // Public callbacks end here.

    void Universe::set_scene_pointer(uint32_t childID, ontology::Scene* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->scene_pointer_vector, this->free_sceneID_queue);
    }

    void Universe::set_terrain_species_pointer(ontology::Species* terrain_species_pointer)
    {
        this->terrain_species_pointer = terrain_species_pointer;
    }

    bool Universe::compute_matrices_from_inputs()
    {
        if (!this->is_flight_mode_in_use)
        {
            this->fall_speed += this->gravity;
            this->cartesian_coordinates.y -= this->fall_speed;
        }

        GLfloat FoV = this->initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

        // adjust position according to the ground.
        if (!this->is_flight_mode_in_use)
        {
            if (this->terrain_species_pointer != nullptr)
            {
                GLfloat ground_y = ontology::get_floor_level(static_cast<ontology::Species*>(this->terrain_species_pointer), this->cartesian_coordinates);

                if (!std::isnan(ground_y) && this->cartesian_coordinates.y < ground_y)
                {
                    this->cartesian_coordinates.y = ground_y;
                    this->fall_speed = 0.0f;
                }
            }
        }

        if (this->testing_spherical_world_in_use)
        {
            // compute spherical coordinates.
            this->spherical_coordinates->rho = sqrt((this->cartesian_coordinates.x * this->cartesian_coordinates.x) + (this->cartesian_coordinates.y * this->cartesian_coordinates.y) + (this->cartesian_coordinates.z * this->cartesian_coordinates.z));
            this->spherical_coordinates->theta = RADIANS_TO_DEGREES(atan2(sqrt((this->cartesian_coordinates.x * this->cartesian_coordinates.x) + (this->cartesian_coordinates.y * this->cartesian_coordinates.y)), this->cartesian_coordinates.z));
            this->spherical_coordinates->phi = RADIANS_TO_DEGREES(atan2(this->cartesian_coordinates.y, this->cartesian_coordinates.x));
        }

        glm::vec3 camera_cartesian_coordinates = this->cartesian_coordinates;
        camera_cartesian_coordinates.y += 2.0f;

        // Projection matrix : 45° Field of View, aspect ratio, display range : 0.1 unit <-> 100 units
        this->ProjectionMatrix = glm::perspective(FoV, aspect_ratio, 0.001f, 5000.0f + 2.0f * static_cast<GLfloat>(this->world_radius));
        // Camera matrix
        this->ViewMatrix = glm::lookAt(
                camera_cartesian_coordinates,                   // Camera is here
                camera_cartesian_coordinates + this->direction, // and looks here : at the same position, plus "direction"
                this->up                                        // Head is up (set to 0,-1,0 to look upside-down)
                );

        return true;
    }
}
