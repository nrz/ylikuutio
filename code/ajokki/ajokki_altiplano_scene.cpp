#include "ajokki_altiplano_scene.hpp"
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
    yli::ontology::Entity* create_altiplano_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world)
    {
        // altiplano `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* altiplano_scene_entity ...\n";
        yli::ontology::Entity* const altiplano_scene_entity = entity_factory->create_Scene(world, 3815.51f);
        std::cout << "Creating yli::ontology::Scene* altiplano_scene ...\n";
        yli::ontology::Scene* const altiplano_scene = dynamic_cast<yli::ontology::Scene*>(altiplano_scene_entity);

        if (altiplano_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        altiplano_scene->set_name("altiplano_scene");

        // Set `altiplano_scene` to be the currently active `Scene`.
        // my_universe->set_active_scene(altiplano_scene);

        altiplano_scene->set_turbo_factor(5.0f);
        altiplano_scene->set_twin_turbo_factor(100.0f);

        // Create the shader, store it in `altiplano_shader`.
        ShaderStruct altiplano_shader_struct;
        altiplano_shader_struct.parent = altiplano_scene;
        altiplano_shader_struct.vertex_shader = "StandardShading.vertexshader";
        altiplano_shader_struct.fragment_shader = "StandardShading.fragmentshader";

        std::cout << "Creating yli::ontology::Entity* altiplano_shader_entity ...\n";
        yli::ontology::Entity* const altiplano_shader_entity = entity_factory->create_Shader(altiplano_shader_struct);
        std::cout << "Creating yli::ontology::Shader* altiplano_shader ...\n";
        yli::ontology::Shader* const altiplano_shader = dynamic_cast<yli::ontology::Shader*>(altiplano_shader_entity);

        if (altiplano_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        // Create the material, store it in `altiplano_grass_material`.
        MaterialStruct altiplano_grass_material_struct;
        altiplano_grass_material_struct.shader = altiplano_shader;
        altiplano_grass_material_struct.texture_file_format = "bmp";
        altiplano_grass_material_struct.texture_filename = "GrassGreenTexture0002.bmp";

        std::cout << "Creating yli::ontology::Entity* altiplano_grass_material_entity ...\n";
        yli::ontology::Entity* const altiplano_grass_material_entity = entity_factory->create_Material(altiplano_grass_material_struct);
        std::cout << "Creating yli::ontology::Material* altiplano_grass_material ...\n";
        yli::ontology::Material* const altiplano_grass_material = dynamic_cast<yli::ontology::Material*>(altiplano_grass_material_entity);

        if (altiplano_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        altiplano_grass_material->set_name("altiplano_grass_material");

        // Create the species, store it in `terrain_species`.
        SpeciesStruct(altiplano_terrain_species_struct);
        altiplano_terrain_species_struct.scene = altiplano_scene;
        altiplano_terrain_species_struct.shader = altiplano_shader;
        altiplano_terrain_species_struct.material = altiplano_grass_material;
        altiplano_terrain_species_struct.model_file_format = "SRTM";
        altiplano_terrain_species_struct.light_position = glm::vec3(0, 100000, 0);
        altiplano_terrain_species_struct.latitude = -16.50f;  // in degrees.
        altiplano_terrain_species_struct.longitude = -68.15f; // in degrees.
        altiplano_terrain_species_struct.is_terrain = true;
        altiplano_terrain_species_struct.x_step = 1;
        altiplano_terrain_species_struct.z_step = 1;

        std::cout << "Creating yli::ontology::Entity* altiplano_terrain_species_entity ...\n";
        yli::ontology::Entity* const altiplano_terrain_species_entity = entity_factory->create_Species(altiplano_terrain_species_struct);
        std::cout << "Creating yli::ontology::Species* altiplano_terrain_species ...\n";
        yli::ontology::Species* const altiplano_terrain_species = dynamic_cast<yli::ontology::Species*>(altiplano_terrain_species_entity);

        if (altiplano_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        altiplano_terrain_species->set_name("altiplano_terrain_species");

        // Create altiplano terrain.
        ObjectStruct altiplano_struct;
        altiplano_struct.species_parent = altiplano_terrain_species;
        altiplano_struct.cartesian_coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
        altiplano_struct.rotate_angle = 0.0f;
        altiplano_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        altiplano_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_Object(altiplano_struct);

        return altiplano_scene_entity;
        // altiplano `Scene` ends here.
    }
}