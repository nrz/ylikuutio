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

#include "ajokki_joensuu_center_west_scene.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"
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
    yli::ontology::Entity* create_joensuu_center_west_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world)
    {
        // Joensuu `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* joensuu_center_west_scene_entity ...\n";
        yli::ontology::SceneStruct scene_struct;
        scene_struct.world = world;
        scene_struct.water_level = 77.0f;
        yli::ontology::Entity* const joensuu_center_west_scene_entity = entity_factory->create_scene(scene_struct);
        std::cout << "Creating yli::ontology::Scene* joensuu_center_west_scene ...\n";
        yli::ontology::Scene* const joensuu_center_west_scene = dynamic_cast<yli::ontology::Scene*>(joensuu_center_west_scene_entity);

        if (joensuu_center_west_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        joensuu_center_west_scene->set_global_name("joensuu_center_west_scene");

        // Set `joensuu_center_west_scene` to be the currently active `Scene`.
        // my_universe->set_active_scene(joensuu_center_west_scene);

        joensuu_center_west_scene->set_turbo_factor(5.0f);
        joensuu_center_west_scene->set_twin_turbo_factor(100.0f);

        // Create the shader, store it in `joensuu_center_west_shader`.
        yli::ontology::ShaderStruct joensuu_center_west_shader_struct;
        joensuu_center_west_shader_struct.parent = joensuu_center_west_scene;
        joensuu_center_west_shader_struct.vertex_shader = "standard_shading.vert";
        joensuu_center_west_shader_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating yli::ontology::Entity* joensuu_center_west_shader_entity ...\n";
        yli::ontology::Entity* const joensuu_center_west_shader_entity = entity_factory->create_shader(joensuu_center_west_shader_struct);
        std::cout << "Creating yli::ontology::Shader* joensuu_center_west_shader ...\n";
        yli::ontology::Shader* const joensuu_center_west_shader = dynamic_cast<yli::ontology::Shader*>(joensuu_center_west_shader_entity);

        if (joensuu_center_west_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        joensuu_center_west_shader->set_global_name("joensuu_center_west_shader");

        // Create the material, store it in `joensuu_center_west_grass_material_struct`.
        yli::ontology::MaterialStruct joensuu_center_west_grass_material_struct;
        joensuu_center_west_grass_material_struct.shader = joensuu_center_west_shader;
        joensuu_center_west_grass_material_struct.texture_file_format = "bmp";
        joensuu_center_west_grass_material_struct.texture_filename = "GrassGreenTexture0002.bmp";

        std::cout << "Creating yli::ontology::Entity* joensuu_center_west_grass_material_entity ...\n";
        yli::ontology::Entity* const joensuu_center_west_grass_material_entity = entity_factory->create_material(joensuu_center_west_grass_material_struct);
        std::cout << "Creating yli::ontology::Material* joensuu_center_west_grass_material ...\n";
        yli::ontology::Material* const joensuu_center_west_grass_material = dynamic_cast<yli::ontology::Material*>(joensuu_center_west_grass_material_entity);

        if (joensuu_center_west_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        joensuu_center_west_grass_material->set_global_name("joensuu_center_west_grass_material");

        yli::ontology::SpeciesStruct joensuu_center_west_terrain_species_struct;
        joensuu_center_west_terrain_species_struct.scene = joensuu_center_west_scene;
        joensuu_center_west_terrain_species_struct.shader = joensuu_center_west_shader;
        joensuu_center_west_terrain_species_struct.material = joensuu_center_west_grass_material;
        joensuu_center_west_terrain_species_struct.model_file_format = "ASCII_grid";
        joensuu_center_west_terrain_species_struct.model_filename = "N5424G.asc"; // Joensuu center & western.
        joensuu_center_west_terrain_species_struct.light_position = glm::vec3(0, 100000, 100000);
        joensuu_center_west_terrain_species_struct.is_terrain = true;
        joensuu_center_west_terrain_species_struct.x_step = 4;
        joensuu_center_west_terrain_species_struct.z_step = 4;
        std::cout << "Creating yli::ontology::Entity* joensuu_center_west_terrain_species_entity ...\n";
        yli::ontology::Entity* const joensuu_center_west_terrain_species_entity = entity_factory->create_species(joensuu_center_west_terrain_species_struct);
        std::cout << "Creating yli::ontology::Species* joensuu_center_west_terrain_species ...\n";
        yli::ontology::Species* const joensuu_center_west_terrain_species = dynamic_cast<yli::ontology::Species*>(joensuu_center_west_terrain_species_entity);

        if (joensuu_center_west_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        joensuu_center_west_terrain_species->set_global_name("joensuu_center_west_terrain_species");

        // Create Joensuu center west terrain.
        yli::ontology::ObjectStruct joensuu_center_west_struct;
        joensuu_center_west_struct.species_parent = joensuu_center_west_terrain_species;
        joensuu_center_west_struct.cartesian_coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
        joensuu_center_west_struct.rotate_angle = 0.0f;
        joensuu_center_west_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        joensuu_center_west_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_object(joensuu_center_west_struct);

        // Create the material, store it in `orange_fur_material_joensuu`.
        yli::ontology::MaterialStruct orange_fur_material_joensuu_struct;
        orange_fur_material_joensuu_struct.shader = joensuu_center_west_shader;
        orange_fur_material_joensuu_struct.texture_file_format = "bmp";
        orange_fur_material_joensuu_struct.texture_filename = "orange_fur_texture.bmp";

        std::cout << "Creating yli::ontology::Entity* orange_fur_material_joensuu_entity ...\n";
        yli::ontology::Entity* const orange_fur_material_joensuu_entity = entity_factory->create_material(orange_fur_material_joensuu_struct);
        std::cout << "Creating yli::ontology::Material* orange_fur_material_joensuu ...\n";
        yli::ontology::Material* const orange_fur_material_joensuu = dynamic_cast<yli::ontology::Material*>(orange_fur_material_joensuu_entity);

        if (orange_fur_material_joensuu == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        orange_fur_material_joensuu->set_global_name("joensuu_center_west_orange_fur_material");

        yli::ontology::SpeciesStruct horse_species_struct;
        horse_species_struct.scene = joensuu_center_west_scene;
        horse_species_struct.shader = joensuu_center_west_shader;
        horse_species_struct.material = orange_fur_material_joensuu;
        horse_species_struct.model_file_format = "fbx";
        horse_species_struct.model_filename = "horse.fbx";
        horse_species_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* horse_species_entity ...\n";
        yli::ontology::Entity* const horse_species_entity = entity_factory->create_species(horse_species_struct);

        std::cout << "Creating yli::ontology::Species* horse_species ...\n";
        yli::ontology::Species* const horse_species = dynamic_cast<yli::ontology::Species*>(horse_species_entity);

        if (horse_species == nullptr)
        {
            std::cerr << "Failed to create horse Species.\n";
            return nullptr;
        }

        horse_species->set_global_name("horse_species");

        yli::ontology::ObjectStruct horse_object_struct1;
        horse_object_struct1.species_parent = horse_species;
        horse_object_struct1.original_scale_vector = glm::vec3(5.0f, 5.0f, 5.0f);
        horse_object_struct1.cartesian_coordinates = glm::vec3(2150.00f, 200.00f, 1990.00f);
        horse_object_struct1.rotate_angle = 0.00f;
        horse_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        horse_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        yli::ontology::Entity* const horse1_entity = entity_factory->create_object(horse_object_struct1);
        yli::ontology::Object* const horse1 = dynamic_cast<yli::ontology::Object*>(horse1_entity);

        if (horse1 == nullptr)
        {
            std::cerr << "Failed to create horse1 Object.\n";
            return nullptr;
        }

        horse1->set_global_name("horse1");

        yli::ontology::CameraStruct horse_camera_struct;
        horse_camera_struct.cartesian_coordinates = glm::vec3(2303.00f, 201.00f, 1822.00f);
        horse_camera_struct.parent = joensuu_center_west_scene;
        horse_camera_struct.yaw = -0.97f;
        horse_camera_struct.pitch = -0.18f;

        std::cout << "Creating yli::ontology::Entity* horse_camera_entity ...\n";
        yli::ontology::Entity* const horse_camera_entity = entity_factory->create_camera(horse_camera_struct);
        std::cout << "Creating yli::ontology::Camera* horse_camera ...\n";
        yli::ontology::Camera* const horse_camera = dynamic_cast<yli::ontology::Camera*>(horse_camera_entity);

        if (horse_camera == nullptr)
        {
            std::cerr << "Failed to create horse_camera Camera.\n";
            return nullptr;
        }

        horse_camera->set_global_name("horse_camera");

        return joensuu_center_west_scene_entity;
        // Joensuu `Scene` ends here.
    }
}
