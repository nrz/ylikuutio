// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "code/ajokki/ajokki.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/cartesian_coordinates_module.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream>   // std::cout, std::cerr
#include <numbers>    // std::numbers::pi

namespace yli
{
    namespace ontology
    {
        class Entity;
    }
}

namespace ajokki
{
    yli::ontology::Scene* AjokkiApplication::create_joensuu_center_west_scene()
    {
        // Joensuu `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* joensuu_center_west_scene_entity ...\n";
        yli::ontology::SceneStruct scene_struct;
        scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
        scene_struct.water_level = 77.0f;
        std::cout << "Creating yli::ontology::Scene* joensuu_center_west_scene ...\n";
        yli::ontology::Scene* const joensuu_center_west_scene = this->entity_factory.create_scene(scene_struct);

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

        // Create the pipeline, store it in `joensuu_center_west_pipeline`.
        yli::ontology::PipelineStruct joensuu_center_west_pipeline_struct(joensuu_center_west_scene);
        joensuu_center_west_pipeline_struct.global_name = "joensuu_center_west_pipeline";
        joensuu_center_west_pipeline_struct.local_name = "joensuu_regular_pipeline";
        joensuu_center_west_pipeline_struct.vertex_shader = "standard_shading.vert";
        joensuu_center_west_pipeline_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating yli::ontology::Pipeline* joensuu_center_west_pipeline ...\n";
        yli::ontology::Pipeline* const joensuu_center_west_pipeline = this->entity_factory.create_pipeline(joensuu_center_west_pipeline_struct);

        if (joensuu_center_west_pipeline == nullptr)
        {
            std::cerr << "Failed to create Pipeline.\n";
            return nullptr;
        }

        joensuu_center_west_pipeline->set_global_name("joensuu_center_west_pipeline");

        // Create the material, store it in `joensuu_center_west_grass_material_struct`.
        yli::ontology::MaterialStruct joensuu_center_west_grass_material_struct(joensuu_center_west_scene, joensuu_center_west_pipeline);
        joensuu_center_west_grass_material_struct.texture_file_format = "png";
        joensuu_center_west_grass_material_struct.texture_filename = "GrassGreenTexture0002.png";

        std::cout << "Creating yli::ontology::Material* joensuu_center_west_grass_material ...\n";
        yli::ontology::Material* const joensuu_center_west_grass_material = this->entity_factory.create_material(joensuu_center_west_grass_material_struct);

        if (joensuu_center_west_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        joensuu_center_west_grass_material->set_global_name("joensuu_center_west_grass_material");

        yli::ontology::SpeciesStruct joensuu_center_west_terrain_species_struct;
        joensuu_center_west_terrain_species_struct.parent = joensuu_center_west_scene;
        joensuu_center_west_terrain_species_struct.pipeline = joensuu_center_west_pipeline;
        joensuu_center_west_terrain_species_struct.material_or_symbiont_material = joensuu_center_west_grass_material;
        joensuu_center_west_terrain_species_struct.model_file_format = "ASCII_grid";
        joensuu_center_west_terrain_species_struct.model_filename = "N5424G.asc"; // Joensuu center & western.
        joensuu_center_west_terrain_species_struct.x_step = 4;
        joensuu_center_west_terrain_species_struct.y_step = 4;
        std::cout << "Creating yli::ontology::Species* joensuu_center_west_terrain_species ...\n";
        yli::ontology::Species* const joensuu_center_west_terrain_species = this->entity_factory.create_species(joensuu_center_west_terrain_species_struct);

        if (joensuu_center_west_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        joensuu_center_west_terrain_species->set_global_name("joensuu_center_west_terrain_species");

        // Create Joensuu center west terrain.
        yli::ontology::ObjectStruct joensuu_center_west_struct(joensuu_center_west_scene);
        joensuu_center_west_struct.mesh_master = joensuu_center_west_terrain_species;
        joensuu_center_west_struct.cartesian_coordinates = yli::ontology::CartesianCoordinatesModule(0.0f, 0.0f, 0.0f);
        this->entity_factory.create_object(joensuu_center_west_struct);

        // Create the material, store it in `orange_fur_material_joensuu`.
        yli::ontology::MaterialStruct orange_fur_material_joensuu_struct(joensuu_center_west_scene, joensuu_center_west_pipeline);
        orange_fur_material_joensuu_struct.texture_file_format = "png";
        orange_fur_material_joensuu_struct.texture_filename = "orange_fur_texture.png";

        std::cout << "Creating yli::ontology::Material* orange_fur_material_joensuu ...\n";
        yli::ontology::Material* const orange_fur_material_joensuu = this->entity_factory.create_material(orange_fur_material_joensuu_struct);

        if (orange_fur_material_joensuu == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        orange_fur_material_joensuu->set_global_name("joensuu_center_west_orange_fur_material");

        yli::ontology::SpeciesStruct horse_species_struct;
        horse_species_struct.parent = joensuu_center_west_scene;
        horse_species_struct.pipeline = joensuu_center_west_pipeline;
        horse_species_struct.material_or_symbiont_material = orange_fur_material_joensuu;
        horse_species_struct.model_file_format = "fbx";
        horse_species_struct.model_filename = "horse.fbx";

        std::cout << "Creating yli::ontology::Species* horse_species ...\n";
        yli::ontology::Species* const horse_species = this->entity_factory.create_species(horse_species_struct);

        if (horse_species == nullptr)
        {
            std::cerr << "Failed to create horse Species.\n";
            return nullptr;
        }

        horse_species->set_global_name("horse_species");

        yli::ontology::ObjectStruct horse_object_struct1(joensuu_center_west_scene);
        horse_object_struct1.mesh_master = horse_species;
        horse_object_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 0.0f, 1.0f) };
        horse_object_struct1.initial_rotate_angles = { 0.5f * static_cast<float>(std::numbers::pi) };
        horse_object_struct1.original_scale_vector = glm::vec3(5.0f, 5.0f, 5.0f);
        horse_object_struct1.cartesian_coordinates = yli::ontology::CartesianCoordinatesModule(2150.00f, -1990.00f, 200.00f);
        yli::ontology::Entity* const horse1_entity = this->entity_factory.create_object(horse_object_struct1);
        auto const horse1 = dynamic_cast<yli::ontology::Object*>(horse1_entity);

        if (horse1 == nullptr)
        {
            std::cerr << "Failed to create horse1 Object.\n";
            return nullptr;
        }

        horse1->set_global_name("horse1");

        yli::ontology::CameraStruct horse_camera_struct;
        horse_camera_struct.scene = joensuu_center_west_scene;
        horse_camera_struct.cartesian_coordinates = yli::ontology::CartesianCoordinatesModule(2303.00f, -1822.00f, 201.00f);
        horse_camera_struct.orientation.yaw = -0.97f;
        horse_camera_struct.orientation.pitch = -0.18f;

        std::cout << "Creating yli::ontology::Camera* horse_camera ...\n";
        yli::ontology::Camera* const horse_camera = this->entity_factory.create_camera(horse_camera_struct);

        if (horse_camera == nullptr)
        {
            std::cerr << "Failed to create horse_camera Camera.\n";
            return nullptr;
        }

        horse_camera->set_global_name("horse_camera");

        return joensuu_center_west_scene;
        // Joensuu `Scene` ends here.
    }
}
