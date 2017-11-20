#include "ajokki_joensuu_center_west_scene.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream>   // std::cout, std::cin, std::cerr
#include <memory>     // std::make_shared, std::shared_ptr
#include <string>     // std::string

namespace ontology
{
    class Entity;
}

namespace ajokki
{
    ontology::Entity* create_joensuu_center_west_scene(std::shared_ptr<ontology::EntityFactory> entity_factory)
    {
        // Joensuu `Scene` begins here.
        ontology::Entity* joensuu_center_west_scene_entity = entity_factory->create_Scene(77.0f);
        ontology::Scene* joensuu_center_west_scene = dynamic_cast<ontology::Scene*>(joensuu_center_west_scene_entity);

        if (joensuu_center_west_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        joensuu_center_west_scene->set_name("joensuu_center_west_scene");

        // Set `joensuu_center_west_scene` to be the currently active `Scene`.
        // my_universe->set_active_scene(joensuu_center_west_scene);

        joensuu_center_west_scene->set_turbo_factor(5.0f);
        joensuu_center_west_scene->set_twin_turbo_factor(100.0f);

        // Create the shader, store it in `joensuu_center_west_shader`.
        ShaderStruct joensuu_center_west_shader_struct;
        joensuu_center_west_shader_struct.parent = joensuu_center_west_scene;
        joensuu_center_west_shader_struct.vertex_shader = "StandardShading.vertexshader";
        joensuu_center_west_shader_struct.fragment_shader = "StandardShading.fragmentshader";

        std::cout << "Creating ontology::Entity* joensuu_center_west_shader_entity ...\n";
        ontology::Entity* joensuu_center_west_shader_entity = entity_factory->create_Shader(joensuu_center_west_shader_struct);
        std::cout << "Creating ontology::Shader* joensuu_center_west_shader ...\n";
        ontology::Shader* joensuu_center_west_shader = dynamic_cast<ontology::Shader*>(joensuu_center_west_shader_entity);

        if (joensuu_center_west_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        // Create the material, store it in `joensuu_center_west_grass_material_struct`.
        MaterialStruct joensuu_center_west_grass_material_struct;
        joensuu_center_west_grass_material_struct.parent = joensuu_center_west_shader;
        joensuu_center_west_grass_material_struct.texture_file_format = "bmp";
        joensuu_center_west_grass_material_struct.texture_filename = "GrassGreenTexture0002.bmp";

        std::cout << "Creating ontology::Entity* joensuu_center_west_grass_material_entity ...\n";
        ontology::Entity* joensuu_center_west_grass_material_entity = entity_factory->create_Material(joensuu_center_west_grass_material_struct);
        std::cout << "Creating ontology::Material* joensuu_center_west_grass_material ...\n";
        ontology::Material* joensuu_center_west_grass_material = dynamic_cast<ontology::Material*>(joensuu_center_west_grass_material_entity);

        if (joensuu_center_west_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        joensuu_center_west_grass_material->set_name("joensuu_center_west_grass_material");

        SpeciesStruct joensuu_center_west_terrain_species_struct;
        joensuu_center_west_terrain_species_struct.scene = joensuu_center_west_scene;
        joensuu_center_west_terrain_species_struct.shader = joensuu_center_west_shader;
        joensuu_center_west_terrain_species_struct.parent = joensuu_center_west_grass_material;
        joensuu_center_west_terrain_species_struct.model_file_format = "ASCII_grid";
        joensuu_center_west_terrain_species_struct.model_filename = "N5424G.asc"; // Joensuu center & western.
        joensuu_center_west_terrain_species_struct.light_position = glm::vec3(0, 100000, 100000);
        joensuu_center_west_terrain_species_struct.is_world = true;
        joensuu_center_west_terrain_species_struct.x_step = 4;
        joensuu_center_west_terrain_species_struct.z_step = 4;
        std::cout << "Creating ontology::Entity* joensuu_center_west_terrain_species_entity ...\n";
        ontology::Entity* joensuu_center_west_terrain_species_entity = entity_factory->create_Species(joensuu_center_west_terrain_species_struct);
        std::cout << "Creating ontology::Species* joensuu_center_west_terrain_species ...\n";
        ontology::Species* joensuu_center_west_terrain_species = dynamic_cast<ontology::Species*>(joensuu_center_west_terrain_species_entity);

        if (joensuu_center_west_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        joensuu_center_west_terrain_species->set_name("joensuu_center_west_terrain_species");

        // Create Joensuu center west terrain.
        ObjectStruct joensuu_center_west_struct;
        joensuu_center_west_struct.species_parent = joensuu_center_west_terrain_species;
        joensuu_center_west_struct.cartesian_coordinates = std::make_shared<glm::vec3>(0.0f, 0.0f, 0.0f);
        joensuu_center_west_struct.rotate_angle = 0.0f;
        joensuu_center_west_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        joensuu_center_west_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_Object(joensuu_center_west_struct);

        return joensuu_center_west_scene_entity;
        // Joensuu `Scene` ends here.
    }
}
