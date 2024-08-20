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

#include "gtest/gtest.h"
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

TEST(holobiont_must_be_initialized_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.pipeline = pipeline;
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);

    yli::ontology::HolobiontStruct holobiont_struct(*scene, *symbiosis);
    yli::ontology::Holobiont* const holobiont = application.get_generic_entity_factory().create_holobiont(
            holobiont_struct);
    ASSERT_NE(holobiont, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(holobiont) % alignof(yli::ontology::Holobiont), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 4); // Default `Camera`, `pipeline`, `symbiosis`, `holobiont`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(holobiont->get_scene(), scene);
    ASSERT_EQ(holobiont->get_parent(), scene);
    ASSERT_EQ(holobiont->get_number_of_non_variable_children(), 0);
}

TEST(holobiont_must_be_initialized_appropriately, headless_turbo_polizei)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.pipeline = pipeline;
    model_struct.model_filename = "turbo_polizei_png_textures.fbx";
    model_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);

    yli::ontology::HolobiontStruct holobiont_struct(*scene, *symbiosis);
    yli::ontology::Holobiont* const holobiont = application.get_generic_entity_factory().create_holobiont(
            holobiont_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 4); // Default `Camera`, `pipeline`, `symbiosis`, `holobiont`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 2);     // 2 `SymbiontMaterial`s.

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(holobiont->get_scene(), scene);
    ASSERT_EQ(holobiont->get_parent(), scene);
    ASSERT_EQ(holobiont->get_number_of_non_variable_children(), 5);     // 5 `Biont`s.
}
