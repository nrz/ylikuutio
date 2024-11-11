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
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"

// Include standard headers
#include <variant> // std::holds_alternative

TEST(material_struct_must_be_initialized_appropriately, material_struct_ecosystem_parent_nullptr_pipeline)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    const yli::ontology::MaterialStruct test_material_struct(
            (yli::ontology::Request(ecosystem)),
            (yli::ontology::Request<yli::ontology::Pipeline>(nullptr)));

    ASSERT_FALSE(test_material_struct.parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Request<yli::ontology::Ecosystem>>(test_material_struct.parent));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Request<yli::ontology::Scene>>(test_material_struct.parent));

    ASSERT_EQ(std::get<yli::ontology::Pipeline*>(test_material_struct.pipeline_master.data), nullptr);
    ASSERT_TRUE(test_material_struct.texture_file_format.empty());
    ASSERT_TRUE(test_material_struct.texture_filename.empty());
}

TEST(material_struct_must_be_initialized_appropriately, material_struct_scene_parent_nullptr_pipeline)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    const yli::ontology::MaterialStruct test_material_struct(
            (yli::ontology::Request(scene)),
            (yli::ontology::Request<yli::ontology::Pipeline>(nullptr)));

    ASSERT_FALSE(test_material_struct.parent.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Request<yli::ontology::Ecosystem>>(test_material_struct.parent));
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Request<yli::ontology::Scene>>(test_material_struct.parent));

    ASSERT_EQ(std::get<yli::ontology::Pipeline*>(test_material_struct.pipeline_master.data), nullptr);
    ASSERT_TRUE(test_material_struct.texture_file_format.empty());
    ASSERT_TRUE(test_material_struct.texture_filename.empty());
}

TEST(material_struct_must_be_initialized_appropriately, material_struct_ecosystem_parent_valid_pipeline)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    const yli::ontology::MaterialStruct test_material_struct {
            yli::ontology::Request(ecosystem),
            yli::ontology::Request(pipeline) };

    ASSERT_FALSE(test_material_struct.parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Request<yli::ontology::Ecosystem>>(test_material_struct.parent));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Request<yli::ontology::Scene>>(test_material_struct.parent));

    ASSERT_EQ(std::get<yli::ontology::Pipeline*>(test_material_struct.pipeline_master.data), pipeline);
    ASSERT_TRUE(test_material_struct.texture_file_format.empty());
    ASSERT_TRUE(test_material_struct.texture_filename.empty());
}

TEST(material_struct_must_be_initialized_appropriately, material_struct_scene_parent_valid_pipeline)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(scene) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    const yli::ontology::MaterialStruct test_material_struct {
            yli::ontology::Request(scene),
            yli::ontology::Request(pipeline) };

    ASSERT_FALSE(test_material_struct.parent.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Request<yli::ontology::Ecosystem>>(test_material_struct.parent));
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Request<yli::ontology::Scene>>(test_material_struct.parent));

    ASSERT_EQ(std::get<yli::ontology::Pipeline*>(test_material_struct.pipeline_master.data), pipeline);
    ASSERT_TRUE(test_material_struct.texture_file_format.empty());
    ASSERT_TRUE(test_material_struct.texture_filename.empty());
}

TEST(material_struct_must_be_initialized_appropriately, material_struct_ecosystem_parent_given_as_string_valid_pipeline)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(scene) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    const yli::ontology::MaterialStruct test_material_struct(
            (yli::ontology::Request<yli::ontology::Ecosystem>("foo")),
            (yli::ontology::Request(pipeline)));

    ASSERT_FALSE(test_material_struct.parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Request<yli::ontology::Ecosystem>>(test_material_struct.parent));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Request<yli::ontology::Scene>>(test_material_struct.parent));

    ASSERT_EQ(std::get<yli::ontology::Pipeline*>(test_material_struct.pipeline_master.data), pipeline);
    ASSERT_TRUE(test_material_struct.texture_file_format.empty());
    ASSERT_TRUE(test_material_struct.texture_filename.empty());
}

TEST(material_struct_must_be_initialized_appropriately, material_struct_scene_parent_given_as_string_valid_pipeline)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(scene) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    const yli::ontology::MaterialStruct test_material_struct(
            (yli::ontology::Request<yli::ontology::Scene>("foo")),
            (yli::ontology::Request(pipeline)));

    ASSERT_FALSE(test_material_struct.parent.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Request<yli::ontology::Ecosystem>>(test_material_struct.parent));
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Request<yli::ontology::Scene>>(test_material_struct.parent));

    ASSERT_EQ(std::get<yli::ontology::Pipeline*>(test_material_struct.pipeline_master.data), pipeline);
    ASSERT_TRUE(test_material_struct.texture_file_format.empty());
    ASSERT_TRUE(test_material_struct.texture_filename.empty());
}
