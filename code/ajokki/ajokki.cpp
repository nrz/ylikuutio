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

#include "ajokki_background_colors.hpp"
#include "ajokki_cleanup_callbacks.hpp"
#include "ajokki_console_callbacks.hpp"
#include "ajokki_altiplano_scene.hpp"
#include "ajokki_helsinki_east_downtown_scene.hpp"
#include "ajokki_joensuu_center_west_scene.hpp"
#include "ajokki_tallinn_scene.hpp"
#include "ajokki_keyboard_callbacks.hpp"
#include "ajokki_debug.hpp"
#include "ajokki_console.hpp"
#include "ajokki_movement.hpp"
#include "ajokki_location_and_orientation.hpp"
#include "ajokki_wireframe.hpp"
#include "code/ylikuutio/audio/audio_master.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/console/console_command_callback.hpp"
#include "code/ylikuutio/console/console_struct.hpp"
#include "code/ylikuutio/console/console_callback_object.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/text3D.hpp"
#include "code/ylikuutio/ontology/text3D_struct.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/vector_font_struct.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/vboindexer.hpp"
#include "code/ylikuutio/time/time.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/printing_struct.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

#define SDL_main main

#include "SDL.h"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <cstddef>       // std::size_t
#include <cstdio>        // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

int main(const int argc, const char* argv[])
{
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    command_line_master.print_keys_and_values();

    int input_method_in_use = yli::input::KEYBOARD;

    // Create the world, store it in `my_universe`.
    std::cout << "Creating yli::ontology::Entity* my_universe_entity ...\n";
    UniverseStruct universe_struct;
    universe_struct.window_title = "Ajokki 0.0.3, powered by Ylikuutio 0.0.3";
    yli::ontology::Universe* my_universe = new yli::ontology::Universe(universe_struct);
    my_universe->set_name("universe");

    yli::ontology::EntityFactory* entity_factory = my_universe->get_entity_factory();

    yli::audio::AudioMaster audio_master;

    float earth_radius = 6371.0f; // in kilometres

    SettingStruct planet_radius_setting_struct(std::make_shared<yli::datatypes::AnyValue>(earth_radius));
    planet_radius_setting_struct.name = "planet_radius";
    planet_radius_setting_struct.setting_master = my_universe->get_setting_master();
    planet_radius_setting_struct.activate_callback = &yli::config::SettingMaster::activate_planet_radius; // world may be a planet or a moon.
    planet_radius_setting_struct.should_ylikuutio_call_activate_callback_now = true;
    new yli::config::Setting(planet_radius_setting_struct);

    std::cout << "Creating yli::callback_system::CallbackEngine* cleanup_callback_engine ...\n";
    yli::callback_system::CallbackEngine* cleanup_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* cleanup_callback_object = new yli::callback_system::CallbackObject(nullptr, cleanup_callback_engine);

    if (my_universe->get_window() == nullptr)
    {
        std::cerr << "Failed to open SDL window.\n";
        cleanup_callback_engine->execute();
        return -1;
    }

    my_universe->create_context();
    my_universe->make_context_current();

    // Initialize GLEW.
    if (!yli::opengl::init_glew())
    {
        cleanup_callback_engine->execute();
        return -1;
    }

    yli::input::disable_cursor();
    yli::input::enable_relative_mouse_mode();

    // Enable depth test.
    yli::opengl::enable_depth_test();
    // Accept fragment if it closer to the camera than the former one.
    yli::opengl::set_depth_func_to_less();

    // Cull triangles which normal is not towards the camera.
    yli::opengl::cull_triangles();

    std::cout << "Setting up background colors ...\n";
    ajokki::set_background_colors(my_universe->get_setting_master());
    std::cout << "Setting up wireframe state ...\n";
    ajokki::set_wireframe(my_universe->get_setting_master());
    std::cout << "Setting up movement ...\n";
    ajokki::set_movement(my_universe->get_setting_master());
    std::cout << "Setting up location and orientation ...\n";
    ajokki::set_location_and_orientation(my_universe->get_setting_master());
    std::cout << "Setting up debug variables ...\n";
    ajokki::set_debug_variables(my_universe->get_setting_master());
    std::cout << "Setting up console ...\n";
    ajokki::set_console(my_universe->get_setting_master());

    // Create the `World`s.

    std::cout << "Creating yli::ontology::Entity* earth_world_entity ...\n";
    yli::ontology::Entity* earth_world_entity = entity_factory->create_World();
    std::cout << "Creating yli::ontology::World* earth_world ...\n";
    yli::ontology::World* earth_world = dynamic_cast<yli::ontology::World*>(earth_world_entity);

    if (earth_world == nullptr)
    {
        cleanup_callback_engine->execute();
        return -1;
    }

    std::cout << "Setting earth_world as the active world ...\n";
    my_universe->set_active_world(earth_world);

    // Create the `Scene`s.
    // The `Scene`s will be created in the following order:
    // 1. Helsinki
    // 2. Joensuu
    // 3. altiplano

    // Helsinki `Scene` begins here.

    std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_scene_entity and its contents ...\n";
    yli::ontology::Entity* helsinki_east_downtown_scene_entity = ajokki::create_helsinki_east_downtown_scene(entity_factory, earth_world);

    if (helsinki_east_downtown_scene_entity == nullptr)
    {
        cleanup_callback_engine->execute();
        return -1;
    }

    std::cout << "Creating yli::ontology::Scene* helsinki_east_downtown_scene ...\n";
    yli::ontology::Scene* helsinki_east_downtown_scene = dynamic_cast<yli::ontology::Scene*>(helsinki_east_downtown_scene_entity);

    my_universe->is_flight_mode_in_use = true;

    if (helsinki_east_downtown_scene == nullptr)
    {
        cleanup_callback_engine->execute();
        return -1;
    }

    // Set `helsinki_east_downtown_scene` to be the currently active `Scene` in `earth_world`.
    std::cout << "Setting helsinki_east_downtown_scene as the active scene ...\n";
    earth_world->set_active_scene(helsinki_east_downtown_scene);

    // Helsinki `Scene` ends here.

    // Joensuu `Scene` begins here.

    std::cout << "Creating yli::ontology::Scene* joensuu_center_west_scene and its contents ...\n";
    if (ajokki::create_joensuu_center_west_scene(entity_factory, earth_world) == nullptr)
    {
        cleanup_callback_engine->execute();
        return -1;
    }

    // Joensuu `Scene` ends here.

    // altiplano `Scene` begins here.

    std::cout << "Creating yli::ontology::Scene* altiplano_scene and its contents ...\n";
    if (ajokki::create_altiplano_scene(entity_factory, earth_world) == nullptr)
    {
        cleanup_callback_engine->execute();
        return -1;
    }

    // altiplano `Scene` ends here.

    // Tallinn `Scene` begins here.

    std::cout << "Creating yli::ontology::Scene* tallinn_scene and its contents ...\n";
    if (ajokki::create_tallinn_scene(entity_factory, earth_world) == nullptr)
    {
        cleanup_callback_engine->execute();
        return -1;
    }

    // Tallinn `Scene` ends here.

    my_universe->turbo_factor = 100.0f;
    my_universe->twin_turbo_factor = 500.0f;
    // keypress callbacks.
    std::vector<KeyAndCallbackStruct>* action_mode_keypress_callback_engines = new std::vector<KeyAndCallbackStruct>();
    std::vector<KeyAndCallbackStruct>* action_mode_continuous_keypress_callback_engines = new std::vector<KeyAndCallbackStruct>();

    // This vector points to current keypress callback engines vector.
    std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer;
    current_keypress_callback_engine_vector_pointer = &action_mode_keypress_callback_engines;

    // keyrelease callbacks.
    std::vector<KeyAndCallbackStruct>* action_mode_keyrelease_callback_engines = new std::vector<KeyAndCallbackStruct>();

    // This vector points to current keyrelease callback engines vector.
    std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer;
    current_keyrelease_callback_engine_vector_pointer = &action_mode_keyrelease_callback_engines;

    // Initialize our little text library with the Holstein font
    const char* char_g_font_texture_filename = "Holstein.bmp";
    const char* char_g_font_texture_file_format = "bmp";

    std::cout << "Creating yli::ontology::Entity* my_font2D_entity ...\n";
    yli::ontology::Entity* my_font2D_entity = entity_factory->create_Font2D(
            my_universe->get_window_width(),
            my_universe->get_window_height(),
            char_g_font_texture_filename,
            char_g_font_texture_file_format);
    std::cout << "Creating yli::ontology::Font2D* my_font2D ...\n";
    yli::ontology::Font2D* my_font2D = dynamic_cast<yli::ontology::Font2D*>(my_font2D_entity);

    if (my_font2D == nullptr)
    {
        std::cerr << "Failed to create Font2D.\n";
        cleanup_callback_engine->execute();
        return -1;
    }

    std::cout << "Font2D created successfully.\n";

    std::unordered_map<std::string, ConsoleCommandCallback> command_callback_map;

    ConsoleStruct console_struct;
    console_struct.current_keypress_callback_engine_vector_pointer_pointer = current_keypress_callback_engine_vector_pointer;
    console_struct.current_keyrelease_callback_engine_vector_pointer_pointer = current_keyrelease_callback_engine_vector_pointer;
    console_struct.command_callback_map_pointer = &command_callback_map;
    console_struct.universe = my_universe;
    console_struct.font2D_pointer = my_font2D;

    std::cout << "Creating yli::console::Console* my_console ...\n";

    yli::console::Console* my_console = new yli::console::Console(console_struct); // create a console.

    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    std::cout << "Defining action mode keyrelease callback engines.\n";

    // Callback code for left Control release: release first turbo.
    yli::callback_system::CallbackEngine* release_first_turbo_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* release_first_turbo_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::release_first_turbo,
            release_first_turbo_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, release_first_turbo_callback_object);

    // Callback code for right Control release: release second turbo.
    yli::callback_system::CallbackEngine* release_second_turbo_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* release_second_turbo_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::release_second_turbo,
            release_second_turbo_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, release_second_turbo_callback_object);

    // Callback code for I release: enable_toggle invert mouse.
    yli::callback_system::CallbackEngine* enable_toggle_invert_mouse_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* enable_toggle_invert_mouse_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::enable_toggle_invert_mouse,
            enable_toggle_invert_mouse_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, enable_toggle_invert_mouse_callback_object);

    // Callback code for F release: enable_toggle flight mode.
    yli::callback_system::CallbackEngine* enable_toggle_flight_mode_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* enable_toggle_flight_mode_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::enable_toggle_flight_mode,
            enable_toggle_flight_mode_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, enable_toggle_flight_mode_callback_object);

    // Callback code for F1 release: enable toggle help mode.
    yli::callback_system::CallbackEngine* enable_toggle_help_mode_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* enable_toggle_help_mode_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::enable_toggle_help_mode,
            enable_toggle_help_mode_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, enable_toggle_help_mode_callback_object);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::cout << "Defining action mode keypress callback engines.\n";

    // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
    yli::callback_system::CallbackEngine* enter_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enter_console, enter_console_callback_engine, my_console);

    // Callback code for esc: exit program.
    yli::callback_system::CallbackEngine* exit_program_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::callback_system::CallbackObject(&ajokki::exit_program, exit_program_callback_engine);

    // Callback code for left Control: first turbo.
    yli::callback_system::CallbackEngine* first_turbo_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* first_turbo_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::first_turbo,
            first_turbo_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, first_turbo_callback_object);

    // Callback code for right Control: second turbo.
    yli::callback_system::CallbackEngine* second_turbo_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* second_turbo_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::second_turbo,
            second_turbo_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, second_turbo_callback_object);

    // Callback code for key up: move forward.
    yli::callback_system::CallbackEngine* move_forward_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* move_forward_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::move_forward,
            move_forward_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, move_forward_callback_object);

    // Callback code for key down: move backward.
    yli::callback_system::CallbackEngine* move_backward_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* move_backward_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::move_backward,
            move_backward_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, move_backward_callback_object);

    // Callback code for key left: strafe left.
    yli::callback_system::CallbackEngine* strafe_left_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* strafe_left_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::strafe_left,
            strafe_left_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, strafe_left_callback_object);

    // Callback code for key right: strafe right.
    yli::callback_system::CallbackEngine* strafe_right_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* strafe_right_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::strafe_right,
            strafe_right_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, strafe_right_callback_object);

    // Callback code for space: ascent.
    yli::callback_system::CallbackEngine* ascent_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* ascent_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::ascent,
            ascent_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, ascent_callback_object);

    // Callback code for enter: descent.
    yli::callback_system::CallbackEngine* descent_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* descent_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::descent,
            descent_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, descent_callback_object);

    // Callback code for I: toggle invert mouse.
    yli::callback_system::CallbackEngine* toggle_invert_mouse_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* toggle_invert_mouse_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::toggle_invert_mouse,
            toggle_invert_mouse_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, toggle_invert_mouse_callback_object);

    // Callback code for F: toggle flight mode.
    yli::callback_system::CallbackEngine* toggle_flight_mode_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* toggle_flight_mode_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::toggle_flight_mode,
            toggle_flight_mode_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, toggle_flight_mode_callback_object);

    // Callback code for F1: toggle help mode.
    yli::callback_system::CallbackEngine* toggle_help_mode_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* toggle_help_mode_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::toggle_help_mode,
            toggle_help_mode_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, toggle_help_mode_callback_object);

    // Callback code for D: delete Suzanne species.
    std::string suzanne_species_string = "suzanne_species";
    yli::callback_system::CallbackEngine* delete_suzanne_species_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* delete_suzanne_species_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::delete_entity,
            delete_suzanne_species_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, delete_suzanne_species_callback_object);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(&suzanne_species_string), false, delete_suzanne_species_callback_object);

    // Callback code for G: switch to grass material.
    std::string grass_material_string = "helsinki_east_downtown_grass_material";
    yli::callback_system::CallbackEngine* switch_to_grass_material_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* switch_to_grass_material_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::switch_to_new_material,
            switch_to_grass_material_callback_engine);
    new yli::callback_system::CallbackParameter(
            "",
            std::make_shared<yli::datatypes::AnyValue>(my_universe),
            false,
            switch_to_grass_material_callback_object);
    new yli::callback_system::CallbackParameter(
            "",
            std::make_shared<yli::datatypes::AnyValue>(&suzanne_species_string),
            false,
            switch_to_grass_material_callback_object);
    new yli::callback_system::CallbackParameter(
            "",
            std::make_shared<yli::datatypes::AnyValue>(&grass_material_string),
            false,
            switch_to_grass_material_callback_object);

    // Callback code for O: switch to orange fur material.
    std::string orange_fur_material_string = "helsinki_east_downtown_orange_fur_material";
    yli::callback_system::CallbackEngine* switch_to_orange_fur_material_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* switch_to_orange_fur_material_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::switch_to_new_material,
            switch_to_orange_fur_material_callback_engine);
    new yli::callback_system::CallbackParameter(
            "",
            std::make_shared<yli::datatypes::AnyValue>(my_universe),
            false,
            switch_to_orange_fur_material_callback_object);
    new yli::callback_system::CallbackParameter(
            "",
            std::make_shared<yli::datatypes::AnyValue>(&suzanne_species_string),
            false,
            switch_to_orange_fur_material_callback_object);
    new yli::callback_system::CallbackParameter(
            "",
            std::make_shared<yli::datatypes::AnyValue>(&orange_fur_material_string),
            false,
            switch_to_orange_fur_material_callback_object);

    // Callback code for P: switch to pink_geometric_tiles_material.
    std::string pink_geometric_tiles_material_string = "helsinki_east_downtown_pink_geometric_tiles_material";
    yli::callback_system::CallbackEngine* switch_to_pink_geometric_tiles_material_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* switch_to_pink_geometric_tiles_material_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::switch_to_new_material,
            switch_to_pink_geometric_tiles_material_callback_engine);
    new yli::callback_system::CallbackParameter(
            "",
            std::make_shared<yli::datatypes::AnyValue>(my_universe),
            false,
            switch_to_pink_geometric_tiles_material_callback_object);
    new yli::callback_system::CallbackParameter(
            "",
            std::make_shared<yli::datatypes::AnyValue>(&suzanne_species_string),
            false,
            switch_to_pink_geometric_tiles_material_callback_object);
    new yli::callback_system::CallbackParameter(
            "",
            std::make_shared<yli::datatypes::AnyValue>(&pink_geometric_tiles_material_string),
            false,
            switch_to_pink_geometric_tiles_material_callback_object);

    // Callback code for T: transform `suzanne2` into terrain.
    std::string helsinki_species_string = "helsinki_east_downtown_terrain_species";
    std::string suzanne2_string = "suzanne2";
    yli::callback_system::CallbackEngine* transform_into_terrain_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* transform_into_terrain_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::transform_into_new_species,
            transform_into_terrain_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, transform_into_terrain_callback_object);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(&suzanne2_string), false, transform_into_terrain_callback_object);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(&helsinki_species_string), false, transform_into_terrain_callback_object);

    // Callback code for A: transform `suzanne2` back into monkey.
    yli::callback_system::CallbackEngine* transform_into_monkey_callback_engine = new yli::callback_system::CallbackEngine();
    yli::callback_system::CallbackObject* transform_into_monkey_callback_object = new yli::callback_system::CallbackObject(
            &ajokki::transform_into_new_species, transform_into_monkey_callback_engine);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, transform_into_monkey_callback_object);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(&suzanne2_string), false, transform_into_monkey_callback_object);
    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(&suzanne_species_string), false, transform_into_monkey_callback_object);

    /*********************************************************************\
     *  Callback engines for console keyreleases begin here.             *
    \*********************************************************************/

    std::cout << "Defining console keyrelease callback engines.\n";

    // Callback code for left Control release.
    yli::callback_system::CallbackEngine* release_left_control_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_left_control_in_console, release_left_control_in_console_callback_engine, my_console);

    // Callback code for right Control release.
    yli::callback_system::CallbackEngine* release_right_control_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_right_control_in_console, release_right_control_in_console_callback_engine, my_console);

    // Callback code for left Alt release.
    yli::callback_system::CallbackEngine* release_left_alt_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_left_alt_in_console, release_left_alt_in_console_callback_engine, my_console);

    // Callback code for right Alt release.
    yli::callback_system::CallbackEngine* release_right_alt_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_right_alt_in_console, release_right_alt_in_console_callback_engine, my_console);

    // Callback code for left Shift release.
    yli::callback_system::CallbackEngine* release_left_shift_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_left_shift_in_console, release_left_shift_in_console_callback_engine, my_console);

    // Callback code for right Shift release.
    yli::callback_system::CallbackEngine* release_right_shift_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::release_right_shift_in_console, release_right_shift_in_console_callback_engine, my_console);

    // Callback code for key up release: enable move to previous input.
    yli::callback_system::CallbackEngine* enable_move_to_previous_input_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_move_to_previous_input, enable_move_to_previous_input_callback_engine, my_console);

    // Callback code for key down release: enable move to next input.
    yli::callback_system::CallbackEngine* enable_move_to_next_input_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_move_to_next_input, enable_move_to_next_input_callback_engine, my_console);

    // Callback code for backspace release: enable backspace.
    yli::callback_system::CallbackEngine* enable_backspace_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_backspace, enable_backspace_callback_engine, my_console);

    // Callback code for enter release: enable Enter key.
    yli::callback_system::CallbackEngine* enable_enter_key_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_enter_key, enable_enter_key_callback_engine, my_console);

    // Callback code for C release: enable Control-C.
    yli::callback_system::CallbackEngine* enable_ctrl_c_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_ctrl_c, enable_ctrl_c_callback_engine, my_console);

    // Callback code for W release: enable Control-W.
    yli::callback_system::CallbackEngine* enable_ctrl_w_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_ctrl_w, enable_ctrl_w_callback_engine, my_console);

    // Callback code for PgUp release: enable PgUp.
    yli::callback_system::CallbackEngine* enable_page_up_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_page_up, enable_page_up_callback_engine, my_console);

    // Callback code for PgDn release: enable PgDn.
    yli::callback_system::CallbackEngine* enable_page_down_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_page_down, enable_page_down_callback_engine, my_console);

    // Callback code for Home release: enable Home.
    yli::callback_system::CallbackEngine* enable_home_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_home, enable_home_callback_engine, my_console);

    // Callback code for End release: enable End.
    yli::callback_system::CallbackEngine* enable_end_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enable_end, enable_end_callback_engine, my_console);

    /*********************************************************************\
     *  Callback engines for console keypresses begin here.              *
    \*********************************************************************/

    std::cout << "Defining console keypress callback engines.\n";

    // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
    yli::callback_system::CallbackEngine* exit_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::exit_console, exit_console_callback_engine, my_console);

    // Callback code for left Control press.
    yli::callback_system::CallbackEngine* press_left_control_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_left_control_in_console, press_left_control_in_console_callback_engine, my_console);

    // Callback code for right Control press.
    yli::callback_system::CallbackEngine* press_right_control_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_right_control_in_console, press_right_control_in_console_callback_engine, my_console);

    // Callback code for left Alt press.
    yli::callback_system::CallbackEngine* press_left_alt_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_left_alt_in_console, press_left_alt_in_console_callback_engine, my_console);

    // Callback code for right Alt press.
    yli::callback_system::CallbackEngine* press_right_alt_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_right_alt_in_console, press_right_alt_in_console_callback_engine, my_console);

    // Callback code for left Shift press.
    yli::callback_system::CallbackEngine* press_left_shift_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_left_shift_in_console, press_left_shift_in_console_callback_engine, my_console);

    // Callback code for right Shift press.
    yli::callback_system::CallbackEngine* press_right_shift_in_console_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::press_right_shift_in_console, press_right_shift_in_console_callback_engine, my_console);

    // Callback code for key up: move to previous input.
    yli::callback_system::CallbackEngine* move_to_previous_input_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::move_to_previous_input, move_to_previous_input_callback_engine, my_console);

    // Callback code for key down: move to next input.
    yli::callback_system::CallbackEngine* move_to_next_input_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::move_to_next_input, move_to_next_input_callback_engine, my_console);

    // Callback code for backspace: delete character left of cursor from current input in console.
    yli::callback_system::CallbackEngine* backspace_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::backspace, backspace_callback_engine, my_console);

    // Callback code for Enter key.
    yli::callback_system::CallbackEngine* enter_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::enter_key, enter_callback_engine, my_console);

    // Callback code for C: Control-C.
    yli::callback_system::CallbackEngine* ctrl_c_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::ctrl_c, ctrl_c_callback_engine, my_console);

    // Callback code for W: Control-W.
    yli::callback_system::CallbackEngine* ctrl_w_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::ctrl_w, ctrl_w_callback_engine, my_console);

    // Callback code for PgUp.
    yli::callback_system::CallbackEngine* page_up_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::page_up, page_up_callback_engine, my_console);

    // Callback code for PgDn.
    yli::callback_system::CallbackEngine* page_down_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::page_down, page_down_callback_engine, my_console);

    // Callback code for Home.
    yli::callback_system::CallbackEngine* home_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::home, home_callback_engine, my_console);

    // Callback code for End.
    yli::callback_system::CallbackEngine* end_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::console::ConsoleCallbackObject(&yli::console::Console::end, end_callback_engine, my_console);

    new yli::callback_system::CallbackParameter("", std::make_shared<yli::datatypes::AnyValue>(my_universe), false, cleanup_callback_object);
    new yli::callback_system::CallbackParameter("font2D_pointer", std::make_shared<yli::datatypes::AnyValue>(my_font2D), false, cleanup_callback_object);
    cleanup_callback_object->set_new_callback(&ajokki::full_cleanup);

    // Keyrelease callbacks for action mode.
    // Key releases are checked in the order of this struct.
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_LCTRL, release_first_turbo_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RCTRL, release_second_turbo_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_I, enable_toggle_invert_mouse_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_F, enable_toggle_flight_mode_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_F1, enable_toggle_help_mode_callback_engine });

    // Keypress callbacks for action mode.
    // Keypresses are checked in the order of this struct.
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_GRAVE, enter_console_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_ESCAPE, exit_program_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_LCTRL, first_turbo_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RCTRL, second_turbo_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_I, toggle_invert_mouse_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_F, toggle_flight_mode_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_F1, toggle_help_mode_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_D, delete_suzanne_species_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_G, switch_to_grass_material_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_O, switch_to_orange_fur_material_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_P, switch_to_pink_geometric_tiles_material_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_T, transform_into_terrain_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_A, transform_into_monkey_callback_engine });

    // Continuous keypress callbacks for action mode.
    // Keypresses are checked in the order of this struct.
    action_mode_continuous_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_UP, move_forward_callback_engine });
    action_mode_continuous_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_DOWN, move_backward_callback_engine });
    action_mode_continuous_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_LEFT, strafe_left_callback_engine });
    action_mode_continuous_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RIGHT, strafe_right_callback_engine });
    action_mode_continuous_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_SPACE, ascent_callback_engine });
    action_mode_continuous_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RETURN, descent_callback_engine });

    // Keyrelease callbacks for console.
    // Key releases are checked in the order of this struct.
    std::vector<KeyAndCallbackStruct>* console_keyrelease_callback_engines = new std::vector<KeyAndCallbackStruct>();
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_LCTRL, release_left_control_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RCTRL, release_right_control_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_LALT, release_left_alt_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RALT, release_right_alt_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_LSHIFT, release_left_shift_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RSHIFT, release_right_shift_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_UP, enable_move_to_previous_input_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_DOWN, enable_move_to_next_input_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_BACKSPACE, enable_backspace_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RETURN, enable_enter_key_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_C, enable_ctrl_c_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_W, enable_ctrl_w_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_PAGEUP, enable_page_up_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_PAGEDOWN, enable_page_down_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_HOME, enable_home_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_END, enable_end_callback_engine });
    my_console->set_my_keyrelease_callback_engine_vector_pointer(console_keyrelease_callback_engines);

    // Keypress callbacks for console.
    // Keypresses are checked in the order of this struct.
    std::vector<KeyAndCallbackStruct>* console_keypress_callback_engines = new std::vector<KeyAndCallbackStruct>();
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_GRAVE, exit_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_LCTRL, press_left_control_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RCTRL, press_right_control_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_LALT, press_left_alt_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RALT, press_right_alt_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_LSHIFT, press_left_shift_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RSHIFT, press_right_shift_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_UP, move_to_previous_input_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_DOWN, move_to_next_input_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_BACKSPACE, backspace_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_RETURN, enter_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_C, ctrl_c_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_W, ctrl_w_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_PAGEUP, page_up_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_PAGEDOWN, page_down_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_HOME, home_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { SDL_SCANCODE_END, end_callback_engine });
    my_console->set_my_keypress_callback_engine_vector_pointer(console_keypress_callback_engines);

    /*********************************************************************\
     * Callback engines for console commands begin here.                 *
     * These define what commands there are available in the console     *
     * and what each command does.                                       *
     \********************************************************************/

    std::cout << "Defining console command callback engines.\n";

    // Config callbacks.
    command_callback_map["set"] = &yli::config::SettingMaster::set_and_print;
    command_callback_map["get"] = &yli::config::SettingMaster::get_and_print;

    // Object handling callbacks.
    command_callback_map["activate"] = &yli::ontology::Universe::activate;
    command_callback_map["delete"] = &yli::ontology::Universe::delete_entity;
    command_callback_map["info"] = &yli::ontology::Universe::info;
    command_callback_map["bind"] = &yli::ontology::Universe::bind;

    // Exit program callbacks.
    command_callback_map["bye"] = &ajokki::quit;
    command_callback_map["chau"] = &ajokki::quit;
    command_callback_map["ciao"] = &ajokki::quit;
    command_callback_map["heippa"] = &ajokki::quit;
    command_callback_map["quit"] = &ajokki::quit;
    command_callback_map["sayonara"] = &ajokki::quit;

    // Other callbacks.
    command_callback_map["help"] = &ajokki::help;
    command_callback_map["version"] = &ajokki::version;

    // For speed computation
    double last_time_to_display_FPS = yli::time::get_time();
    double last_time_for_display_sync = yli::time::get_time();
    int32_t number_of_frames = 0;

    bool ms_frame_text_ready = false;

    bool is_exit_requested = false;
    bool has_mouse_focus = true;

    audio_master.add_to_playlist("Ajokki_playlist", "414270__greek555__sample-97-bpm.wav");
    audio_master.add_to_playlist("Ajokki_playlist", "419588__greek555__dreaming-of-me.ogg");
    audio_master.add_to_playlist("Ajokki_playlist", "416882__greek555__blue-play.ogg");
    audio_master.add_to_playlist("Ajokki_playlist", "395487__frankum__tecno-pop-base-and-guitar-2.ogg");
    audio_master.play_playlist("Ajokki_playlist");

    SDL_Event sdl_event;

    while (!is_exit_requested)
    {
        double current_time_in_main_loop = yli::time::get_time();

        if (current_time_in_main_loop - last_time_for_display_sync >= (1.0f / my_universe->get_max_FPS()))
        {
            last_time_for_display_sync = yli::time::get_time();

            char ms_frame_text[256];
            number_of_frames++;

            while (current_time_in_main_loop - last_time_to_display_FPS >= 1.0f)
            {
                // If last `std::printf()` was more than 1 sec ago,
                // `std::printf` and reset.
                if (number_of_frames > 0)
                {
                    std::snprintf(
                            ms_frame_text,
                            sizeof(ms_frame_text),
                            "%.02f ms/frame; %d Hz",
                            1000.0f / ((double) number_of_frames),
                            number_of_frames);
                    ms_frame_text_ready = true;
                    number_of_frames = 0;
                }

                // `last_time_to_display_FPS` needs to be incremented to avoid infinite loop.
                last_time_to_display_FPS += 1.0;

                // Update audio also (in case the sound has reached the end).
                audio_master.update();
            }

            // Clear the screen.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            my_universe->compute_delta_time();

            int32_t mouse_x = my_universe->get_window_width() / 2;
            int32_t mouse_y = my_universe->get_window_height() / 2;

            // poll all SDL events.
            while (SDL_PollEvent(&sdl_event))
            {
                if (sdl_event.type == SDL_MOUSEMOTION)
                {
                    mouse_x += sdl_event.motion.xrel; // horizontal motion relative to screen center.
                    mouse_y += sdl_event.motion.yrel; // vertical motion relative to screen center.
                }
                else if (sdl_event.type == SDL_KEYDOWN)
                {
                    uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                    for (std::size_t i = 0; i < (*current_keypress_callback_engine_vector_pointer)->size(); i++)
                    {
                        if ((*current_keypress_callback_engine_vector_pointer)->at(i).keycode == scancode)
                        {
                            yli::callback_system::CallbackEngine* callback_engine = (*current_keypress_callback_engine_vector_pointer)->at(i).callback_engine;
                            std::shared_ptr<yli::datatypes::AnyValue> any_value = callback_engine->execute();

                            if (any_value != nullptr &&
                                    any_value->type == yli::datatypes::UINT32_T)
                            {
                                if (any_value->uint32_t_value == ENTER_CONSOLE_MAGIC_NUMBER)
                                {
                                    // Do not display help screen when in console.
                                    my_universe->can_display_help_screen = false;
                                }
                                else if (any_value->uint32_t_value == EXIT_CONSOLE_MAGIC_NUMBER)
                                {
                                    // Enable display help screen when not in console.
                                    my_universe->can_display_help_screen = true;
                                }
                                else if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                                {
                                    is_exit_requested = true;
                                }

                                // process no more than 1 callback for each keypress.
                                break;
                            }
                        }
                    }

                    my_console->process_key_event(sdl_event.key);
                }
                else if (sdl_event.type == SDL_KEYUP)
                {
                    uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                    for (std::size_t i = 0; i < (*current_keyrelease_callback_engine_vector_pointer)->size(); i++)
                    {
                        if ((*current_keyrelease_callback_engine_vector_pointer)->at(i).keycode == scancode)
                        {
                            yli::callback_system::CallbackEngine* callback_engine = (*current_keyrelease_callback_engine_vector_pointer)->at(i).callback_engine;
                            std::shared_ptr<yli::datatypes::AnyValue> any_value = callback_engine->execute();

                            if (any_value != nullptr &&
                                    any_value->type == yli::datatypes::UINT32_T)
                            {
                                if (any_value->uint32_t_value == ENTER_CONSOLE_MAGIC_NUMBER)
                                {
                                    // Do not display help screen when in console.
                                    my_universe->can_display_help_screen = false;
                                }
                                else if (any_value->uint32_t_value == EXIT_CONSOLE_MAGIC_NUMBER)
                                {
                                    // Enable display help screen when not in console.
                                    my_universe->can_display_help_screen = true;
                                }
                                else if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                                {
                                    is_exit_requested = true;
                                }

                                // process no more than 1 callback for each keyrelease.
                                break;
                            }
                        }
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
                    is_exit_requested = true;
                }
            }

            // mouse position.
            double xpos = static_cast<double>(mouse_x);
            double ypos = static_cast<double>(mouse_y);

            // Reset mouse position for next frame
            if (has_mouse_focus)
            {
                yli::input::set_cursor_position(
                        my_universe->get_window(),
                        static_cast<double>(my_universe->get_window_width()) / 2,
                        static_cast<double>(my_universe->get_window_height()) / 2);
            }

            if (my_universe->has_mouse_ever_moved || (abs(xpos) > 0.0001) || (abs(ypos) > 0.0001))
            {
                my_universe->has_mouse_ever_moved = true;

                // Compute new orientation
                my_universe->current_camera_horizontal_angle += my_universe->mouse_speed * GLfloat(my_universe->get_window_width() / 2 - xpos);
                my_universe->current_camera_horizontal_angle = remainder(my_universe->current_camera_horizontal_angle, (2.0f * PI));

                if (my_universe->is_invert_mouse_in_use)
                {
                    // invert mouse.
                    my_universe->current_camera_vertical_angle -= my_universe->mouse_speed * GLfloat(my_universe->get_window_height() / 2 - ypos);
                }
                else
                {
                    // don't invert mouse.
                    my_universe->current_camera_vertical_angle += my_universe->mouse_speed * GLfloat(my_universe->get_window_height() / 2 - ypos);
                }

                my_universe->current_camera_vertical_angle = remainder(my_universe->current_camera_vertical_angle, (2.0f * PI));
            }

            // Direction : Spherical coordinates to Cartesian coordinates conversion
            my_universe->current_camera_direction = glm::vec3(
                    cos(my_universe->current_camera_vertical_angle) * sin(my_universe->current_camera_horizontal_angle),
                    sin(my_universe->current_camera_vertical_angle),
                    cos(my_universe->current_camera_vertical_angle) * cos(my_universe->current_camera_horizontal_angle));

            // Right vector
            my_universe->current_camera_right = glm::vec3(
                    sin(my_universe->current_camera_horizontal_angle - PI/2.0f),
                    0,
                    cos(my_universe->current_camera_horizontal_angle - PI/2.0f));

            // Up vector
            my_universe->current_camera_up = glm::cross(my_universe->current_camera_right, my_universe->current_camera_direction);

            if (!my_console->get_in_console())
            {
                const uint8_t* current_key_states = SDL_GetKeyboardState(nullptr);

                // Check for keypresses and call corresponding callbacks.
                for (std::size_t i = 0; i < action_mode_continuous_keypress_callback_engines->size(); i++)
                {
                    bool is_pressed = false;

                    if (input_method_in_use == yli::input::KEYBOARD)
                    {
                        if (current_key_states[action_mode_continuous_keypress_callback_engines->at(i).keycode] == 1) // 1 = pressed, 0 = not pressed.
                        {
                            is_pressed = true;
                        }
                    }
                    else if (input_method_in_use == yli::input::INPUT_FILE)
                    {
                        // TODO: implement optionally loading keyreleases from a file (do not execute `SDL_GetKeyboardState` in that case).
                        if (false)
                        {
                            is_pressed = true;
                        }
                    }
                    else
                    {
                        std::cerr << "Unsupported input method: " << input_method_in_use << "\n";
                    }

                    if (is_pressed)
                    {
                        yli::callback_system::CallbackEngine* callback_engine = action_mode_continuous_keypress_callback_engines->at(i).callback_engine;
                        std::shared_ptr<yli::datatypes::AnyValue> any_value = callback_engine->execute();

                        if (any_value != nullptr &&
                                any_value->type == yli::datatypes::UINT32_T)
                        {
                            if (any_value->uint32_t_value == ENTER_CONSOLE_MAGIC_NUMBER)
                            {
                                // Do not display help screen when in console.
                                my_universe->can_display_help_screen = false;
                                break;
                            }
                            else if (any_value->uint32_t_value == EXIT_CONSOLE_MAGIC_NUMBER)
                            {
                                // Enable display help screen when not in console.
                                my_universe->can_display_help_screen = true;
                                break;
                            }
                            else if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                            {
                                is_exit_requested = true;
                                break;
                            }
                        }
                    }
                }
            }

            // Gravity etc.
            my_universe->do_physics();

            // Render the `Universe`.
            my_universe->render();

            yli::opengl::disable_depth_test();

            // Draw the console (including current input).
            my_console->draw_console();

            PrintingStruct printing_struct;
            printing_struct.screen_width = my_universe->get_window_width();
            printing_struct.screen_height = my_universe->get_window_height();
            printing_struct.text_size = my_universe->get_text_size();
            printing_struct.font_size = my_universe->get_font_size();
            printing_struct.char_font_texture_file_format = "bmp";

            char angles_and_coordinates_text[256];
            std::snprintf(
                    angles_and_coordinates_text,
                    sizeof(angles_and_coordinates_text),
                    "%.2f,%.2f rad; %.2f,%.2f deg\\n(%.2f,%.2f,%.2f)",
                    my_universe->current_camera_horizontal_angle,
                    my_universe->current_camera_vertical_angle,
                    RADIANS_TO_DEGREES(my_universe->current_camera_horizontal_angle),
                    RADIANS_TO_DEGREES(my_universe->current_camera_vertical_angle),
                    my_universe->current_camera_cartesian_coordinates.x,
                    my_universe->current_camera_cartesian_coordinates.y,
                    my_universe->current_camera_cartesian_coordinates.z);

            char time_text[256];
            std::snprintf(time_text, sizeof(time_text), "%.2f sec", yli::time::get_time());

            char on_text[] = "on";
            char off_text[] = "off";

            char help_text_char[1024];
            std::snprintf(
                    help_text_char,
                    sizeof(help_text_char),
                    "Ajokki 0.0.3\\n"
                    "\\n"
                    "arrow keys\\n"
                    "space jump\\n"
                    "enter duck\\n"
                    "F1 help mode\\n"
                    "`  enter console\\n"
                    "I  invert mouse (%s)\\n"
                    "F  flight mode (%s)\\n"
                    "Ctrl      turbo\\n"
                    "Ctrl+Ctrl extra turbo\\n"
                    "for debugging:\\n"
                    "G  grass texture\\n"
                    "O  orange fur texture\\n"
                    "P  pink geometric tiles texture\\n"
                    "T  terrain species\\n"
                    "A  suzanne species\\n",
                    (my_universe->is_invert_mouse_in_use ? on_text : off_text),
                    (my_universe->is_flight_mode_in_use ? on_text : off_text));

            char spherical_coordinates_text[256];

            if (my_universe->testing_spherical_terrain_in_use)
            {
                std::snprintf(
                        spherical_coordinates_text,
                        sizeof(spherical_coordinates_text),
                        "rho:%.2f theta:%.2f phi:%.2f",
                        my_universe->current_camera_spherical_coordinates.rho,
                        my_universe->current_camera_spherical_coordinates.theta,
                        my_universe->current_camera_spherical_coordinates.phi);
            }

            // print cartesian coordinates on bottom left corner.
            printing_struct.x = 0;
            printing_struct.y = 0;
            printing_struct.text_char = angles_and_coordinates_text;
            printing_struct.horizontal_alignment = "left";
            printing_struct.vertical_alignment = "bottom";
            my_font2D->printText2D(printing_struct);

            if (my_universe->in_help_mode && my_universe->can_display_help_screen)
            {
                // print help text.
                printing_struct.x = 0;
                printing_struct.y = my_universe->get_window_height() - (3 * my_universe->get_text_size());
                printing_struct.text_char = help_text_char;
                printing_struct.horizontal_alignment = "left";
                printing_struct.vertical_alignment = "top";
                my_font2D->printText2D(printing_struct);
            }

            if (my_universe->testing_spherical_terrain_in_use)
            {
                // print spherical coordinates on bottom left corner.
                printing_struct.x = 0;
                printing_struct.y += 2 * my_universe->get_text_size();
                printing_struct.text_char = spherical_coordinates_text;
                printing_struct.horizontal_alignment = "left";
                printing_struct.vertical_alignment = "bottom";
                my_font2D->printText2D(printing_struct);
            }

            // print time data on top left corner.
            printing_struct.x = 0;
            printing_struct.y = static_cast<GLuint>(my_universe->get_window_height());
            printing_struct.text_char = time_text;
            printing_struct.horizontal_alignment = "left";
            printing_struct.vertical_alignment = "top";
            my_font2D->printText2D(printing_struct);

            if (ms_frame_text_ready)
            {
                // print frame rate data on top right corner.
                printing_struct.x = my_universe->get_window_width();
                printing_struct.y = my_universe->get_window_height();
                printing_struct.text_char = ms_frame_text;
                printing_struct.horizontal_alignment = "right";
                printing_struct.vertical_alignment = "top";
                my_font2D->printText2D(printing_struct);
            }

            yli::opengl::enable_depth_test();

            // Swap buffers.
            SDL_GL_SwapWindow(my_universe->get_window());

            my_universe->finalize_delta_time_loop();
        }
    }

    // do cleanup.
    cleanup_callback_engine->execute();

    // Delete all keyrelease callback engines.
    for (std::size_t i = 0; i < action_mode_keyrelease_callback_engines->size(); i++)
    {
        delete action_mode_keyrelease_callback_engines->at(i).callback_engine;
    }
    delete action_mode_keyrelease_callback_engines;

    // Delete all keypress callback engines.
    for (std::size_t i = 0; i < action_mode_keypress_callback_engines->size(); i++)
    {
        delete action_mode_keypress_callback_engines->at(i).callback_engine;
    }
    delete action_mode_keypress_callback_engines;

    delete cleanup_callback_engine;
    delete my_console;

    return 0;
}
