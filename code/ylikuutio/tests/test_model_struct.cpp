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
#include "code/ylikuutio/ontology/mesh_provider_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

TEST(mesh_provider_struct_must_be_initialized_appropriately, mesh_provider_struct)
{
    const yli::ontology::MeshProviderStruct test_mesh_provider_struct;
    ASSERT_EQ(test_mesh_provider_struct.model_loader_struct.model_filename, "");
    ASSERT_EQ(test_mesh_provider_struct.model_loader_struct.model_file_format, "");
    ASSERT_EQ(test_mesh_provider_struct.model_loader_struct.color_channel, "");
    ASSERT_EQ(test_mesh_provider_struct.model_loader_struct.divisor, 1.0f);
    ASSERT_EQ(test_mesh_provider_struct.model_loader_struct.latitude, 0.0f);
    ASSERT_EQ(test_mesh_provider_struct.model_loader_struct.longitude, 0.0f);
    ASSERT_EQ(test_mesh_provider_struct.model_loader_struct.mesh_i, 0);
    ASSERT_EQ(test_mesh_provider_struct.model_loader_struct.x_step, 1);
    ASSERT_EQ(test_mesh_provider_struct.model_loader_struct.y_step, 1);
    ASSERT_EQ(test_mesh_provider_struct.vertices, std::vector<glm::vec3> { });
    ASSERT_EQ(test_mesh_provider_struct.uvs, std::vector<glm::vec2> { });
    ASSERT_EQ(test_mesh_provider_struct.normals, std::vector<glm::vec3> { });
}
