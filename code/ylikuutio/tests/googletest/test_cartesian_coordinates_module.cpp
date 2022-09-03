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
#include "code/ylikuutio/ontology/cartesian_coordinates_module.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

TEST(cartesian_coordinates_module_must_be_initialized_appropriately, location_0_0_0)
{
    yli::ontology::CartesianCoordinatesModule location(glm::vec3 { 0.0f, 0.0f, 0.0f });
    ASSERT_EQ(location.cartesian_coordinates.x, 0.0f);
    ASSERT_EQ(location.cartesian_coordinates.y, 0.0f);
    ASSERT_EQ(location.cartesian_coordinates.z, 0.0f);
}

TEST(cartesian_coordinates_module_must_be_initialized_appropriately, location_1_2_3)
{
    yli::ontology::CartesianCoordinatesModule location(glm::vec3 { 1.0f, 2.0f, 3.0f });
    ASSERT_EQ(location.cartesian_coordinates.x, 1.0f);
    ASSERT_EQ(location.cartesian_coordinates.y, 2.0f);
    ASSERT_EQ(location.cartesian_coordinates.z, 3.0f);
}
