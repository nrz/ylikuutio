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
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(holobiont_must_be_initialized_appropriately, headless)
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

    yli::ontology::HolobiontStruct holobiont_struct;
    holobiont_struct.scene = scene;
    holobiont_struct.parent = symbiosis;
    yli::ontology::Holobiont* const holobiont = new yli::ontology::Holobiont(
            *universe,
            holobiont_struct,
            &symbiosis->parent_of_holobionts, nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `shader`, `symbiosis`.

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_scene(), scene);
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(&(holobiont->get_universe()), universe);
    ASSERT_EQ(holobiont->get_scene(), scene);
    ASSERT_EQ(holobiont->get_parent(), symbiosis);
    ASSERT_EQ(holobiont->get_number_of_non_variable_children(), 0);
}

TEST(holobiont_must_be_initialized_appropriately, headless_turbo_polizei)
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

    yli::ontology::HolobiontStruct holobiont_struct;
    holobiont_struct.scene = scene;
    holobiont_struct.parent = symbiosis;
    yli::ontology::Holobiont* const holobiont = new yli::ontology::Holobiont(
            *universe,
            holobiont_struct,
            &symbiosis->parent_of_holobionts, nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `shader`, `symbiosis`.

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_scene(), scene);
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 3);     // 2 `SymbiontMaterial`s and 1 `Holobiont`.

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(&(holobiont->get_universe()), universe);
    ASSERT_EQ(holobiont->get_scene(), scene);
    ASSERT_EQ(holobiont->get_parent(), symbiosis);
    ASSERT_EQ(holobiont->get_number_of_non_variable_children(), 5);     // 5 `Biont`s.
}
