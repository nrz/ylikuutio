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
#include "code/ylikuutio/ontology/orientation_module.hpp"

TEST(orientation_module_must_be_initialized_appropriately, orientation_0_0_0)
{
    yli::ontology::OrientationModule orientation(0.0f, 0.0f, 0.0f);
    ASSERT_EQ(orientation.roll,  0.0f);
    ASSERT_EQ(orientation.yaw,   0.0f);
    ASSERT_EQ(orientation.pitch, 0.0f);
}

TEST(orientation_module_must_be_initialized_appropriately, orientation_1_2_3)
{
    yli::ontology::OrientationModule orientation(1.0f, 2.0f, 3.0f);
    ASSERT_EQ(orientation.roll,  1.0f);
    ASSERT_EQ(orientation.yaw,   2.0f);
    ASSERT_EQ(orientation.pitch, 3.0f);
}
