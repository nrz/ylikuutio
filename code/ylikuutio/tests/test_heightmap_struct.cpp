// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/heightmap_struct.hpp"

TEST(heightmap_struct_must_be_initialized_appropriately, scene_provided_as_nullptr)
{
    const yli::ontology::HeightmapStruct heightmap_struct(
            yli::ontology::Request<yli::ontology::Scene>(nullptr));

    ASSERT_EQ(heightmap_struct.scene, yli::ontology::Request<yli::ontology::Scene>(nullptr));
}

TEST(heightmap_struct_must_be_initialized_appropriately, scene_provided_as_valid_global_name)
{
    const yli::ontology::HeightmapStruct heightmap_struct(
            yli::ontology::Request<yli::ontology::Scene>("foo"));

    ASSERT_EQ(heightmap_struct.scene, yli::ontology::Request<yli::ontology::Scene>("foo"));
}
