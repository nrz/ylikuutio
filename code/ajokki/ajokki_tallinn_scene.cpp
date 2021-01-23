// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#include "ajokki_tallinn_scene.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
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
    yli::ontology::Entity* create_tallinn_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world)
    {
        // Tallinn `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* tallinn_scene_entity ...\n";
        yli::ontology::SceneStruct scene_struct;
        scene_struct.world = world;
        scene_struct.water_level = 0.9f;
        yli::ontology::Entity* const tallinn_scene_entity = entity_factory->create_scene(scene_struct);
        std::cout << "Creating yli::ontology::Scene* tallinn_scene ...\n";
        yli::ontology::Scene* const tallinn_scene = dynamic_cast<yli::ontology::Scene*>(tallinn_scene_entity);

        if (tallinn_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        tallinn_scene->set_global_name("tallinn_scene");

        // Set `tallinn_scene` to be the currently active `Scene`.
        // my_universe->set_active_scene(tallinn_scene);

        tallinn_scene->set_turbo_factor(5.0f);
        tallinn_scene->set_twin_turbo_factor(100.0f);

        // Create the shader, store it in `tallinn_shader`.
        yli::ontology::ShaderStruct tallinn_shader_struct;
        tallinn_shader_struct.parent = tallinn_scene;
        tallinn_shader_struct.vertex_shader = "standard_shading.vert";
        tallinn_shader_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating yli::ontology::Entity* tallinn_shader_entity ...\n";
        yli::ontology::Entity* const tallinn_shader_entity = entity_factory->create_shader(tallinn_shader_struct);
        std::cout << "Creating yli::ontology::Shader* tallinn_shader ...\n";
        yli::ontology::Shader* const tallinn_shader = dynamic_cast<yli::ontology::Shader*>(tallinn_shader_entity);

        if (tallinn_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        // Create the material, store it in `tallinn_grass_material`.
        yli::ontology::MaterialStruct tallinn_grass_material_struct;
        tallinn_grass_material_struct.shader = tallinn_shader;
        tallinn_grass_material_struct.texture_file_format = "bmp";
        tallinn_grass_material_struct.texture_filename = "GrassGreenTexture0002.bmp";

        std::cout << "Creating yli::ontology::Entity* tallinn_grass_material_entity ...\n";
        yli::ontology::Entity* const tallinn_grass_material_entity = entity_factory->create_material(tallinn_grass_material_struct);
        std::cout << "Creating yli::ontology::Material* tallinn_grass_material ...\n";
        yli::ontology::Material* const tallinn_grass_material = dynamic_cast<yli::ontology::Material*>(tallinn_grass_material_entity);

        if (tallinn_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        tallinn_grass_material->set_global_name("tallinn_grass_material");

        // Create the species, store it in `terrain_species`.
        yli::ontology::SpeciesStruct tallinn_terrain_species_struct;
        tallinn_terrain_species_struct.scene = tallinn_scene;
        tallinn_terrain_species_struct.shader = tallinn_shader;
        tallinn_terrain_species_struct.material = tallinn_grass_material;
        tallinn_terrain_species_struct.model_file_format = "SRTM";
        tallinn_terrain_species_struct.light_position = glm::vec3(0, 100000, 0);
        tallinn_terrain_species_struct.latitude = 59.437222f;  // in degrees.
        tallinn_terrain_species_struct.longitude = 24.745278f; // in degrees.
        tallinn_terrain_species_struct.is_terrain = true;
        tallinn_terrain_species_struct.x_step = 1;
        tallinn_terrain_species_struct.z_step = 1;

        std::cout << "Creating yli::ontology::Entity* tallinn_terrain_species_entity ...\n";
        yli::ontology::Entity* const tallinn_terrain_species_entity = entity_factory->create_species(tallinn_terrain_species_struct);
        std::cout << "Creating yli::ontology::Species* tallinn_terrain_species ...\n";
        yli::ontology::Species* const tallinn_terrain_species = dynamic_cast<yli::ontology::Species*>(tallinn_terrain_species_entity);

        if (tallinn_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        tallinn_terrain_species->set_global_name("tallinn_terrain_species");

        // Create tallinn terrain.
        yli::ontology::ObjectStruct tallinn_struct(tallinn_terrain_species);
        tallinn_struct.cartesian_coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_object(tallinn_struct);

        return tallinn_scene_entity;
        // Tallinn `Scene` ends here.
    }
}
