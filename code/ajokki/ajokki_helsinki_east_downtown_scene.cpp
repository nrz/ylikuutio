// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef PI
#define PI 3.14159265359f
#endif

#include "ajokki_helsinki_east_downtown_scene.hpp"
#include "code/app/app_brain.hpp"
#include "code/app/app_keyboard_callbacks.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
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
    yli::ontology::Entity* create_helsinki_east_downtown_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world)
    {
        // Helsinki `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_scene_entity ...\n";
        yli::ontology::SceneStruct scene_struct;
        scene_struct.world = world;
        scene_struct.water_level = 0.9f;
        yli::ontology::Entity* const helsinki_east_downtown_scene_entity = entity_factory->create_Scene(scene_struct);
        std::cout << "Creating yli::ontology::Scene* helsinki_east_downtown_scene ...\n";
        yli::ontology::Scene* const helsinki_east_downtown_scene = dynamic_cast<yli::ontology::Scene*>(helsinki_east_downtown_scene_entity);

        if (helsinki_east_downtown_scene == nullptr)
        {
            std::cerr << "Failed to create Scene.\n";
            return nullptr;
        }

        helsinki_east_downtown_scene->set_name("helsinki_east_downtown_scene");

        helsinki_east_downtown_scene->set_turbo_factor(5.0f);
        helsinki_east_downtown_scene->set_twin_turbo_factor(100.0f);

        // Create the `CallbackEngine`s for the `Brain`s.
        std::shared_ptr<yli::callback::CallbackEngine> rest_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        rest_callback_engine->create_CallbackObject(&app::rest);

        std::shared_ptr<yli::callback::CallbackEngine> go_east_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        go_east_callback_engine->create_CallbackObject(&app::go_east);

        std::shared_ptr<yli::callback::CallbackEngine> go_west_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        go_west_callback_engine->create_CallbackObject(&app::go_west);

        std::shared_ptr<yli::callback::CallbackEngine> go_north_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        go_north_callback_engine->create_CallbackObject(&app::go_north);

        std::shared_ptr<yli::callback::CallbackEngine> go_south_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        go_south_callback_engine->create_CallbackObject(&app::go_south);

        std::shared_ptr<yli::callback::CallbackEngine> orient_to_east_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        orient_to_east_callback_engine->create_CallbackObject(&app::orient_to_east);

        std::shared_ptr<yli::callback::CallbackEngine> orient_to_west_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        orient_to_west_callback_engine->create_CallbackObject(&app::orient_to_west);

        std::shared_ptr<yli::callback::CallbackEngine> orient_to_north_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        orient_to_north_callback_engine->create_CallbackObject(&app::orient_to_north);

        std::shared_ptr<yli::callback::CallbackEngine> orient_to_south_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        orient_to_south_callback_engine->create_CallbackObject(&app::orient_to_south);

        std::shared_ptr<yli::callback::CallbackEngine> orient_and_go_east_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        orient_and_go_east_callback_engine->create_CallbackObject(&app::orient_and_go_east);

        std::shared_ptr<yli::callback::CallbackEngine> orient_and_go_west_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        orient_and_go_west_callback_engine->create_CallbackObject(&app::orient_and_go_west);

        std::shared_ptr<yli::callback::CallbackEngine> orient_and_go_north_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        orient_and_go_north_callback_engine->create_CallbackObject(&app::orient_and_go_north);

        std::shared_ptr<yli::callback::CallbackEngine> orient_and_go_south_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        orient_and_go_south_callback_engine->create_CallbackObject(&app::orient_and_go_south);

        std::shared_ptr<yli::callback::CallbackEngine> rotate_clockwise_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        rotate_clockwise_callback_engine->create_CallbackObject(&app::rotate_clockwise);

        std::shared_ptr<yli::callback::CallbackEngine> rotate_counterclockwise_callback_engine = std::make_shared<yli::callback::CallbackEngine>();
        rotate_counterclockwise_callback_engine->create_CallbackObject(&app::rotate_counterclockwise);

        // Create the `Brain`s.

        // `rest_brain`.
        yli::ontology::BrainStruct rest_brain_struct;
        rest_brain_struct.parent = helsinki_east_downtown_scene;
        rest_brain_struct.callback_engine = rest_callback_engine;
        std::cout << "Creating yli::ontology::Entity* rest_brain_entity ...\n";
        yli::ontology::Entity* const rest_brain_entity = entity_factory->create_Brain(rest_brain_struct);
        std::cout << "Creating yli::ontology::Brain* rest_brain ...\n";
        yli::ontology::Brain* const rest_brain = dynamic_cast<yli::ontology::Brain*>(rest_brain_entity);

        if (rest_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        rest_brain->set_name("rest_brain");

        // `go_east_brain`.
        yli::ontology::BrainStruct go_east_brain_struct;
        go_east_brain_struct.parent = helsinki_east_downtown_scene;
        go_east_brain_struct.callback_engine = go_east_callback_engine;
        std::cout << "Creating yli::ontology::Entity* go_east_brain_entity ...\n";
        yli::ontology::Entity* const go_east_brain_entity = entity_factory->create_Brain(go_east_brain_struct);
        std::cout << "Creating yli::ontology::Brain* go_east_brain ...\n";
        yli::ontology::Brain* const go_east_brain = dynamic_cast<yli::ontology::Brain*>(go_east_brain_entity);

        if (go_east_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        go_east_brain->set_name("go_east_brain");

        // `go_west_brain`.
        yli::ontology::BrainStruct go_west_brain_struct;
        go_west_brain_struct.parent = helsinki_east_downtown_scene;
        go_west_brain_struct.callback_engine = go_west_callback_engine;
        std::cout << "Creating yli::ontology::Entity* go_west_brain_entity ...\n";
        yli::ontology::Entity* const go_west_brain_entity = entity_factory->create_Brain(go_west_brain_struct);
        std::cout << "Creating yli::ontology::Brain* go_west_brain ...\n";
        yli::ontology::Brain* const go_west_brain = dynamic_cast<yli::ontology::Brain*>(go_west_brain_entity);

        if (go_west_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        go_west_brain->set_name("go_west_brain");

        // `go_north_brain`.
        yli::ontology::BrainStruct go_north_brain_struct;
        go_north_brain_struct.parent = helsinki_east_downtown_scene;
        go_north_brain_struct.callback_engine = go_north_callback_engine;
        std::cout << "Creating yli::ontology::Entity* go_north_brain_entity ...\n";
        yli::ontology::Entity* const go_north_brain_entity = entity_factory->create_Brain(go_north_brain_struct);
        std::cout << "Creating yli::ontology::Brain* go_north_brain ...\n";
        yli::ontology::Brain* const go_north_brain = dynamic_cast<yli::ontology::Brain*>(go_north_brain_entity);

        if (go_north_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        go_north_brain->set_name("go_north_brain");

        // `go_south_brain`.
        yli::ontology::BrainStruct go_south_brain_struct;
        go_south_brain_struct.parent = helsinki_east_downtown_scene;
        go_south_brain_struct.callback_engine = go_south_callback_engine;
        std::cout << "Creating yli::ontology::Entity* go_south_brain_entity ...\n";
        yli::ontology::Entity* const go_south_brain_entity = entity_factory->create_Brain(go_south_brain_struct);
        std::cout << "Creating yli::ontology::Brain* go_south_brain ...\n";
        yli::ontology::Brain* const go_south_brain = dynamic_cast<yli::ontology::Brain*>(go_south_brain_entity);

        if (go_south_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        go_south_brain->set_name("go_south_brain");

        // `orient_to_east_brain`.
        yli::ontology::BrainStruct orient_to_east_brain_struct;
        orient_to_east_brain_struct.parent = helsinki_east_downtown_scene;
        orient_to_east_brain_struct.callback_engine = orient_to_east_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_to_east_brain_entity ...\n";
        yli::ontology::Entity* const orient_to_east_brain_entity = entity_factory->create_Brain(orient_to_east_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_to_east_brain ...\n";
        yli::ontology::Brain* const orient_to_east_brain = dynamic_cast<yli::ontology::Brain*>(orient_to_east_brain_entity);

        if (orient_to_east_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        orient_to_east_brain->set_name("orient_to_east_brain");

        // `orient_to_west_brain`.
        yli::ontology::BrainStruct orient_to_west_brain_struct;
        orient_to_west_brain_struct.parent = helsinki_east_downtown_scene;
        orient_to_west_brain_struct.callback_engine = orient_to_west_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_to_west_brain_entity ...\n";
        yli::ontology::Entity* const orient_to_west_brain_entity = entity_factory->create_Brain(orient_to_west_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_to_west_brain ...\n";
        yli::ontology::Brain* const orient_to_west_brain = dynamic_cast<yli::ontology::Brain*>(orient_to_west_brain_entity);

        if (orient_to_west_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        orient_to_west_brain->set_name("orient_to_west_brain");

        // `orient_to_north_brain`.
        yli::ontology::BrainStruct orient_to_north_brain_struct;
        orient_to_north_brain_struct.parent = helsinki_east_downtown_scene;
        orient_to_north_brain_struct.callback_engine = orient_to_north_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_to_north_brain_entity ...\n";
        yli::ontology::Entity* const orient_to_north_brain_entity = entity_factory->create_Brain(orient_to_north_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_to_north_brain ...\n";
        yli::ontology::Brain* const orient_to_north_brain = dynamic_cast<yli::ontology::Brain*>(orient_to_north_brain_entity);

        if (orient_to_north_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        orient_to_north_brain->set_name("orient_to_north_brain");

        // `orient_to_south_brain`.
        yli::ontology::BrainStruct orient_to_south_brain_struct;
        orient_to_south_brain_struct.parent = helsinki_east_downtown_scene;
        orient_to_south_brain_struct.callback_engine = orient_to_south_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_to_south_brain_entity ...\n";
        yli::ontology::Entity* const orient_to_south_brain_entity = entity_factory->create_Brain(orient_to_south_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_to_south_brain ...\n";
        yli::ontology::Brain* const orient_to_south_brain = dynamic_cast<yli::ontology::Brain*>(orient_to_south_brain_entity);

        if (orient_to_south_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        orient_to_south_brain->set_name("orient_to_south_brain");

        // `rotate_clockwise_brain`.
        yli::ontology::BrainStruct rotate_clockwise_brain_struct;
        rotate_clockwise_brain_struct.parent = helsinki_east_downtown_scene;
        rotate_clockwise_brain_struct.callback_engine = rotate_clockwise_callback_engine;
        std::cout << "Creating yli::ontology::Entity* rotate_clockwise_brain_entity ...\n";
        yli::ontology::Entity* const rotate_clockwise_brain_entity = entity_factory->create_Brain(rotate_clockwise_brain_struct);
        std::cout << "Creating yli::ontology::Brain* rotate_clockwise_brain ...\n";
        yli::ontology::Brain* const rotate_clockwise_brain = dynamic_cast<yli::ontology::Brain*>(rotate_clockwise_brain_entity);

        if (rotate_clockwise_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        rotate_clockwise_brain->set_name("rotate_clockwise_brain");

        // `orient_and_go_east_brain`.
        yli::ontology::BrainStruct orient_and_go_east_brain_struct;
        orient_and_go_east_brain_struct.parent = helsinki_east_downtown_scene;
        orient_and_go_east_brain_struct.callback_engine = orient_and_go_east_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_and_go_east_brain_entity ...\n";
        yli::ontology::Entity* const orient_and_go_east_brain_entity = entity_factory->create_Brain(orient_and_go_east_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_and_go_east_brain ...\n";
        yli::ontology::Brain* const orient_and_go_east_brain = dynamic_cast<yli::ontology::Brain*>(orient_and_go_east_brain_entity);

        if (orient_and_go_east_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        orient_and_go_east_brain->set_name("orient_and_go_east_brain");

        // `orient_and_go_west_brain`.
        yli::ontology::BrainStruct orient_and_go_west_brain_struct;
        orient_and_go_west_brain_struct.parent = helsinki_east_downtown_scene;
        orient_and_go_west_brain_struct.callback_engine = orient_and_go_west_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_and_go_west_brain_entity ...\n";
        yli::ontology::Entity* const orient_and_go_west_brain_entity = entity_factory->create_Brain(orient_and_go_west_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_and_go_west_brain ...\n";
        yli::ontology::Brain* const orient_and_go_west_brain = dynamic_cast<yli::ontology::Brain*>(orient_and_go_west_brain_entity);

        if (orient_and_go_west_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        orient_and_go_west_brain->set_name("orient_and_go_west_brain");

        // `orient_and_go_north_brain`.
        yli::ontology::BrainStruct orient_and_go_north_brain_struct;
        orient_and_go_north_brain_struct.parent = helsinki_east_downtown_scene;
        orient_and_go_north_brain_struct.callback_engine = orient_and_go_north_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_and_go_north_brain_entity ...\n";
        yli::ontology::Entity* const orient_and_go_north_brain_entity = entity_factory->create_Brain(orient_and_go_north_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_and_go_north_brain ...\n";
        yli::ontology::Brain* const orient_and_go_north_brain = dynamic_cast<yli::ontology::Brain*>(orient_and_go_north_brain_entity);

        if (orient_and_go_north_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        orient_and_go_north_brain->set_name("orient_and_go_north_brain");

        // `orient_and_go_south_brain`.
        yli::ontology::BrainStruct orient_and_go_south_brain_struct;
        orient_and_go_south_brain_struct.parent = helsinki_east_downtown_scene;
        orient_and_go_south_brain_struct.callback_engine = orient_and_go_south_callback_engine;
        std::cout << "Creating yli::ontology::Entity* orient_and_go_south_brain_entity ...\n";
        yli::ontology::Entity* const orient_and_go_south_brain_entity = entity_factory->create_Brain(orient_and_go_south_brain_struct);
        std::cout << "Creating yli::ontology::Brain* orient_and_go_south_brain ...\n";
        yli::ontology::Brain* const orient_and_go_south_brain = dynamic_cast<yli::ontology::Brain*>(orient_and_go_south_brain_entity);

        if (orient_and_go_south_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        orient_and_go_south_brain->set_name("orient_and_go_south_brain");

        // `rotate_counterclockwise_brain`.
        yli::ontology::BrainStruct rotate_counterclockwise_brain_struct;
        rotate_counterclockwise_brain_struct.parent = helsinki_east_downtown_scene;
        rotate_counterclockwise_brain_struct.callback_engine = rotate_counterclockwise_callback_engine;
        std::cout << "Creating yli::ontology::Entity* rotate_counterclockwise_brain_entity ...\n";
        yli::ontology::Entity* const rotate_counterclockwise_brain_entity = entity_factory->create_Brain(rotate_counterclockwise_brain_struct);
        std::cout << "Creating yli::ontology::Brain* rotate_counterclockwise_brain ...\n";
        yli::ontology::Brain* const rotate_counterclockwise_brain = dynamic_cast<yli::ontology::Brain*>(rotate_counterclockwise_brain_entity);

        if (rotate_counterclockwise_brain == nullptr)
        {
            std::cerr << "Failed to create Brain.\n";
            return nullptr;
        }

        rotate_counterclockwise_brain->set_name("rotate_counterclockwise_brain");

        // Create the shader, store it in `helsinki_east_downtown_shader`.
        yli::ontology::ShaderStruct helsinki_east_downtown_shader_struct;
        helsinki_east_downtown_shader_struct.parent = helsinki_east_downtown_scene;
        helsinki_east_downtown_shader_struct.vertex_shader = "standard_shading.vert";
        helsinki_east_downtown_shader_struct.fragment_shader = "standard_shading.frag";

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_shader_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_shader_entity = entity_factory->create_Shader(helsinki_east_downtown_shader_struct);
        std::cout << "Creating yli::ontology::Shader* helsinki_east_downtown_shader ...\n";
        yli::ontology::Shader* const helsinki_east_downtown_shader = dynamic_cast<yli::ontology::Shader*>(helsinki_east_downtown_shader_entity);

        if (helsinki_east_downtown_shader == nullptr)
        {
            std::cerr << "Failed to create Shader.\n";
            return nullptr;
        }

        helsinki_east_downtown_shader->set_name("helsinki_east_downtown_shader");

        // Create the material, store it in `helsinki_east_downtown_grass_material`.
        yli::ontology::MaterialStruct helsinki_east_downtown_grass_material_struct;
        helsinki_east_downtown_grass_material_struct.shader = helsinki_east_downtown_shader;
        helsinki_east_downtown_grass_material_struct.texture_file_format = "bmp";
        helsinki_east_downtown_grass_material_struct.texture_filename = "GrassGreenTexture0002.bmp";

        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_grass_material_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_grass_material_entity = entity_factory->create_Material(helsinki_east_downtown_grass_material_struct);
        std::cout << "Creating yli::ontology::Material* helsinki_east_downtown_grass_material ...\n";
        yli::ontology::Material* const helsinki_east_downtown_grass_material = dynamic_cast<yli::ontology::Material*>(helsinki_east_downtown_grass_material_entity);

        if (helsinki_east_downtown_grass_material == nullptr)
        {
            std::cerr << "Failed to create grass Material.\n";
            return nullptr;
        }

        helsinki_east_downtown_grass_material->set_name("helsinki_east_downtown_grass_material");

        // Create the material, store it in `pink_geometric_tiles_material`.
        yli::ontology::MaterialStruct pink_geometric_tiles_material_struct;
        pink_geometric_tiles_material_struct.shader = helsinki_east_downtown_shader;
        pink_geometric_tiles_material_struct.texture_file_format = "bmp";
        pink_geometric_tiles_material_struct.texture_filename = "pavers1b2.bmp";

        std::cout << "Creating yli::ontology::Entity* pink_geometric_tiles_material_entity ...\n";
        yli::ontology::Entity* const pink_geometric_tiles_material_entity = entity_factory->create_Material(pink_geometric_tiles_material_struct);
        std::cout << "Creating yli::ontology::Material* pink_geometric_tiles_material ...\n";
        yli::ontology::Material* const pink_geometric_tiles_material = dynamic_cast<yli::ontology::Material*>(pink_geometric_tiles_material_entity);

        if (pink_geometric_tiles_material == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        pink_geometric_tiles_material->set_name("helsinki_east_downtown_pink_geometric_tiles_material");

        // Create the material, store it in `orange_fur_material`.
        yli::ontology::MaterialStruct orange_fur_material_struct;
        orange_fur_material_struct.shader = helsinki_east_downtown_shader;
        orange_fur_material_struct.texture_file_format = "bmp";
        orange_fur_material_struct.texture_filename = "orange_fur_texture.bmp";

        std::cout << "Creating yli::ontology::Entity* orange_fur_material_entity ...\n";
        yli::ontology::Entity* const orange_fur_material_entity = entity_factory->create_Material(orange_fur_material_struct);
        std::cout << "Creating yli::ontology::Material* orange_fur_material ...\n";
        yli::ontology::Material* const orange_fur_material = dynamic_cast<yli::ontology::Material*>(orange_fur_material_entity);

        if (orange_fur_material == nullptr)
        {
            std::cerr << "Failed to create pink geometric tiles Material.\n";
            return nullptr;
        }

        orange_fur_material->set_name("helsinki_east_downtown_orange_fur_material");

        yli::ontology::SpeciesStruct helsinki_east_downtown_terrain_species_struct;
        helsinki_east_downtown_terrain_species_struct.scene = helsinki_east_downtown_scene;
        helsinki_east_downtown_terrain_species_struct.shader = helsinki_east_downtown_shader;
        helsinki_east_downtown_terrain_species_struct.material = helsinki_east_downtown_grass_material;
        helsinki_east_downtown_terrain_species_struct.model_file_format = "ASCII_grid";
        helsinki_east_downtown_terrain_species_struct.model_filename = "L4133D.asc"; // Helsinki eastern downtown.
        helsinki_east_downtown_terrain_species_struct.light_position = glm::vec3(0, 100000, 100000);
        helsinki_east_downtown_terrain_species_struct.is_terrain = true;
        helsinki_east_downtown_terrain_species_struct.x_step = 4;
        helsinki_east_downtown_terrain_species_struct.z_step = 4;
        std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_terrain_species_entity ...\n";
        yli::ontology::Entity* const helsinki_east_downtown_terrain_species_entity = entity_factory->create_Species(helsinki_east_downtown_terrain_species_struct);
        std::cout << "Creating yli::ontology::Species* helsinki_east_downtown_terrain_species ...\n";
        yli::ontology::Species* const helsinki_east_downtown_terrain_species = dynamic_cast<yli::ontology::Species*>(helsinki_east_downtown_terrain_species_entity);

        if (helsinki_east_downtown_terrain_species == nullptr)
        {
            std::cerr << "Failed to create Species.\n";
            return nullptr;
        }

        helsinki_east_downtown_terrain_species->set_name("helsinki_east_downtown_terrain_species");

        // Create Helsinki eastern downtown terrain.
        yli::ontology::ObjectStruct helsinki_east_downtown_struct;
        helsinki_east_downtown_struct.species_parent = helsinki_east_downtown_terrain_species;
        helsinki_east_downtown_struct.cartesian_coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
        helsinki_east_downtown_struct.rotate_angle = 0.0f;
        helsinki_east_downtown_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        helsinki_east_downtown_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_Object(helsinki_east_downtown_struct);

        yli::ontology::SpeciesStruct suzanne_species_struct;
        suzanne_species_struct.scene = helsinki_east_downtown_scene;
        suzanne_species_struct.shader = helsinki_east_downtown_shader;
        suzanne_species_struct.material = orange_fur_material;
        suzanne_species_struct.model_file_format = "obj";
        suzanne_species_struct.model_filename = "suzanne.obj";
        suzanne_species_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* suzanne_species_entity ...\n";
        yli::ontology::Entity* const suzanne_species_entity = entity_factory->create_Species(suzanne_species_struct);
        std::cout << "Creating yli::ontology::Species* suzanne_species ...\n";
        yli::ontology::Species* const suzanne_species = dynamic_cast<yli::ontology::Species*>(suzanne_species_entity);

        if (suzanne_species == nullptr)
        {
            std::cerr << "Failed to create suzanne Species.\n";
            return nullptr;
        }

        suzanne_species->set_name("suzanne_species");

        // Create suzanne1, store it in `suzanne1`.
        yli::ontology::ObjectStruct suzanne_object_struct1;
        suzanne_object_struct1.species_parent = suzanne_species;
        suzanne_object_struct1.cartesian_coordinates = glm::vec3(82.50f, 119.00f, 95.50f);
        suzanne_object_struct1.rotate_angle = 0.10f;
        suzanne_object_struct1.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        suzanne_object_struct1.translate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne1_entity ...\n";
        yli::ontology::Entity* const suzanne1_entity = entity_factory->create_Object(suzanne_object_struct1);
        std::cout << "Creating yli::ontology::Species* suzanne1 ...\n";
        yli::ontology::Object* const suzanne1 = dynamic_cast<yli::ontology::Object*>(suzanne1_entity);

        if (suzanne1 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne1->set_name("suzanne1");

        suzanne_species->set_name("suzanne_species");
        yli::ontology::ObjectStruct suzanne_object_struct2;
        suzanne_object_struct2.species_parent = suzanne_species;
        suzanne_object_struct2.cartesian_coordinates = glm::vec3(112.90f, 113.90f, 75.50f);
        suzanne_object_struct2.rotate_angle = 0.20f;
        suzanne_object_struct2.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        suzanne_object_struct2.translate_vector = glm::vec3(0.0f, 1.0f, 0.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne2_entity ...\n";
        yli::ontology::Entity* const suzanne2_entity = entity_factory->create_Object(suzanne_object_struct2);
        std::cout << "Creating yli::ontology::Species* suzanne2 ...\n";
        yli::ontology::Object* const suzanne2 = dynamic_cast<yli::ontology::Object*>(suzanne2_entity);

        if (suzanne2 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne2->set_name("suzanne2");

        yli::ontology::ObjectStruct suzanne_object_struct3;
        suzanne_object_struct3.species_parent = suzanne_species;
        suzanne_object_struct3.cartesian_coordinates = glm::vec3(126.90f, 162.90f, 103.00f);
        suzanne_object_struct3.rotate_angle = 0.05f;
        suzanne_object_struct3.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        suzanne_object_struct3.translate_vector = glm::vec3(0.0f, 0.0f, 1.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne3_entity ...\n";
        yli::ontology::Entity* const suzanne3_entity = entity_factory->create_Object(suzanne_object_struct3);
        std::cout << "Creating yli::ontology::Species* suzanne3 ...\n";
        yli::ontology::Object* const suzanne3 = dynamic_cast<yli::ontology::Object*>(suzanne3_entity);

        if (suzanne3 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne3->set_name("suzanne3");

        yli::ontology::ObjectStruct suzanne_object_struct4;
        suzanne_object_struct4.species_parent = suzanne_species;
        suzanne_object_struct4.cartesian_coordinates = glm::vec3(96.00f, 130.00f, 109.00f);
        suzanne_object_struct4.rotate_angle = 0.15f;
        suzanne_object_struct4.rotate_vector = glm::vec3(1.0f, 0.0f, 0.0f);
        suzanne_object_struct4.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne4_entity ...\n";
        yli::ontology::Entity* const suzanne4_entity = entity_factory->create_Object(suzanne_object_struct4);
        std::cout << "Creating yli::ontology::Species* suzanne4 ...\n";
        yli::ontology::Object* const suzanne4 = dynamic_cast<yli::ontology::Object*>(suzanne4_entity);

        if (suzanne4 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne4->set_name("suzanne4");

        yli::ontology::ObjectStruct suzanne_object_struct5;
        suzanne_object_struct5.species_parent = suzanne_species;
        suzanne_object_struct5.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
        suzanne_object_struct5.cartesian_coordinates = glm::vec3(103.00f, 140.00f, 109.00f);
        suzanne_object_struct5.rotate_angle = 0.03f;
        suzanne_object_struct5.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        suzanne_object_struct5.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        std::cout << "Creating yli::ontology::Entity* suzanne5_entity ...\n";
        yli::ontology::Entity* const suzanne5_entity = entity_factory->create_Object(suzanne_object_struct5);
        std::cout << "Creating yli::ontology::Species* suzanne5 ...\n";
        yli::ontology::Object* const suzanne5 = dynamic_cast<yli::ontology::Object*>(suzanne5_entity);

        if (suzanne5 == nullptr)
        {
            std::cerr << "Failed to create suzanne Object.\n";
            return nullptr;
        }

        suzanne5->set_name("suzanne5");

        yli::ontology::SpeciesStruct cat_species_struct;
        cat_species_struct.scene = helsinki_east_downtown_scene;
        cat_species_struct.shader = helsinki_east_downtown_shader;
        cat_species_struct.material = orange_fur_material;
        cat_species_struct.model_file_format = "fbx";
        cat_species_struct.model_filename = "cat.fbx";
        cat_species_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* cat_species_entity ...\n";
        yli::ontology::Entity* const cat_species_entity = entity_factory->create_Species(cat_species_struct);

        std::cout << "Creating yli::ontology::Species* cat_species ...\n";
        yli::ontology::Species* const cat_species = dynamic_cast<yli::ontology::Species*>(cat_species_entity);

        if (cat_species == nullptr)
        {
            std::cerr << "Failed to create cat Species.\n";
            return nullptr;
        }

        cat_species->set_name("cat_species");

        yli::ontology::ObjectStruct cat_object_struct1;
        cat_object_struct1.species_parent = cat_species;
        cat_object_struct1.brain = rest_brain;
        cat_object_struct1.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
        cat_object_struct1.cartesian_coordinates = glm::vec3(500.00f, 100.00f, 1000.00f);
        cat_object_struct1.rotate_angle = 0.00f;
        cat_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        cat_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        yli::ontology::Entity* const cat1_entity = entity_factory->create_Object(cat_object_struct1);
        yli::ontology::Object* const cat1 = dynamic_cast<yli::ontology::Object*>(cat1_entity);

        if (cat1 == nullptr)
        {
            std::cerr << "Failed to create cat1 Object.\n";
            return nullptr;
        }

        cat1->set_name("cat1");

        yli::ontology::ObjectStruct cat_object_struct2;
        cat_object_struct2.species_parent = cat_species;
        cat_object_struct2.brain = rest_brain;
        cat_object_struct2.original_scale_vector = glm::vec3(15.0f, 15.0f, 15.0f);
        cat_object_struct2.cartesian_coordinates = glm::vec3(700.00f, 100.00f, 1200.00f);
        cat_object_struct2.rotate_angle = 0.00f;
        cat_object_struct2.rotate_vector = glm::vec3(1.5f, 1.0f, 0.9f);
        cat_object_struct2.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        yli::ontology::Entity* const cat2_entity = entity_factory->create_Object(cat_object_struct2);
        yli::ontology::Object* const cat2 = dynamic_cast<yli::ontology::Object*>(cat2_entity);

        if (cat2 == nullptr)
        {
            std::cerr << "Failed to create cat2 Object.\n";
            return nullptr;
        }

        cat2->set_name("cat2");

        yli::ontology::SymbiosisStruct freight_train_symbiosis_struct;
        freight_train_symbiosis_struct.parent = helsinki_east_downtown_shader;
        freight_train_symbiosis_struct.model_file_format = "fbx";
        freight_train_symbiosis_struct.model_filename = "freight_train.fbx";
        freight_train_symbiosis_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* freight_train_symbiosis_entity ...\n";
        yli::ontology::Entity* const freight_train_symbiosis_entity = entity_factory->create_Symbiosis(freight_train_symbiosis_struct);

        std::cout << "Creating yli::ontology::Symbiosis* freight_train_symbiosis ...\n";
        yli::ontology::Symbiosis* const freight_train_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(freight_train_symbiosis_entity);

        if (freight_train_symbiosis == nullptr)
        {
            std::cerr << "Failed to create freight_train Symbiosis.\n";
            return nullptr;
        }

        freight_train_symbiosis->set_name("freight_train_symbiosis");

        yli::ontology::HolobiontStruct freight_train_object_struct1;
        freight_train_object_struct1.symbiosis_parent = freight_train_symbiosis;
        freight_train_object_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        freight_train_object_struct1.cartesian_coordinates = glm::vec3(125.00f, 40.00f, 80.00f);
        freight_train_object_struct1.rotate_angle = 0.00f;
        freight_train_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        freight_train_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);

        std::cout << "Creating yli::ontology::Entity* freight_train1_entity ...\n";

        yli::ontology::Entity* const freight_train1_entity = entity_factory->create_Holobiont(freight_train_object_struct1);

        std::cout << "Creating yli::ontology::Holobiont* freight_train1 ...\n";

        yli::ontology::Holobiont* const freight_train1 = dynamic_cast<yli::ontology::Holobiont*>(freight_train1_entity);

        if (freight_train1 == nullptr)
        {
            std::cerr << "Failed to create freight_train1 Object.\n";
            return nullptr;
        }

        freight_train1->set_name("freight_train1");

        yli::ontology::SymbiosisStruct turbo_polizei_symbiosis_struct;
        turbo_polizei_symbiosis_struct.parent = helsinki_east_downtown_shader;
        turbo_polizei_symbiosis_struct.model_file_format = "fbx";
        turbo_polizei_symbiosis_struct.model_filename = "turbo_polizei.fbx";
        turbo_polizei_symbiosis_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* turbo_polizei_symbiosis_entity ...\n";
        yli::ontology::Entity* const turbo_polizei_symbiosis_entity = entity_factory->create_Symbiosis(turbo_polizei_symbiosis_struct);

        std::cout << "Creating yli::ontology::Symbiosis* turbo_polizei_symbiosis ...\n";
        yli::ontology::Symbiosis* const turbo_polizei_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(turbo_polizei_symbiosis_entity);

        if (turbo_polizei_symbiosis == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei Symbiosis.\n";
            return nullptr;
        }

        turbo_polizei_symbiosis->set_name("turbo_polizei_symbiosis");

        yli::ontology::HolobiontStruct turbo_polizei_object_struct1;
        turbo_polizei_object_struct1.symbiosis_parent = turbo_polizei_symbiosis;
        turbo_polizei_object_struct1.brain = rest_brain;
        turbo_polizei_object_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_object_struct1.cartesian_coordinates = glm::vec3(85.00f, 30.00f, 175.00f);
        turbo_polizei_object_struct1.rotate_angle = 0.00f;
        turbo_polizei_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        turbo_polizei_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);

        std::cout << "Creating yli::ontology::Entity* turbo_polizei1_entity ...\n";

        yli::ontology::Entity* const turbo_polizei1_entity = entity_factory->create_Holobiont(turbo_polizei_object_struct1);

        std::cout << "Creating yli::ontology::Holobiont* turbo_polizei1 ...\n";

        yli::ontology::Holobiont* const turbo_polizei1 = dynamic_cast<yli::ontology::Holobiont*>(turbo_polizei1_entity);

        if (turbo_polizei1 == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei1 Object.\n";
            return nullptr;
        }

        turbo_polizei1->set_name("turbo_polizei1");

        yli::ontology::SymbiosisStruct fantasy_house_with_balcony_symbiosis_struct;
        fantasy_house_with_balcony_symbiosis_struct.parent = helsinki_east_downtown_shader;
        fantasy_house_with_balcony_symbiosis_struct.model_file_format = "fbx";
        fantasy_house_with_balcony_symbiosis_struct.model_filename = "fantasy_house_with_balcony.fbx";
        fantasy_house_with_balcony_symbiosis_struct.light_position = glm::vec3(0, 100000, 100000);

        std::cout << "Creating yli::ontology::Entity* fantasy_house_with_balcony_symbiosis_entity ...\n";
        yli::ontology::Entity* const fantasy_house_with_balcony_symbiosis_entity = entity_factory->create_Symbiosis(fantasy_house_with_balcony_symbiosis_struct);

        std::cout << "Creating yli::ontology::Symbiosis* fantasy_house_with_balcony_symbiosis ...\n";
        yli::ontology::Symbiosis* const fantasy_house_with_balcony_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(fantasy_house_with_balcony_symbiosis_entity);

        if (fantasy_house_with_balcony_symbiosis == nullptr)
        {
            std::cerr << "Failed to create fantasy_house_with_balcony Symbiosis.\n";
            return nullptr;
        }

        fantasy_house_with_balcony_symbiosis->set_name("fantasy_house_with_balcony_symbiosis");

        yli::ontology::HolobiontStruct fantasy_house_with_balcony_object_struct1;
        fantasy_house_with_balcony_object_struct1.symbiosis_parent = fantasy_house_with_balcony_symbiosis;
        fantasy_house_with_balcony_object_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        fantasy_house_with_balcony_object_struct1.cartesian_coordinates = glm::vec3(268.00f, 59.00f, 174.00f);
        fantasy_house_with_balcony_object_struct1.rotate_angle = 0.00f;
        fantasy_house_with_balcony_object_struct1.initial_rotate_angle = 0.0f;
        fantasy_house_with_balcony_object_struct1.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        fantasy_house_with_balcony_object_struct1.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);

        std::cout << "Creating yli::ontology::Entity* fantasy_house_with_balcony1_entity ...\n";

        yli::ontology::Entity* const fantasy_house_with_balcony1_entity = entity_factory->create_Holobiont(fantasy_house_with_balcony_object_struct1);

        std::cout << "Creating yli::ontology::Holobiont* fantasy_house_with_balcony1 ...\n";

        yli::ontology::Holobiont* const fantasy_house_with_balcony1 = dynamic_cast<yli::ontology::Holobiont*>(fantasy_house_with_balcony1_entity);

        if (fantasy_house_with_balcony1 == nullptr)
        {
            std::cerr << "Failed to create fantasy_house_with_balcony1 Object.\n";
            return nullptr;
        }

        fantasy_house_with_balcony1->set_name("fantasy_house_with_balcony1");

        yli::ontology::HolobiontStruct fantasy_house_with_balcony_object_struct2;
        fantasy_house_with_balcony_object_struct2.symbiosis_parent = fantasy_house_with_balcony_symbiosis;
        fantasy_house_with_balcony_object_struct2.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        fantasy_house_with_balcony_object_struct2.cartesian_coordinates = glm::vec3(252.00f, 23.50f, 2614.00f);
        fantasy_house_with_balcony_object_struct2.rotate_angle = 0.00f;
        fantasy_house_with_balcony_object_struct2.initial_rotate_angle = PI / 2;
        fantasy_house_with_balcony_object_struct2.rotate_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        fantasy_house_with_balcony_object_struct2.initial_rotate_vector = glm::vec3(0.0f, 1.0f, 0.0f);
        fantasy_house_with_balcony_object_struct2.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);

        std::cout << "Creating yli::ontology::Entity* fantasy_house_with_balcony2_entity ...\n";

        yli::ontology::Entity* const fantasy_house_with_balcony2_entity = entity_factory->create_Holobiont(fantasy_house_with_balcony_object_struct2);

        std::cout << "Creating yli::ontology::Holobiont* fantasy_house_with_balcony2 ...\n";

        yli::ontology::Holobiont* const fantasy_house_with_balcony2 = dynamic_cast<yli::ontology::Holobiont*>(fantasy_house_with_balcony2_entity);

        if (fantasy_house_with_balcony2 == nullptr)
        {
            std::cerr << "Failed to create fantasy_house_with_balcony2 Object.\n";
            return nullptr;
        }

        fantasy_house_with_balcony2->set_name("fantasy_house_with_balcony2");

        yli::ontology::VectorFontStruct kongtext_vector_font_struct;
        kongtext_vector_font_struct.parent = helsinki_east_downtown_grass_material;
        kongtext_vector_font_struct.font_file_format = "svg";
        kongtext_vector_font_struct.font_filename = "kongtext.svg";

        std::cout << "Creating yli::ontology::Entity* kongtext_font_entity ...\n";
        yli::ontology::Entity* const kongtext_font_entity = entity_factory->create_VectorFont(kongtext_vector_font_struct);
        std::cout << "Creating yli::ontology::VectorFont* kongtext_font ...\n";
        yli::ontology::VectorFont* const kongtext_font = dynamic_cast<yli::ontology::VectorFont*>(kongtext_font_entity);

        if (kongtext_font == nullptr)
        {
            std::cerr << "Failed to create kongtext VectorFont.\n";
            return nullptr;
        }

        yli::ontology::Text3DStruct text3D_struct;
        text3D_struct.parent = kongtext_font;
        text3D_struct.text_string = "Hello world &#x26; its habitants!";
        text3D_struct.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
        text3D_struct.cartesian_coordinates = glm::vec3(100.00f, 100.00f, 100.00f);
        text3D_struct.rotate_angle = 0.0f;
        text3D_struct.rotate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        text3D_struct.translate_vector = glm::vec3(0.0f, 0.0f, 0.0f);
        entity_factory->create_Text3D(text3D_struct);

        yli::ontology::CameraStruct cat_camera_struct;
        cat_camera_struct.cartesian_coordinates = glm::vec3(800.00f, 400.00f, 950.00f);
        cat_camera_struct.parent = helsinki_east_downtown_scene;
        cat_camera_struct.horizontal_angle = -0.90f;
        cat_camera_struct.vertical_angle = -1.00f;

        std::cout << "Creating yli::ontology::Entity* cat_camera_entity ...\n";
        yli::ontology::Entity* const cat_camera_entity = entity_factory->create_Camera(cat_camera_struct);
        std::cout << "Creating yli::ontology::Camera* cat_camera ...\n";
        yli::ontology::Camera* const cat_camera = dynamic_cast<yli::ontology::Camera*>(cat_camera_entity);

        if (cat_camera == nullptr)
        {
            std::cerr << "Failed to create cat_camera Camera.\n";
            return nullptr;
        }

        cat_camera->set_name("cat_camera");

        yli::ontology::CameraStruct turbo_polizei_camera_struct;
        turbo_polizei_camera_struct.cartesian_coordinates = glm::vec3(87.00f, 28.00f, 169.00f);
        turbo_polizei_camera_struct.parent = helsinki_east_downtown_scene;
        turbo_polizei_camera_struct.horizontal_angle = -0.45f;
        turbo_polizei_camera_struct.vertical_angle = -0.05f;

        std::cout << "Creating yli::ontology::Entity* turbo_polizei_camera_entity ...\n";
        yli::ontology::Entity* const turbo_polizei_camera_entity = entity_factory->create_Camera(turbo_polizei_camera_struct);
        std::cout << "Creating yli::ontology::Camera* turbo_polizei_camera ...\n";
        yli::ontology::Camera* const turbo_polizei_camera = dynamic_cast<yli::ontology::Camera*>(turbo_polizei_camera_entity);

        if (turbo_polizei_camera == nullptr)
        {
            std::cerr << "Failed to create turbo_polizei_camera Camera.\n";
            return nullptr;
        }

        turbo_polizei_camera->set_name("turbo_polizei_camera");

        return helsinki_east_downtown_scene_entity;
        // Helsinki `Scene` ends here.
    }
}
