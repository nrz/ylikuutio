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

#include "ajokki_altiplano_scene.hpp"
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
        class Entity;
    }
}

namespace ajokki
{
    yli::ontology::Entity* create_altiplano_scene(yli::ontology::EntityFactory* const entity_factory)
    {
        // altiplano `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* altiplano_scene_entity ...\n";
        yli::ontology::SceneStruct scene_struct;
        scene_struct.water_level = 3815.51f;
        yli::ontology::Entity* const altiplano_scene_entity = entity_factory->create_scene(scene_struct);
        std::cout << "Creating yli::ontology::Scene* altiplano_scene ...\n";
        yli::ontology::Scene* const altiplano_scene = dynamic_cast<yli::ontology::Scene*>(altiplano_scene_entity);

        if (altiplano_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        altiplano_scene->set_global_name("altiplano_scene");

        // Set `altiplano_scene` to be the currently active `Scene`.
        // my_universe->set_active_scene(altiplano_scene);

        altiplano_scene->set_turbo_factor(5.0f);
        altiplano_scene->set_twin_turbo_factor(100.0f);

        // Create the shader, store it in `altiplano_shader`.
        yli::ontology::ShaderStruct altiplano_shader_struct;
        altiplano_shader_struct.parent = altiplano_scene;
        altiplano_shader_struct.vertex_shader = "standard_shading.vert";
        altiplano_shader_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating yli::ontology::Entity* altiplano_shader_entity ...\n";
        yli::ontology::Entity* const altiplano_shader_entity = entity_factory->create_shader(altiplano_shader_struct);
        std::cout << "Creating yli::ontology::Shader* altiplano_shader ...\n";
        yli::ontology::Shader* const altiplano_shader = dynamic_cast<yli::ontology::Shader*>(altiplano_shader_entity);

        if (altiplano_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        // Create the material, store it in `altiplano_grass_material`.
        yli::ontology::MaterialStruct altiplano_grass_material_struct;
        altiplano_grass_material_struct.shader = altiplano_shader;
        altiplano_grass_material_struct.texture_file_format = "png";
        altiplano_grass_material_struct.texture_filename = "GrassGreenTexture0002.png";

        std::cout << "Creating yli::ontology::Entity* altiplano_grass_material_entity ...\n";
        yli::ontology::Entity* const altiplano_grass_material_entity = entity_factory->create_material(altiplano_grass_material_struct);
        std::cout << "Creating yli::ontology::Material* altiplano_grass_material ...\n";
        yli::ontology::Material* const altiplano_grass_material = dynamic_cast<yli::ontology::Material*>(altiplano_grass_material_entity);

        if (altiplano_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        altiplano_grass_material->set_global_name("altiplano_grass_material");

        // Create the species, store it in `terrain_species`.
        yli::ontology::SpeciesStruct altiplano_terrain_species_struct;
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
        yli::ontology::Entity* const altiplano_terrain_species_entity = entity_factory->create_species(altiplano_terrain_species_struct);
        std::cout << "Creating yli::ontology::Species* altiplano_terrain_species ...\n";
        yli::ontology::Species* const altiplano_terrain_species = dynamic_cast<yli::ontology::Species*>(altiplano_terrain_species_entity);

        if (altiplano_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        altiplano_terrain_species->set_global_name("altiplano_terrain_species");

        // Create altiplano terrain.
        yli::ontology::ObjectStruct altiplano_struct(altiplano_terrain_species);
        altiplano_struct.scene = altiplano_scene;
        altiplano_struct.cartesian_coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_object(altiplano_struct);

        return altiplano_scene_entity;
        // altiplano `Scene` ends here.
    }
}
