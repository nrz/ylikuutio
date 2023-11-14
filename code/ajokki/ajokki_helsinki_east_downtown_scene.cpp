// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "ajokki.hpp"
#include "code/ylikuutio/snippets/brain_snippets.hpp"
#include "code/ylikuutio/snippets/keyboard_callback_snippets.hpp"
#include "code/ylikuutio/data/pi.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/callback_engine_struct.hpp"
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
    yli::ontology::Entity* AjokkiApplication::create_helsinki_east_downtown_scene()
    {
        // Helsinki `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_scene_entity ...\n";
        yli::ontology::SceneStruct scene_struct;
        scene_struct.global_name = "helsinki_east_downtown_scene";
        scene_struct.light_position = { 0.0f, 100000.0f, 100000.0f, 1.0f };
        scene_struct.water_level = 0.9f;
        yli::ontology::Entity* const helsinki_east_downtown_scene_entity = this->entity_factory.create_scene(scene_struct);
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
        yli::ontology::CallbackEngineStruct rest_callback_engine_struct;
        auto rest_callback_engine = this->entity_factory.create_callback_engine(rest_callback_engine_struct);
        rest_callback_engine->create_callback_object(&yli::snippets::rest);

        yli::ontology::CallbackEngineStruct go_east_callback_engine_struct;
        auto go_east_callback_engine = this->entity_factory.create_callback_engine(go_east_callback_engine_struct);
        go_east_callback_engine->create_callback_object(&yli::snippets::go_east);

        yli::ontology::CallbackEngineStruct go_west_callback_engine_struct;
        auto go_west_callback_engine = this->entity_factory.create_callback_engine(go_west_callback_engine_struct);
        go_west_callback_engine->create_callback_object(&yli::snippets::go_west);

        yli::ontology::CallbackEngineStruct go_north_callback_engine_struct;
        auto go_north_callback_engine = this->entity_factory.create_callback_engine(go_north_callback_engine_struct);
        go_north_callback_engine->create_callback_object(&yli::snippets::go_north);

        yli::ontology::CallbackEngineStruct go_south_callback_engine_struct;
        auto go_south_callback_engine = this->entity_factory.create_callback_engine(go_south_callback_engine_struct);
        go_south_callback_engine->create_callback_object(&yli::snippets::go_south);

        yli::ontology::CallbackEngineStruct orient_to_east_callback_engine_struct;
        auto orient_to_east_callback_engine = this->entity_factory.create_callback_engine(orient_to_east_callback_engine_struct);
        orient_to_east_callback_engine->create_callback_object(&yli::snippets::orient_to_east);

        yli::ontology::CallbackEngineStruct orient_to_west_callback_engine_struct;
        auto orient_to_west_callback_engine = this->entity_factory.create_callback_engine(orient_to_west_callback_engine_struct);
        orient_to_west_callback_engine->create_callback_object(&yli::snippets::orient_to_west);

        yli::ontology::CallbackEngineStruct orient_to_north_callback_engine_struct;
        auto orient_to_north_callback_engine = this->entity_factory.create_callback_engine(orient_to_north_callback_engine_struct);
        orient_to_north_callback_engine->create_callback_object(&yli::snippets::orient_to_north);

        yli::ontology::CallbackEngineStruct orient_to_south_callback_engine_struct;
        auto orient_to_south_callback_engine = this->entity_factory.create_callback_engine(orient_to_south_callback_engine_struct);
        orient_to_south_callback_engine->create_callback_object(&yli::snippets::orient_to_south);

        yli::ontology::CallbackEngineStruct orient_and_go_east_callback_engine_struct;
        auto orient_and_go_east_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_east_callback_engine_struct);
        orient_and_go_east_callback_engine->create_callback_object(&yli::snippets::orient_and_go_east);

        yli::ontology::CallbackEngineStruct orient_and_go_west_callback_engine_struct;
        auto orient_and_go_west_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_west_callback_engine_struct);
        orient_and_go_west_callback_engine->create_callback_object(&yli::snippets::orient_and_go_west);

        yli::ontology::CallbackEngineStruct orient_and_go_north_callback_engine_struct;
        auto orient_and_go_north_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_north_callback_engine_struct);
        orient_and_go_north_callback_engine->create_callback_object(&yli::snippets::orient_and_go_north);

        yli::ontology::CallbackEngineStruct orient_and_go_south_callback_engine_struct;
        auto orient_and_go_south_callback_engine = this->entity_factory.create_callback_engine(orient_and_go_south_callback_engine_struct);
        orient_and_go_south_callback_engine->create_callback_object(&yli::snippets::orient_and_go_south);

        yli::ontology::CallbackEngineStruct rotate_clockwise_callback_engine_struct;
        auto rotate_clockwise_callback_engine = this->entity_factory.create_callback_engine(rotate_clockwise_callback_engine_struct);
        rotate_clockwise_callback_engine->create_callback_object(&yli::snippets::rotate_clockwise);

        yli::ontology::CallbackEngineStruct rotate_counterclockwise_callback_engine_struct;
        auto rotate_counterclockwise_callback_engine = this->entity_factory.create_callback_engine(rotate_counterclockwise_callback_engine_struct);
        rotate_counterclockwise_callback_engine->create_callback_object(&yli::snippets::rotate_counterclockwise);

        // Create the `Brain`s.

        // `rest_brain`.
        yli::ontology::BrainStruct rest_brain_struct;
        rest_brain_struct.parent = helsinki_east_downtown_scene;
        rest_brain_struct.global_name = "rest_brain";
        rest_brain_struct.local_name = "rest";
        rest_brain_struct.callback_engine = rest_callback_engine;
        std::cout << "Creating yli::ontology::Entity* rest_brain_entity ...\n";
        yli::ontology::Entity* const rest_brain_entity = this->entity_factory.create_brain(rest_brain_struct);
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
        yli::ontology::Entity* const go_east_brain_entity = this->entity_factory.create_brain(go_east_brain_struct);
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
        yli::ontology::Entity* const go_west_brain_entity = this->entity_factory.create_brain(go_west_brain_struct);
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
        yli::ontology::Entity* const go_north_brain_entity = this->entity_factory.create_brain(go_north_brain_struct);
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
        yli::ontology::Entity* const go_south_brain_entity = this->entity_factory.create_brain(go_south_brain_struct);
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
        yli::ontology::Entity* const orient_to_east_brain_entity = this->entity_factory.create_brain(orient_to_east_brain_struct);
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
        yli::ontology::Entity* const orient_to_west_brain_entity = this->entity_factory.create_brain(orient_to_west_brain_struct);
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
        yli::ontology::Entity* const orient_to_north_brain_entity = this->entity_factory.create_brain(orient_to_north_brain_struct);
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
        yli::ontology::Entity* const orient_to_south_brain_entity = this->entity_factory.create_brain(orient_to_south_brain_struct);
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
        yli::ontology::Entity* const rotate_clockwise_brain_entity = this->entity_factory.create_brain(rotate_clockwise_brain_struct);
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
        yli::ontology::Entity* const orient_and_go_east_brain_entity = this->entity_factory.create_brain(orient_and_go_east_brain_struct);
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
        yli::ontology::Entity* const orient_and_go_west_brain_entity = this->entity_factory.create_brain(orient_and_go_west_brain_struct);
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
        yli::ontology::Entity* const orient_and_go_north_brain_entity = this->entity_factory.create_brain(orient_and_go_north_brain_struct);
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
        yli::ontology::Entity* const orient_and_go_south_brain_entity = this->entity_factory.create_brain(orient_and_go_south_brain_struct);
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
        yli::ontology::Entity* const rotate_counterclockwise_brain_entity = this->entity_factory.create_brain(rotate_counterclockwise_brain_struct);
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
        yli::ontology::Entity* const helsinki_east_downtown_pipeline_entity = this->entity_factory.create_pipeline(helsinki_east_downtown_pipeline_struct);
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
        yli::ontology::Entity* const helsinki_east_downtown_grayscale_pipeline_entity = this->entity_factory.create_pipeline(helsinki_east_downtown_grayscale_pipeline_struct);
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
        yli::ontology::Entity* const helsinki_east_downtown_grass_material_entity = this->entity_factory.create_material(helsinki_east_downtown_grass_material_struct);
        std::cout << "Creating yli::ontology::Material* helsinki_east_downtown_grass_material ...\n";
        yli::ontology::Material* const helsinki_east_downtown_grass_material = dynamic_cast<yli::ontology::Material*>(helsinki_east_downtown_grass_material_entity);

        if (helsinki_east_downtown_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        helsinki_east_downtown_grass_material->set_global_name("helsinki_east_downtown_grass_material");

        // Create the material, store it in `pink_geometric_tiles_material`.
        yli::ontology::MaterialStruct pink_geometric_tiles_material_struct;
        pink_geometric_tiles_material_struct.parent = helsinki_east_downtown_scene;
        pink_geometric_tiles_material_struct.pipeline = helsinki_east_downtown_pipeline;
        pink_geometric_tiles_material_struct.texture_file_format = "png";
        pink_geometric_tiles_material_struct.texture_filename = "pavers1b2.png";

        std::cout << "Creating yli::ontology::Entity* pink_geometric_tiles_material_entity ...\n";
        yli::ontology::Entity* const pink_geometric_tiles_material_entity = this->entity_factory.create_material(pink_geometric_tiles_material_struct);
        std::cout << "Creating yli::ontology::Material* pink_geometric_tiles_material ...\n";
        yli::ontology::Material* const pink_geometric_tiles_material = dynamic_cast<yli::ontology::Material*>(pink_geometric_tiles_material_entity);

        if (pink_geometric_tiles_material == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        pink_geometric_tiles_material->set_global_name("helsinki_east_downtown_pink_geometric_tiles_material");

        // Create the material, store it in `orange_fur_material`.
        yli::ontology::MaterialStruct orange_fur_material_struct;
        orange_fur_material_struct.parent = helsinki_east_downtown_scene;
        orange_fur_material_struct.pipeline = helsinki_east_downtown_pipeline;
        orange_fur_material_struct.texture_file_format = "png";
        orange_fur_material_struct.texture_filename = "orange_fur_texture.png";

        std::cout << "Creating yli::ontology::Entity* orange_fur_material_entity ...\n";
        yli::ontology::Entity* const orange_fur_material_entity = this->entity_factory.create_material(orange_fur_material_struct);
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
        yli::ontology::Entity* const helsinki_east_downtown_terrain_species_entity = this->entity_factory.create_species(helsinki_east_downtown_terrain_model_struct);
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
        this->entity_factory.create_object(helsinki_east_downtown_struct);

        yli::ontology::ModelStruct suzanne_model_struct;
        suzanne_model_struct.parent = helsinki_east_downtown_scene;
        suzanne_model_struct.pipeline = helsinki_east_downtown_pipeline;
        suzanne_model_struct.material = orange_fur_material;
        suzanne_model_struct.model_file_format = "obj";
        suzanne_model_struct.model_filename = "suzanne.obj";

        std::cout << "Creating yli::ontology::Entity* suzanne_species_entity ...\n";
        yli::ontology::Entity* const suzanne_species_entity = this->entity_factory.create_species(suzanne_model_struct);
        std::cout << "Creating yli::ontology::Species* suzanne_species ...\n";
        yli::ontology::Species* const suzanne_species = dynamic_cast<yli::ontology::Species*>(suzanne_species_entity);

        if (suzanne_species == nullptr)
        {
            std::cerr << "Failed to create suzanne Species.\n";
            return nullptr;
        }

        suzanne_species->set_global_name("suzanne_species");

        // Create suzanne1, store it in `suzanne1`.
        yli::ontology::ObjectStruct suzanne_object_struct1(helsinki_east_downtown_scene);
        suzanne_object_struct1.mesh_master = suzanne_species;
        suzanne_object_struct1.cartesian_coordinates = glm::vec3(82.50f, 119.00f, 95.50f);
        std::cout << "Creating yli::ontology::Entity* suzanne1_entity ...\n";
        yli::ontology::Entity* const suzanne1_entity = this->entity_factory.create_object(suzanne_object_struct1);
        std::cout << "Creating yli::ontology::Species* suzanne1 ...\n";
        yli::ontology::Object* const suzanne1 = dynamic_cast<yli::ontology::Object*>(suzanne1_entity);

        if (suzanne1 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne1->set_global_name("suzanne1");

        suzanne_species->set_global_name("suzanne_species");
        yli::ontology::ObjectStruct suzanne_object_struct2(helsinki_east_downtown_scene);
        suzanne_object_struct2.mesh_master = suzanne_species;
        suzanne_object_struct2.scene = helsinki_east_downtown_scene;
        suzanne_object_struct2.cartesian_coordinates = glm::vec3(112.90f, 113.90f, 75.50f);
        std::cout << "Creating yli::ontology::Entity* suzanne2_entity ...\n";
        yli::ontology::Entity* const suzanne2_entity = this->entity_factory.create_object(suzanne_object_struct2);
        std::cout << "Creating yli::ontology::Species* suzanne2 ...\n";
        yli::ontology::Object* const suzanne2 = dynamic_cast<yli::ontology::Object*>(suzanne2_entity);

        if (suzanne2 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne2->set_global_name("suzanne2");

        yli::ontology::ObjectStruct suzanne_object_struct3(helsinki_east_downtown_scene);
        suzanne_object_struct3.mesh_master = suzanne_species;
        suzanne_object_struct3.cartesian_coordinates = glm::vec3(126.90f, 162.90f, 103.00f);
        std::cout << "Creating yli::ontology::Entity* suzanne3_entity ...\n";
        yli::ontology::Entity* const suzanne3_entity = this->entity_factory.create_object(suzanne_object_struct3);
        std::cout << "Creating yli::ontology::Species* suzanne3 ...\n";
        yli::ontology::Object* const suzanne3 = dynamic_cast<yli::ontology::Object*>(suzanne3_entity);

        if (suzanne3 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne3->set_global_name("suzanne3");

        yli::ontology::ObjectStruct suzanne_object_struct4(helsinki_east_downtown_scene);
        suzanne_object_struct4.mesh_master = suzanne_species;
        suzanne_object_struct4.cartesian_coordinates = glm::vec3(96.00f, 130.00f, 109.00f);
        std::cout << "Creating yli::ontology::Entity* suzanne4_entity ...\n";
        yli::ontology::Entity* const suzanne4_entity = this->entity_factory.create_object(suzanne_object_struct4);
        std::cout << "Creating yli::ontology::Species* suzanne4 ...\n";
        yli::ontology::Object* const suzanne4 = dynamic_cast<yli::ontology::Object*>(suzanne4_entity);

        if (suzanne4 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne4->set_global_name("suzanne4");

        yli::ontology::ObjectStruct suzanne_object_struct5(helsinki_east_downtown_scene);
        suzanne_object_struct5.mesh_master = suzanne_species;
        suzanne_object_struct5.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
        suzanne_object_struct5.cartesian_coordinates = glm::vec3(103.00f, 140.00f, 109.00f);
        std::cout << "Creating yli::ontology::Entity* suzanne5_entity ...\n";
        yli::ontology::Entity* const suzanne5_entity = this->entity_factory.create_object(suzanne_object_struct5);
        std::cout << "Creating yli::ontology::Species* suzanne5 ...\n";
        yli::ontology::Object* const suzanne5 = dynamic_cast<yli::ontology::Object*>(suzanne5_entity);

        if (suzanne5 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne5->set_global_name("suzanne5");

        yli::ontology::ModelStruct cat_model_struct;
        cat_model_struct.parent = helsinki_east_downtown_scene;
        cat_model_struct.global_name = "cat_species";
        cat_model_struct.local_name = "cat";
        cat_model_struct.pipeline = helsinki_east_downtown_pipeline;
        cat_model_struct.material = orange_fur_material;
        cat_model_struct.model_file_format = "fbx";
        cat_model_struct.model_filename = "cat.fbx";

        std::cout << "Creating yli::ontology::Entity* cat_species_entity ...\n";
        yli::ontology::Entity* const cat_species_entity = this->entity_factory.create_species(cat_model_struct);

        std::cout << "Creating yli::ontology::Species* cat_species ...\n";
        yli::ontology::Species* const cat_species = dynamic_cast<yli::ontology::Species*>(cat_species_entity);

        if (cat_species == nullptr)
        {
            std::cerr << "Failed to create cat Species.\n";
            return nullptr;
        }

        // Create some cats.

        for (std::size_t i = 0; i < 1000; i++)
        {
            const std::string index_string = std::to_string(i);

            const float first_cat_x { 500.00f };
            const float first_cat_y { 100.00f };
            const float first_cat_z { 1000.00f };

            const float translation_x { 200.00f };
            const float translation_y { 000.00f };
            const float translation_z { 200.00f };

            const float first_cat_scale { 10.0f };

            yli::ontology::ObjectStruct cat_object_struct1(helsinki_east_downtown_scene);
            cat_object_struct1.mesh_master = cat_species;
            cat_object_struct1.global_name = "cat" + index_string;
            cat_object_struct1.local_name = "kissa" + index_string;
            cat_object_struct1.brain = rest_brain;
            cat_object_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
            cat_object_struct1.initial_rotate_angles = { pi, -0.5f * pi };
            cat_object_struct1.original_scale_vector = glm::vec3(first_cat_scale, first_cat_scale, first_cat_scale);
            cat_object_struct1.cartesian_coordinates = glm::vec3(
                    first_cat_x + i * translation_x,
                    first_cat_y + i * translation_y,
                    first_cat_z + i * translation_z);
            yli::ontology::Entity* const cat1_entity = this->entity_factory.create_object(cat_object_struct1);
            yli::ontology::Object* const cat1 = dynamic_cast<yli::ontology::Object*>(cat1_entity);

            if (cat1 == nullptr)
            {
                std::cerr << "Failed to create cat1 Object.\n";
                return nullptr;
            }
        }

        yli::ontology::Entity* const turbo_polizei_png_symbiosis_entity = this->get_universe().get_entity("turbo_polizei_png_symbiosis");

        yli::ontology::Symbiosis* const turbo_polizei_png_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(turbo_polizei_png_symbiosis_entity);

        if (turbo_polizei_png_symbiosis != nullptr)
        {
            yli::ontology::HolobiontStruct turbo_polizei_png_holobiont_struct1(*helsinki_east_downtown_scene, *turbo_polizei_png_symbiosis);
            turbo_polizei_png_holobiont_struct1.brain = rest_brain;
            turbo_polizei_png_holobiont_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f) };
            turbo_polizei_png_holobiont_struct1.initial_rotate_angles = { pi };
            turbo_polizei_png_holobiont_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
            turbo_polizei_png_holobiont_struct1.cartesian_coordinates = glm::vec3(85.00f, 30.00f, 160.00f);

            std::cout << "Creating yli::ontology::Entity* turbo_polizei_png1_entity ...\n";

            yli::ontology::Entity* const turbo_polizei_png1_entity = this->entity_factory.create_holobiont(turbo_polizei_png_holobiont_struct1);

            std::cout << "Creating yli::ontology::Holobiont* turbo_polizei_png1 ...\n";

            yli::ontology::Holobiont* const turbo_polizei_png1 = dynamic_cast<yli::ontology::Holobiont*>(turbo_polizei_png1_entity);

            if (turbo_polizei_png1 == nullptr)
            {
                std::cerr << "Failed to create turbo_polizei_png1 Object.\n";
                return nullptr;
            }

            turbo_polizei_png1->set_global_name("turbo_polizei_png1");
            turbo_polizei_png1->set_local_name("sinivuokko1");

            yli::ontology::HolobiontStruct turbo_polizei_png_holobiont_struct2(*helsinki_east_downtown_scene, *turbo_polizei_png_symbiosis);
            turbo_polizei_png_holobiont_struct2.brain = rest_brain;
            turbo_polizei_png_holobiont_struct2.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f) };
            turbo_polizei_png_holobiont_struct2.initial_rotate_angles = { pi };
            turbo_polizei_png_holobiont_struct2.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
            turbo_polizei_png_holobiont_struct2.cartesian_coordinates = glm::vec3(85.00f, 30.00f, 175.00f);

            std::cout << "Creating yli::ontology::Entity* turbo_polizei_png2_entity ...\n";

            yli::ontology::Entity* const turbo_polizei_png2_entity = this->entity_factory.create_holobiont(turbo_polizei_png_holobiont_struct2);

            std::cout << "Creating yli::ontology::Holobiont* turbo_polizei_png2 ...\n";

            yli::ontology::Holobiont* const turbo_polizei_png2 = dynamic_cast<yli::ontology::Holobiont*>(turbo_polizei_png2_entity);

            if (turbo_polizei_png2 == nullptr)
            {
                std::cerr << "Failed to create turbo_polizei_png2 Object.\n";
                return nullptr;
            }

            turbo_polizei_png2->set_global_name("turbo_polizei_png2");
            turbo_polizei_png2->set_local_name("sinivuokko2");
        }

        yli::ontology::CameraStruct cat_camera_struct;
        cat_camera_struct.scene = helsinki_east_downtown_scene;
        cat_camera_struct.cartesian_coordinates = glm::vec3(800.00f, 400.00f, 950.00f);
        cat_camera_struct.orientation.yaw = -0.90f;
        cat_camera_struct.orientation.pitch = -1.00f;

        std::cout << "Creating yli::ontology::Entity* cat_camera_entity ...\n";
        yli::ontology::Entity* const cat_camera_entity = this->entity_factory.create_camera(cat_camera_struct);
        std::cout << "Creating yli::ontology::Camera* cat_camera ...\n";
        yli::ontology::Camera* const cat_camera = dynamic_cast<yli::ontology::Camera*>(cat_camera_entity);

        if (cat_camera == nullptr)
        {
            std::cerr << "Failed to create cat_camera Camera.\n";
            return nullptr;
        }

        cat_camera->set_global_name("cat_camera");

        yli::ontology::CameraStruct turbo_polizei_camera_struct;
        turbo_polizei_camera_struct.scene = helsinki_east_downtown_scene;
        turbo_polizei_camera_struct.cartesian_coordinates = glm::vec3(87.00f, 28.00f, 169.00f);
        turbo_polizei_camera_struct.orientation.yaw = -0.45f;
        turbo_polizei_camera_struct.orientation.pitch = -0.05f;

        std::cout << "Creating yli::ontology::Entity* turbo_polizei_camera_entity ...\n";
        yli::ontology::Entity* const turbo_polizei_camera_entity = this->entity_factory.create_camera(turbo_polizei_camera_struct);
        std::cout << "Creating yli::ontology::Camera* turbo_polizei_camera ...\n";
        yli::ontology::Camera* const turbo_polizei_camera = dynamic_cast<yli::ontology::Camera*>(turbo_polizei_camera_entity);

        if (turbo_polizei_camera == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_camera Camera.\n";
            return nullptr;
        }

        turbo_polizei_camera->set_global_name("turbo_polizei_camera");

        return helsinki_east_downtown_scene_entity;
        // Helsinki `Scene` ends here.
    }
}
