// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/species.hpp"
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

TEST(ObjectStruct_must_be_initialized_appropriately, ObjectStruct)
{
    const yli::ontology::ObjectStruct test_object_struct;
    ASSERT_EQ(test_object_struct.species_parent, nullptr);
    ASSERT_EQ(test_object_struct.text3D_parent, nullptr);
    ASSERT_EQ(test_object_struct.glyph, nullptr);
    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_EQ(test_object_struct.object_type, yli::ontology::ObjectType::REGULAR);
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.x));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.y));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.z));
}
