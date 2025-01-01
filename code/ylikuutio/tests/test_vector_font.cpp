// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/vector_font_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class GenericParentModule;
}

TEST(vector_font_must_be_initialized_and_must_bind_to_material_appropriately, headless_pipeline_and_material_are_children_of_an_ecosystem_material_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct {
            yli::ontology::Request(ecosystem),
            yli::ontology::Request(pipeline) };
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::VectorFontStruct vector_font_struct { yli::ontology::Request(material) };
    yli::ontology::VectorFont* const vector_font = application.get_generic_entity_factory().create_vector_font(
            vector_font_struct);
    ASSERT_NE(vector_font, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(vector_font) % alignof(yli::ontology::VectorFont), 0);

    for (int datatype = 0; datatype < yli::data::Datatype::MAX_VALUE; datatype++)
    {
        const yli::ontology::GenericParentModule* const generic_parent_module = vector_font->get_generic_parent_module(datatype);

        if (datatype == yli::data::Datatype::GLYPH)
        {
            ASSERT_NE(generic_parent_module, nullptr);
        }
        else
        {
            ASSERT_EQ(generic_parent_module, nullptr);
        }
    }

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 2); // `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1); // `vector_font`.

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_childID(), 0);
    ASSERT_EQ(vector_font->get_type(), "yli::ontology::VectorFont*");
    ASSERT_TRUE(vector_font->get_can_be_erased());
    ASSERT_EQ(vector_font->get_scene(), nullptr);
    ASSERT_EQ(vector_font->get_parent(), material);
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);
}

TEST(vector_font_must_be_initialized_and_must_bind_to_material_appropriately, headless_pipeline_and_material_are_children_of_scene_material_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(scene) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct {
            yli::ontology::Request(scene),
            yli::ontology::Request(pipeline) };
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::VectorFontStruct vector_font_struct { yli::ontology::Request(material) };
    yli::ontology::VectorFont* const vector_font = application.get_generic_entity_factory().create_vector_font(
            vector_font_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `scene`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3);    // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1); // `vector_font`.

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_childID(), 0);
    ASSERT_EQ(vector_font->get_type(), "yli::ontology::VectorFont*");
    ASSERT_TRUE(vector_font->get_can_be_erased());
    ASSERT_EQ(vector_font->get_scene(), scene);
    ASSERT_EQ(vector_font->get_parent(), material);
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);
}

TEST(vector_font_must_be_initialized_and_must_bind_to_material_appropriately, headless_pipeline_and_material_are_children_of_an_ecosystem_material_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct {
            yli::ontology::Request(ecosystem),
            yli::ontology::Request(pipeline) };
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::VectorFontStruct vector_font_struct { yli::ontology::Request<yli::ontology::Material>(nullptr) };
    yli::ontology::VectorFont* const vector_font = application.get_generic_entity_factory().create_vector_font(
            vector_font_struct);
    ASSERT_NE(vector_font, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(vector_font) % alignof(yli::ontology::VectorFont), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 2); // `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(vector_font->get_type(), "yli::ontology::VectorFont*");
    ASSERT_TRUE(vector_font->get_can_be_erased());
    ASSERT_EQ(vector_font->get_parent(), nullptr);
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);
}

TEST(vector_font_must_be_initialized_and_must_bind_to_material_appropriately, headless_pipeline_and_material_are_children_of_an_ecosystem_material_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct {
            yli::ontology::Request(ecosystem),
            yli::ontology::Request(pipeline) };
    material_struct.global_name = "foo";
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::VectorFontStruct vector_font_struct { yli::ontology::Request<yli::ontology::Material>("foo") };
    yli::ontology::VectorFont* const vector_font = application.get_generic_entity_factory().create_vector_font(
            vector_font_struct);
    ASSERT_NE(vector_font, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(vector_font) % alignof(yli::ontology::VectorFont), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 2); // `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1); // `vector_font`.

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_childID(), 0);
    ASSERT_EQ(vector_font->get_type(), "yli::ontology::VectorFont*");
    ASSERT_TRUE(vector_font->get_can_be_erased());
    ASSERT_EQ(vector_font->get_scene(), nullptr);
    ASSERT_EQ(vector_font->get_parent(), material);
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);
}

TEST(vector_font_must_be_initialized_and_must_bind_to_material_appropriately, headless_pipeline_and_material_are_children_of_an_ecosystem_material_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct {
            yli::ontology::Request(ecosystem),
            yli::ontology::Request(pipeline) };
    material_struct.global_name = "foo";
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::VectorFontStruct vector_font_struct { yli::ontology::Request<yli::ontology::Material>("bar") };
    yli::ontology::VectorFont* const vector_font = application.get_generic_entity_factory().create_vector_font(
            vector_font_struct);
    ASSERT_NE(vector_font, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(vector_font) % alignof(yli::ontology::VectorFont), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 2); // `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(vector_font->get_type(), "yli::ontology::VectorFont*");
    ASSERT_TRUE(vector_font->get_can_be_erased());
    ASSERT_EQ(vector_font->get_parent(), nullptr);
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 0);
}
