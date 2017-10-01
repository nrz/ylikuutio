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
#include "entity.hpp"
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
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <inttypes.h>    // PRId32, PRId64, PRIu32, PRIu64, PRIx32, PRIx64
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

namespace ontology
{
    Universe::Universe()
    {
        this->cartesian_coordinates = nullptr;
        this->spherical_coordinates = nullptr;

        // constructor.
        this->world_radius = NAN; // world radius is NAN as long it doesn't get `set` by `SettingMaster`.
        this->terrain_species_pointer = nullptr;
        this->active_scene = nullptr;
        this->setting_master_pointer = nullptr;
        this->console_pointer = nullptr;

        this->background_red = NAN;
        this->background_green = NAN;
        this->background_blue = NAN;
        this->background_alpha = NAN;

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

        this->horizontal_angle = NAN;
        this->vertical_angle = NAN;
        this->turbo_factor = NAN;
        this->twin_turbo_factor = NAN;

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

        this->number_of_scenes = 0;

        this->child_vector_pointers_vector.push_back(&this->scene_pointer_vector);
        this->type = "ontology::Universe*";
    }

    Universe::~Universe()
    {
        // destructor.
        std::cout << "This world will be destroyed.\n";

        // destroy all scenes of this world.
        std::cout << "All scenes of this world will be destroyed.\n";
        hierarchy::delete_children<ontology::Scene*>(this->scene_pointer_vector, &this->number_of_scenes);

        std::cout << "The setting master of this universe will be destroyed.\n";
        delete this->setting_master_pointer;
    }

    void Universe::render()
    {
        this->prerender();

        if (this->compute_matrices_from_inputs())
        {
            // render this `Universe` by calling `render()` function of the active `Scene`.
            this->active_scene->render();
        }

        this->postrender();
    }

    int32_t Universe::get_number_of_children()
    {
        return this->number_of_scenes;
    }

    int32_t Universe::get_number_of_descendants()
    {
        return -1;
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

    GLFWwindow* Universe::get_window() const
    {
        return this->window;
    }

    uint32_t Universe::get_window_width() const
    {
        return this->window_width;
    }

    uint32_t Universe::get_window_height() const
    {
        return this->window_height;
    }

    uint32_t Universe::get_text_size() const
    {
        return this->text_size;
    }

    uint32_t Universe::get_font_size() const
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

    float Universe::get_delta_time() const
    {
        return this->delta_time;
    }

    void Universe::finalize_delta_time_loop()
    {
        this->last_time_before_reading_keyboard = this->current_time_before_reading_keyboard;
    }

    uint32_t Universe::get_max_FPS() const
    {
        return this->max_FPS;
    }

    void Universe::set(std::string& setting_name, std::shared_ptr<datatypes::AnyValue> setting_any_value)
    {
        this->setting_master_pointer->set(setting_name, setting_any_value);
    }

    config::Setting* Universe::get(std::string key) const
    {
        return this->setting_master_pointer->get(key);
    }

    std::string Universe::get_entity_names() const
    {
        std::string entity_names = "";

        std::vector<std::string> keys;
        keys.reserve(this->entity_anyvalue_map.size());

        for (auto it : this->entity_anyvalue_map)
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

    // Public callbacks.

    std::shared_ptr<datatypes::AnyValue> Universe::delete_entity(
            console::Console* const console,
            ontology::Universe* const universe,
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
                    break;
                case (datatypes::datatype::SCENE_POINTER):
                    // OK, this is a `Scene` to be deleted.
                    delete static_cast<ontology::Scene*>(any_value->scene_pointer);
                    break;
                case (datatypes::datatype::SHADER_POINTER):
                    // OK, this is a `Shader` to be deleted.
                    delete static_cast<ontology::Shader*>(any_value->shader_pointer);
                    break;
                case (datatypes::datatype::MATERIAL_POINTER):
                    // OK, this is a `Material` to be deleted.
                    delete static_cast<ontology::Material*>(any_value->material_pointer);
                    break;
                case (datatypes::datatype::SPECIES_POINTER):
                    // OK, this is a `Species` to be deleted.
                    delete static_cast<ontology::Species*>(any_value->species_pointer);
                    break;
                case (datatypes::datatype::OBJECT_POINTER):
                    // OK, this is a `Object` to be deleted.
                    delete static_cast<ontology::Object*>(any_value->object_pointer);
                    break;
                case (datatypes::datatype::VECTORFONT_POINTER):
                    // OK, this is a `VectorFont` to be deleted.
                    delete static_cast<ontology::VectorFont*>(any_value->vector_font_pointer);
                    break;
                case (datatypes::datatype::GLYPH_POINTER):
                    // OK, this is a `Glyph` to be deleted.
                    delete static_cast<ontology::Glyph*>(any_value->glyph_pointer);
                    break;
                case (datatypes::datatype::TEXT3D_POINTER):
                    // OK, this is a `Text3D` to be deleted.
                    delete static_cast<ontology::Text3D*>(any_value->text3D_pointer);
                    break;
                default:
                    return nullptr;
            }
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Universe::info(
            console::Console* const console,
            ontology::Universe* const universe,
            std::vector<std::string>& command_parameters)
    {
        if (console == nullptr ||
                universe == nullptr ||
                universe->setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print names of named entities.
            console->print_text(universe->get_entity_names());
        }
        else if (command_parameters.size() == 1)
        {
            std::string name = command_parameters[0];

            if (universe->entity_anyvalue_map.count(name) != 1)
            {
                return nullptr;
            }

            datatypes::AnyValue* any_value = universe->entity_anyvalue_map[name];

            if (any_value == nullptr)
            {
                return nullptr;
            }

            // OK, let's find out information about the entity.
            ontology::Entity* entity = any_value->get_entity_pointer();

            if (entity == nullptr)
            {
                return nullptr;
            }

            console->print_text(entity->get_type());

            uint64_t memory_address = reinterpret_cast<uint64_t>((void*) entity);
            char memory_address_char_array[256];
            snprintf(memory_address_char_array, sizeof(memory_address_char_array), "0x%" PRIx64, static_cast<uint64_t>(memory_address));

            std::string entity_info = "memory address: ";
            entity_info += std::string(memory_address_char_array);
            console->print_text(entity_info);

            int32_t number_of_children = entity->get_number_of_children();
            char number_of_children_char_array[256];
            snprintf(number_of_children_char_array, sizeof(number_of_children_char_array), "%d", number_of_children);

            std::string children_info = "number of children: ";
            children_info += std::string(number_of_children_char_array);
            console->print_text(children_info);
        }
        return nullptr;
    }

    // Public callbacks end here.

    void Universe::set_scene_pointer(int32_t childID, ontology::Scene* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->scene_pointer_vector, this->free_sceneID_queue, &this->number_of_scenes);
    }

    void Universe::set_terrain_species_pointer(ontology::Species* terrain_species_pointer)
    {
        this->terrain_species_pointer = terrain_species_pointer;
    }

    bool Universe::compute_matrices_from_inputs()
    {
        if (this->cartesian_coordinates == nullptr)
        {
            return false;
        }

        if (!this->is_flight_mode_in_use)
        {
            this->fall_speed += this->gravity;
            this->cartesian_coordinates->y -= this->fall_speed;
        }

        GLfloat FoV = this->initialFoV;

        // adjust position according to the ground.
        if (!this->is_flight_mode_in_use)
        {
            if (this->terrain_species_pointer != nullptr)
            {
                GLfloat ground_y = ontology::get_floor_level(static_cast<ontology::Species*>(this->terrain_species_pointer), this->cartesian_coordinates);

                if (!std::isnan(ground_y) && this->cartesian_coordinates->y < ground_y)
                {
                    this->cartesian_coordinates->y = ground_y;
                    this->fall_speed = 0.0f;
                }
            }
        }

        if (this->testing_spherical_world_in_use)
        {
            if (this->spherical_coordinates == nullptr)
            {
                return false;
            }

            // compute spherical coordinates.
            this->spherical_coordinates->rho = sqrt((this->cartesian_coordinates->x * this->cartesian_coordinates->x) + (this->cartesian_coordinates->y * this->cartesian_coordinates->y) + (this->cartesian_coordinates->z * this->cartesian_coordinates->z));
            this->spherical_coordinates->theta = RADIANS_TO_DEGREES(atan2(sqrt((this->cartesian_coordinates->x * this->cartesian_coordinates->x) + (this->cartesian_coordinates->y * this->cartesian_coordinates->y)), this->cartesian_coordinates->z));
            this->spherical_coordinates->phi = RADIANS_TO_DEGREES(atan2(this->cartesian_coordinates->y, this->cartesian_coordinates->x));
        }

        glm::vec3 camera_cartesian_coordinates;
        camera_cartesian_coordinates.x = this->cartesian_coordinates->x;
        camera_cartesian_coordinates.y = this->cartesian_coordinates->y;
        camera_cartesian_coordinates.z = this->cartesian_coordinates->z;
        camera_cartesian_coordinates.y += 2.0f;

        // Projection matrix : 45° Field of View, aspect ratio, display range : 0.1 unit <-> 100 units
        this->ProjectionMatrix = glm::perspective(DEGREES_TO_RADIANS(FoV), aspect_ratio, 0.001f, 5000.0f + 2.0f * static_cast<GLfloat>(this->world_radius));
        // Camera matrix
        this->ViewMatrix = glm::lookAt(
                camera_cartesian_coordinates,                   // Camera is here
                camera_cartesian_coordinates + this->direction, // and looks here : at the same position, plus "direction"
                this->up                                        // Head is up (set to 0,-1,0 to look upside-down)
                );

        return true;
    }
}
