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
#include "ajokki_keyboard_callbacks.hpp"
#include "ajokki_debug.hpp"
#include "ajokki_console.hpp"
#include "ajokki_movement.hpp"
#include "ajokki_location_and_orientation.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/console/console_command_callback.hpp"
#include "code/ylikuutio/console/console_struct.hpp"
#include "code/ylikuutio/console/console_callback_object.hpp"
#include "code/ylikuutio/ontology/vboindexer.hpp"
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
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
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

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <cstdio>        // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <stdint.h>      // uint32_t etc.
#include <unordered_map> // std::unordered_map

// model file format: obj/bmp/...
std::string g_model_file_format = "bmp";
std::string ASCII_grid_model_file_format = "ASCII_grid";

// model filename.
// std::string g_model_filename = "cube.obj";
// std::string g_model_filename = "oma_icosphere.obj";
// std::string g_model_filename = "kirjainkuutio.obj";
// std::string g_model_filename = "noise1024x1024.bmp";
std::string g_model_filename = "noise256x256.bmp";
// std::string g_model_filename = "noise128x128.bmp";

// std::string ASCII_grid_model_filename = "N5424G.asc"; // Joensuu center & western.
std::string ASCII_grid_model_filename = "L4133D.asc"; // Helsinki eastern downtown.

// texture file format: bmp/...
std::string g_texture_file_format = "bmp";

// color channel to use for height data.
// std::string g_height_data_color_channel = "red";
// std::string g_height_data_color_channel = "green";
// std::string g_height_data_color_channel = "blue";
std::string g_height_data_color_channel = "mean"; // "all" is equivalent to "mean".

// texture filename.
// std::string_g_texture_filename = "kuutio-uv-numerot.bmp";
// std::string g_texture_filename = "punamusta.bmp";
std::string g_texture_filename = "GrassGreenTexture0002.bmp";

// font texture file format: bmp/...
std::string g_font_texture_file_format = "bmp";

// font texture filename.
// std::string g_font_texture_filename = "Holstein.DDS";
std::string g_font_texture_filename = "Holstein.bmp";

std::string g_font_file_format = "svg";
std::string g_font_filename = "kongtext.svg";

int main(void)
{
    // Create the world, store it in `my_universe`.
    ontology::Entity* my_universe_entity = ontology::EntityFactory::create_Universe();
    ontology::Universe* my_universe = dynamic_cast<ontology::Universe*>(my_universe_entity);

    if (my_universe == nullptr)
    {
        std::cerr << "Failed to create Universe.\n";
        return -1;
    }

    // Create the setting master, store it in `my_setting_master`.
    config::SettingMaster* my_setting_master = new config::SettingMaster(my_universe);

    float earth_radius = 6371.0f; // in kilometres

    SettingStruct world_radius_setting_struct(std::make_shared<datatypes::AnyValue>(earth_radius));
    world_radius_setting_struct.name = "world_radius";
    world_radius_setting_struct.setting_master_pointer = my_setting_master;
    world_radius_setting_struct.activate_callback = &config::SettingMaster::activate_world_radius; // world may be a planet or a moon.
    world_radius_setting_struct.should_ylikuutio_call_activate_callback_now = true;
    new config::Setting(world_radius_setting_struct);

    callback_system::CallbackEngine* cleanup_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* cleanup_callback_object = new callback_system::CallbackObject(nullptr, cleanup_callback_engine);

    // Initialise GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW.\n";
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context.
    my_universe->set_window(
            glfwCreateWindow(
                static_cast<GLuint>(my_universe->get_window_width()),
                static_cast<GLuint>(my_universe->get_window_height()),
                "Ajokki v. 0.0.1, powered by Ylikuutio v. 0.0.1",
                nullptr,
                nullptr));
    cleanup_callback_object->set_new_callback(&ajokki::glfwTerminate_cleanup);

    if (my_universe->get_window() == nullptr)
    {
        std::cerr << "Failed to open GLFW window.\n";
        cleanup_callback_engine->execute();
        return -1;
    }
    glfwMakeContextCurrent(my_universe->get_window());
    glfwSetInputMode(my_universe->get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW.
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW.\n";
        cleanup_callback_engine->execute();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below.
    glfwSetInputMode(my_universe->get_window(), GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPos(my_universe->get_window(), (static_cast<GLuint>(my_universe->get_window_width()) / 2), (static_cast<GLuint>(my_universe->get_window_height()) / 2));

    // Enable depth test.
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one.
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera.
    glEnable(GL_CULL_FACE);

    ajokki::set_background_colors(my_setting_master);
    ajokki::set_movement(my_setting_master);
    ajokki::set_location_and_orientation(my_setting_master);
    ajokki::set_debug_variables(my_setting_master);
    ajokki::set_console(my_setting_master);

    ontology::Entity* my_scene_entity = ontology::EntityFactory::create_Scene(my_universe, 0.9f);
    ontology::Scene* my_scene = dynamic_cast<ontology::Scene*>(my_scene_entity);

    if (my_scene == nullptr)
    {
        std::cerr << "Failed to create Scene.\n";
        return -1;
    }

    // Create the shader, store it in `my_shader`.
    ShaderStruct shader_struct;
    shader_struct.parent_pointer = my_scene;
    shader_struct.vertex_shader = "StandardShading.vertexshader";
    shader_struct.fragment_shader = "StandardShading.fragmentshader";

    ontology::Entity* my_shader_entity = ontology::EntityFactory::create_Shader(shader_struct);
    ontology::Shader* my_shader = dynamic_cast<ontology::Shader*>(my_shader_entity);

    if (my_shader == nullptr)
    {
        std::cerr << "Failed to create Shader.\n";
        return -1;
    }

    // Create the material, store it in `grass_material`.
    MaterialStruct grass_material_struct;
    grass_material_struct.parent_pointer = my_shader;
    grass_material_struct.texture_file_format = g_texture_file_format;
    grass_material_struct.texture_filename = g_texture_filename;

    ontology::Entity* grass_material_entity = ontology::EntityFactory::create_Material(grass_material_struct);
    ontology::Material* grass_material = dynamic_cast<ontology::Material*>(grass_material_entity);

    if (grass_material == nullptr)
    {
        std::cerr << "Failed to create grass Material.\n";
        return -1;
    }

    grass_material->set_name("grass_material");

    // Create the material, store it in `uvmap_material`.
    MaterialStruct uvmap_material_struct;
    uvmap_material_struct.parent_pointer = my_shader;
    uvmap_material_struct.texture_file_format = "dds";
    uvmap_material_struct.texture_filename = "uvmap.DDS";

    ontology::Entity* uvmap_material_entity = ontology::EntityFactory::create_Material(uvmap_material_struct);
    ontology::Material* uvmap_material = dynamic_cast<ontology::Material*>(uvmap_material_entity);

    if (uvmap_material == nullptr)
    {
        std::cerr << "Failed to create uvmap Material.\n";
        return -1;
    }

    uvmap_material->set_name("uvmap_material");

    // Create the material, store it in `pink_geometric_tiles_material`.
    MaterialStruct pink_geometric_tiles_material_struct;
    pink_geometric_tiles_material_struct.parent_pointer = my_shader;
    pink_geometric_tiles_material_struct.texture_file_format = "bmp";
    pink_geometric_tiles_material_struct.texture_filename = "pavers1b2.bmp";

    ontology::Entity* pink_geometric_tiles_material_entity = ontology::EntityFactory::create_Material(pink_geometric_tiles_material_struct);
    ontology::Material* pink_geometric_tiles_material = dynamic_cast<ontology::Material*>(pink_geometric_tiles_material_entity);

    if (pink_geometric_tiles_material == nullptr)
    {
        std::cerr << "Failed to create pink geometric tiles Material.\n";
        return -1;
    }

    ontology::Species* terrain_species;

    if (my_universe->testing_spherical_world_in_use)
    {
        // Create the species, store it in `terrain_species`.
        SpeciesStruct(SRTM_terrain_species_struct);
        SRTM_terrain_species_struct.parent_pointer = grass_material;
        SRTM_terrain_species_struct.model_file_format = "SRTM";
        // SRTM_terrain_species_struct.model_filename = "/media/laatikko_4TB/satelliittikuvat/srtm/version3/data/";
        SRTM_terrain_species_struct.model_filename = "./"; // for testing
        SRTM_terrain_species_struct.color_channel = g_height_data_color_channel;
        SRTM_terrain_species_struct.light_position = glm::vec3(0, 100000, 100000);
        SRTM_terrain_species_struct.is_world = true;
        SRTM_terrain_species_struct.x_step = 1;
        SRTM_terrain_species_struct.z_step = 1;
        SRTM_terrain_species_struct.world_radius = earth_radius;
        SRTM_terrain_species_struct.divisor = 1000.0f;
        terrain_species = new ontology::Species(SRTM_terrain_species_struct);

        terrain_species->set_name("altiplano_species");

        my_universe->turbo_factor = 100.0f;
        my_universe->twin_turbo_factor = 50000.0f;
    }
    else
    {
        // Create the species, store it in `terrain_species`.
        /*
        SpeciesStruct bmp_terrain_species_struct;
        bmp_terrain_species_struct.parent_pointer = grass_material;
        bmp_terrain_species_struct.model_file_format = g_model_file_format;
        bmp_terrain_species_struct.model_filename = g_model_filename;
        bmp_terrain_species_struct.color_channel = g_height_data_color_channel;
        bmp_terrain_species_struct.light_position = glm::vec3(0, 100000, 100000);
        bmp_terrain_species_struct.is_world = true;
        terrain_species = new ontology::Species(bmp_terrain_species_struct);
        */

        SpeciesStruct ASCII_grid_terrain_species_struct;
        ASCII_grid_terrain_species_struct.parent_pointer = grass_material;
        ASCII_grid_terrain_species_struct.model_file_format = ASCII_grid_model_file_format;
        ASCII_grid_terrain_species_struct.model_filename = ASCII_grid_model_filename;
        ASCII_grid_terrain_species_struct.light_position = glm::vec3(0, 100000, 100000);
        ASCII_grid_terrain_species_struct.is_world = true;
        ASCII_grid_terrain_species_struct.x_step = 4;
        ASCII_grid_terrain_species_struct.z_step = 4;
        terrain_species = new ontology::Species(ASCII_grid_terrain_species_struct);

        terrain_species->set_name("Helsinki_species");

        my_universe->is_flight_mode_in_use = true;

        my_universe->turbo_factor = 5.0f;
        my_universe->twin_turbo_factor = 100.0f;
    }

    // Create terrain1, store it in `terrain1`.
    ObjectStruct terrain_object_struct1;
    terrain_object_struct1.species_parent_pointer = terrain_species;
    terrain_object_struct1.coordinate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    terrain_object_struct1.rotate_angle = 0.0f;
    terrain_object_struct1.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    terrain_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    ontology::EntityFactory::create_Object(terrain_object_struct1);

    // Create the species, store it in `snow_cottage_species`.
    SpeciesStruct snow_cottage_species_struct;
    snow_cottage_species_struct.parent_pointer = pink_geometric_tiles_material;
    snow_cottage_species_struct.model_file_format = "obj";
    snow_cottage_species_struct.model_filename = "snow_cottage_triangulated.obj";
    snow_cottage_species_struct.light_position = glm::vec3(0, 100000, 100000);

    ontology::Entity* snow_cottage_species_entity = ontology::EntityFactory::create_Species(snow_cottage_species_struct);
    ontology::Species* snow_cottage_species = dynamic_cast<ontology::Species*>(snow_cottage_species_entity);

    if (snow_cottage_species == nullptr)
    {
        std::cerr << "Failed to create snow cottage Species.\n";
        return -1;
    }

    snow_cottage_species->set_name("snow_cottage");

    // Create snow cottage, store it in `snow_cottage1`.
    ObjectStruct snow_cottage_object_struct1;
    snow_cottage_object_struct1.species_parent_pointer = snow_cottage_species;
    snow_cottage_object_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    snow_cottage_object_struct1.coordinate_vector = glm::vec3(121.50f, 126.50f, 63.70f);
    snow_cottage_object_struct1.rotate_angle = 0.10f;
    snow_cottage_object_struct1.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    snow_cottage_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);

    /*
    ontology::Entity* snow_cottage_object_entity = ontology::EntityFactory::create_Object(snow_cottage_object_struct1);
    ontology::Object* snow_cottage_object = dynamic_cast<ontology::Object*>(snow_cottage_object_entity);

    if (snow_cottage_object == nullptr)
    {
        std::cerr << "Failed to create snow cottage Object.\n";
        return -1;
    }
    */

    SpeciesStruct suzanne_species_struct;
    suzanne_species_struct.parent_pointer = uvmap_material;
    suzanne_species_struct.model_file_format = "obj";
    suzanne_species_struct.model_filename = "suzanne.obj";
    suzanne_species_struct.light_position = glm::vec3(0, 100000, 100000);

    ontology::Entity* suzanne_species_entity = ontology::EntityFactory::create_Species(suzanne_species_struct);
    ontology::Species* suzanne_species = dynamic_cast<ontology::Species*>(suzanne_species_entity);

    if (suzanne_species == nullptr)
    {
        std::cerr << "Failed to create suzanne Species.\n";
        return -1;
    }

    suzanne_species->set_name("suzanne_species");

    // Create suzanne1, store it in `suzanne1`.
    ObjectStruct suzanne_object_struct1;
    suzanne_object_struct1.species_parent_pointer = suzanne_species;
    suzanne_object_struct1.coordinate_vector = glm::vec3(82.50f, 119.00f, 95.50f);
    suzanne_object_struct1.rotate_angle = 0.10f;
    suzanne_object_struct1.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    suzanne_object_struct1.translate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    ontology::EntityFactory::create_Object(suzanne_object_struct1);

    ObjectStruct suzanne_object_struct2;
    suzanne_object_struct2.species_parent_pointer = suzanne_species;
    suzanne_object_struct2.coordinate_vector = glm::vec3(112.90f, 113.90f, 75.50f);
    suzanne_object_struct2.rotate_angle = 0.20f;
    suzanne_object_struct2.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    suzanne_object_struct2.translate_vector = glm::vec3(0.0f, 1.0f, 0.0f);
    ontology::Object* suzanne2 = new ontology::Object(suzanne_object_struct2);
    suzanne2->set_name("suzanne2");

    ObjectStruct suzanne_object_struct3;
    suzanne_object_struct3.species_parent_pointer = suzanne_species;
    suzanne_object_struct3.coordinate_vector = glm::vec3(126.90f, 162.90f, 103.00f);
    suzanne_object_struct3.rotate_angle = 0.05f;
    suzanne_object_struct3.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    suzanne_object_struct3.translate_vector = glm::vec3(0.0f, 0.0f, 1.0f);
    ontology::EntityFactory::create_Object(suzanne_object_struct3);

    ObjectStruct suzanne_object_struct4;
    suzanne_object_struct4.species_parent_pointer = suzanne_species;
    suzanne_object_struct4.coordinate_vector = glm::vec3(96.00f, 130.00f, 109.00f);
    suzanne_object_struct4.rotate_angle = 0.15f;
    suzanne_object_struct4.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    suzanne_object_struct4.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    ontology::EntityFactory::create_Object(suzanne_object_struct4);

    ObjectStruct suzanne_object_struct5;
    suzanne_object_struct5.species_parent_pointer = suzanne_species;
    suzanne_object_struct5.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
    suzanne_object_struct5.coordinate_vector = glm::vec3(103.00f, 140.00f, 109.00f);
    suzanne_object_struct5.rotate_angle = 0.03f;
    suzanne_object_struct5.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    suzanne_object_struct5.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    ontology::EntityFactory::create_Object(suzanne_object_struct5);

    VectorFontStruct kongtext_vector_font_struct;
    kongtext_vector_font_struct.parent_pointer = grass_material;
    kongtext_vector_font_struct.font_file_format = g_font_file_format;
    kongtext_vector_font_struct.font_filename = g_font_filename;

    ontology::Entity* kongtext_font_entity = ontology::EntityFactory::create_VectorFont(kongtext_vector_font_struct);
    ontology::VectorFont* kongtext_font = dynamic_cast<ontology::VectorFont*>(kongtext_font_entity);

    if (kongtext_font == nullptr)
    {
        std::cerr << "Failed to create kongtext VectorFont.\n";
        return -1;
    }

    Text3DStruct text3D_struct;
    text3D_struct.parent_pointer = kongtext_font;
    text3D_struct.text_string = "Hello world &#x26; its habitants!";
    text3D_struct.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    text3D_struct.coordinate_vector = glm::vec3(100.00f, 100.00f, 100.00f);
    text3D_struct.rotate_angle = 0.0f;
    text3D_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    text3D_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    ontology::EntityFactory::create_Text3D(text3D_struct);

    // keypress callbacks.
    std::vector<KeyAndCallbackStruct>* action_mode_keypress_callback_engines = new std::vector<KeyAndCallbackStruct>();

    // This vector points to current keypress callback engines vector.
    std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer;
    current_keypress_callback_engine_vector_pointer = &action_mode_keypress_callback_engines;

    // keyrelease callbacks.
    std::vector<KeyAndCallbackStruct>* action_mode_keyrelease_callback_engines = new std::vector<KeyAndCallbackStruct>();

    // This vector points to current keyrelease callback engines vector.
    std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer;
    current_keyrelease_callback_engine_vector_pointer = &action_mode_keyrelease_callback_engines;

    // Initialize our little text library with the Holstein font
    const char* char_g_font_texture_filename = g_font_texture_filename.c_str();
    const char* char_g_font_texture_file_format = g_font_texture_file_format.c_str();

    ontology::Entity* my_font2D_entity = ontology::EntityFactory::create_Font2D(my_universe, my_universe->get_window_width(), my_universe->get_window_height(), char_g_font_texture_filename, char_g_font_texture_file_format);
    ontology::Font2D* my_font2D = dynamic_cast<ontology::Font2D*>(my_font2D_entity);

    if (my_font2D == nullptr)
    {
        std::cerr << "Failed to create Font2D.\n";
        return -1;
    }

    std::unordered_map<std::string, ConsoleCommandCallback> command_callback_map;

    ConsoleStruct console_struct;
    console_struct.current_keypress_callback_engine_vector_pointer_pointer = current_keypress_callback_engine_vector_pointer;
    console_struct.current_keyrelease_callback_engine_vector_pointer_pointer = current_keyrelease_callback_engine_vector_pointer;
    console_struct.command_callback_map_pointer = &command_callback_map;
    console_struct.universe_pointer = my_universe;
    console_struct.font2D_pointer = my_font2D;

    console::Console* my_console = new console::Console(console_struct); // create a console.

    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` release: enable enter console.
    callback_system::CallbackEngine* enable_enter_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_enter_console, enable_enter_console_callback_engine, my_console);

    // Callback code for left Control release: release first turbo.
    callback_system::CallbackEngine* release_first_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* release_first_turbo_callback_object = new callback_system::CallbackObject(&ajokki::release_first_turbo, release_first_turbo_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, release_first_turbo_callback_object);

    // Callback code for right Control release: release second turbo.
    callback_system::CallbackEngine* release_second_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* release_second_turbo_callback_object = new callback_system::CallbackObject(&ajokki::release_second_turbo, release_second_turbo_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, release_second_turbo_callback_object);

    // Callback code for I release: enable_toggle invert mouse.
    callback_system::CallbackEngine* enable_toggle_invert_mouse_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* enable_toggle_invert_mouse_callback_object = new callback_system::CallbackObject(&ajokki::enable_toggle_invert_mouse, enable_toggle_invert_mouse_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, enable_toggle_invert_mouse_callback_object);

    // Callback code for F release: enable_toggle flight mode.
    callback_system::CallbackEngine* enable_toggle_flight_mode_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* enable_toggle_flight_mode_callback_object = new callback_system::CallbackObject(&ajokki::enable_toggle_flight_mode, enable_toggle_flight_mode_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, enable_toggle_flight_mode_callback_object);

    // Callback code for F1 release: enable toggle help mode.
    callback_system::CallbackEngine* enable_toggle_help_mode_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* enable_toggle_help_mode_callback_object = new callback_system::CallbackObject(&ajokki::enable_toggle_help_mode, enable_toggle_help_mode_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, enable_toggle_help_mode_callback_object);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` (tilde key above Tab, usually used for console).
    callback_system::CallbackEngine* enter_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enter_console, enter_console_callback_engine, my_console);

    // Callback code for esc: exit program.
    callback_system::CallbackEngine* exit_program_callback_engine = new callback_system::CallbackEngine();
    new callback_system::CallbackObject(&ajokki::exit_program, exit_program_callback_engine);

    // Callback code for left Control: first turbo.
    callback_system::CallbackEngine* first_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* first_turbo_callback_object = new callback_system::CallbackObject(&ajokki::first_turbo, first_turbo_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, first_turbo_callback_object);

    // Callback code for right Control: second turbo.
    callback_system::CallbackEngine* second_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* second_turbo_callback_object = new callback_system::CallbackObject(&ajokki::second_turbo, second_turbo_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, second_turbo_callback_object);

    // Callback code for key up: move forward.
    callback_system::CallbackEngine* move_forward_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* move_forward_callback_object = new callback_system::CallbackObject(
            &ajokki::move_forward, move_forward_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, move_forward_callback_object);

    // Callback code for key down: move backward.
    callback_system::CallbackEngine* move_backward_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* move_backward_callback_object = new callback_system::CallbackObject(
            &ajokki::move_backward, move_backward_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, move_backward_callback_object);

    // Callback code for key left: strafe left.
    callback_system::CallbackEngine* strafe_left_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* strafe_left_callback_object = new callback_system::CallbackObject(
            &ajokki::strafe_left, strafe_left_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, strafe_left_callback_object);

    // Callback code for key right: strafe right.
    callback_system::CallbackEngine* strafe_right_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* strafe_right_callback_object = new callback_system::CallbackObject(
            &ajokki::strafe_right, strafe_right_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, strafe_right_callback_object);

    // Callback code for space: ascent.
    callback_system::CallbackEngine* ascent_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* ascent_callback_object = new callback_system::CallbackObject(
            &ajokki::ascent, ascent_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, ascent_callback_object);

    // Callback code for enter: descent.
    callback_system::CallbackEngine* descent_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* descent_callback_object = new callback_system::CallbackObject(
            &ajokki::descent, descent_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, descent_callback_object);

    // Callback code for I: toggle invert mouse.
    callback_system::CallbackEngine* toggle_invert_mouse_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* toggle_invert_mouse_callback_object = new callback_system::CallbackObject(&ajokki::toggle_invert_mouse, toggle_invert_mouse_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, toggle_invert_mouse_callback_object);

    // Callback code for F: toggle flight mode.
    callback_system::CallbackEngine* toggle_flight_mode_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* toggle_flight_mode_callback_object = new callback_system::CallbackObject(&ajokki::toggle_flight_mode, toggle_flight_mode_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, toggle_flight_mode_callback_object);

    // Callback code for F1: toggle help mode.
    callback_system::CallbackEngine* toggle_help_mode_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* toggle_help_mode_callback_object = new callback_system::CallbackObject(&ajokki::toggle_help_mode, toggle_help_mode_callback_engine);
    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, toggle_help_mode_callback_object);

    // Callback code for D: delete Suzanne species.
    bool does_suzanne_species_exist = true;
    callback_system::CallbackEngine* delete_suzanne_species_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* delete_suzanne_species_callback_object = new callback_system::CallbackObject(
            &ajokki::delete_suzanne_species, delete_suzanne_species_callback_engine);
    new callback_system::CallbackParameter("suzanne_species", std::make_shared<datatypes::AnyValue>(suzanne_species), false, delete_suzanne_species_callback_object);
    new callback_system::CallbackParameter("does_suzanne_species_exist", std::make_shared<datatypes::AnyValue>(&does_suzanne_species_exist), false, delete_suzanne_species_callback_object);

    // Callback code for G: switch to grass material.
    bool does_suzanne_species_have_uvmap_texture = true;
    bool does_suzanne_species_have_grass_texture = false;
    callback_system::CallbackEngine* switch_to_grass_material_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* switch_to_grass_material_callback_object = new callback_system::CallbackObject(
            &ajokki::switch_to_new_material, switch_to_grass_material_callback_engine);
    new callback_system::CallbackParameter("suzanne_species", std::make_shared<datatypes::AnyValue>(suzanne_species), false, switch_to_grass_material_callback_object);
    new callback_system::CallbackParameter("new_material", std::make_shared<datatypes::AnyValue>(grass_material), false, switch_to_grass_material_callback_object);
    new callback_system::CallbackParameter("does_suzanne_species_exist", std::make_shared<datatypes::AnyValue>(&does_suzanne_species_exist), false, switch_to_grass_material_callback_object);
    new callback_system::CallbackParameter(
            "does_suzanne_species_have_old_texture",
            std::make_shared<datatypes::AnyValue>(&does_suzanne_species_have_uvmap_texture),
            false,
            switch_to_grass_material_callback_object);
    new callback_system::CallbackParameter(
            "does_suzanne_species_have_new_texture",
            std::make_shared<datatypes::AnyValue>(&does_suzanne_species_have_grass_texture),
            false,
            switch_to_grass_material_callback_object);

    // Callback code for U: switch back to uvmap material.
    callback_system::CallbackEngine* switch_to_uvmap_material_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* switch_to_uvmap_material_callback_object = new callback_system::CallbackObject(
            &ajokki::switch_to_new_material, switch_to_uvmap_material_callback_engine);
    new callback_system::CallbackParameter("suzanne_species", std::make_shared<datatypes::AnyValue>(suzanne_species), false, switch_to_uvmap_material_callback_object);
    new callback_system::CallbackParameter("new_material", std::make_shared<datatypes::AnyValue>(uvmap_material), false, switch_to_uvmap_material_callback_object);
    new callback_system::CallbackParameter("does_suzanne_species_exist", std::make_shared<datatypes::AnyValue>(&does_suzanne_species_exist), false, switch_to_uvmap_material_callback_object);
    new callback_system::CallbackParameter(
            "does_suzanne_species_have_old_texture",
            std::make_shared<datatypes::AnyValue>(&does_suzanne_species_have_grass_texture),
            false,
            switch_to_uvmap_material_callback_object);
    new callback_system::CallbackParameter(
            "does_suzanne_species_have_new_texture",
            std::make_shared<datatypes::AnyValue>(&does_suzanne_species_have_uvmap_texture),
            false,
            switch_to_uvmap_material_callback_object);

    // Callback code for T: transform `suzanne2` into terrain.
    bool has_suzanne_2_transformed_into_monkey = true;
    bool has_suzanne_2_transformed_into_terrain = false;
    callback_system::CallbackEngine* transform_into_terrain_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* transform_into_terrain_callback_object = new callback_system::CallbackObject(
            &ajokki::transform_into_new_species, transform_into_terrain_callback_engine);
    new callback_system::CallbackParameter("suzanne2", std::make_shared<datatypes::AnyValue>(suzanne2), false, transform_into_terrain_callback_object); // suzanne2!!!
    new callback_system::CallbackParameter("terrain_species", std::make_shared<datatypes::AnyValue>(terrain_species), false, transform_into_terrain_callback_object);
    new callback_system::CallbackParameter("does_suzanne_species_exist", std::make_shared<datatypes::AnyValue>(&does_suzanne_species_exist), false, transform_into_terrain_callback_object);
    new callback_system::CallbackParameter(
            "has_suzanne_2_transformed_into_monkey",
            std::make_shared<datatypes::AnyValue>(&has_suzanne_2_transformed_into_monkey),
            false,
            transform_into_terrain_callback_object);
    new callback_system::CallbackParameter(
            "has_suzanne_2_transformed_into_terrain",
            std::make_shared<datatypes::AnyValue>(&has_suzanne_2_transformed_into_terrain),
            false,
            transform_into_terrain_callback_object);

    // Callback code for A: transform `suzanne2` back into monkey.
    callback_system::CallbackEngine* transform_into_monkey_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* transform_into_monkey_callback_object = new callback_system::CallbackObject(
            &ajokki::transform_into_new_species, transform_into_monkey_callback_engine);
    new callback_system::CallbackParameter("suzanne2", std::make_shared<datatypes::AnyValue>(suzanne2), false, transform_into_monkey_callback_object); // suzanne2!!!
    new callback_system::CallbackParameter("monkey_species", std::make_shared<datatypes::AnyValue>(suzanne_species), false, transform_into_monkey_callback_object);
    new callback_system::CallbackParameter("does_suzanne_species_exist", std::make_shared<datatypes::AnyValue>(&does_suzanne_species_exist), false, transform_into_monkey_callback_object);
    new callback_system::CallbackParameter(
            "has_suzanne_2_transformed_into_terrain",
            std::make_shared<datatypes::AnyValue>(&has_suzanne_2_transformed_into_terrain),
            false,
            transform_into_monkey_callback_object);
    new callback_system::CallbackParameter(
            "has_suzanne_2_transformed_into_monkey",
            std::make_shared<datatypes::AnyValue>(&has_suzanne_2_transformed_into_monkey),
            false,
            transform_into_monkey_callback_object);

    /*********************************************************************\
     *  Callback engines for console keyreleases begin here.             *
    \*********************************************************************/

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` release: enable exit console.
    callback_system::CallbackEngine* enable_exit_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_exit_console, enable_exit_console_callback_engine, my_console);

    // Callback code for left Control release.
    callback_system::CallbackEngine* release_left_control_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_left_control_in_console, release_left_control_in_console_callback_engine, my_console);

    // Callback code for right Control release.
    callback_system::CallbackEngine* release_right_control_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_right_control_in_console, release_right_control_in_console_callback_engine, my_console);

    // Callback code for left Alt release.
    callback_system::CallbackEngine* release_left_alt_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_left_alt_in_console, release_left_alt_in_console_callback_engine, my_console);

    // Callback code for right Alt release.
    callback_system::CallbackEngine* release_right_alt_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_right_alt_in_console, release_right_alt_in_console_callback_engine, my_console);

    // Callback code for left Shift release.
    callback_system::CallbackEngine* release_left_shift_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_left_shift_in_console, release_left_shift_in_console_callback_engine, my_console);

    // Callback code for right Shift release.
    callback_system::CallbackEngine* release_right_shift_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::release_right_shift_in_console, release_right_shift_in_console_callback_engine, my_console);

    // Callback code for key up release: enable move to previous input.
    callback_system::CallbackEngine* enable_move_to_previous_input_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_move_to_previous_input, enable_move_to_previous_input_callback_engine, my_console);

    // Callback code for key down release: enable move to next input.
    callback_system::CallbackEngine* enable_move_to_next_input_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_move_to_next_input, enable_move_to_next_input_callback_engine, my_console);

    // Callback code for backspace release: enable backspace.
    callback_system::CallbackEngine* enable_backspace_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_backspace, enable_backspace_callback_engine, my_console);

    // Callback code for enter release: enable Enter key.
    callback_system::CallbackEngine* enable_enter_key_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_enter_key, enable_enter_key_callback_engine, my_console);

    // Callback code for C release: enable Control-C.
    callback_system::CallbackEngine* enable_ctrl_c_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_ctrl_c, enable_ctrl_c_callback_engine, my_console);

    // Callback code for PgUp release: enable PgUp.
    callback_system::CallbackEngine* enable_page_up_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_page_up, enable_page_up_callback_engine, my_console);

    // Callback code for PgDn release: enable PgDn.
    callback_system::CallbackEngine* enable_page_down_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_page_down, enable_page_down_callback_engine, my_console);

    // Callback code for Home release: enable Home.
    callback_system::CallbackEngine* enable_home_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_home, enable_home_callback_engine, my_console);

    // Callback code for End release: enable End.
    callback_system::CallbackEngine* enable_end_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enable_end, enable_end_callback_engine, my_console);

    /*********************************************************************\
     *  Callback engines for console keypresses begin here.              *
    \*********************************************************************/

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` (tilde key above Tab, usually used for console).
    callback_system::CallbackEngine* exit_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::exit_console, exit_console_callback_engine, my_console);

    // Callback code for left Control press.
    callback_system::CallbackEngine* press_left_control_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_left_control_in_console, press_left_control_in_console_callback_engine, my_console);

    // Callback code for right Control press.
    callback_system::CallbackEngine* press_right_control_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_right_control_in_console, press_right_control_in_console_callback_engine, my_console);

    // Callback code for left Alt press.
    callback_system::CallbackEngine* press_left_alt_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_left_alt_in_console, press_left_alt_in_console_callback_engine, my_console);

    // Callback code for right Alt press.
    callback_system::CallbackEngine* press_right_alt_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_right_alt_in_console, press_right_alt_in_console_callback_engine, my_console);

    // Callback code for left Shift press.
    callback_system::CallbackEngine* press_left_shift_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_left_shift_in_console, press_left_shift_in_console_callback_engine, my_console);

    // Callback code for right Shift press.
    callback_system::CallbackEngine* press_right_shift_in_console_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::press_right_shift_in_console, press_right_shift_in_console_callback_engine, my_console);

    // Callback code for key up: move to previous input.
    callback_system::CallbackEngine* move_to_previous_input_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::move_to_previous_input, move_to_previous_input_callback_engine, my_console);

    // Callback code for key down: move to next input.
    callback_system::CallbackEngine* move_to_next_input_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::move_to_next_input, move_to_next_input_callback_engine, my_console);

    // Callback code for backspace: delete character left of cursor from current input in console.
    callback_system::CallbackEngine* backspace_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::backspace, backspace_callback_engine, my_console);

    // Callback code for Enter key.
    callback_system::CallbackEngine* enter_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::enter_key, enter_callback_engine, my_console);

    // Callback code for C: Control-C.
    callback_system::CallbackEngine* ctrl_c_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::ctrl_c, ctrl_c_callback_engine, my_console);

    // Callback code for PgUp.
    callback_system::CallbackEngine* page_up_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::page_up, page_up_callback_engine, my_console);

    // Callback code for PgDn.
    callback_system::CallbackEngine* page_down_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::page_down, page_down_callback_engine, my_console);

    // Callback code for Home.
    callback_system::CallbackEngine* home_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::home, home_callback_engine, my_console);

    // Callback code for End.
    callback_system::CallbackEngine* end_callback_engine = new callback_system::CallbackEngine();
    new console::ConsoleCallbackObject(&console::Console::end, end_callback_engine, my_console);

    new callback_system::CallbackParameter("", std::make_shared<datatypes::AnyValue>(my_universe), false, cleanup_callback_object);
    new callback_system::CallbackParameter("font2D_pointer", std::make_shared<datatypes::AnyValue>(my_font2D), false, cleanup_callback_object);
    cleanup_callback_object->set_new_callback(&ajokki::full_cleanup);

    // Keyrelease callbacks for action mode.
    // Key releases are checked in the order of this struct.
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, enable_enter_console_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, release_first_turbo_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, release_second_turbo_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_I, enable_toggle_invert_mouse_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_F, enable_toggle_flight_mode_callback_engine });
    action_mode_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_F1, enable_toggle_help_mode_callback_engine });

    // Keypress callbacks for action mode.
    // Keypresses are checked in the order of this struct.
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, enter_console_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_ESCAPE, exit_program_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, first_turbo_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, second_turbo_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_UP, move_forward_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_DOWN, move_backward_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT, strafe_left_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT, strafe_right_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_SPACE, ascent_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_ENTER, descent_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_I, toggle_invert_mouse_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_F, toggle_flight_mode_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_F1, toggle_help_mode_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_D, delete_suzanne_species_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_G, switch_to_grass_material_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_U, switch_to_uvmap_material_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_T, transform_into_terrain_callback_engine });
    action_mode_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_A, transform_into_monkey_callback_engine });

    // Keyrelease callbacks for console.
    // Key releases are checked in the order of this struct.
    std::vector<KeyAndCallbackStruct>* console_keyrelease_callback_engines = new std::vector<KeyAndCallbackStruct>();
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, enable_exit_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, release_left_control_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, release_right_control_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_ALT, release_left_alt_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_ALT, release_right_alt_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_SHIFT, release_left_shift_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_SHIFT, release_right_shift_in_console_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_UP, enable_move_to_previous_input_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_DOWN, enable_move_to_next_input_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_BACKSPACE, enable_backspace_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_ENTER, enable_enter_key_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_C, enable_ctrl_c_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_PAGE_UP, enable_page_up_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_PAGE_DOWN, enable_page_down_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_HOME, enable_home_callback_engine });
    console_keyrelease_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_END, enable_end_callback_engine });
    my_console->set_my_keyrelease_callback_engine_vector_pointer(console_keyrelease_callback_engines);

    // Keypress callbacks for console.
    // Keypresses are checked in the order of this struct.
    std::vector<KeyAndCallbackStruct>* console_keypress_callback_engines = new std::vector<KeyAndCallbackStruct>();
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, exit_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, press_left_control_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, press_right_control_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_ALT, press_left_alt_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_ALT, press_right_alt_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_SHIFT, press_left_shift_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_SHIFT, press_right_shift_in_console_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_UP, move_to_previous_input_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_DOWN, move_to_next_input_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_BACKSPACE, backspace_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_ENTER, enter_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_C, ctrl_c_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_PAGE_UP, page_up_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_PAGE_DOWN, page_down_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_HOME, home_callback_engine });
    console_keypress_callback_engines->push_back(KeyAndCallbackStruct { GLFW_KEY_END, end_callback_engine });
    my_console->set_my_keypress_callback_engine_vector_pointer(console_keypress_callback_engines);

    /*********************************************************************\
     * Callback engines for console commands begin here.                 *
     * These define what commands there are available in the console     *
     * and what each command does.                                       *
     \********************************************************************/

    // Config callbacks.
    command_callback_map["set"] = &config::SettingMaster::set_and_print;
    command_callback_map["get"] = &config::SettingMaster::get_and_print;

    // Object handling callbacks.
    command_callback_map["info"] = &ontology::Universe::info;
    command_callback_map["delete"] = &ontology::Universe::delete_entity;

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
    double last_time_to_display_FPS = glfwGetTime();
    double last_time_for_display_sync = glfwGetTime();
    int nbFrames = 0;

    bool ms_frame_text_ready = false;

    bool is_exit_requested = false;

    // Measure speed
    double last_time_before_reading_keyboard = NAN;
    double current_time_before_reading_keyboard = NAN;

    while (!is_exit_requested)
    {
        double current_time_in_main_loop = glfwGetTime();

        if (current_time_in_main_loop - last_time_for_display_sync >= (1.0f / my_universe->get_max_FPS()))
        {
            last_time_for_display_sync = glfwGetTime();

            char ms_frame_text[256];
            nbFrames++;

            while (current_time_in_main_loop - last_time_to_display_FPS >= 1.0f)
            {
                // If last `std::printf()` was more than 1 sec ago,
                // `std::printf` and reset.
                std::snprintf(ms_frame_text, sizeof(ms_frame_text), "%.02f ms/frame; %.02f Hz", 1000.0f / ((double) nbFrames), 1000.0f / (1000.0f / ((double) nbFrames)));
                ms_frame_text_ready = true;
                nbFrames = 0;
                last_time_to_display_FPS += 1.0;
            }

            // Clear the screen.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwPollEvents();

            my_universe->compute_delta_time();

            // Get mouse position
            double xpos, ypos;
            glfwGetCursorPos(my_universe->get_window(), &xpos, &ypos);

            // Reset mouse position for next frame
            glfwSetCursorPos(my_universe->get_window(), my_universe->get_window_width() / 2, my_universe->get_window_height() / 2);

            if (my_universe->has_mouse_ever_moved || (abs(xpos) > 0.0001) || (abs(ypos) > 0.0001))
            {
                my_universe->has_mouse_ever_moved = true;

                // Compute new orientation
                my_universe->horizontal_angle += my_universe->mouse_speed * GLfloat(my_universe->get_window_width() / 2 - xpos);
                my_universe->horizontal_angle = remainder(my_universe->horizontal_angle, (2.0f * PI));

                if (my_universe->is_invert_mouse_in_use)
                {
                    // invert mouse.
                    my_universe->vertical_angle -= my_universe->mouse_speed * GLfloat(my_universe->get_window_height() / 2 - ypos);
                }
                else
                {
                    // don't invert mouse.
                    my_universe->vertical_angle += my_universe->mouse_speed * GLfloat(my_universe->get_window_height() / 2 - ypos);
                }
                my_universe->vertical_angle = remainder(my_universe->vertical_angle, (2.0f * PI));
            }

            // Direction : Spherical coordinates to Cartesian coordinates conversion
            my_universe->direction = glm::vec3(
                    cos(my_universe->vertical_angle) * sin(my_universe->horizontal_angle),
                    sin(my_universe->vertical_angle),
                    cos(my_universe->vertical_angle) * cos(my_universe->horizontal_angle)
                    );

            // Right vector
            my_universe->right = glm::vec3(
                    sin(my_universe->horizontal_angle - PI/2.0f),
                    0,
                    cos(my_universe->horizontal_angle - PI/2.0f)
                    );

            // Up vector
            my_universe->up = glm::cross(my_universe->right, my_universe->direction);

            // Check for key releases and call corresponding callbacks.
            for (uint32_t i = 0; i < (*current_keyrelease_callback_engine_vector_pointer)->size(); i++)
            {
                if (glfwGetKey(my_universe->get_window(), (*current_keyrelease_callback_engine_vector_pointer)->at(i).keycode) == GLFW_RELEASE)
                {
                    callback_system::CallbackEngine* callback_engine = (*current_keyrelease_callback_engine_vector_pointer)->at(i).callback_engine;
                    std::shared_ptr<datatypes::AnyValue> any_value = callback_engine->execute();
                }
            }

            // Check for keypresses and call corresponding callbacks.
            for (uint32_t i = 0; i < (*current_keypress_callback_engine_vector_pointer)->size(); i++)
            {
                if (glfwGetKey(my_universe->get_window(), (*current_keypress_callback_engine_vector_pointer)->at(i).keycode) == GLFW_PRESS)
                {
                    callback_system::CallbackEngine* callback_engine = (*current_keypress_callback_engine_vector_pointer)->at(i).callback_engine;
                    std::shared_ptr<datatypes::AnyValue> any_value = callback_engine->execute();

                    if (any_value != nullptr &&
                            any_value->type == datatypes::UINT32_T)
                    {
                        if (any_value->uint32_t_value == ENTER_CONSOLE_MAGIC_NUMBER)
                        {
                            // Read all keys, but don't call any more callbacks,
                            // as we are entering the console now. Reading all keys
                            // is needed to flush the input. Not calling any more
                            // callbacks is needed to make callback-related code
                            // simpler, we don't need to worry about consecutive
                            // changes in program mode or in
                            // `current_callback_engine_vector_pointer`. That allows
                            // callbacks to change eg.
                            // `current_callback_engine_vector_pointer` given that
                            // they signal it, eg. with `ENTER_CONSOLE_MAGIC_NUMBER`
                            // (as in this loop).

                            for (uint32_t key_code = 0; key_code <= GLFW_KEY_LAST; key_code++)
                            {
                                glfwGetKey(my_universe->get_window(), key_code);
                            }

                            // Do not display help screen when in console.
                            my_universe->can_display_help_screen = false;
                            break;
                        }
                        if (any_value->uint32_t_value == EXIT_CONSOLE_MAGIC_NUMBER)
                        {
                            // Read all keys, but don't call any more callbacks,
                            // we are exiting the console now. The reasons for doing
                            // this are the same as when entering the console.
                            // See the above comment related to entering the console.

                            for (uint32_t key_code = 0; key_code <= GLFW_KEY_LAST; key_code++)
                            {
                                glfwGetKey(my_universe->get_window(), key_code);
                            }

                            // Enable display help screen when not in console.
                            my_universe->can_display_help_screen = true;
                            break;
                        }
                        if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                        {
                            // Read all keys, but don't call any more callbacks,
                            // we are exiting the program now. The reasons for doing
                            // this are the same as when entering the console.
                            // See the above comment related to entering the console.

                            for (uint32_t key_code = 0; key_code <= GLFW_KEY_LAST; key_code++)
                            {
                                glfwGetKey(my_universe->get_window(), key_code);
                            }

                            is_exit_requested = true;
                            break;
                        }
                    }
                }
            }

            // Render the world.
            my_universe->render();

            // Draw the console (including current input).
            my_console->draw_console();

            PrintingStruct printing_struct;
            printing_struct.screen_width = static_cast<GLuint>(my_universe->get_window_width());
            printing_struct.screen_height = static_cast<GLuint>(my_universe->get_window_height());
            printing_struct.text_size = my_universe->get_text_size();
            printing_struct.font_size = my_universe->get_font_size();
            printing_struct.char_font_texture_file_format = "bmp";

            if (my_universe != nullptr && my_universe->cartesian_coordinates != nullptr)
            {
                char angles_and_coordinates_text[256];
                std::snprintf(
                        angles_and_coordinates_text,
                        sizeof(angles_and_coordinates_text),
                        "%.2f,%.2f rad; %.2f,%.2f deg\\n(%.2f,%.2f,%.2f)",
                        my_universe->horizontal_angle,
                        my_universe->vertical_angle,
                        RADIANS_TO_DEGREES(my_universe->horizontal_angle),
                        RADIANS_TO_DEGREES(my_universe->vertical_angle),
                        my_universe->cartesian_coordinates->x,
                        my_universe->cartesian_coordinates->y,
                        my_universe->cartesian_coordinates->z);

                char time_text[256];
                std::snprintf(time_text, sizeof(time_text), "%.2f sec", glfwGetTime());

                char null_text[] = "";
                char on_text[] = "on";
                char off_text[] = "off";
                char in_use_text[] = " (in use)";

                char help_text_char[1024];
                std::snprintf(
                        help_text_char,
                        sizeof(help_text_char),
                        "Ajokki v. 0.0.1\\n"
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
                        "G  grass texture%s\\n"
                        "U  uvmap texture%s\\n"
                        "T  terrain species\\n"
                        "A  suzanne species\\n",
                        (my_universe->is_invert_mouse_in_use ? on_text : off_text),
                        (my_universe->is_flight_mode_in_use ? on_text : off_text),
                        (!does_suzanne_species_have_uvmap_texture ? in_use_text : null_text),
                        (does_suzanne_species_have_uvmap_texture ? in_use_text : null_text));

                char spherical_coordinates_text[256];

                if (my_universe != nullptr && my_universe->testing_spherical_world_in_use)
                {
                    std::snprintf(spherical_coordinates_text, sizeof(spherical_coordinates_text), "rho:%.2f theta:%.2f phi:%.2f", my_universe->spherical_coordinates->rho, my_universe->spherical_coordinates->theta, my_universe->spherical_coordinates->phi);
                }

                // print cartesian coordinates on bottom left corner.
                printing_struct.x = 0;
                printing_struct.y = 0;
                printing_struct.text_char = angles_and_coordinates_text;
                printing_struct.horizontal_alignment = "left";
                printing_struct.vertical_alignment = "bottom";
                my_font2D->printText2D(printing_struct);

                if (my_universe != nullptr && my_universe->in_help_mode && my_universe->can_display_help_screen)
                {
                    // print help text.
                    printing_struct.x = 0;
                    printing_struct.y = my_universe->get_window_height() - (3 * my_universe->get_text_size());
                    printing_struct.text_char = help_text_char;
                    printing_struct.horizontal_alignment = "left";
                    printing_struct.vertical_alignment = "top";
                    my_font2D->printText2D(printing_struct);
                }

                if (my_universe != nullptr && my_universe->testing_spherical_world_in_use)
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
            }

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

            // Swap buffers.
            glfwSwapBuffers(my_universe->get_window());

            my_universe->finalize_delta_time_loop();
        }

        // Check if the window was closed.
        if (glfwWindowShouldClose(my_universe->get_window()) != 0)
        {
            is_exit_requested = true;
        }
    }

    // do cleanup.
    cleanup_callback_engine->execute();

    // Delete all keyrelease callback engines.
    for (uint32_t i = 0; i < action_mode_keyrelease_callback_engines->size(); i++)
    {
        delete action_mode_keyrelease_callback_engines->at(i).callback_engine;
    }
    delete action_mode_keyrelease_callback_engines;

    // Delete all keypress callback engines.
    for (uint32_t i = 0; i < action_mode_keypress_callback_engines->size(); i++)
    {
        delete action_mode_keypress_callback_engines->at(i).callback_engine;
    }
    delete action_mode_keypress_callback_engines;

    delete cleanup_callback_engine;
    delete my_console;

    return 0;
}
