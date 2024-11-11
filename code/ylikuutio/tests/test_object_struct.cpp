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
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>   // std::isnan
#include <string>  // std::string
#include <variant> // std::holds_alternative

TEST(object_struct_must_be_initialized_appropriately, object_struct_scene_parent)
{
    const yli::ontology::ObjectStruct test_object_struct(yli::ontology::Request<yli::ontology::Scene>(nullptr));

    ASSERT_TRUE(std::holds_alternative<yli::ontology::Scene*>(test_object_struct.scene.data));
    ASSERT_FALSE(std::holds_alternative<std::string>(test_object_struct.scene.data));
    ASSERT_EQ(std::get<yli::ontology::Scene*>(test_object_struct.scene.data), nullptr);

    ASSERT_FALSE(test_object_struct.species_master.data.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Species*>(test_object_struct.species_master.data));

    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.x));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.y));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.z));
}

TEST(object_struct_must_be_initialized_appropriately, object_struct_scene_parent_species_master)
{
    const yli::ontology::ObjectStruct test_object_struct {
            yli::ontology::Request<yli::ontology::Scene>(nullptr),
            yli::ontology::Request<yli::ontology::Species>(nullptr) };

    ASSERT_FALSE(test_object_struct.scene.data.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Scene*>(test_object_struct.scene.data));
    ASSERT_FALSE(std::holds_alternative<std::string>(test_object_struct.scene.data));
    ASSERT_EQ(std::get<yli::ontology::Scene*>(test_object_struct.scene.data), nullptr);

    ASSERT_FALSE(test_object_struct.species_master.data.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Species*>(test_object_struct.species_master.data));

    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.x));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.y));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.xyz.z));
}
