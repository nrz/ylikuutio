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

#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/object_type.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath> // NAN, std::isnan, std::pow
#include <variant> // std::holds_alternative, std::monostate, std::variant

TEST(object_struct_must_be_initialized_appropriately, object_struct_scene_parent)
{
    const yli::ontology::ObjectStruct test_object_struct(static_cast<yli::ontology::Scene*>(nullptr));
    ASSERT_EQ(test_object_struct.scene, nullptr);
    ASSERT_FALSE(test_object_struct.mesh_master.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<std::monostate>(test_object_struct.mesh_master));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Species*>(test_object_struct.mesh_master));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::ShapeshifterSequence*>(test_object_struct.mesh_master));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Text3D*>(test_object_struct.mesh_master));
    ASSERT_EQ(test_object_struct.glyph, nullptr);
    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.x));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.y));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.z));
}

TEST(object_struct_must_be_initialized_appropriately, object_struct_scene_parent_species_master)
{
    const yli::ontology::ObjectStruct test_object_struct(
            static_cast<yli::ontology::Scene*>(nullptr),
            static_cast<yli::ontology::Species*>(nullptr));
    ASSERT_EQ(test_object_struct.scene, nullptr);
    ASSERT_FALSE(test_object_struct.mesh_master.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<std::monostate>(test_object_struct.mesh_master));
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Species*>(test_object_struct.mesh_master));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::ShapeshifterSequence*>(test_object_struct.mesh_master));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Text3D*>(test_object_struct.mesh_master));
    ASSERT_EQ(test_object_struct.glyph, nullptr);
    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.x));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.y));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.z));
}

TEST(object_struct_must_be_initialized_appropriately, object_struct_scene_parent_shapeshifter_sequence_master)
{
    const yli::ontology::ObjectStruct test_object_struct(
            static_cast<yli::ontology::Scene*>(nullptr),
            static_cast<yli::ontology::ShapeshifterSequence*>(nullptr));
    ASSERT_EQ(test_object_struct.scene, nullptr);
    ASSERT_FALSE(test_object_struct.mesh_master.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<std::monostate>(test_object_struct.mesh_master));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Species*>(test_object_struct.mesh_master));
    ASSERT_TRUE(std::holds_alternative<yli::ontology::ShapeshifterSequence*>(test_object_struct.mesh_master));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Text3D*>(test_object_struct.mesh_master));
    ASSERT_EQ(test_object_struct.glyph, nullptr);
    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.x));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.y));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.z));
}

TEST(object_struct_must_be_initialized_appropriately, object_struct_scene_parent_shapeshifter_text_3d_master)
{
    const yli::ontology::ObjectStruct test_object_struct(
            static_cast<yli::ontology::Scene*>(nullptr),
            static_cast<yli::ontology::Text3D*>(nullptr));
    ASSERT_EQ(test_object_struct.scene, nullptr);
    ASSERT_FALSE(test_object_struct.mesh_master.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<std::monostate>(test_object_struct.mesh_master));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Species*>(test_object_struct.mesh_master));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::ShapeshifterSequence*>(test_object_struct.mesh_master));
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Text3D*>(test_object_struct.mesh_master));
    ASSERT_EQ(test_object_struct.glyph, nullptr);
    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.x));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.y));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.z));
}
