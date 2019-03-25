#ifndef PI
#define PI 3.14159265359f
#endif

#include "ajokki_helsinki_east_downtown_scene.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream>   // std::cout, std::cin, std::cerr
#include <string>     // std::string

namespace yli
{
    namespace ontology
    {
        class World;
        class Entity;
    }
}

namespace ajokki
{
    yli::ontology::Entity* create_helsinki_east_downtown_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world)
    {
        // Helsinki `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_scene_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_scene_entity = entity_factory->create_Scene(world, 0.9f);
        std::cout << "Creating yli::ontology::Scene* helsinki_east_downtown_scene ...\n";
        yli::ontology::Scene* const helsinki_east_downtown_scene = dynamic_cast<yli::ontology::Scene*>(helsinki_east_downtown_scene_entity);

        if (helsinki_east_downtown_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        helsinki_east_downtown_scene->set_name("helsinki_east_downtown_scene");

        helsinki_east_downtown_scene->set_turbo_factor(5.0f);
        helsinki_east_downtown_scene->set_twin_turbo_factor(100.0f);

        // Create the shader, store it in `helsinki_east_downtown_shader`.
        ShaderStruct helsinki_east_downtown_shader_struct;
        helsinki_east_downtown_shader_struct.parent = helsinki_east_downtown_scene;
        helsinki_east_downtown_shader_struct.vertex_shader = "standard_shading.vert";
        helsinki_east_downtown_shader_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_shader_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_shader_entity = entity_factory->create_Shader(helsinki_east_downtown_shader_struct);
        std::cout << "Creating yli::ontology::Shader* helsinki_east_downtown_shader ...\n";
        yli::ontology::Shader* const helsinki_east_downtown_shader = dynamic_cast<yli::ontology::Shader*>(helsinki_east_downtown_shader_entity);

        if (helsinki_east_downtown_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        helsinki_east_downtown_shader->set_name("helsinki_east_downtown_shader");

        // Create the material, store it in `helsinki_east_downtown_grass_material`.
        MaterialStruct helsinki_east_downtown_grass_material_struct;
        helsinki_east_downtown_grass_material_struct.shader = helsinki_east_downtown_shader;
        helsinki_east_downtown_grass_material_struct.texture_file_format = "bmp";
        helsinki_east_downtown_grass_material_struct.texture_filename = "GrassGreenTexture0002.bmp";

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_grass_material_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_grass_material_entity = entity_factory->create_Material(helsinki_east_downtown_grass_material_struct);
        std::cout << "Creating yli::ontology::Material* helsinki_east_downtown_grass_material ...\n";
        yli::ontology::Material* const helsinki_east_downtown_grass_material = dynamic_cast<yli::ontology::Material*>(helsinki_east_downtown_grass_material_entity);

        if (helsinki_east_downtown_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        helsinki_east_downtown_grass_material->set_name("helsinki_east_downtown_grass_material");

        // Create the material, store it in `pink_geometric_tiles_material`.
        MaterialStruct pink_geometric_tiles_material_struct;
        pink_geometric_tiles_material_struct.shader = helsinki_east_downtown_shader;
        pink_geometric_tiles_material_struct.texture_file_format = "bmp";
        pink_geometric_tiles_material_struct.texture_filename = "pavers1b2.bmp";

        std::cout << "Creating yli::ontology::Entity* pink_geometric_tiles_material_entity ...\n";
        yli::ontology::Entity* const pink_geometric_tiles_material_entity = entity_factory->create_Material(pink_geometric_tiles_material_struct);
        std::cout << "Creating yli::ontology::Material* pink_geometric_tiles_material ...\n";
        yli::ontology::Material* const pink_geometric_tiles_material = dynamic_cast<yli::ontology::Material*>(pink_geometric_tiles_material_entity);

        if (pink_geometric_tiles_material == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        pink_geometric_tiles_material->set_name("helsinki_east_downtown_pink_geometric_tiles_material");

        // Create the material, store it in `orange_fur_material`.
        MaterialStruct orange_fur_material_struct;
        orange_fur_material_struct.shader = helsinki_east_downtown_shader;
        orange_fur_material_struct.texture_file_format = "bmp";
        orange_fur_material_struct.texture_filename = "orange_fur_texture.bmp";

        std::cout << "Creating yli::ontology::Entity* orange_fur_material_entity ...\n";
        yli::ontology::Entity* const orange_fur_material_entity = entity_factory->create_Material(orange_fur_material_struct);
        std::cout << "Creating yli::ontology::Material* orange_fur_material ...\n";
        yli::ontology::Material* const orange_fur_material = dynamic_cast<yli::ontology::Material*>(orange_fur_material_entity);

        if (orange_fur_material == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        orange_fur_material->set_name("helsinki_east_downtown_orange_fur_material");

        SpeciesStruct helsinki_east_downtown_terrain_species_struct;
        helsinki_east_downtown_terrain_species_struct.scene = helsinki_east_downtown_scene;
        helsinki_east_downtown_terrain_species_struct.shader = helsinki_east_downtown_shader;
        helsinki_east_downtown_terrain_species_struct.material = helsinki_east_downtown_grass_material;
        helsinki_east_downtown_terrain_species_struct.model_file_format = "ASCII_grid";
        helsinki_east_downtown_terrain_species_struct.model_filename = "L4133D.asc"; // Helsinki eastern downtown.
        helsinki_east_downtown_terrain_species_struct.light_position = glm::vec3(0, 100000, 100000);
        helsinki_east_downtown_terrain_species_struct.is_terrain = true;
        helsinki_east_downtown_terrain_species_struct.x_step = 4;
        helsinki_east_downtown_terrain_species_struct.z_step = 4;
        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_terrain_species_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_terrain_species_entity = entity_factory->create_Species(helsinki_east_downtown_terrain_species_struct);
        std::cout << "Creating yli::ontology::Species* helsinki_east_downtown_terrain_species ...\n";
        yli::ontology::Species* const helsinki_east_downtown_terrain_species = dynamic_cast<yli::ontology::Species*>(helsinki_east_downtown_terrain_species_entity);

        if (helsinki_east_downtown_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        helsinki_east_downtown_terrain_species->set_name("helsinki_east_downtown_terrain_species");

        // Create Helsinki eastern downtown terrain.
        ObjectStruct helsinki_east_downtown_struct;
        helsinki_east_downtown_struct.species_parent = helsinki_east_downtown_terrain_species;
        helsinki_east_downtown_struct.cartesian_coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
        helsinki_east_downtown_struct.rotate_angle = 0.0f;
        helsinki_east_downtown_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        helsinki_east_downtown_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_Object(helsinki_east_downtown_struct);

        SpeciesStruct suzanne_species_struct;
        suzanne_species_struct.scene = helsinki_east_downtown_scene;
        suzanne_species_struct.shader = helsinki_east_downtown_shader;
        suzanne_species_struct.material = orange_fur_material;
        suzanne_species_struct.model_file_format = "obj";
        suzanne_species_struct.model_filename = "suzanne.obj";
        suzanne_species_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* suzanne_species_entity ...\n";
        yli::ontology::Entity* const suzanne_species_entity = entity_factory->create_Species(suzanne_species_struct);
        std::cout << "Creating yli::ontology::Species* suzanne_species ...\n";
        yli::ontology::Species* const suzanne_species = dynamic_cast<yli::ontology::Species*>(suzanne_species_entity);

        if (suzanne_species == nullptr)
        {
            std::cerr << "Failed to create suzanne Species.\n";
            return nullptr;
        }

        suzanne_species->set_name("suzanne_species");

        // Create suzanne1, store it in `suzanne1`.
        ObjectStruct suzanne_object_struct1;
        suzanne_object_struct1.species_parent = suzanne_species;
        suzanne_object_struct1.cartesian_coordinates = glm::vec3(82.50f, 119.00f, 95.50f);
        suzanne_object_struct1.rotate_angle = 0.10f;
        suzanne_object_struct1.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        suzanne_object_struct1.translate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne1_entity ...\n";
        yli::ontology::Entity* const suzanne1_entity = entity_factory->create_Object(suzanne_object_struct1);
        std::cout << "Creating yli::ontology::Species* suzanne1 ...\n";
        yli::ontology::Object* const suzanne1 = dynamic_cast<yli::ontology::Object*>(suzanne1_entity);

        if (suzanne1 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne1->set_name("suzanne1");

        suzanne_species->set_name("suzanne_species");
        ObjectStruct suzanne_object_struct2;
        suzanne_object_struct2.species_parent = suzanne_species;
        suzanne_object_struct2.cartesian_coordinates = glm::vec3(112.90f, 113.90f, 75.50f);
        suzanne_object_struct2.rotate_angle = 0.20f;
        suzanne_object_struct2.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        suzanne_object_struct2.translate_vector = glm::vec3(0.0f, 1.0f, 0.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne2_entity ...\n";
        yli::ontology::Entity* const suzanne2_entity = entity_factory->create_Object(suzanne_object_struct2);
        std::cout << "Creating yli::ontology::Species* suzanne2 ...\n";
        yli::ontology::Object* const suzanne2 = dynamic_cast<yli::ontology::Object*>(suzanne2_entity);

        if (suzanne2 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne2->set_name("suzanne2");

        ObjectStruct suzanne_object_struct3;
        suzanne_object_struct3.species_parent = suzanne_species;
        suzanne_object_struct3.cartesian_coordinates = glm::vec3(126.90f, 162.90f, 103.00f);
        suzanne_object_struct3.rotate_angle = 0.05f;
        suzanne_object_struct3.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        suzanne_object_struct3.translate_vector = glm::vec3(0.0f, 0.0f, 1.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne3_entity ...\n";
        yli::ontology::Entity* const suzanne3_entity = entity_factory->create_Object(suzanne_object_struct3);
        std::cout << "Creating yli::ontology::Species* suzanne3 ...\n";
        yli::ontology::Object* const suzanne3 = dynamic_cast<yli::ontology::Object*>(suzanne3_entity);

        if (suzanne3 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne3->set_name("suzanne3");

        ObjectStruct suzanne_object_struct4;
        suzanne_object_struct4.species_parent = suzanne_species;
        suzanne_object_struct4.cartesian_coordinates = glm::vec3(96.00f, 130.00f, 109.00f);
        suzanne_object_struct4.rotate_angle = 0.15f;
        suzanne_object_struct4.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        suzanne_object_struct4.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne4_entity ...\n";
        yli::ontology::Entity* const suzanne4_entity = entity_factory->create_Object(suzanne_object_struct4);
        std::cout << "Creating yli::ontology::Species* suzanne4 ...\n";
        yli::ontology::Object* const suzanne4 = dynamic_cast<yli::ontology::Object*>(suzanne4_entity);

        if (suzanne4 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne4->set_name("suzanne4");

        ObjectStruct suzanne_object_struct5;
        suzanne_object_struct5.species_parent = suzanne_species;
        suzanne_object_struct5.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
        suzanne_object_struct5.cartesian_coordinates = glm::vec3(103.00f, 140.00f, 109.00f);
        suzanne_object_struct5.rotate_angle = 0.03f;
        suzanne_object_struct5.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        suzanne_object_struct5.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne5_entity ...\n";
        yli::ontology::Entity* const suzanne5_entity = entity_factory->create_Object(suzanne_object_struct5);
        std::cout << "Creating yli::ontology::Species* suzanne5 ...\n";
        yli::ontology::Object* const suzanne5 = dynamic_cast<yli::ontology::Object*>(suzanne5_entity);

        if (suzanne5 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne5->set_name("suzanne5");

        SpeciesStruct cat_species_struct;
        cat_species_struct.scene = helsinki_east_downtown_scene;
        cat_species_struct.shader = helsinki_east_downtown_shader;
        cat_species_struct.material = orange_fur_material;
        cat_species_struct.model_file_format = "fbx";
        cat_species_struct.model_filename = "cat.fbx";
        cat_species_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* cat_species_entity ...\n";
        yli::ontology::Entity* const cat_species_entity = entity_factory->create_Species(cat_species_struct);

        std::cout << "Creating yli::ontology::Species* cat_species ...\n";
        yli::ontology::Species* const cat_species = dynamic_cast<yli::ontology::Species*>(cat_species_entity);

        if (cat_species == nullptr)
        {
            std::cerr << "Failed to create cat Species.\n";
            return nullptr;
        }

        cat_species->set_name("cat_species");

        ObjectStruct cat_object_struct1;
        cat_object_struct1.species_parent = cat_species;
        cat_object_struct1.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
        cat_object_struct1.cartesian_coordinates = glm::vec3(500.00f, 100.00f, 1000.00f);
        cat_object_struct1.rotate_angle = 0.00f;
        cat_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        cat_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        yli::ontology::Entity* const cat1_entity = entity_factory->create_Object(cat_object_struct1);
        yli::ontology::Object* const cat1 = dynamic_cast<yli::ontology::Object*>(cat1_entity);

        if (cat1 == nullptr)
        {
            std::cerr << "Failed to create cat1 Object.\n";
            return nullptr;
        }

        cat1->set_name("cat1");

        ObjectStruct cat_object_struct2;
        cat_object_struct2.species_parent = cat_species;
        cat_object_struct2.original_scale_vector = glm::vec3(15.0f, 15.0f, 15.0f);
        cat_object_struct2.cartesian_coordinates = glm::vec3(700.00f, 100.00f, 1200.00f);
        cat_object_struct2.rotate_angle = 0.00f;
        cat_object_struct2.rotate_vector = glm::vec3(1.5f, 1.0f, 0.9f);
        cat_object_struct2.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        yli::ontology::Entity* const cat2_entity = entity_factory->create_Object(cat_object_struct2);
        yli::ontology::Object* const cat2 = dynamic_cast<yli::ontology::Object*>(cat2_entity);

        if (cat2 == nullptr)
        {
            std::cerr << "Failed to create cat2 Object.\n";
            return nullptr;
        }

        cat2->set_name("cat2");

        SymbiosisStruct freight_train_symbiosis_struct;
        freight_train_symbiosis_struct.parent = helsinki_east_downtown_shader;
        freight_train_symbiosis_struct.model_file_format = "fbx";
        freight_train_symbiosis_struct.model_filename = "freight_train.fbx";
        freight_train_symbiosis_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* freight_train_symbiosis_entity ...\n";
        yli::ontology::Entity* const freight_train_symbiosis_entity = entity_factory->create_Symbiosis(freight_train_symbiosis_struct);

        std::cout << "Creating yli::ontology::Symbiosis* freight_train_symbiosis ...\n";
        yli::ontology::Symbiosis* const freight_train_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(freight_train_symbiosis_entity);

        if (freight_train_symbiosis == nullptr)
        {
            std::cerr << "Failed to create freight_train Symbiosis.\n";
            return nullptr;
        }

        freight_train_symbiosis->set_name("freight_train_symbiosis");

        HolobiontStruct freight_train_object_struct1;
        freight_train_object_struct1.symbiosis_parent = freight_train_symbiosis;
        freight_train_object_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        freight_train_object_struct1.cartesian_coordinates = glm::vec3(125.00f, 40.00f, 80.00f);
        freight_train_object_struct1.rotate_angle = 0.00f;
        freight_train_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        freight_train_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);

        std::cout << "Creating yli::ontology::Entity* freight_train1_entity ...\n";

        yli::ontology::Entity* const freight_train1_entity = entity_factory->create_Holobiont(freight_train_object_struct1);

        std::cout << "Creating yli::ontology::Holobiont* freight_train1 ...\n";

        yli::ontology::Holobiont* const freight_train1 = dynamic_cast<yli::ontology::Holobiont*>(freight_train1_entity);

        if (freight_train1 == nullptr)
        {
            std::cerr << "Failed to create freight_train1 Object.\n";
            return nullptr;
        }

        freight_train1->set_name("freight_train1");

        SymbiosisStruct turbo_polizei_symbiosis_struct;
        turbo_polizei_symbiosis_struct.parent = helsinki_east_downtown_shader;
        turbo_polizei_symbiosis_struct.model_file_format = "fbx";
        turbo_polizei_symbiosis_struct.model_filename = "turbo_polizei.fbx";
        turbo_polizei_symbiosis_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* turbo_polizei_symbiosis_entity ...\n";
        yli::ontology::Entity* const turbo_polizei_symbiosis_entity = entity_factory->create_Symbiosis(turbo_polizei_symbiosis_struct);

        std::cout << "Creating yli::ontology::Symbiosis* turbo_polizei_symbiosis ...\n";
        yli::ontology::Symbiosis* const turbo_polizei_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(turbo_polizei_symbiosis_entity);

        if (turbo_polizei_symbiosis == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei Symbiosis.\n";
            return nullptr;
        }

        turbo_polizei_symbiosis->set_name("turbo_polizei_symbiosis");

        HolobiontStruct turbo_polizei_object_struct1;
        turbo_polizei_object_struct1.symbiosis_parent = turbo_polizei_symbiosis;
        turbo_polizei_object_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_object_struct1.cartesian_coordinates = glm::vec3(85.00f, 30.00f, 175.00f);
        turbo_polizei_object_struct1.rotate_angle = 0.00f;
        turbo_polizei_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);

        std::cout << "Creating yli::ontology::Entity* turbo_polizei1_entity ...\n";

        yli::ontology::Entity* const turbo_polizei1_entity = entity_factory->create_Holobiont(turbo_polizei_object_struct1);

        std::cout << "Creating yli::ontology::Holobiont* turbo_polizei1 ...\n";

        yli::ontology::Holobiont* const turbo_polizei1 = dynamic_cast<yli::ontology::Holobiont*>(turbo_polizei1_entity);

        if (turbo_polizei1 == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei1 Object.\n";
            return nullptr;
        }

        turbo_polizei1->set_name("turbo_polizei1");

        SymbiosisStruct fantasy_house_with_balcony_symbiosis_struct;
        fantasy_house_with_balcony_symbiosis_struct.parent = helsinki_east_downtown_shader;
        fantasy_house_with_balcony_symbiosis_struct.model_file_format = "fbx";
        fantasy_house_with_balcony_symbiosis_struct.model_filename = "fantasy_house_with_balcony.fbx";
        fantasy_house_with_balcony_symbiosis_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* fantasy_house_with_balcony_symbiosis_entity ...\n";
        yli::ontology::Entity* const fantasy_house_with_balcony_symbiosis_entity = entity_factory->create_Symbiosis(fantasy_house_with_balcony_symbiosis_struct);

        std::cout << "Creating yli::ontology::Symbiosis* fantasy_house_with_balcony_symbiosis ...\n";
        yli::ontology::Symbiosis* const fantasy_house_with_balcony_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(fantasy_house_with_balcony_symbiosis_entity);

        if (fantasy_house_with_balcony_symbiosis == nullptr)
        {
            std::cerr << "Failed to create fantasy_house_with_balcony Symbiosis.\n";
            return nullptr;
        }

        fantasy_house_with_balcony_symbiosis->set_name("fantasy_house_with_balcony_symbiosis");

        HolobiontStruct fantasy_house_with_balcony_object_struct1;
        fantasy_house_with_balcony_object_struct1.symbiosis_parent = fantasy_house_with_balcony_symbiosis;
        fantasy_house_with_balcony_object_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        fantasy_house_with_balcony_object_struct1.cartesian_coordinates = glm::vec3(268.00f, 59.00f, 174.00f);
        fantasy_house_with_balcony_object_struct1.rotate_angle = 0.00f;
        fantasy_house_with_balcony_object_struct1.initial_rotate_angle = 0.0f;
        fantasy_house_with_balcony_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        fantasy_house_with_balcony_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);

        std::cout << "Creating yli::ontology::Entity* fantasy_house_with_balcony1_entity ...\n";

        yli::ontology::Entity* const fantasy_house_with_balcony1_entity = entity_factory->create_Holobiont(fantasy_house_with_balcony_object_struct1);

        std::cout << "Creating yli::ontology::Holobiont* fantasy_house_with_balcony1 ...\n";

        yli::ontology::Holobiont* const fantasy_house_with_balcony1 = dynamic_cast<yli::ontology::Holobiont*>(fantasy_house_with_balcony1_entity);

        if (fantasy_house_with_balcony1 == nullptr)
        {
            std::cerr << "Failed to create fantasy_house_with_balcony1 Object.\n";
            return nullptr;
        }

        fantasy_house_with_balcony1->set_name("fantasy_house_with_balcony1");

        HolobiontStruct fantasy_house_with_balcony_object_struct2;
        fantasy_house_with_balcony_object_struct2.symbiosis_parent = fantasy_house_with_balcony_symbiosis;
        fantasy_house_with_balcony_object_struct2.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        fantasy_house_with_balcony_object_struct2.cartesian_coordinates = glm::vec3(252.00f, 23.50f, 2614.00f);
        fantasy_house_with_balcony_object_struct2.rotate_angle = 0.00f;
        fantasy_house_with_balcony_object_struct2.initial_rotate_angle = PI / 2;
        fantasy_house_with_balcony_object_struct2.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        fantasy_house_with_balcony_object_struct2.initial_rotate_vector = glm::vec3(0.0f, 1.0f, 0.0f);
        fantasy_house_with_balcony_object_struct2.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);

        std::cout << "Creating yli::ontology::Entity* fantasy_house_with_balcony2_entity ...\n";

        yli::ontology::Entity* const fantasy_house_with_balcony2_entity = entity_factory->create_Holobiont(fantasy_house_with_balcony_object_struct2);

        std::cout << "Creating yli::ontology::Holobiont* fantasy_house_with_balcony2 ...\n";

        yli::ontology::Holobiont* const fantasy_house_with_balcony2 = dynamic_cast<yli::ontology::Holobiont*>(fantasy_house_with_balcony2_entity);

        if (fantasy_house_with_balcony2 == nullptr)
        {
            std::cerr << "Failed to create fantasy_house_with_balcony2 Object.\n";
            return nullptr;
        }

        fantasy_house_with_balcony2->set_name("fantasy_house_with_balcony2");

        VectorFontStruct kongtext_vector_font_struct;
        kongtext_vector_font_struct.parent = helsinki_east_downtown_grass_material;
        kongtext_vector_font_struct.font_file_format = "svg";
        kongtext_vector_font_struct.font_filename = "kongtext.svg";

        std::cout << "Creating yli::ontology::Entity* kongtext_font_entity ...\n";
        yli::ontology::Entity* const kongtext_font_entity = entity_factory->create_VectorFont(kongtext_vector_font_struct);
        std::cout << "Creating yli::ontology::VectorFont* kongtext_font ...\n";
        yli::ontology::VectorFont* const kongtext_font = dynamic_cast<yli::ontology::VectorFont*>(kongtext_font_entity);

        if (kongtext_font == nullptr)
        {
            std::cerr << "Failed to create kongtext VectorFont.\n";
            return nullptr;
        }

        Text3DStruct text3D_struct;
        text3D_struct.parent = kongtext_font;
        text3D_struct.text_string = "Hello world &#x26; its habitants!";
        text3D_struct.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        text3D_struct.cartesian_coordinates = glm::vec3(100.00f, 100.00f, 100.00f);
        text3D_struct.rotate_angle = 0.0f;
        text3D_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        text3D_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_Text3D(text3D_struct);

        return helsinki_east_downtown_scene_entity;
        // Helsinki `Scene` ends here.
    }
}
