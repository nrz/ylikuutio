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

#include "code/hirvi/hirvi.hpp"
#include "code/hirvi/ontology/cat.hpp"
#include "code/hirvi/ontology/police_car.hpp"
#include "code/hirvi/data/datatype.hpp"
#include "code/ylikuutio/snippets/brain_snippets.hpp"
#include "code/ylikuutio/snippets/keyboard_callback_snippets.hpp"
#include "code/ylikuutio/ontology/locomotion_module_struct.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/cartesian_coordinates_module.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream>   // std::cout, std::cerr
#include <numbers>    // std::numbers::pi

namespace yli::ontology
{
    class Entity;
}

namespace hirvi
{
    using namespace yli::ontology;

    Scene* HirviApplication::create_helsinki_east_downtown_scene()
    {
        // Helsinki `Scene` begins here.

        std::cout << "Creating Entity* helsinki_east_downtown_scene_entity ...\n";
        SceneStruct scene_struct;
        scene_struct.global_name = "helsinki_east_downtown_scene";
        scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
        scene_struct.water_level = 0.9f;
        std::cout << "Creating Scene* helsinki_east_downtown_scene ...\n";
        Scene* const helsinki_east_downtown_scene = this->entity_factory.create_scene(scene_struct);

        if (helsinki_east_downtown_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        helsinki_east_downtown_scene->set_turbo_factor(5.0f);
        helsinki_east_downtown_scene->set_twin_turbo_factor(100.0f);

        // Create the `CallbackEngine`s for the `Brain`s.
        CallbackEngineStruct rest_callback_engine_struct;
        auto rest_callback_engine = this->entity_factory.create_callback_engine(rest_callback_engine_struct);
        rest_callback_engine->create_callback_object(&yli::snippets::rest);

        CallbackEngineStruct go_east_callback_engine_struct;
        auto go_east_callback_engine = this->entity_factory.create_callback_engine(go_east_callback_engine_struct);
        go_east_callback_engine->create_callback_object(&yli::snippets::go_east);

        CallbackEngineStruct go_west_callback_engine_struct;
        auto go_west_callback_engine = this->entity_factory.create_callback_engine(go_west_callback_engine_struct);
        go_west_callback_engine->create_callback_object(&yli::snippets::go_west);

        CallbackEngineStruct go_north_callback_engine_struct;
        auto go_north_callback_engine = this->entity_factory.create_callback_engine(go_north_callback_engine_struct);
        go_north_callback_engine->create_callback_object(&yli::snippets::go_north);

        CallbackEngineStruct go_south_callback_engine_struct;
        auto go_south_callback_engine = this->entity_factory.create_callback_engine(go_south_callback_engine_struct);
        go_south_callback_engine->create_callback_object(&yli::snippets::go_south);

        CallbackEngineStruct orient_to_east_callback_engine_struct;
        auto orient_to_east_callback_engine = this->entity_factory.create_callback_engine(orient_to_east_callback_engine_struct);
        orient_to_east_callback_engine->create_callback_object(&yli::snippets::orient_to_east);

        CallbackEngineStruct orient_to_west_callback_engine_struct;
        auto orient_to_west_callback_engine = this->entity_factory.create_callback_engine(orient_to_west_callback_engine_struct);
        orient_to_west_callback_engine->create_callback_object(&yli::snippets::orient_to_west);

        CallbackEngineStruct orient_to_north_callback_engine_struct;
        auto orient_to_north_callback_engine = this->entity_factory.create_callback_engine(orient_to_north_callback_engine_struct);
        orient_to_north_callback_engine->create_callback_object(&yli::snippets::orient_to_north);

        CallbackEngineStruct orient_to_south_callback_engine_struct;
        auto orient_to_south_callback_engine = this->entity_factory.create_callback_engine(orient_to_south_callback_engine_struct);
        orient_to_south_callback_engine->create_callback_object(&yli::snippets::orient_to_south);

        CallbackEngineStruct orient_and_go_east_callback_engine_struct;
        auto orient_and_go_east_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_east_callback_engine_struct);
        orient_and_go_east_callback_engine->create_callback_object(&yli::snippets::orient_and_go_east);

        CallbackEngineStruct orient_and_go_west_callback_engine_struct;
        auto orient_and_go_west_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_west_callback_engine_struct);
        orient_and_go_west_callback_engine->create_callback_object(&yli::snippets::orient_and_go_west);

        CallbackEngineStruct orient_and_go_north_callback_engine_struct;
        auto orient_and_go_north_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_north_callback_engine_struct);
        orient_and_go_north_callback_engine->create_callback_object(&yli::snippets::orient_and_go_north);

        CallbackEngineStruct orient_and_go_south_callback_engine_struct;
        auto orient_and_go_south_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_south_callback_engine_struct);
        orient_and_go_south_callback_engine->create_callback_object(&yli::snippets::orient_and_go_south);

        CallbackEngineStruct rotate_clockwise_callback_engine_struct;
        auto rotate_clockwise_callback_engine = this->entity_factory.create_callback_engine(rotate_clockwise_callback_engine_struct);
        rotate_clockwise_callback_engine->create_callback_object(&yli::snippets::rotate_clockwise);

        CallbackEngineStruct rotate_counterclockwise_callback_engine_struct;
        auto rotate_counterclockwise_callback_engine = this->entity_factory.create_callback_engine(rotate_counterclockwise_callback_engine_struct);
        rotate_counterclockwise_callback_engine->create_callback_object(&yli::snippets::rotate_counterclockwise);

        // Create the `Brain`s.

        // `rest_brain`.
        BrainStruct rest_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(rest_callback_engine) };
        rest_brain_struct.global_name = "rest_brain";
        rest_brain_struct.local_name = "rest";
        std::cout << "Creating Brain* rest_brain ...\n";
        Brain* const rest_brain = this->entity_factory.create_brain(rest_brain_struct);

        if (rest_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `go_east_brain`.
        BrainStruct go_east_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(go_east_callback_engine) };
        go_east_brain_struct.global_name = "go_east_brain";
        go_east_brain_struct.local_name = "go_east";
        std::cout << "Creating Brain* go_east_brain ...\n";
        if (this->entity_factory.create_brain(go_east_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `go_west_brain`.
        BrainStruct go_west_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(go_west_callback_engine) };
        go_west_brain_struct.global_name = "go_west_brain";
        go_west_brain_struct.local_name = "go_west";
        std::cout << "Creating Brain* go_west_brain ...\n";
        if (this->entity_factory.create_brain(go_west_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `go_north_brain`.
        BrainStruct go_north_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(go_north_callback_engine) };
        go_north_brain_struct.global_name = "go_north_brain";
        go_north_brain_struct.local_name = "go_north";
        std::cout << "Creating Brain* go_north_brain ...\n";
        if (this->entity_factory.create_brain(go_north_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `go_south_brain`.
        BrainStruct go_south_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(go_south_callback_engine) };
        go_south_brain_struct.global_name = "go_south_brain";
        go_south_brain_struct.local_name = "go_south";
        std::cout << "Creating Brain* go_south_brain ...\n";
        if (this->entity_factory.create_brain(go_south_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_to_east_brain`.
        BrainStruct orient_to_east_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(orient_to_east_callback_engine) };
        orient_to_east_brain_struct.global_name = "orient_to_east_brain";
        orient_to_east_brain_struct.local_name = "orient_to_east";
        std::cout << "Creating Brain* orient_to_east_brain ...\n";
        if (this->entity_factory.create_brain(orient_to_east_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_to_west_brain`.
        BrainStruct orient_to_west_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(orient_to_west_callback_engine) };
        orient_to_west_brain_struct.global_name = "orient_to_west_brain";
        orient_to_west_brain_struct.local_name = "orient_to_west";
        std::cout << "Creating Brain* orient_to_west_brain ...\n";
        if (this->entity_factory.create_brain(orient_to_west_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_to_north_brain`.
        BrainStruct orient_to_north_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(orient_to_north_callback_engine) };
        orient_to_north_brain_struct.global_name = "orient_to_north_brain";
        orient_to_north_brain_struct.local_name = "orient_to_north";
        std::cout << "Creating Brain* orient_to_north_brain ...\n";
        if (this->entity_factory.create_brain(orient_to_north_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_to_south_brain`.
        BrainStruct orient_to_south_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(orient_to_south_callback_engine) };
        orient_to_south_brain_struct.global_name = "orient_to_south_brain";
        orient_to_south_brain_struct.local_name = "orient_to_south";
        std::cout << "Creating Brain* orient_to_south_brain ...\n";
        if (this->entity_factory.create_brain(orient_to_south_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `rotate_clockwise_brain`.
        BrainStruct rotate_clockwise_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(rotate_clockwise_callback_engine) };
        rotate_clockwise_brain_struct.global_name = "rotate_clockwise_brain";
        rotate_clockwise_brain_struct.local_name = "rotate_clockwise";
        std::cout << "Creating Brain* rotate_clockwise_brain ...\n";
        if (this->entity_factory.create_brain(rotate_clockwise_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_and_go_east_brain`.
        BrainStruct orient_and_go_east_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(orient_and_go_east_callback_engine) };
        orient_and_go_east_brain_struct.global_name = "orient_and_go_east_brain";
        orient_and_go_east_brain_struct.local_name = "orient_and_go_east";
        std::cout << "Creating Brain* orient_and_go_east_brain ...\n";
        if (this->entity_factory.create_brain(orient_and_go_east_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_and_go_west_brain`.
        BrainStruct orient_and_go_west_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(orient_and_go_west_callback_engine) };
        orient_and_go_west_brain_struct.global_name = "orient_and_go_west_brain";
        orient_and_go_west_brain_struct.local_name = "orient_and_go_west";
        std::cout << "Creating Brain* orient_and_go_west_brain ...\n";
        if (this->entity_factory.create_brain(orient_and_go_west_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_and_go_north_brain`.
        BrainStruct orient_and_go_north_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(orient_and_go_north_callback_engine) };
        orient_and_go_north_brain_struct.global_name = "orient_and_go_north_brain";
        orient_and_go_north_brain_struct.local_name = "orient_and_go_north";
        std::cout << "Creating Brain* orient_and_go_north_brain ...\n";
        if (this->entity_factory.create_brain(orient_and_go_north_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_and_go_south_brain`.
        BrainStruct orient_and_go_south_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(orient_and_go_south_callback_engine) };
        orient_and_go_south_brain_struct.global_name = "orient_and_go_south_brain";
        orient_and_go_south_brain_struct.local_name = "orient_and_go_south";
        std::cout << "Creating Brain* orient_and_go_south_brain ...\n";
        if (this->entity_factory.create_brain(orient_and_go_south_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `rotate_counterclockwise_brain`.
        BrainStruct rotate_counterclockwise_brain_struct { Request<Scene>("helsinki_east_downtown_scene"), Request(rotate_counterclockwise_callback_engine) };
        rotate_counterclockwise_brain_struct.global_name = "rotate_counterclockwise_brain";
        rotate_counterclockwise_brain_struct.local_name = "rotate_counterclockwise";
        std::cout << "Creating Brain* rotate_counterclockwise_brain ...\n";
        if (this->entity_factory.create_brain(rotate_counterclockwise_brain_struct) == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // Create the pipeline, store it in `helsinki_east_downtown_pipeline`.
        PipelineStruct helsinki_east_downtown_pipeline_struct { Request<Scene>("helsinki_east_downtown_scene") };
        helsinki_east_downtown_pipeline_struct.global_name = "helsinki_east_downtown_pipeline";
        helsinki_east_downtown_pipeline_struct.local_name = "helsinki_regular_pipeline";
        helsinki_east_downtown_pipeline_struct.vertex_shader = "standard_shading.vert";
        helsinki_east_downtown_pipeline_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating Pipeline* helsinki_east_downtown_pipeline ...\n";
        Pipeline* const helsinki_east_downtown_pipeline = this->entity_factory.create_pipeline(helsinki_east_downtown_pipeline_struct);

        if (helsinki_east_downtown_pipeline == nullptr)
        {
            std::cerr << "Failed to create Pipeline.\n";
            return nullptr;
        }

        // Create the grayscale pipeline, store it in `helsinki_east_downtown_grayscale_pipeline`.
        PipelineStruct helsinki_east_downtown_grayscale_pipeline_struct { Request<Scene>("helsinki_east_downtown_scene") };
        helsinki_east_downtown_grayscale_pipeline_struct.global_name = "helsinki_east_downtown_grayscale_pipeline";
        helsinki_east_downtown_grayscale_pipeline_struct.local_name = "helsinki_grayscale_pipeline";
        helsinki_east_downtown_grayscale_pipeline_struct.vertex_shader = "standard_shading.vert";
        helsinki_east_downtown_grayscale_pipeline_struct.fragment_shader = "grayscale_standard_shading.frag";

        std::cout << "Creating Pipeline* helsinki_east_downtown_grayscale_pipeline ...\n";
        if (this->entity_factory.create_pipeline(helsinki_east_downtown_grayscale_pipeline_struct) == nullptr)
        {
            std::cerr << "Failed to create Pipeline.\n";
            return nullptr;
        }

        // Create the material, store it in `helsinki_east_downtown_grass_material`.
        MaterialStruct helsinki_east_downtown_grass_material_struct { Request(helsinki_east_downtown_scene), Request(helsinki_east_downtown_pipeline) };
        helsinki_east_downtown_grass_material_struct.texture_file_format = "png";
        helsinki_east_downtown_grass_material_struct.texture_filename = "GrassGreenTexture0002.png";

        std::cout << "Creating Material* helsinki_east_downtown_grass_material ...\n";
        Material* const helsinki_east_downtown_grass_material = this->entity_factory.create_material(helsinki_east_downtown_grass_material_struct);

        if (helsinki_east_downtown_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        helsinki_east_downtown_grass_material->set_global_name("helsinki_east_downtown_grass_material");

        // Create the material, store it in `orange_fur_material`.
        MaterialStruct orange_fur_material_struct { Request(helsinki_east_downtown_scene), Request(helsinki_east_downtown_pipeline) };
        orange_fur_material_struct.texture_file_format = "png";
        orange_fur_material_struct.texture_filename = "orange_fur_texture.png";

        std::cout << "Creating Material* orange_fur_material ...\n";
        Material* const orange_fur_material = this->entity_factory.create_material(orange_fur_material_struct);

        if (orange_fur_material == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        orange_fur_material->set_global_name("helsinki_east_downtown_orange_fur_material");

        SpeciesStruct helsinki_east_downtown_terrain_species_struct { Request(helsinki_east_downtown_scene), Request(helsinki_east_downtown_grass_material) };
        helsinki_east_downtown_terrain_species_struct.model_loader_struct.model_file_format = "ASCII_grid";
        helsinki_east_downtown_terrain_species_struct.model_loader_struct.model_filename = "L4133D.asc"; // Helsinki eastern downtown.
        helsinki_east_downtown_terrain_species_struct.model_loader_struct.x_step = 4;
        helsinki_east_downtown_terrain_species_struct.model_loader_struct.y_step = 4;
        std::cout << "Creating Species* helsinki_east_downtown_terrain_species ...\n";
        Species* const helsinki_east_downtown_terrain_species = this->entity_factory.create_species(helsinki_east_downtown_terrain_species_struct);

        if (helsinki_east_downtown_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        helsinki_east_downtown_terrain_species->set_global_name("helsinki_east_downtown_terrain_species");

        // Create Helsinki eastern downtown terrain.
        ObjectStruct helsinki_east_downtown_struct { Request(helsinki_east_downtown_scene) };
        helsinki_east_downtown_struct.species_master = Request(helsinki_east_downtown_terrain_species);
        helsinki_east_downtown_struct.cartesian_coordinates = CartesianCoordinatesModule(0.0f, 0.0f, 0.0f);
        this->entity_factory.create_object(helsinki_east_downtown_struct);

        SpeciesStruct cat_species_struct { Request(helsinki_east_downtown_scene), Request(orange_fur_material) };
        cat_species_struct.global_name = "cat_species";
        cat_species_struct.local_name = "cat";
        cat_species_struct.model_loader_struct.model_file_format = "fbx";
        cat_species_struct.model_loader_struct.model_filename = "cat.fbx";

        std::cout << "Creating Species* cat_species ...\n";
        Species* const cat_species = this->entity_factory.create_species(cat_species_struct);

        if (cat_species == nullptr)
        {
            std::cerr << "Failed to create cat Species.\n";
            return nullptr;
        }

        ObjectStruct cat1_object_struct(
                Request<Scene>("helsinki_east_downtown_scene"),
                Request(cat_species));
        cat1_object_struct.global_name = "cat1";
        cat1_object_struct.local_name = "kissa1";
        cat1_object_struct.initial_rotate_vectors = { glm::vec3(0.0f, 0.0f, 1.0f) };
        cat1_object_struct.initial_rotate_angles = { 0.5f * static_cast<float>(std::numbers::pi) };
        cat1_object_struct.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
        cat1_object_struct.cartesian_coordinates = CartesianCoordinatesModule(500.00f, -1000.00f, 100.00f);

        LocomotionModuleStruct cat1_walk_struct(1.0f); // 3.6 km/h.
        LocomotionModuleStruct cat1_trot_struct(5.0f);
        LocomotionModuleStruct cat1_canter_struct(10.0f);
        LocomotionModuleStruct cat1_gallop_struct(12.5f); // 45 km/h.
        LocomotionModuleStruct cat1_climb_struct;

        if (this->entity_factory.create_object_derivative<
                hirvi::Cat,
                CatMemoryAllocator>(
                    hirvi::Datatype::CAT,
                    cat1_object_struct,
                    cat1_walk_struct,
                    cat1_trot_struct,
                    cat1_canter_struct,
                    cat1_gallop_struct,
                    cat1_climb_struct) == nullptr)
        {
            std::cerr << "Failed to create cat1.\n";
            return nullptr;
        }

        ObjectStruct cat2_object_struct(
                Request<Scene>("helsinki_east_downtown_scene"),
                Request(rest_brain),
                Request(cat_species));
        cat2_object_struct.global_name = "cat2";
        cat2_object_struct.local_name = "kissa2";
        cat2_object_struct.brain_master = Request(rest_brain);
        cat2_object_struct.initial_rotate_vectors = { glm::vec3(0.0f, 0.0f, 1.0f) };
        cat2_object_struct.initial_rotate_angles = { 0.5f * static_cast<float>(std::numbers::pi) };
        cat2_object_struct.original_scale_vector = glm::vec3(15.0f, 15.0f, 15.0f);
        cat2_object_struct.cartesian_coordinates = CartesianCoordinatesModule(700.00f, -1200.00f, 100.00f);

        LocomotionModuleStruct cat2_walk_struct(1.0f); // 3.6 km/h.
        LocomotionModuleStruct cat2_trot_struct(5.0f);
        LocomotionModuleStruct cat2_canter_struct(10.0f);
        LocomotionModuleStruct cat2_gallop_struct(12.5f); // 45 km/h.
        LocomotionModuleStruct cat2_climb_struct;

        hirvi::Cat* const cat2 = this->entity_factory.create_object_derivative<
            hirvi::Cat,
            CatMemoryAllocator>(
                    hirvi::Datatype::CAT,
                    cat2_object_struct,
                    cat2_walk_struct,
                    cat2_trot_struct,
                    cat2_canter_struct,
                    cat2_gallop_struct,
                    cat2_climb_struct);

        if (cat2 == nullptr)
        {
            std::cerr << "Failed to create cat2.\n";
            return nullptr;
        }

        Entity* const turbo_polizei_png_symbiosis_entity = this->get_universe().get_entity("turbo_polizei_png_symbiosis");

        auto const turbo_polizei_png_symbiosis = dynamic_cast<Symbiosis*>(turbo_polizei_png_symbiosis_entity);

        if (turbo_polizei_png_symbiosis == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png_symbiosis.\n";
            return nullptr;
        }

        HolobiontStruct turbo_polizei_png_police_car_struct1(
                Request<Scene>("helsinki_east_downtown_scene"),
                Request(rest_brain),
                Request(turbo_polizei_png_symbiosis));
        turbo_polizei_png_police_car_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 0.0f, 1.0f) };
        turbo_polizei_png_police_car_struct1.initial_rotate_angles = { static_cast<float>(std::numbers::pi) };
        turbo_polizei_png_police_car_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_png_police_car_struct1.cartesian_coordinates = CartesianCoordinatesModule(85.00f, -160.00f, 30.00f);

        LocomotionModuleStruct road_vehicle_struct1;

        std::cout << "Creating hirvi::PoliceCar* turbo_polizei_png1 ...\n";
        hirvi::PoliceCar* const turbo_polizei_png1 = this->entity_factory.create_holobiont_derivative<
            hirvi::PoliceCar,
            PoliceCarMemoryAllocator>(
                    hirvi::Datatype::POLICE_CAR,
                    turbo_polizei_png_police_car_struct1,
                    road_vehicle_struct1);

        if (turbo_polizei_png1 == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png1.\n";
            return nullptr;
        }

        turbo_polizei_png1->set_global_name("turbo_polizei_png1");
        turbo_polizei_png1->set_local_name("sinivuokko1");

        HolobiontStruct turbo_polizei_png_police_car_struct2(
                Request<Scene>("helsinki_east_downtown_scene"),
                Request(rest_brain),
                Request(turbo_polizei_png_symbiosis));
        turbo_polizei_png_police_car_struct2.initial_rotate_vectors = { glm::vec3(0.0f, 0.0f, 1.0f) };
        turbo_polizei_png_police_car_struct2.initial_rotate_angles = { static_cast<float>(std::numbers::pi) };
        turbo_polizei_png_police_car_struct2.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_png_police_car_struct2.cartesian_coordinates = CartesianCoordinatesModule(85.00f, -175.00f, 30.00f);

        LocomotionModuleStruct road_vehicle_struct2;

        std::cout << "Creating hirvi::PoliceCar* turbo_polizei_png2 ...\n";
        hirvi::PoliceCar* const turbo_polizei_png2 = this->entity_factory.create_holobiont_derivative<
            hirvi::PoliceCar,
            PoliceCarMemoryAllocator>(
                    hirvi::Datatype::POLICE_CAR,
                    turbo_polizei_png_police_car_struct2,
                    road_vehicle_struct2);

        if (turbo_polizei_png2 == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png2.\n";
            return nullptr;
        }

        turbo_polizei_png2->set_global_name("turbo_polizei_png2");
        turbo_polizei_png2->set_local_name("sinivuokko2");

        CameraStruct cat_camera_struct { Request<Scene>("helsinki_east_downtown_scene") };
        cat_camera_struct.cartesian_coordinates = CartesianCoordinatesModule(800.00f, -950.00f, 400.00f);
        cat_camera_struct.orientation.yaw = -0.90f;
        cat_camera_struct.orientation.pitch = -1.00f;

        std::cout << "Creating Camera* cat_camera ...\n";
        Camera* const cat_camera = this->entity_factory.create_camera(cat_camera_struct);

        if (cat_camera == nullptr)
        {
            std::cerr << "Failed to create cat_camera.\n";
            return nullptr;
        }

        cat_camera->set_global_name("cat_camera");

        CameraStruct turbo_polizei_camera_struct { Request<Scene>("helsinki_east_downtown_scene") };
        turbo_polizei_camera_struct.cartesian_coordinates = CartesianCoordinatesModule(87.00f, -169.00f, 28.00f);
        turbo_polizei_camera_struct.orientation.yaw = -0.45f;
        turbo_polizei_camera_struct.orientation.pitch = -0.05f;

        std::cout << "Creating Camera* turbo_polizei_camera ...\n";
        Camera* const turbo_polizei_camera = this->entity_factory.create_camera(turbo_polizei_camera_struct);

        if (turbo_polizei_camera == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_camera.\n";
            return nullptr;
        }

        turbo_polizei_camera->set_global_name("turbo_polizei_camera");

        return helsinki_east_downtown_scene;
        // Helsinki `Scene` ends here.
    }
}
