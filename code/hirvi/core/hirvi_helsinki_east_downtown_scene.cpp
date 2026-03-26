// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#include "hirvi_core.hpp"
#include "code/hirvi/data/datatype.hpp"
#include "code/ylikuutio/snippets/movable_controller_snippets.hpp"
#include "code/ylikuutio/snippets/keyboard_callback_snippets.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/movable_controller.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/cartesian_coordinates_module.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/texture_file_format.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"
#include "code/ylikuutio/ontology/movable_controller_struct.hpp"

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

    Scene* HirviCore::create_helsinki_scene()
    {
        // Helsinki `Scene` begins here.

        std::cout << "Creating Entity* helsinki_scene_entity ...\n";
        SceneStruct scene_struct;
        scene_struct.global_name = "helsinki_scene";
        scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
        scene_struct.water_level = 0.9f;
        std::cout << "Creating Scene* helsinki_scene ...\n";
        Scene* const helsinki_scene = this->entity_factory.create_scene(scene_struct);

        if (helsinki_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        helsinki_scene->set_turbo_factor(5.0f);
        helsinki_scene->set_twin_turbo_factor(100.0f);

        // Create the `CallbackEngine`s for the `MovableController`s.
        CallbackEngineStruct rest_callback_engine_struct;
        rest_callback_engine_struct.global_name = "rest_callback_engine";
        auto rest_callback_engine = this->entity_factory.create_callback_engine(rest_callback_engine_struct);
        rest_callback_engine->create_callback_object(&yli::snippets::rest);

        CallbackEngineStruct go_east_callback_engine_struct;
        go_east_callback_engine_struct.global_name = "go_east_callback_engine";
        auto go_east_callback_engine = this->entity_factory.create_callback_engine(go_east_callback_engine_struct);
        go_east_callback_engine->create_callback_object(&yli::snippets::go_east);

        CallbackEngineStruct go_west_callback_engine_struct;
        go_west_callback_engine_struct.global_name = "go_west_callback_engine";
        auto go_west_callback_engine = this->entity_factory.create_callback_engine(go_west_callback_engine_struct);
        go_west_callback_engine->create_callback_object(&yli::snippets::go_west);

        CallbackEngineStruct go_north_callback_engine_struct;
        go_north_callback_engine_struct.global_name = "go_north_callback_engine";
        auto go_north_callback_engine = this->entity_factory.create_callback_engine(go_north_callback_engine_struct);
        go_north_callback_engine->create_callback_object(&yli::snippets::go_north);

        CallbackEngineStruct go_south_callback_engine_struct;
        go_south_callback_engine_struct.global_name = "go_south_callback_engine";
        auto go_south_callback_engine = this->entity_factory.create_callback_engine(go_south_callback_engine_struct);
        go_south_callback_engine->create_callback_object(&yli::snippets::go_south);

        CallbackEngineStruct orient_to_east_callback_engine_struct;
        orient_to_east_callback_engine_struct.global_name = "orient_to_east_callback_engine";
        auto orient_to_east_callback_engine = this->entity_factory.create_callback_engine(orient_to_east_callback_engine_struct);
        orient_to_east_callback_engine->create_callback_object(&yli::snippets::orient_to_east);

        CallbackEngineStruct orient_to_west_callback_engine_struct;
        orient_to_west_callback_engine_struct.global_name = "orient_to_west_callback_engine";
        auto orient_to_west_callback_engine = this->entity_factory.create_callback_engine(orient_to_west_callback_engine_struct);
        orient_to_west_callback_engine->create_callback_object(&yli::snippets::orient_to_west);

        CallbackEngineStruct orient_to_north_callback_engine_struct;
        orient_to_north_callback_engine_struct.global_name = "orient_to_north_callback_engine";
        auto orient_to_north_callback_engine = this->entity_factory.create_callback_engine(orient_to_north_callback_engine_struct);
        orient_to_north_callback_engine->create_callback_object(&yli::snippets::orient_to_north);

        CallbackEngineStruct orient_to_south_callback_engine_struct;
        orient_to_south_callback_engine_struct.global_name = "orient_to_south_callback_engine";
        auto orient_to_south_callback_engine = this->entity_factory.create_callback_engine(orient_to_south_callback_engine_struct);
        orient_to_south_callback_engine->create_callback_object(&yli::snippets::orient_to_south);

        CallbackEngineStruct orient_and_go_east_callback_engine_struct;
        orient_and_go_east_callback_engine_struct.global_name = "orient_and_go_east_callback_engine";
        auto orient_and_go_east_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_east_callback_engine_struct);
        orient_and_go_east_callback_engine->create_callback_object(&yli::snippets::orient_and_go_east);

        CallbackEngineStruct orient_and_go_west_callback_engine_struct;
        orient_and_go_west_callback_engine_struct.global_name = "orient_and_go_west_callback_engine";
        auto orient_and_go_west_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_west_callback_engine_struct);
        orient_and_go_west_callback_engine->create_callback_object(&yli::snippets::orient_and_go_west);

        CallbackEngineStruct orient_and_go_north_callback_engine_struct;
        orient_and_go_north_callback_engine_struct.global_name = "orient_and_go_north_callback_engine";
        auto orient_and_go_north_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_north_callback_engine_struct);
        orient_and_go_north_callback_engine->create_callback_object(&yli::snippets::orient_and_go_north);

        CallbackEngineStruct orient_and_go_south_callback_engine_struct;
        orient_and_go_south_callback_engine_struct.global_name = "orient_and_go_south_callback_engine";
        auto orient_and_go_south_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_south_callback_engine_struct);
        orient_and_go_south_callback_engine->create_callback_object(&yli::snippets::orient_and_go_south);

        CallbackEngineStruct rotate_clockwise_callback_engine_struct;
        rotate_clockwise_callback_engine_struct.global_name = "rotate_clockwise_callback_engine";
        auto rotate_clockwise_callback_engine = this->entity_factory.create_callback_engine(rotate_clockwise_callback_engine_struct);
        rotate_clockwise_callback_engine->create_callback_object(&yli::snippets::rotate_clockwise);

        CallbackEngineStruct rotate_counterclockwise_callback_engine_struct;
        rotate_counterclockwise_callback_engine_struct.global_name = "rotate_counterclockwise_callback_engine";
        auto rotate_counterclockwise_callback_engine = this->entity_factory.create_callback_engine(rotate_counterclockwise_callback_engine_struct);
        rotate_counterclockwise_callback_engine->create_callback_object(&yli::snippets::rotate_counterclockwise);

        // Create the `MovableController`s.

        // `rest_movable_controller`.
        MovableControllerStruct rest_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("rest_callback_engine") };
        rest_movable_controller_struct.global_name = "rest_movable_controller";
        rest_movable_controller_struct.local_name = "rest";
        std::cout << "Creating MovableController* rest_movable_controller ...\n";
        MovableController* const rest_movable_controller = this->entity_factory.create_movable_controller(rest_movable_controller_struct);

        if (rest_movable_controller == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `go_east_movable_controller`.
        MovableControllerStruct go_east_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("go_east_callback_engine") };
        go_east_movable_controller_struct.global_name = "go_east_movable_controller";
        go_east_movable_controller_struct.local_name = "go_east";
        std::cout << "Creating MovableController* go_east_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(go_east_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `go_west_movable_controller`.
        MovableControllerStruct go_west_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("go_west_callback_engine") };
        go_west_movable_controller_struct.global_name = "go_west_movable_controller";
        go_west_movable_controller_struct.local_name = "go_west";
        std::cout << "Creating MovableController* go_west_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(go_west_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `go_north_movable_controller`.
        MovableControllerStruct go_north_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("go_north_callback_engine") };
        go_north_movable_controller_struct.global_name = "go_north_movable_controller";
        go_north_movable_controller_struct.local_name = "go_north";
        std::cout << "Creating MovableController* go_north_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(go_north_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `go_south_movable_controller`.
        MovableControllerStruct go_south_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("go_south_callback_engine") };
        go_south_movable_controller_struct.global_name = "go_south_movable_controller";
        go_south_movable_controller_struct.local_name = "go_south";
        std::cout << "Creating MovableController* go_south_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(go_south_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `orient_to_east_movable_controller`.
        MovableControllerStruct orient_to_east_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("orient_to_east_callback_engine") };
        orient_to_east_movable_controller_struct.global_name = "orient_to_east_movable_controller";
        orient_to_east_movable_controller_struct.local_name = "orient_to_east";
        std::cout << "Creating MovableController* orient_to_east_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(orient_to_east_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `orient_to_west_movable_controller`.
        MovableControllerStruct orient_to_west_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("orient_to_west_callback_engine") };
        orient_to_west_movable_controller_struct.global_name = "orient_to_west_movable_controller";
        orient_to_west_movable_controller_struct.local_name = "orient_to_west";
        std::cout << "Creating MovableController* orient_to_west_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(orient_to_west_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `orient_to_north_movable_controller`.
        MovableControllerStruct orient_to_north_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("orient_to_north_callback_engine") };
        orient_to_north_movable_controller_struct.global_name = "orient_to_north_movable_controller";
        orient_to_north_movable_controller_struct.local_name = "orient_to_north";
        std::cout << "Creating MovableController* orient_to_north_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(orient_to_north_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `orient_to_south_movable_controller`.
        MovableControllerStruct orient_to_south_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("orient_to_south_callback_engine") };
        orient_to_south_movable_controller_struct.global_name = "orient_to_south_movable_controller";
        orient_to_south_movable_controller_struct.local_name = "orient_to_south";
        std::cout << "Creating MovableController* orient_to_south_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(orient_to_south_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `rotate_clockwise_movable_controller`.
        MovableControllerStruct rotate_clockwise_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("rotate_clockwise_callback_engine") };
        rotate_clockwise_movable_controller_struct.global_name = "rotate_clockwise_movable_controller";
        rotate_clockwise_movable_controller_struct.local_name = "rotate_clockwise";
        std::cout << "Creating MovableController* rotate_clockwise_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(rotate_clockwise_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `orient_and_go_east_movable_controller`.
        MovableControllerStruct orient_and_go_east_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("orient_and_go_east_callback_engine") };
        orient_and_go_east_movable_controller_struct.global_name = "orient_and_go_east_movable_controller";
        orient_and_go_east_movable_controller_struct.local_name = "orient_and_go_east";
        std::cout << "Creating MovableController* orient_and_go_east_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(orient_and_go_east_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `orient_and_go_west_movable_controller`.
        MovableControllerStruct orient_and_go_west_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("orient_and_go_west_callback_engine") };
        orient_and_go_west_movable_controller_struct.global_name = "orient_and_go_west_movable_controller";
        orient_and_go_west_movable_controller_struct.local_name = "orient_and_go_west";
        std::cout << "Creating MovableController* orient_and_go_west_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(orient_and_go_west_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `orient_and_go_north_movable_controller`.
        MovableControllerStruct orient_and_go_north_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("orient_and_go_north_callback_engine") };
        orient_and_go_north_movable_controller_struct.global_name = "orient_and_go_north_movable_controller";
        orient_and_go_north_movable_controller_struct.local_name = "orient_and_go_north";
        std::cout << "Creating MovableController* orient_and_go_north_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(orient_and_go_north_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `orient_and_go_south_movable_controller`.
        MovableControllerStruct orient_and_go_south_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("orient_and_go_south_callback_engine") };
        orient_and_go_south_movable_controller_struct.global_name = "orient_and_go_south_movable_controller";
        orient_and_go_south_movable_controller_struct.local_name = "orient_and_go_south";
        std::cout << "Creating MovableController* orient_and_go_south_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(orient_and_go_south_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // `rotate_counterclockwise_movable_controller`.
        MovableControllerStruct rotate_counterclockwise_movable_controller_struct { Request<Scene>("helsinki_scene"), Request<CallbackEngine>("rotate_counterclockwise_callback_engine") };
        rotate_counterclockwise_movable_controller_struct.global_name = "rotate_counterclockwise_movable_controller";
        rotate_counterclockwise_movable_controller_struct.local_name = "rotate_counterclockwise";
        std::cout << "Creating MovableController* rotate_counterclockwise_movable_controller ...\n";
        if (this->entity_factory.create_movable_controller(rotate_counterclockwise_movable_controller_struct) == nullptr)
        {
            std::cerr << "Failed to create MovableController.\n";
            return nullptr;
        }

        // Create the pipeline, store it in `helsinki_pipeline`.
        PipelineStruct helsinki_pipeline_struct { Request<Scene>("helsinki_scene") };
        helsinki_pipeline_struct.global_name = "helsinki_pipeline";
        helsinki_pipeline_struct.local_name = "helsinki_regular_pipeline";
        helsinki_pipeline_struct.vertex_shader = "standard_shading.vert";
        helsinki_pipeline_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating Pipeline* helsinki_pipeline ...\n";
        Pipeline* const helsinki_pipeline = this->entity_factory.create_pipeline(helsinki_pipeline_struct);

        if (helsinki_pipeline == nullptr)
        {
            std::cerr << "Failed to create Pipeline.\n";
            return nullptr;
        }

        // Create the grayscale pipeline, store it in `helsinki_grayscale_pipeline`.
        PipelineStruct helsinki_grayscale_pipeline_struct { Request<Scene>("helsinki_scene") };
        helsinki_grayscale_pipeline_struct.global_name = "helsinki_grayscale_pipeline";
        helsinki_grayscale_pipeline_struct.local_name = "helsinki_grayscale_pipeline";
        helsinki_grayscale_pipeline_struct.vertex_shader = "standard_shading.vert";
        helsinki_grayscale_pipeline_struct.fragment_shader = "grayscale_standard_shading.frag";

        std::cout << "Creating Pipeline* helsinki_grayscale_pipeline ...\n";
        if (this->entity_factory.create_pipeline(helsinki_grayscale_pipeline_struct) == nullptr)
        {
            std::cerr << "Failed to create Pipeline.\n";
            return nullptr;
        }

        // Create the material, store it in `helsinki_grass_material`.
        MaterialStruct helsinki_grass_material_struct { Request(helsinki_scene), Request(helsinki_pipeline), yli::ontology::TextureFileFormat::PNG };
        helsinki_grass_material_struct.texture_filename = "GrassGreenTexture0002.png";

        std::cout << "Creating Material* helsinki_grass_material ...\n";
        Material* const helsinki_grass_material = this->entity_factory.create_material(helsinki_grass_material_struct);

        if (helsinki_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        helsinki_grass_material->set_global_name("helsinki_grass_material");

        // Create the material, store it in `orange_fur_material`.
        MaterialStruct orange_fur_material_struct { Request(helsinki_scene), Request(helsinki_pipeline), yli::ontology::TextureFileFormat::PNG };
        orange_fur_material_struct.texture_filename = "orange_fur_texture.png";

        std::cout << "Creating Material* orange_fur_material ...\n";
        Material* const orange_fur_material = this->entity_factory.create_material(orange_fur_material_struct);

        if (orange_fur_material == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        orange_fur_material->set_global_name("helsinki_orange_fur_material");

        SpeciesStruct helsinki_terrain_species_struct { Request(helsinki_scene), Request(helsinki_grass_material) };
        helsinki_terrain_species_struct.model_loader_struct.model_file_format = "ASCII_grid";
        helsinki_terrain_species_struct.model_loader_struct.model_filename = "L4133D.asc"; // Helsinki eastern downtown.
        helsinki_terrain_species_struct.model_loader_struct.x_step = 4;
        helsinki_terrain_species_struct.model_loader_struct.y_step = 4;
        std::cout << "Creating Species* helsinki_terrain_species ...\n";
        Species* const helsinki_terrain_species = this->entity_factory.create_species(helsinki_terrain_species_struct);

        if (helsinki_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        helsinki_terrain_species->set_global_name("helsinki_terrain_species");

        // Create Helsinki eastern downtown terrain.
        ObjectStruct helsinki_struct { Request(helsinki_scene) };
        helsinki_struct.species_master = Request(helsinki_terrain_species);
        helsinki_struct.cartesian_coordinates = CartesianCoordinatesModule(0.0f, 0.0f, 0.0f);
        this->entity_factory.create_object(helsinki_struct);

        SpeciesStruct cat_species_struct { Request(helsinki_scene), Request(orange_fur_material) };
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

        ObjectStruct cat1_object_struct { Request<Scene>("helsinki_scene"), Request(cat_species) };
        cat1_object_struct.global_name = "cat1";
        cat1_object_struct.local_name = "kissa1";
        cat1_object_struct.initial_rotate_vectors = { glm::vec3(0.0f, 0.0f, 1.0f) };
        cat1_object_struct.initial_rotate_angles = { 0.5f * static_cast<float>(std::numbers::pi) };
        cat1_object_struct.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
        cat1_object_struct.cartesian_coordinates = CartesianCoordinatesModule(500.00f, -1000.00f, 100.00f);

        if (this->entity_factory.create_object(cat1_object_struct) == nullptr)
        {
            std::cerr << "Failed to create cat1.\n";
            return nullptr;
        }

        ObjectStruct cat2_object_struct { Request<Scene>("helsinki_scene"), Request(rest_movable_controller), Request(cat_species) };
        cat2_object_struct.global_name = "cat2";
        cat2_object_struct.local_name = "kissa2";
        cat2_object_struct.movable_controller_master = Request(rest_movable_controller);
        cat2_object_struct.initial_rotate_vectors = { glm::vec3(0.0f, 0.0f, 1.0f) };
        cat2_object_struct.initial_rotate_angles = { 0.5f * static_cast<float>(std::numbers::pi) };
        cat2_object_struct.original_scale_vector = glm::vec3(15.0f, 15.0f, 15.0f);
        cat2_object_struct.cartesian_coordinates = CartesianCoordinatesModule(700.00f, -1200.00f, 100.00f);

        if (this->entity_factory.create_object(cat2_object_struct) == nullptr)
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

        HolobiontStruct turbo_polizei_png_police_car_struct1 { Request<Scene>("helsinki_scene"), Request(rest_movable_controller), Request(turbo_polizei_png_symbiosis) };
        turbo_polizei_png_police_car_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 0.0f, 1.0f) };
        turbo_polizei_png_police_car_struct1.initial_rotate_angles = { static_cast<float>(std::numbers::pi) };
        turbo_polizei_png_police_car_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_png_police_car_struct1.cartesian_coordinates = CartesianCoordinatesModule(85.00f, -160.00f, 30.00f);

        std::cout << "Creating hirvi::PoliceCar* turbo_polizei_png1 ...\n";
        yli::ontology::Holobiont* const turbo_polizei_png1 = this->entity_factory.create_holobiont(turbo_polizei_png_police_car_struct1);

        if (turbo_polizei_png1 == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png1.\n";
            return nullptr;
        }

        turbo_polizei_png1->set_global_name("turbo_polizei_png1");
        turbo_polizei_png1->set_local_name("sinivuokko1");

        HolobiontStruct turbo_polizei_png_police_car_struct2 { Request<Scene>("helsinki_scene"), Request(rest_movable_controller), Request(turbo_polizei_png_symbiosis) };
        turbo_polizei_png_police_car_struct2.initial_rotate_vectors = { glm::vec3(0.0f, 0.0f, 1.0f) };
        turbo_polizei_png_police_car_struct2.initial_rotate_angles = { static_cast<float>(std::numbers::pi) };
        turbo_polizei_png_police_car_struct2.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_png_police_car_struct2.cartesian_coordinates = CartesianCoordinatesModule(85.00f, -175.00f, 30.00f);

        std::cout << "Creating hirvi::PoliceCar* turbo_polizei_png2 ...\n";
        yli::ontology::Holobiont* const turbo_polizei_png2 = this->entity_factory.create_holobiont(turbo_polizei_png_police_car_struct2);

        if (turbo_polizei_png2 == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png2.\n";
            return nullptr;
        }

        turbo_polizei_png2->set_global_name("turbo_polizei_png2");
        turbo_polizei_png2->set_local_name("sinivuokko2");

        CameraStruct cat_camera_struct { Request<Scene>("helsinki_scene") };
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

        CameraStruct turbo_polizei_camera_struct { Request<Scene>("helsinki_scene") };
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

        return helsinki_scene;
        // Helsinki `Scene` ends here.
    }
}
