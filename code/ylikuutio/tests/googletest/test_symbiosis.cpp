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

#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(symbiosis_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene->parent_of_shaders);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene;
    model_struct.shader = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(
            *universe,
            model_struct,
            &scene->parent_of_symbioses,
            &shader->master_of_symbioses);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `shader`, `symbiosis`.

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_scene(), scene);
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);

    ASSERT_EQ(symbiosis->apprentice_of_shader.get_master(), shader);
    ASSERT_EQ(symbiosis->apprentice_of_shader.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(&(symbiosis->get_universe()), universe);
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_parent(), scene);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 0);
}

TEST(symbiosis_must_be_initialized_appropriately, headless_turbo_polizei)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene->parent_of_shaders);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene;
    model_struct.shader = shader;
    model_struct.model_filename = "turbo_polizei_png_textures.fbx";
    model_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(
            *universe,
            model_struct,
            &scene->parent_of_symbioses,
            &shader->master_of_symbioses);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `shader`, `symbiosis`.

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_scene(), scene);
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);

    ASSERT_EQ(symbiosis->apprentice_of_shader.get_master(), shader);
    ASSERT_EQ(symbiosis->apprentice_of_shader.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(&(symbiosis->get_universe()), universe);
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_parent(), scene);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 2);    // 2 `SymbiontMaterial`s.
}

TEST(symbiosis_must_bind_to_scene_appropriately, scenes)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene1->parent_of_shaders);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene1;
    model_struct.shader = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(
            *universe,
            model_struct,
            &scene1->parent_of_symbioses,
            &shader->master_of_symbioses);

    ASSERT_EQ(symbiosis->get_scene(), scene1);
    ASSERT_EQ(symbiosis->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 3); // Default `Camera`, `shader`, `symbiosis`.

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    ASSERT_EQ(symbiosis->get_scene(), scene1);
    ASSERT_EQ(symbiosis->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Symbiosis::bind_to_new_scene_parent(*symbiosis, *scene2);
    ASSERT_EQ(symbiosis->get_scene(), scene2);
    ASSERT_EQ(symbiosis->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `shader`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `symbiosis`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);

    yli::ontology::Symbiosis::bind_to_new_scene_parent(*symbiosis, *scene1);
    ASSERT_EQ(symbiosis->get_scene(), scene1);
    ASSERT_EQ(symbiosis->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 3); // Default `Camera`, `shader`, `symbiosis`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);
}

TEST(symbiosis_must_bind_to_shader_appropriately, master_and_apprentice)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(*universe, shader_struct, &scene->parent_of_shaders);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene;
    model_struct.shader = shader1;
    model_struct.model_filename = "turbo_polizei_png_textures.fbx";
    model_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(
            *universe,
            model_struct,
            &scene->parent_of_symbioses,
            &shader1->master_of_symbioses);
    ASSERT_EQ(symbiosis->get_shader(), shader1);

    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(*universe, shader_struct, &scene->parent_of_shaders);
    ASSERT_EQ(symbiosis->get_shader(), shader1);

    yli::ontology::Symbiosis::bind_to_new_shader(*symbiosis, *shader2);
    ASSERT_EQ(symbiosis->get_shader(), shader2);

    ASSERT_EQ(symbiosis->apprentice_of_shader.get_master(), shader2);
    ASSERT_EQ(symbiosis->apprentice_of_shader.get_apprenticeID(), 0);

    yli::ontology::Symbiosis::bind_to_new_shader(*symbiosis, *shader1);
    ASSERT_EQ(symbiosis->get_shader(), shader1);

    ASSERT_EQ(symbiosis->apprentice_of_shader.get_master(), shader1);
    ASSERT_EQ(symbiosis->apprentice_of_shader.get_apprenticeID(), 0);
}
