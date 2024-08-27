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
#include "code/ylikuutio/ontology/model_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.
#include <variant>  // std::holds_alternative, std::monostate
#include <vector>   // std::vector

namespace yli::ontology
{
    class Ecosystem;
    class Scene;
    class Material;
    class SymbiontMaterial;
    class VectorFont;
}

TEST(model_struct_must_be_initialized_appropriately, model_struct)
{
    const yli::ontology::ModelStruct test_model_struct;
    ASSERT_EQ(test_model_struct.model_filename, "");
    ASSERT_EQ(test_model_struct.model_file_format, "");
    ASSERT_EQ(test_model_struct.color_channel, "");
    ASSERT_EQ(test_model_struct.divisor, 1.0f);
    ASSERT_EQ(test_model_struct.latitude, 0.0f);
    ASSERT_EQ(test_model_struct.longitude, 0.0f);
    ASSERT_EQ(test_model_struct.mesh_i, 0);
    ASSERT_EQ(test_model_struct.x_step, 1);
    ASSERT_EQ(test_model_struct.y_step, 1);
    ASSERT_EQ(test_model_struct.vertices, std::vector<glm::vec3> { });
    ASSERT_EQ(test_model_struct.uvs, std::vector<glm::vec2> { });
    ASSERT_EQ(test_model_struct.normals, std::vector<glm::vec3> { });

    ASSERT_FALSE(test_model_struct.parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<std::monostate>(test_model_struct.parent));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Ecosystem*>(test_model_struct.parent));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Scene*>(test_model_struct.parent));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::VectorFont*>(test_model_struct.parent));

    ASSERT_EQ(test_model_struct.pipeline, nullptr);

    ASSERT_FALSE(test_model_struct.material_or_symbiont_material.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<std::monostate>(test_model_struct.material_or_symbiont_material));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Material*>(test_model_struct.material_or_symbiont_material));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::SymbiontMaterial*>(test_model_struct.material_or_symbiont_material));

    ASSERT_EQ(test_model_struct.shapeshifter_transformation, nullptr);
    ASSERT_EQ(test_model_struct.glyph_vertex_data, nullptr);
    ASSERT_EQ(test_model_struct.glyph_name_pointer, nullptr);
    ASSERT_EQ(test_model_struct.unicode_char_pointer, nullptr);
    ASSERT_EQ(test_model_struct.vertex_count, std::numeric_limits<std::uint32_t>::max());
    ASSERT_TRUE(test_model_struct.use_real_texture_coordinates);
}
