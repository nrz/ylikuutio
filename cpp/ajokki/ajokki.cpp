#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

#include "ajokki_callbacks.hpp"
#include "cpp/ylikuutio/callback_system/callback_parameter.hpp"
#include "cpp/ylikuutio/callback_system/callback_object.hpp"
#include "cpp/ylikuutio/callback_system/callback_engine.hpp"
#include "cpp/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "cpp/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "cpp/ylikuutio/console/console.hpp"
#include "cpp/ylikuutio/console/console_keypress_callbacks.hpp"
#include "cpp/ylikuutio/ontology/shader_loader.hpp"
#include "cpp/ylikuutio/ontology/texture_loader.hpp"
#include "cpp/ylikuutio/ontology/vboindexer.hpp"
#include "cpp/ylikuutio/ontology/text2D.hpp"
#include "cpp/ylikuutio/ontology/object.hpp"
#include "cpp/ylikuutio/ontology/species.hpp"
#include "cpp/ylikuutio/ontology/glyph.hpp"
#include "cpp/ylikuutio/ontology/text3D.hpp"
#include "cpp/ylikuutio/ontology/vector_font.hpp"
#include "cpp/ylikuutio/ontology/material.hpp"
#include "cpp/ylikuutio/ontology/shader.hpp"
#include "cpp/ylikuutio/ontology/scene.hpp"
#include "cpp/ylikuutio/ontology/universe.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/common/globals.hpp"

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

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.

// model file format: obj/bmp/...
std::string g_model_file_format = "bmp";

// model filename.
// std::string g_model_filename = "cube.obj";
// std::string g_model_filename = "oma_icosphere.obj";
// std::string g_model_filename = "kirjainkuutio.obj";
// std::string g_model_filename = "noise1024x1024.bmp";
std::string g_model_filename = "noise256x256.bmp";
// std::string g_model_filename = "noise128x128.bmp";

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
    // Initial position : on +Z
    // position = glm::vec3(100, 100, 100);
    // position = glm::vec3(100, 3900, 100);
    // position = glm::vec3(100.0f, 5000.0f, 100.0f);
    if (testing_spherical_world_in_use)
    {
        // position = glm::vec3(100.0f, 5000.0f + EARTH_RADIUS, 100.0f);
        // position = glm::vec3(100.0f, 5000.0f, 100.0f);
        // position = glm::vec3(-5658223.00f, -1700825.12f, 2322764.00f);
        position = glm::vec3(-5659377.50f, -1696985.38f, 2358353.25f);
    }
    else
    {
        position = glm::vec3(100.0f, 100.0f, 100.0f);
    }
    // Initial horizontal angle : toward -Z
    // horizontalAngle = 0.0f;
    horizontalAngle = 42.42f;
    // Initial vertical angle : none
    // verticalAngle = PI / 2;
    verticalAngle = 7.44f;
    // Initial Field of View
    // initialFoV = 45.0f;
    initialFoV = 60.0f;

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
    window = glfwCreateWindow((GLuint) window_width, (GLuint) window_height, "Ylikuutio", nullptr, nullptr);
    cleanup_callback_object->set_new_callback(&ajokki::glfwTerminate_cleanup);

    if (window == nullptr)
    {
        std::cerr << "Failed to open GLFW window.\n";
        cleanup_callback_engine->execute();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW.
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW.\n";
        cleanup_callback_engine->execute();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below.
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPos(window, ((GLuint) window_width / 2), ((GLuint) window_height / 2));

    // Dark blue background.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test.
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one.
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera.
    glEnable(GL_CULL_FACE);

    // Create the world, store it in `my_world`.
    ontology::Universe* my_world = new ontology::Universe();

    ontology::Scene* my_scene = new ontology::Scene(my_world);

    // Create the shader, store it in `my_shader`.
    ShaderStruct shader_struct;
    shader_struct.parent_pointer = my_scene;
    shader_struct.vertex_shader = "StandardShading.vertexshader";
    shader_struct.fragment_shader = "StandardShading.fragmentshader";
    ontology::Shader* my_shader = new ontology::Shader(shader_struct);

    // Create the material, store it in `grass_material`.
    MaterialStruct grass_material_struct;
    grass_material_struct.parent_pointer = my_shader;
    grass_material_struct.texture_file_format = g_texture_file_format;
    grass_material_struct.texture_filename = g_texture_filename;
    ontology::Material* grass_material = new ontology::Material(grass_material_struct);

    // Create the material, store it in `uvmap_material`.
    MaterialStruct uvmap_material_struct;
    uvmap_material_struct.parent_pointer = my_shader;
    uvmap_material_struct.texture_file_format = "dds";
    uvmap_material_struct.texture_filename = "uvmap.DDS";
    ontology::Material* uvmap_material = new ontology::Material(uvmap_material_struct);

    ontology::Species* terrain_species;

    if (testing_spherical_world_in_use)
    {
        // Create the species, store it in `terrain_species`.
        SpeciesStruct(SRTM_terrain_species_struct);
        SRTM_terrain_species_struct.parent_pointer = grass_material;
        SRTM_terrain_species_struct.model_file_format = "SRTM";
        // SRTM_terrain_species_struct.model_filename = "/media/laatikko_4TB/satelliittikuvat/srtm/version3/data/";
        SRTM_terrain_species_struct.model_filename = "./"; // for testing
        SRTM_terrain_species_struct.color_channel = g_height_data_color_channel;
        SRTM_terrain_species_struct.light_position = glm::vec3(4, 4, 4);
        SRTM_terrain_species_struct.is_world = true;
        terrain_species = new ontology::Species(SRTM_terrain_species_struct);

        turbo_factor = 100.0f;
        twin_turbo_factor = 50000.0f;
    }
    else
    {
        // Create the species, store it in `terrain_species`.
        SpeciesStruct bmp_terrain_species_struct;
        bmp_terrain_species_struct.parent_pointer = grass_material;
        bmp_terrain_species_struct.model_file_format = g_model_file_format;
        bmp_terrain_species_struct.model_filename = g_model_filename;
        bmp_terrain_species_struct.color_channel = g_height_data_color_channel;
        bmp_terrain_species_struct.light_position = glm::vec3(4, 4, 4);
        bmp_terrain_species_struct.is_world = true;
        terrain_species = new ontology::Species(bmp_terrain_species_struct);

        turbo_factor = 5.0f;
        twin_turbo_factor = 100.0f;
    }

    // Create terrain1, store it in `terrain1`.
    ObjectStruct terrain_object_struct1;
    terrain_object_struct1.species_parent_pointer = terrain_species;
    terrain_object_struct1.coordinate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    terrain_object_struct1.rotate_angle = 0.0f;
    terrain_object_struct1.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    terrain_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    ontology::Object* terrain1 = new ontology::Object(terrain_object_struct1);

    SpeciesStruct suzanne_species_struct;
    suzanne_species_struct.parent_pointer = uvmap_material;
    suzanne_species_struct.model_file_format = "obj";
    suzanne_species_struct.model_filename = "suzanne.obj";
    suzanne_species_struct.light_position = glm::vec3(4, 4, 4);
    ontology::Species* suzanne_species = new ontology::Species(suzanne_species_struct);

    // Create suzanne1, store it in `suzanne1`.
    ObjectStruct suzanne_object_struct1;
    suzanne_object_struct1.species_parent_pointer = suzanne_species;
    suzanne_object_struct1.coordinate_vector = glm::vec3(82.50f, 119.00f, 95.50f);
    suzanne_object_struct1.rotate_angle = 0.10f;
    suzanne_object_struct1.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    suzanne_object_struct1.translate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    ontology::Object* suzanne1 = new ontology::Object(suzanne_object_struct1);

    ObjectStruct suzanne_object_struct2;
    suzanne_object_struct2.species_parent_pointer = suzanne_species;
    suzanne_object_struct2.coordinate_vector = glm::vec3(112.90f, 113.90f, 75.50f);
    suzanne_object_struct2.rotate_angle = 0.20f;
    suzanne_object_struct2.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    suzanne_object_struct2.translate_vector = glm::vec3(0.0f, 1.0f, 0.0f);
    ontology::Object* suzanne2 = new ontology::Object(suzanne_object_struct2);

    ObjectStruct suzanne_object_struct3;
    suzanne_object_struct3.species_parent_pointer = suzanne_species;
    suzanne_object_struct3.coordinate_vector = glm::vec3(126.90f, 162.90f, 103.00f);
    suzanne_object_struct3.rotate_angle = 0.05f;
    suzanne_object_struct3.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    suzanne_object_struct3.translate_vector = glm::vec3(0.0f, 0.0f, 1.0f);
    ontology::Object* suzanne3 = new ontology::Object(suzanne_object_struct3);

    ObjectStruct suzanne_object_struct4;
    suzanne_object_struct4.species_parent_pointer = suzanne_species;
    suzanne_object_struct4.coordinate_vector = glm::vec3(96.00f, 130.00f, 109.00f);
    suzanne_object_struct4.rotate_angle = 0.15f;
    suzanne_object_struct4.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
    suzanne_object_struct4.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    ontology::Object* suzanne4 = new ontology::Object(suzanne_object_struct4);

    ObjectStruct suzanne_object_struct5;
    suzanne_object_struct5.species_parent_pointer = suzanne_species;
    suzanne_object_struct5.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
    suzanne_object_struct5.coordinate_vector = glm::vec3(103.00f, 105.00f, 109.00f);
    suzanne_object_struct5.rotate_angle = 0.03f;
    suzanne_object_struct5.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    suzanne_object_struct5.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    ontology::Object* suzanne5 = new ontology::Object(suzanne_object_struct5);

    VectorFontStruct kongtext_vector_font_struct;
    kongtext_vector_font_struct.parent_pointer = grass_material;
    kongtext_vector_font_struct.font_file_format = g_font_file_format;
    kongtext_vector_font_struct.font_filename = g_font_filename;
    ontology::VectorFont* kongtext_font = new ontology::VectorFont(kongtext_vector_font_struct);

    Text3DStruct text3D_struct;
    text3D_struct.parent_pointer = kongtext_font;
    text3D_struct.text_string = "Hello world &#x26; its habitants!";
    text3D_struct.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    text3D_struct.coordinate_vector = glm::vec3(100.00f, 100.00f, 100.00f);
    text3D_struct.rotate_angle = 0.0f;
    text3D_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    text3D_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
    ontology::Text3D* hello_world_text3D = new ontology::Text3D(text3D_struct);

    // keypress callbacks.
    std::vector<KeyAndCallbackStruct> keypress_callback_engines;

    // This vector points to current keypress callback engines vector.
    std::vector<KeyAndCallbackStruct>* current_callback_engine_vector_pointer;
    current_callback_engine_vector_pointer = &keypress_callback_engines;

    // keyrelease callbacks.
    std::vector<KeyAndCallbackStruct> keyrelease_callback_engines;

    // This vector points to current keyrelease callback engines vector.
    std::vector<KeyAndCallbackStruct>* current_keyrelease_callback_engine_vector_pointer;
    current_keyrelease_callback_engine_vector_pointer = &keyrelease_callback_engines;

    console::Console* my_console = new console::Console(&current_callback_engine_vector_pointer); // create a console.
    global_console_pointer = my_console;

    // Callback code for left control release: release first turbo.
    callback_system::CallbackEngine* release_first_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* release_first_turbo_callback_object = new callback_system::CallbackObject(
            &ajokki::release_first_turbo, release_first_turbo_callback_engine);

    // Callback code for right control release: release second turbo.
    callback_system::CallbackEngine* release_second_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* release_second_turbo_callback_object = new callback_system::CallbackObject(
            &ajokki::release_second_turbo, release_second_turbo_callback_engine);

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` (tilde key above Tab, usually used for console).
    callback_system::CallbackEngine* enter_console_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* enter_console_callback_object = new callback_system::CallbackObject(
            &console::enter_console, enter_console_callback_engine);
    callback_system::CallbackParameter* enter_console_parameter = new callback_system::CallbackParameter(
            "console_pointer", new datatypes::AnyValue(my_console), false, enter_console_callback_object);

    // Callback code for `GLFW_KEY_GRAVE_ACCENT` (tilde key above Tab, usually used for console).
    callback_system::CallbackEngine* exit_console_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* exit_console_callback_object = new callback_system::CallbackObject(
            &console::exit_console, exit_console_callback_engine);
    callback_system::CallbackParameter* exit_console_parameter = new callback_system::CallbackParameter(
            "console_pointer", new datatypes::AnyValue(my_console), false, exit_console_callback_object);

    // Callback code for backspace: delete character left of cursor from current input in console.
    callback_system::CallbackEngine* backspace_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* backspace_callback_object = new callback_system::CallbackObject(
            &console::backspace, backspace_callback_engine);
    callback_system::CallbackParameter* backspace_console_pointer = new callback_system::CallbackParameter(
            "console_pointer", new datatypes::AnyValue(my_console), false, backspace_callback_object);

    // Callback code for esc: exit program.
    callback_system::CallbackEngine* exit_program_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* exit_program_callback_object = new callback_system::CallbackObject(
            &ajokki::exit_program, exit_program_callback_engine);

    // Callback code for left control: first turbo.
    callback_system::CallbackEngine* first_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* first_turbo_callback_object = new callback_system::CallbackObject(
            &ajokki::first_turbo, first_turbo_callback_engine);

    // Callback code for right control: second turbo.
    callback_system::CallbackEngine* second_turbo_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* second_turbo_callback_object = new callback_system::CallbackObject(
            &ajokki::second_turbo, second_turbo_callback_engine);

    // Callback code for key up: move forward.
    callback_system::CallbackEngine* move_forward_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* move_forward_callback_object = new callback_system::CallbackObject(
            &ajokki::move_forward, move_forward_callback_engine);

    // Callback code for key down: move backward.
    callback_system::CallbackEngine* move_backward_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* move_backward_callback_object = new callback_system::CallbackObject(
            &ajokki::move_backward, move_backward_callback_engine);

    // Callback code for key left: strafe left.
    callback_system::CallbackEngine* strafe_left_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* strafe_left_callback_object = new callback_system::CallbackObject(
            &ajokki::strafe_left, strafe_left_callback_engine);

    // Callback code for key right: strafe right.
    callback_system::CallbackEngine* strafe_right_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* strafe_right_callback_object = new callback_system::CallbackObject(
            &ajokki::strafe_right, strafe_right_callback_engine);

    // Callback code for enter: delete character left of cursor from current input in console.
    callback_system::CallbackEngine* enter_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* enter_callback_object = new callback_system::CallbackObject(
            &console::enter_key, enter_callback_engine);
    callback_system::CallbackParameter* enter_console_pointer = new callback_system::CallbackParameter(
            "console_pointer", new datatypes::AnyValue(my_console), false, enter_callback_object);

    // Callback code for D: delete Suzanne species.
    bool does_suzanne_species_exist = true;
    callback_system::CallbackEngine* delete_suzanne_species_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* delete_suzanne_species_callback_object = new callback_system::CallbackObject(
            &ajokki::delete_suzanne_species, delete_suzanne_species_callback_engine);
    callback_system::CallbackParameter* delete_suzanne_species_callback_parameter0 = new callback_system::CallbackParameter(
            "suzanne_species", new datatypes::AnyValue(suzanne_species), false, delete_suzanne_species_callback_object);
    callback_system::CallbackParameter* delete_suzanne_species_callback_parameter1 = new callback_system::CallbackParameter(
            "does_suzanne_species_exist", new datatypes::AnyValue(&does_suzanne_species_exist), false, delete_suzanne_species_callback_object);

    // Callback code for G: switch to grass material.
    bool does_suzanne_species_have_uvmap_texture = true;
    bool does_suzanne_species_have_grass_texture = false;
    callback_system::CallbackEngine* switch_to_grass_material_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* switch_to_grass_material_callback_object = new callback_system::CallbackObject(
            &ajokki::switch_to_new_material, switch_to_grass_material_callback_engine);
    callback_system::CallbackParameter* switch_to_grass_material_callback_parameter0 = new callback_system::CallbackParameter(
            "suzanne_species", new datatypes::AnyValue(suzanne_species), false, switch_to_grass_material_callback_object);
    callback_system::CallbackParameter* switch_to_grass_material_callback_parameter1 = new callback_system::CallbackParameter(
            "new_material", new datatypes::AnyValue(grass_material), false, switch_to_grass_material_callback_object);
    callback_system::CallbackParameter* switch_to_grass_material_callback_parameter2 = new callback_system::CallbackParameter(
            "does_suzanne_species_exist", new datatypes::AnyValue(&does_suzanne_species_exist), false, switch_to_grass_material_callback_object);
    callback_system::CallbackParameter* switch_to_grass_material_callback_parameter3 = new callback_system::CallbackParameter(
            "does_suzanne_species_have_old_texture",
            new datatypes::AnyValue(&does_suzanne_species_have_uvmap_texture),
            false,
            switch_to_grass_material_callback_object);
    callback_system::CallbackParameter* switch_to_grass_material_callback_parameter4 = new callback_system::CallbackParameter(
            "does_suzanne_species_have_new_texture",
            new datatypes::AnyValue(&does_suzanne_species_have_grass_texture),
            false,
            switch_to_grass_material_callback_object);

    // Callback code for U: switch back to uvmap material.
    callback_system::CallbackEngine* switch_to_uvmap_material_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* switch_to_uvmap_material_callback_object = new callback_system::CallbackObject(
            &ajokki::switch_to_new_material, switch_to_uvmap_material_callback_engine);
    callback_system::CallbackParameter* switch_to_uvmap_material_callback_parameter0 = new callback_system::CallbackParameter(
            "suzanne_species", new datatypes::AnyValue(suzanne_species), false, switch_to_uvmap_material_callback_object);
    callback_system::CallbackParameter* switch_to_uvmap_material_callback_parameter1 = new callback_system::CallbackParameter(
            "new_material", new datatypes::AnyValue(uvmap_material), false, switch_to_uvmap_material_callback_object);
    callback_system::CallbackParameter* switch_to_uvmap_material_callback_parameter2 = new callback_system::CallbackParameter(
            "does_suzanne_species_exist", new datatypes::AnyValue(&does_suzanne_species_exist), false, switch_to_uvmap_material_callback_object);
    callback_system::CallbackParameter* switch_to_uvmap_material_callback_parameter3 = new callback_system::CallbackParameter(
            "does_suzanne_species_have_old_texture",
            new datatypes::AnyValue(&does_suzanne_species_have_grass_texture),
            false,
            switch_to_uvmap_material_callback_object);
    callback_system::CallbackParameter* switch_to_uvmap_material_callback_parameter4 = new callback_system::CallbackParameter(
            "does_suzanne_species_have_new_texture",
            new datatypes::AnyValue(&does_suzanne_species_have_uvmap_texture),
            false,
            switch_to_uvmap_material_callback_object);

    // Callback code for T: transform `suzanne2` into terrain.
    bool has_suzanne_2_transformed_into_monkey = true;
    bool has_suzanne_2_transformed_into_terrain = false;
    callback_system::CallbackEngine* transform_into_terrain_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* transform_into_terrain_callback_object = new callback_system::CallbackObject(
            &ajokki::transform_into_new_species, transform_into_terrain_callback_engine);
    callback_system::CallbackParameter* transform_into_terrain_callback_parameter0 = new callback_system::CallbackParameter(
            "suzanne2", new datatypes::AnyValue(suzanne2), false, transform_into_terrain_callback_object); // suzanne2!!!
    callback_system::CallbackParameter* transform_into_terrain_callback_parameter1 = new callback_system::CallbackParameter(
            "terrain_species", new datatypes::AnyValue(terrain_species), false, transform_into_terrain_callback_object);
    callback_system::CallbackParameter* transform_into_terrain_callback_parameter2 = new callback_system::CallbackParameter(
            "does_suzanne_species_exist", new datatypes::AnyValue(&does_suzanne_species_exist), false, transform_into_terrain_callback_object);
    callback_system::CallbackParameter* transform_into_terrain_callback_parameter3 = new callback_system::CallbackParameter(
            "has_suzanne_2_transformed_into_monkey",
            new datatypes::AnyValue(&has_suzanne_2_transformed_into_monkey),
            false,
            transform_into_terrain_callback_object);
    callback_system::CallbackParameter* transform_into_terrain_callback_parameter4 = new callback_system::CallbackParameter(
            "has_suzanne_2_transformed_into_terrain",
            new datatypes::AnyValue(&has_suzanne_2_transformed_into_terrain),
            false,
            transform_into_terrain_callback_object);

    // Callback code for A: transform `suzanne2` back into monkey.
    callback_system::CallbackEngine* transform_into_monkey_callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* transform_into_monkey_callback_object = new callback_system::CallbackObject(
            &ajokki::transform_into_new_species, transform_into_monkey_callback_engine);
    callback_system::CallbackParameter* transform_into_monkey_callback_parameter0 = new callback_system::CallbackParameter(
            "suzanne2", new datatypes::AnyValue(suzanne2), false, transform_into_monkey_callback_object); // suzanne2!!!
    callback_system::CallbackParameter* transform_into_monkey_callback_parameter1 = new callback_system::CallbackParameter(
            "monkey_species", new datatypes::AnyValue(suzanne_species), false, transform_into_monkey_callback_object);
    callback_system::CallbackParameter* transform_into_monkey_callback_parameter2 = new callback_system::CallbackParameter(
            "does_suzanne_species_exist", new datatypes::AnyValue(&does_suzanne_species_exist), false, transform_into_monkey_callback_object);
    callback_system::CallbackParameter* transform_into_monkey_callback_parameter3 = new callback_system::CallbackParameter(
            "has_suzanne_2_transformed_into_terrain",
            new datatypes::AnyValue(&has_suzanne_2_transformed_into_terrain),
            false,
            transform_into_monkey_callback_object);
    callback_system::CallbackParameter* transform_into_monkey_callback_parameter4 = new callback_system::CallbackParameter(
            "has_suzanne_2_transformed_into_monkey",
            new datatypes::AnyValue(&has_suzanne_2_transformed_into_monkey),
            false,
            transform_into_monkey_callback_object);

    datatypes::AnyValue* my_world_value = new datatypes::AnyValue(my_world);
    callback_system::CallbackParameter* callback_parameter = new callback_system::CallbackParameter("", my_world_value, false, cleanup_callback_object);
    cleanup_callback_object->set_new_callback(&ajokki::full_cleanup);

    // This is one of the possible `std::vector<KeyAndCallbackStruct>`.
    // Key releases are checked in the order of this struct.
    keyrelease_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, release_first_turbo_callback_engine });
    keyrelease_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, release_second_turbo_callback_engine });

    // This is one of the possible `std::vector<KeyAndCallbackStruct>`.
    // Keypresses are checked in the order of this struct.
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, enter_console_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_ESCAPE, exit_program_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT_CONTROL, first_turbo_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT_CONTROL, second_turbo_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_UP, move_forward_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_DOWN, move_backward_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_LEFT, strafe_left_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_RIGHT, strafe_right_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_D, delete_suzanne_species_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_G, switch_to_grass_material_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_U, switch_to_uvmap_material_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_T, transform_into_terrain_callback_engine });
    keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_A, transform_into_monkey_callback_engine });

    // QWERTY keypress callbacks for console.
    std::vector<KeyAndCallbackStruct> console_QWERTY_keypress_callback_engines;
    console_QWERTY_keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, exit_console_callback_engine });
    console_QWERTY_keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_BACKSPACE, backspace_callback_engine });
    console_QWERTY_keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_ENTER, enter_callback_engine });
    my_console->set_my_callback_engine_vector_pointer(&console_QWERTY_keypress_callback_engines);

    // Standard Dvorak keypress callbacks for console.
    std::vector<KeyAndCallbackStruct> console_Dvorak_keypress_callback_engines;
    console_Dvorak_keypress_callback_engines.push_back(KeyAndCallbackStruct { GLFW_KEY_GRAVE_ACCENT, exit_console_callback_engine });

    // Initialize our little text library with the Holstein font
    const char* char_g_font_texture_filename = g_font_texture_filename.c_str();
    const char* char_g_font_texture_file_format = g_font_texture_file_format.c_str();
    text2D::initText2D((GLuint) window_width, (GLuint) window_height, char_g_font_texture_filename, char_g_font_texture_file_format);

    // For speed computation
    double last_time_to_display_FPS = glfwGetTime();
    double last_time_for_display_sync = glfwGetTime();
    int nbFrames = 0;

    bool ms_frame_text_ready = false;

    bool is_exit_requested = false;

    while (!is_exit_requested)
    {
        // Measure speed
        double currentTime = glfwGetTime();

        if (currentTime - last_time_for_display_sync >= (1.0f / max_FPS))
        {
            last_time_for_display_sync = glfwGetTime();

            char ms_frame_text[256];
            nbFrames++;

            while (currentTime - last_time_to_display_FPS >= 1.0f)
            {
                // If last `std::printf()` was more than 1 sec ago,
                // `std::printf` and reset.
                std::sprintf(ms_frame_text, "%.02f ms/frame; %.02f Hz", 1000.0f / ((double) nbFrames), 1000.0f / (1000.0f / ((double) nbFrames)));
                ms_frame_text_ready = true;
                nbFrames = 0;
                last_time_to_display_FPS += 1.0;
            }

            // Clear the screen.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render the world.
            my_world->render();

            // Draw the console (including current input).
            my_console->draw_console();

            PrintingStruct printing_struct;
            printing_struct.screen_width = (GLuint) window_width;
            printing_struct.screen_height = (GLuint) window_height;
            printing_struct.text_size = text_size;
            printing_struct.font_size = font_size;
            printing_struct.char_font_texture_file_format = "bmp";

            char angles_and_coordinates_text[256];
            std::sprintf(
                    angles_and_coordinates_text,
                    "%.2f,%.2f rad; %.2f,%.2f deg\\n(%.2f,%.2f,%.2f)",
                    horizontalAngle,
                    verticalAngle,
                    RADIANS_TO_DEGREES(horizontalAngle),
                    RADIANS_TO_DEGREES(verticalAngle),
                    position.x,
                    position.y,
                    position.z);

            char time_text[256];
            std::sprintf(time_text, "%.2f sec", glfwGetTime());

            char null_text[] = "";
            char on_text[] = "on";
            char off_text[] = "off";
            char in_use_text[] = " (in use)";

            char help_text_char[1024];
            std::sprintf(
                    help_text_char,
                    "Ajokki v. 0.0.1\\n"
                    "\\n"
                    "F1-help mode\\n"
                    "arrow keys\\n"
                    "N-north S-south W-west E-east\\n"
                    "I-invert mouse (%s)\\n"
                    "F-flight mode (%s)\\n"
                    "G-grass texture%s\\n"
                    "U-uvmap texture%s\\n"
                    "T-terrain species\\n"
                    "A-suzanne species\\n"
                    "Ctrl     -turbo\\n"
                    "Ctrl+Ctrl-extra turbo\\n",
                    (is_invert_mouse_in_use ? on_text : off_text),
                    (is_flight_mode_in_use ? on_text : off_text),
                    (!does_suzanne_species_have_uvmap_texture ? in_use_text : null_text),
                    (does_suzanne_species_have_uvmap_texture ? in_use_text : null_text));

            char spherical_coordinates_text[256];

            if (testing_spherical_world_in_use)
            {
                std::sprintf(spherical_coordinates_text, "rho:%.2f theta:%.2f phi:%.2f", spherical_position.rho, spherical_position.theta, spherical_position.phi);
            }

            // print cartesian coordinates on bottom left corner.
            printing_struct.x = 0;
            printing_struct.y = 0;
            printing_struct.text_char = angles_and_coordinates_text;
            printing_struct.horizontal_alignment = "left";
            printing_struct.vertical_alignment = "bottom";
            text2D::printText2D(printing_struct);

            if (in_help_mode)
            {
                // print help text.
                printing_struct.x = 0;
                printing_struct.y = window_height - (7 * text_size);
                printing_struct.text_char = help_text_char;
                printing_struct.horizontal_alignment = "left";
                printing_struct.vertical_alignment = "top";
                text2D::printText2D(printing_struct);
            }

            if (testing_spherical_world_in_use)
            {
                // print spherical coordinates on bottom left corner.
                printing_struct.x = 0;
                printing_struct.y += 2 * text_size;
                printing_struct.text_char = spherical_coordinates_text;
                printing_struct.horizontal_alignment = "left";
                printing_struct.vertical_alignment = "bottom";
                text2D::printText2D(printing_struct);
            }

            // print time data on top left corner.
            printing_struct.x = 0;
            printing_struct.y = (GLuint) window_height;
            printing_struct.text_char = time_text;
            printing_struct.horizontal_alignment = "left";
            printing_struct.vertical_alignment = "top";
            text2D::printText2D(printing_struct);

            if (ms_frame_text_ready)
            {
                // print frame rate data on top right corner.
                printing_struct.x = window_width;
                printing_struct.y = window_height;
                printing_struct.text_char = ms_frame_text;
                printing_struct.horizontal_alignment = "right";
                printing_struct.vertical_alignment = "top";
                text2D::printText2D(printing_struct);
            }

            // Swap buffers.
            glfwSwapBuffers(window);
        }

        glfwPollEvents();

        // Check for key releases and call corresponding callbacks.
        for (uint32_t i = 0; i < (*current_keyrelease_callback_engine_vector_pointer).size(); i++)
        {
            if (glfwGetKey(window, (*current_keyrelease_callback_engine_vector_pointer).at(i).keycode) == GLFW_RELEASE)
            {
                callback_system::CallbackEngine* callback_engine = (*current_keyrelease_callback_engine_vector_pointer).at(i).callback_engine;
                datatypes::AnyValue* any_value = callback_engine->execute();
            }
        }

        // Check for keypresses and call corresponding callbacks.
        for (uint32_t i = 0; i < (*current_callback_engine_vector_pointer).size(); i++)
        {
            if (glfwGetKey(window, (*current_callback_engine_vector_pointer).at(i).keycode) == GLFW_PRESS)
            {
                callback_system::CallbackEngine* callback_engine = (*current_callback_engine_vector_pointer).at(i).callback_engine;
                datatypes::AnyValue* any_value = callback_engine->execute();

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
                            glfwGetKey(window, key_code);
                        }

                        delete any_value;
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
                            glfwGetKey(window, key_code);
                        }

                        delete any_value;
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
                            glfwGetKey(window, key_code);
                        }

                        is_exit_requested = true;
                        delete any_value;
                        break;
                    }
                }
                delete any_value;
            }
        }

        // Check if the window was closed.
        if (glfwWindowShouldClose(window) != 0)
        {
            is_exit_requested = true;
        }
    }

    // do cleanup.
    cleanup_callback_engine->execute();

    // Delete all callback engines.
    for (uint32_t i = 0; i < keypress_callback_engines.size(); i++)
    {
        delete keypress_callback_engines.at(i).callback_engine;
    }

    delete cleanup_callback_engine;
    delete my_console;

    return 0;
}
