// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#include "hirvi_helsinki_east_downtown_scene.hpp"
#include "cat.hpp"
#include "police_car.hpp"
#include "code/ylikuutio/snippets/brain_snippets.hpp"
#include "code/ylikuutio/snippets/keyboard_callback_snippets.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/data/pi.hpp"
#include "code/ylikuutio/ontology/locomotion_module_struct.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/terrain.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/custom_entity_factory.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
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
#include <iostream>   // std::cout, std::cin, std::cerr
#include <memory>     // std::make_shared, std::shared_ptr
#include <string>     // std::string

namespace yli::ontology
{
    class Entity;
    class Universe;
    class CustomEntityFactory;
}

namespace hirvi
{
    yli::ontology::Entity* create_helsinki_east_downtown_scene(
            yli::ontology::Universe& universe,
            yli::ontology::CustomEntityFactory* const entity_factory)
    {
        // Helsinki `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_scene_entity ...\n";
        yli::ontology::SceneStruct scene_struct;
        scene_struct.global_name = "helsinki_east_downtown_scene";
        scene_struct.light_position = { 0.0f, 100000.0f, 100000.0f, 1.0f };
        scene_struct.water_level = 0.9f;
        yli::ontology::Entity* const helsinki_east_downtown_scene_entity = entity_factory->create_scene(scene_struct);
        std::cout << "Creating yli::ontology::Scene* helsinki_east_downtown_scene ...\n";
        yli::ontology::Scene* const helsinki_east_downtown_scene = dynamic_cast<yli::ontology::Scene*>(helsinki_east_downtown_scene_entity);

        if (helsinki_east_downtown_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        helsinki_east_downtown_scene->set_turbo_factor(5.0f);
        helsinki_east_downtown_scene->set_twin_turbo_factor(100.0f);

        // Create the `CallbackEngine`s for the `Brain`s.
        std::shared_ptr<yli::callback::CallbackEngine> rest_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        rest_callback_engine->create_callback_object(&yli::snippets::rest);

        std::shared_ptr<yli::callback::CallbackEngine> go_east_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        go_east_callback_engine->create_callback_object(&yli::snippets::go_east);

        std::shared_ptr<yli::callback::CallbackEngine> go_west_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        go_west_callback_engine->create_callback_object(&yli::snippets::go_west);

        std::shared_ptr<yli::callback::CallbackEngine> go_north_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        go_north_callback_engine->create_callback_object(&yli::snippets::go_north);

        std::shared_ptr<yli::callback::CallbackEngine> go_south_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        go_south_callback_engine->create_callback_object(&yli::snippets::go_south);

        std::shared_ptr<yli::callback::CallbackEngine> orient_to_east_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        orient_to_east_callback_engine->create_callback_object(&yli::snippets::orient_to_east);

        std::shared_ptr<yli::callback::CallbackEngine> orient_to_west_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        orient_to_west_callback_engine->create_callback_object(&yli::snippets::orient_to_west);

        std::shared_ptr<yli::callback::CallbackEngine> orient_to_north_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        orient_to_north_callback_engine->create_callback_object(&yli::snippets::orient_to_north);

        std::shared_ptr<yli::callback::CallbackEngine> orient_to_south_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        orient_to_south_callback_engine->create_callback_object(&yli::snippets::orient_to_south);

        std::shared_ptr<yli::callback::CallbackEngine> orient_and_go_east_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        orient_and_go_east_callback_engine->create_callback_object(&yli::snippets::orient_and_go_east);

        std::shared_ptr<yli::callback::CallbackEngine> orient_and_go_west_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        orient_and_go_west_callback_engine->create_callback_object(&yli::snippets::orient_and_go_west);

        std::shared_ptr<yli::callback::CallbackEngine> orient_and_go_north_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        orient_and_go_north_callback_engine->create_callback_object(&yli::snippets::orient_and_go_north);

        std::shared_ptr<yli::callback::CallbackEngine> orient_and_go_south_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        orient_and_go_south_callback_engine->create_callback_object(&yli::snippets::orient_and_go_south);

        std::shared_ptr<yli::callback::CallbackEngine> rotate_clockwise_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        rotate_clockwise_callback_engine->create_callback_object(&yli::snippets::rotate_clockwise);

        std::shared_ptr<yli::callback::CallbackEngine> rotate_counterclockwise_callback_engine = std::make_shared<yli::callback::CallbackEngine>(universe);
        rotate_counterclockwise_callback_engine->create_callback_object(&yli::snippets::rotate_counterclockwise);

        // Create the `Brain`s.

        // `rest_brain`.
        yli::ontology::BrainStruct rest_brain_struct;
        rest_brain_struct.parent = helsinki_east_downtown_scene;
        rest_brain_struct.global_name = "rest_brain";
        rest_brain_struct.local_name = "rest";
        rest_brain_struct.callback_engine = rest_callback_engine;
        std::cout << "Creating yli::ontology::Entity* rest_brain_entity ...\n";
        yli::ontology::Entity* const rest_brain_entity = entity_factory->create_brain(rest_brain_struct);
        std::cout << "Creating yli::ontology::Brain* rest_brain ...\n";
        yli::ontology::Brain* const rest_brain = dynamic_cast<yli::ontology::Brain*>(rest_brain_entity);

        if (rest_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `go_east_brain`.
        yli::ontology::BrainStruct go_east_brain_struct;
        go_east_brain_struct.parent = helsinki_east_downtown_scene;
        go_east_brain_struct.global_name = "go_east_brain";
        go_east_brain_struct.local_name = "go_east";
        go_east_brain_struct.callback_engine = go_east_callback_engine;
        std::cout << "Creating yli::ontology::Entity* go_east_brain_entity ...\n";
        yli::ontology::Entity* const go_east_brain_entity = entity_factory->create_brain(go_east_brain_struct);
        std::cout << "Creating yli::ontology::Brain* go_east_brain ...\n";
        yli::ontology::Brain* const go_east_brain = dynamic_cast<yli::ontology::Brain*>(go_east_brain_entity);

        if (go_east_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `go_west_brain`.
        yli::ontology::BrainStruct go_west_brain_struct;
        go_west_brain_struct.parent = helsinki_east_downtown_scene;
        go_west_brain_struct.global_name = "go_west_brain";
        go_west_brain_struct.local_name = "go_west";
        go_west_brain_struct.callback_engine = go_west_callback_engine;
        std::cout << "Creating yli::ontology::Entity* go_west_brain_entity ...\n";
        yli::ontology::Entity* const go_west_brain_entity = entity_factory->create_brain(go_west_brain_struct);
        std::cout << "Creating yli::ontology::Brain* go_west_brain ...\n";
        yli::ontology::Brain* const go_west_brain = dynamic_cast<yli::ontology::Brain*>(go_west_brain_entity);

        if (go_west_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `go_north_brain`.
        yli::ontology::BrainStruct go_north_brain_struct;
        go_north_brain_struct.parent = helsinki_east_downtown_scene;
        go_north_brain_struct.global_name = "go_north_brain";
        go_north_brain_struct.local_name = "go_north";
        go_north_brain_struct.callback_engine = go_north_callback_engine;
        std::cout << "Creating yli::ontology::Entity* go_north_brain_entity ...\n";
        yli::ontology::Entity* const go_north_brain_entity = entity_factory->create_brain(go_north_brain_struct);
        std::cout << "Creating yli::ontology::Brain* go_north_brain ...\n";
        yli::ontology::Brain* const go_north_brain = dynamic_cast<yli::ontology::Brain*>(go_north_brain_entity);

        if (go_north_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `go_south_brain`.
        yli::ontology::BrainStruct go_south_brain_struct;
        go_south_brain_struct.parent = helsinki_east_downtown_scene;
        go_south_brain_struct.global_name = "go_south_brain";
        go_south_brain_struct.local_name = "go_south";
        go_south_brain_struct.callback_engine = go_south_callback_engine;
        std::cout << "Creating yli::ontology::Entity* go_south_brain_entity ...\n";
        yli::ontology::Entity* const go_south_brain_entity = entity_factory->create_brain(go_south_brain_struct);
        std::cout << "Creating yli::ontology::Brain* go_south_brain ...\n";
        yli::ontology::Brain* const go_south_brain = dynamic_cast<yli::ontology::Brain*>(go_south_brain_entity);

        if (go_south_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_to_east_brain`.
        yli::ontology::BrainStruct orient_to_east_brain_struct;
        orient_to_east_brain_struct.parent = helsinki_east_downtown_scene;
        orient_to_east_brain_struct.global_name = "orient_to_east_brain";
        orient_to_east_brain_struct.local_name = "orient_to_east";
        orient_to_east_brain_struct.callback_engine = orient_to_east_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_to_east_brain_entity ...\n";
        yli::ontology::Entity* const orient_to_east_brain_entity = entity_factory->create_brain(orient_to_east_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_to_east_brain ...\n";
        yli::ontology::Brain* const orient_to_east_brain = dynamic_cast<yli::ontology::Brain*>(orient_to_east_brain_entity);

        if (orient_to_east_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_to_west_brain`.
        yli::ontology::BrainStruct orient_to_west_brain_struct;
        orient_to_west_brain_struct.parent = helsinki_east_downtown_scene;
        orient_to_west_brain_struct.global_name = "orient_to_west_brain";
        orient_to_west_brain_struct.local_name = "orient_to_west";
        orient_to_west_brain_struct.callback_engine = orient_to_west_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_to_west_brain_entity ...\n";
        yli::ontology::Entity* const orient_to_west_brain_entity = entity_factory->create_brain(orient_to_west_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_to_west_brain ...\n";
        yli::ontology::Brain* const orient_to_west_brain = dynamic_cast<yli::ontology::Brain*>(orient_to_west_brain_entity);

        if (orient_to_west_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_to_north_brain`.
        yli::ontology::BrainStruct orient_to_north_brain_struct;
        orient_to_north_brain_struct.parent = helsinki_east_downtown_scene;
        orient_to_north_brain_struct.global_name = "orient_to_north_brain";
        orient_to_north_brain_struct.local_name = "orient_to_north";
        orient_to_north_brain_struct.callback_engine = orient_to_north_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_to_north_brain_entity ...\n";
        yli::ontology::Entity* const orient_to_north_brain_entity = entity_factory->create_brain(orient_to_north_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_to_north_brain ...\n";
        yli::ontology::Brain* const orient_to_north_brain = dynamic_cast<yli::ontology::Brain*>(orient_to_north_brain_entity);

        if (orient_to_north_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_to_south_brain`.
        yli::ontology::BrainStruct orient_to_south_brain_struct;
        orient_to_south_brain_struct.parent = helsinki_east_downtown_scene;
        orient_to_south_brain_struct.global_name = "orient_to_south_brain";
        orient_to_south_brain_struct.local_name = "orient_to_south";
        orient_to_south_brain_struct.callback_engine = orient_to_south_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_to_south_brain_entity ...\n";
        yli::ontology::Entity* const orient_to_south_brain_entity = entity_factory->create_brain(orient_to_south_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_to_south_brain ...\n";
        yli::ontology::Brain* const orient_to_south_brain = dynamic_cast<yli::ontology::Brain*>(orient_to_south_brain_entity);

        if (orient_to_south_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `rotate_clockwise_brain`.
        yli::ontology::BrainStruct rotate_clockwise_brain_struct;
        rotate_clockwise_brain_struct.parent = helsinki_east_downtown_scene;
        rotate_clockwise_brain_struct.global_name = "rotate_clockwise_brain";
        rotate_clockwise_brain_struct.local_name = "rotate_clockwise";
        rotate_clockwise_brain_struct.callback_engine = rotate_clockwise_callback_engine;
        std::cout << "Creating yli::ontology::Entity* rotate_clockwise_brain_entity ...\n";
        yli::ontology::Entity* const rotate_clockwise_brain_entity = entity_factory->create_brain(rotate_clockwise_brain_struct);
        std::cout << "Creating yli::ontology::Brain* rotate_clockwise_brain ...\n";
        yli::ontology::Brain* const rotate_clockwise_brain = dynamic_cast<yli::ontology::Brain*>(rotate_clockwise_brain_entity);

        if (rotate_clockwise_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_and_go_east_brain`.
        yli::ontology::BrainStruct orient_and_go_east_brain_struct;
        orient_and_go_east_brain_struct.parent = helsinki_east_downtown_scene;
        orient_and_go_east_brain_struct.global_name = "orient_and_go_east_brain";
        orient_and_go_east_brain_struct.local_name = "orient_and_go_east";
        orient_and_go_east_brain_struct.callback_engine = orient_and_go_east_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_and_go_east_brain_entity ...\n";
        yli::ontology::Entity* const orient_and_go_east_brain_entity = entity_factory->create_brain(orient_and_go_east_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_and_go_east_brain ...\n";
        yli::ontology::Brain* const orient_and_go_east_brain = dynamic_cast<yli::ontology::Brain*>(orient_and_go_east_brain_entity);

        if (orient_and_go_east_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_and_go_west_brain`.
        yli::ontology::BrainStruct orient_and_go_west_brain_struct;
        orient_and_go_west_brain_struct.parent = helsinki_east_downtown_scene;
        orient_and_go_west_brain_struct.global_name = "orient_and_go_west_brain";
        orient_and_go_west_brain_struct.local_name = "orient_and_go_west";
        orient_and_go_west_brain_struct.callback_engine = orient_and_go_west_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_and_go_west_brain_entity ...\n";
        yli::ontology::Entity* const orient_and_go_west_brain_entity = entity_factory->create_brain(orient_and_go_west_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_and_go_west_brain ...\n";
        yli::ontology::Brain* const orient_and_go_west_brain = dynamic_cast<yli::ontology::Brain*>(orient_and_go_west_brain_entity);

        if (orient_and_go_west_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_and_go_north_brain`.
        yli::ontology::BrainStruct orient_and_go_north_brain_struct;
        orient_and_go_north_brain_struct.parent = helsinki_east_downtown_scene;
        orient_and_go_north_brain_struct.global_name = "orient_and_go_north_brain";
        orient_and_go_north_brain_struct.local_name = "orient_and_go_north";
        orient_and_go_north_brain_struct.callback_engine = orient_and_go_north_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_and_go_north_brain_entity ...\n";
        yli::ontology::Entity* const orient_and_go_north_brain_entity = entity_factory->create_brain(orient_and_go_north_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_and_go_north_brain ...\n";
        yli::ontology::Brain* const orient_and_go_north_brain = dynamic_cast<yli::ontology::Brain*>(orient_and_go_north_brain_entity);

        if (orient_and_go_north_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `orient_and_go_south_brain`.
        yli::ontology::BrainStruct orient_and_go_south_brain_struct;
        orient_and_go_south_brain_struct.parent = helsinki_east_downtown_scene;
        orient_and_go_south_brain_struct.global_name = "orient_and_go_south_brain";
        orient_and_go_south_brain_struct.local_name = "orient_and_go_south";
        orient_and_go_south_brain_struct.callback_engine = orient_and_go_south_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_and_go_south_brain_entity ...\n";
        yli::ontology::Entity* const orient_and_go_south_brain_entity = entity_factory->create_brain(orient_and_go_south_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_and_go_south_brain ...\n";
        yli::ontology::Brain* const orient_and_go_south_brain = dynamic_cast<yli::ontology::Brain*>(orient_and_go_south_brain_entity);

        if (orient_and_go_south_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // `rotate_counterclockwise_brain`.
        yli::ontology::BrainStruct rotate_counterclockwise_brain_struct;
        rotate_counterclockwise_brain_struct.parent = helsinki_east_downtown_scene;
        rotate_counterclockwise_brain_struct.global_name = "rotate_counterclockwise_brain";
        rotate_counterclockwise_brain_struct.local_name = "rotate_counterclockwise";
        rotate_counterclockwise_brain_struct.callback_engine = rotate_counterclockwise_callback_engine;
        std::cout << "Creating yli::ontology::Entity* rotate_counterclockwise_brain_entity ...\n";
        yli::ontology::Entity* const rotate_counterclockwise_brain_entity = entity_factory->create_brain(rotate_counterclockwise_brain_struct);
        std::cout << "Creating yli::ontology::Brain* rotate_counterclockwise_brain ...\n";
        yli::ontology::Brain* const rotate_counterclockwise_brain = dynamic_cast<yli::ontology::Brain*>(rotate_counterclockwise_brain_entity);

        if (rotate_counterclockwise_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        // Create the pipeline, store it in `helsinki_east_downtown_pipeline`.
        yli::ontology::PipelineStruct helsinki_east_downtown_pipeline_struct;
        helsinki_east_downtown_pipeline_struct.parent = helsinki_east_downtown_scene;
        helsinki_east_downtown_pipeline_struct.global_name = "helsinki_east_downtown_pipeline";
        helsinki_east_downtown_pipeline_struct.local_name = "helsinki_regular_pipeline";
        helsinki_east_downtown_pipeline_struct.vertex_shader = "standard_shading.vert";
        helsinki_east_downtown_pipeline_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_pipeline_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_pipeline_entity = entity_factory->create_pipeline(helsinki_east_downtown_pipeline_struct);
        std::cout << "Creating yli::ontology::Pipeline* helsinki_east_downtown_pipeline ...\n";
        yli::ontology::Pipeline* const helsinki_east_downtown_pipeline = dynamic_cast<yli::ontology::Pipeline*>(helsinki_east_downtown_pipeline_entity);

        if (helsinki_east_downtown_pipeline == nullptr)
        {
            std::cerr << "Failed to create Pipeline.\n";
            return nullptr;
        }

        // Create the grayscale pipeline, store it in `helsinki_east_downtown_grayscale_pipeline`.
        yli::ontology::PipelineStruct helsinki_east_downtown_grayscale_pipeline_struct;
        helsinki_east_downtown_grayscale_pipeline_struct.parent = helsinki_east_downtown_scene;
        helsinki_east_downtown_grayscale_pipeline_struct.global_name = "helsinki_east_downtown_grayscale_pipeline";
        helsinki_east_downtown_grayscale_pipeline_struct.local_name = "helsinki_grayscale_pipeline";
        helsinki_east_downtown_grayscale_pipeline_struct.vertex_shader = "standard_shading.vert";
        helsinki_east_downtown_grayscale_pipeline_struct.fragment_shader = "grayscale_standard_shading.frag";

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_grayscale_pipeline_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_grayscale_pipeline_entity = entity_factory->create_pipeline(helsinki_east_downtown_grayscale_pipeline_struct);
        std::cout << "Creating yli::ontology::Pipeline* helsinki_east_downtown_grayscale_pipeline ...\n";
        yli::ontology::Pipeline* const helsinki_east_downtown_grayscale_pipeline = dynamic_cast<yli::ontology::Pipeline*>(helsinki_east_downtown_grayscale_pipeline_entity);

        if (helsinki_east_downtown_grayscale_pipeline == nullptr)
        {
            std::cerr << "Failed to create Pipeline.\n";
            return nullptr;
        }

        // Create the material, store it in `helsinki_east_downtown_grass_material`.
        yli::ontology::MaterialStruct helsinki_east_downtown_grass_material_struct;
        helsinki_east_downtown_grass_material_struct.parent = helsinki_east_downtown_scene;
        helsinki_east_downtown_grass_material_struct.pipeline = helsinki_east_downtown_pipeline;
        helsinki_east_downtown_grass_material_struct.texture_file_format = "png";
        helsinki_east_downtown_grass_material_struct.texture_filename = "GrassGreenTexture0002.png";

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_grass_material_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_grass_material_entity = entity_factory->create_material(helsinki_east_downtown_grass_material_struct);
        std::cout << "Creating yli::ontology::Material* helsinki_east_downtown_grass_material ...\n";
        yli::ontology::Material* const helsinki_east_downtown_grass_material = dynamic_cast<yli::ontology::Material*>(helsinki_east_downtown_grass_material_entity);

        if (helsinki_east_downtown_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        helsinki_east_downtown_grass_material->set_global_name("helsinki_east_downtown_grass_material");

        // Create the material, store it in `orange_fur_material`.
        yli::ontology::MaterialStruct orange_fur_material_struct;
        orange_fur_material_struct.parent = helsinki_east_downtown_scene;
        orange_fur_material_struct.pipeline = helsinki_east_downtown_pipeline;
        orange_fur_material_struct.texture_file_format = "png";
        orange_fur_material_struct.texture_filename = "orange_fur_texture.png";

        std::cout << "Creating yli::ontology::Entity* orange_fur_material_entity ...\n";
        yli::ontology::Entity* const orange_fur_material_entity = entity_factory->create_material(orange_fur_material_struct);
        std::cout << "Creating yli::ontology::Material* orange_fur_material ...\n";
        yli::ontology::Material* const orange_fur_material = dynamic_cast<yli::ontology::Material*>(orange_fur_material_entity);

        if (orange_fur_material == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        orange_fur_material->set_global_name("helsinki_east_downtown_orange_fur_material");

        yli::ontology::ModelStruct helsinki_east_downtown_terrain_model_struct;
        helsinki_east_downtown_terrain_model_struct.parent = helsinki_east_downtown_scene;
        helsinki_east_downtown_terrain_model_struct.pipeline = helsinki_east_downtown_pipeline;
        helsinki_east_downtown_terrain_model_struct.material = helsinki_east_downtown_grass_material;
        helsinki_east_downtown_terrain_model_struct.model_file_format = "ASCII_grid";
        helsinki_east_downtown_terrain_model_struct.model_filename = "L4133D.asc"; // Helsinki eastern downtown.
        helsinki_east_downtown_terrain_model_struct.x_step = 4;
        helsinki_east_downtown_terrain_model_struct.z_step = 4;
        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_terrain_species_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_terrain_species_entity = entity_factory->create_species(helsinki_east_downtown_terrain_model_struct);
        std::cout << "Creating yli::ontology::Species* helsinki_east_downtown_terrain_species ...\n";
        yli::ontology::Species* const helsinki_east_downtown_terrain_species = dynamic_cast<yli::ontology::Species*>(helsinki_east_downtown_terrain_species_entity);

        if (helsinki_east_downtown_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        helsinki_east_downtown_terrain_species->set_global_name("helsinki_east_downtown_terrain_species");

        // Create Helsinki eastern downtown terrain.
        yli::ontology::ObjectStruct helsinki_east_downtown_struct(helsinki_east_downtown_scene);
        helsinki_east_downtown_struct.mesh_master = helsinki_east_downtown_terrain_species;
        helsinki_east_downtown_struct.cartesian_coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_object_derivative<yli::ontology::Terrain>(helsinki_east_downtown_struct);

        yli::ontology::ModelStruct cat_model_struct;
        cat_model_struct.parent = helsinki_east_downtown_scene;
        cat_model_struct.global_name = "cat_species";
        cat_model_struct.local_name = "cat";
        cat_model_struct.pipeline = helsinki_east_downtown_pipeline;
        cat_model_struct.material = orange_fur_material;
        cat_model_struct.model_file_format = "fbx";
        cat_model_struct.model_filename = "cat.fbx";

        std::cout << "Creating yli::ontology::Entity* cat_species_entity ...\n";
        yli::ontology::Entity* const cat_species_entity = entity_factory->create_species(cat_model_struct);

        std::cout << "Creating yli::ontology::Species* cat_species ...\n";
        yli::ontology::Species* const cat_species = dynamic_cast<yli::ontology::Species*>(cat_species_entity);

        if (cat_species == nullptr)
        {
            std::cerr << "Failed to create cat Species.\n";
            return nullptr;
        }

        yli::ontology::ObjectStruct cat1_object_struct(helsinki_east_downtown_scene);
        cat1_object_struct.mesh_master = cat_species;
        cat1_object_struct.global_name = "cat1";
        cat1_object_struct.local_name = "kissa1";
        cat1_object_struct.brain = rest_brain;
        cat1_object_struct.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
        cat1_object_struct.initial_rotate_angles = { pi, -0.5f * pi };
        cat1_object_struct.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
        cat1_object_struct.cartesian_coordinates = glm::vec3(500.00f, 100.00f, 1000.00f);

        yli::ontology::LocomotionModuleStruct cat1_walk_struct(1.0f); // 3.6 km/h.
        yli::ontology::LocomotionModuleStruct cat1_trot_struct(5.0f);
        yli::ontology::LocomotionModuleStruct cat1_canter_struct(10.0f);
        yli::ontology::LocomotionModuleStruct cat1_gallop_struct(12.5f); // 45 km/h.
        yli::ontology::LocomotionModuleStruct cat1_climb_struct;

        yli::ontology::Entity* const cat1_entity = entity_factory->create_object_derivative<hirvi::Cat>(
                cat1_object_struct,
                cat1_walk_struct,
                cat1_trot_struct,
                cat1_canter_struct,
                cat1_gallop_struct,
                cat1_climb_struct);
        hirvi::Cat* const cat1 = dynamic_cast<hirvi::Cat*>(cat1_entity);

        if (cat1 == nullptr)
        {
            std::cerr << "Failed to create cat1.\n";
            return nullptr;
        }

        yli::ontology::ObjectStruct cat2_object_struct(helsinki_east_downtown_scene);
        cat2_object_struct.mesh_master = cat_species;
        cat2_object_struct.global_name = "cat2";
        cat2_object_struct.local_name = "kissa2";
        cat2_object_struct.brain = rest_brain;
        cat2_object_struct.scene = helsinki_east_downtown_scene;
        cat2_object_struct.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
        cat2_object_struct.initial_rotate_angles = { pi, -0.5f * pi };
        cat2_object_struct.original_scale_vector = glm::vec3(15.0f, 15.0f, 15.0f);
        cat2_object_struct.cartesian_coordinates = glm::vec3(700.00f, 100.00f, 1200.00f);

        yli::ontology::LocomotionModuleStruct cat2_walk_struct(1.0f); // 3.6 km/h.
        yli::ontology::LocomotionModuleStruct cat2_trot_struct(5.0f);
        yli::ontology::LocomotionModuleStruct cat2_canter_struct(10.0f);
        yli::ontology::LocomotionModuleStruct cat2_gallop_struct(12.5f); // 45 km/h.
        yli::ontology::LocomotionModuleStruct cat2_climb_struct;

        yli::ontology::Entity* const cat2_entity = entity_factory->create_object_derivative<hirvi::Cat>(
                cat2_object_struct,
                cat2_walk_struct,
                cat2_trot_struct,
                cat2_canter_struct,
                cat2_gallop_struct,
                cat2_climb_struct);
        hirvi::Cat* const cat2 = dynamic_cast<hirvi::Cat*>(cat2_entity);

        if (cat2 == nullptr)
        {
            std::cerr << "Failed to create cat2.\n";
            return nullptr;
        }

        yli::ontology::Entity* const turbo_polizei_png_symbiosis_entity = universe.get_entity("turbo_polizei_png_symbiosis");

        yli::ontology::Symbiosis* const turbo_polizei_png_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(turbo_polizei_png_symbiosis_entity);

        if (turbo_polizei_png_symbiosis == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png_symbiosis.\n";
            return nullptr;
        }

        yli::ontology::HolobiontStruct turbo_polizei_png_police_car_struct1(*helsinki_east_downtown_scene, *turbo_polizei_png_symbiosis);
        turbo_polizei_png_police_car_struct1.brain = rest_brain;
        turbo_polizei_png_police_car_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f) };
        turbo_polizei_png_police_car_struct1.initial_rotate_angles = { pi };
        turbo_polizei_png_police_car_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_png_police_car_struct1.cartesian_coordinates = glm::vec3(85.00f, 30.00f, 160.00f);

        std::cout << "Creating yli::ontology::Entity* turbo_polizei_png1_entity ...\n";

        yli::ontology::LocomotionModuleStruct road_vehicle_struct1;

        yli::ontology::Entity* const turbo_polizei_png1_entity = entity_factory->create_holobiont_derivative<hirvi::PoliceCar>(turbo_polizei_png_police_car_struct1, road_vehicle_struct1);

        std::cout << "Creating hirvi::PoliceCar* turbo_polizei_png1 ...\n";

        hirvi::PoliceCar* const turbo_polizei_png1 = dynamic_cast<hirvi::PoliceCar*>(turbo_polizei_png1_entity);

        if (turbo_polizei_png1 == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png1.\n";
            return nullptr;
        }

        turbo_polizei_png1->set_global_name("turbo_polizei_png1");
        turbo_polizei_png1->set_local_name("sinivuokko1");

        yli::ontology::HolobiontStruct turbo_polizei_png_police_car_struct2(*helsinki_east_downtown_scene, *turbo_polizei_png_symbiosis);
        turbo_polizei_png_police_car_struct2.brain = rest_brain;
        turbo_polizei_png_police_car_struct2.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f) };
        turbo_polizei_png_police_car_struct2.initial_rotate_angles = { pi };
        turbo_polizei_png_police_car_struct2.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_png_police_car_struct2.cartesian_coordinates = glm::vec3(85.00f, 30.00f, 175.00f);

        std::cout << "Creating yli::ontology::Entity* turbo_polizei_png2_entity ...\n";

        yli::ontology::LocomotionModuleStruct road_vehicle_struct2;

        yli::ontology::Entity* const turbo_polizei_png2_entity = entity_factory->create_holobiont_derivative<hirvi::PoliceCar>(turbo_polizei_png_police_car_struct2, road_vehicle_struct2);

        std::cout << "Creating hirvi::PoliceCar* turbo_polizei_png2 ...\n";

        hirvi::PoliceCar* const turbo_polizei_png2 = dynamic_cast<hirvi::PoliceCar*>(turbo_polizei_png2_entity);

        if (turbo_polizei_png2 == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_png2.\n";
            return nullptr;
        }

        turbo_polizei_png2->set_global_name("turbo_polizei_png2");
        turbo_polizei_png2->set_local_name("sinivuokko2");

        yli::ontology::CameraStruct cat_camera_struct;
        cat_camera_struct.scene = helsinki_east_downtown_scene;
        cat_camera_struct.cartesian_coordinates = glm::vec3(800.00f, 400.00f, 950.00f);
        cat_camera_struct.orientation.yaw = -0.90f;
        cat_camera_struct.orientation.pitch = -1.00f;

        std::cout << "Creating yli::ontology::Entity* cat_camera_entity ...\n";
        yli::ontology::Entity* const cat_camera_entity = entity_factory->create_camera(cat_camera_struct);
        std::cout << "Creating yli::ontology::Camera* cat_camera ...\n";
        yli::ontology::Camera* const cat_camera = dynamic_cast<yli::ontology::Camera*>(cat_camera_entity);

        if (cat_camera == nullptr)
        {
            std::cerr << "Failed to create cat_camera.\n";
            return nullptr;
        }

        cat_camera->set_global_name("cat_camera");

        yli::ontology::CameraStruct turbo_polizei_camera_struct;
        turbo_polizei_camera_struct.scene = helsinki_east_downtown_scene;
        turbo_polizei_camera_struct.cartesian_coordinates = glm::vec3(87.00f, 28.00f, 169.00f);
        turbo_polizei_camera_struct.orientation.yaw = -0.45f;
        turbo_polizei_camera_struct.orientation.pitch = -0.05f;

        std::cout << "Creating yli::ontology::Entity* turbo_polizei_camera_entity ...\n";
        yli::ontology::Entity* const turbo_polizei_camera_entity = entity_factory->create_camera(turbo_polizei_camera_struct);
        std::cout << "Creating yli::ontology::Camera* turbo_polizei_camera ...\n";
        yli::ontology::Camera* const turbo_polizei_camera = dynamic_cast<yli::ontology::Camera*>(turbo_polizei_camera_entity);

        if (turbo_polizei_camera == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_camera.\n";
            return nullptr;
        }

        turbo_polizei_camera->set_global_name("turbo_polizei_camera");

        return helsinki_east_downtown_scene_entity;
        // Helsinki `Scene` ends here.
    }
}