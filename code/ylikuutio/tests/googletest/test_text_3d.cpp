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
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/vector_font_struct.hpp"
#include "code/ylikuutio/ontology/text_3d_struct.hpp"

TEST(text_3d_must_be_initialized_and_must_bind_to_material_appropriately, headless_pipeline_and_material_are_children_of_an_ecosystem)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = ecosystem;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = ecosystem;
    material_struct.pipeline = pipeline;
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::VectorFontStruct vector_font_struct;
    vector_font_struct.parent = material;
    yli::ontology::VectorFont* const vector_font = application.get_generic_entity_factory().create_vector_font(
            vector_font_struct);

    yli::ontology::Text3DStruct text_3d_struct;
    text_3d_struct.parent = vector_font;
    yli::ontology::Text3D* text_3d = application.get_generic_entity_factory().create_text_3d(
            text_3d_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 2); // `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1); // `vector_font`.

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 1); // `text_3d`.

    // `Entity` member functions of `Text3D`.
    ASSERT_EQ(text_3d->get_childID(), 0);
    ASSERT_EQ(text_3d->get_type(), "yli::ontology::Text3D*");
    ASSERT_TRUE(text_3d->get_can_be_erased());
    ASSERT_EQ(text_3d->get_scene(), nullptr);
    ASSERT_EQ(text_3d->get_parent(), vector_font);
    ASSERT_EQ(text_3d->get_number_of_non_variable_children(), 0);
}

TEST(text_3d_must_be_initialized_and_must_bind_to_material_appropriately, headless_pipeline_and_material_are_children_of_a_scene)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    material_struct.pipeline = pipeline;
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::VectorFontStruct vector_font_struct;
    vector_font_struct.parent = material;
    yli::ontology::VectorFont* const vector_font = application.get_generic_entity_factory().create_vector_font(
            vector_font_struct);

    yli::ontology::Text3DStruct text_3d_struct;
    text_3d_struct.parent = vector_font;
    yli::ontology::Text3D* text_3d = application.get_generic_entity_factory().create_text_3d(
            text_3d_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `scene`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 1); // `text_3d`.

    // `Entity` member functions of `Text3D`.
    ASSERT_EQ(text_3d->get_childID(), 0);
    ASSERT_EQ(text_3d->get_type(), "yli::ontology::Text3D*");
    ASSERT_TRUE(text_3d->get_can_be_erased());
    ASSERT_EQ(text_3d->get_scene(), scene);
    ASSERT_EQ(text_3d->get_parent(), vector_font);
    ASSERT_EQ(text_3d->get_number_of_non_variable_children(), 0);
}
