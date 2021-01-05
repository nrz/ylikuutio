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
#include "code/ylikuutio/ontology/glyph_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

TEST(GlyphStruct_must_be_initialized_appropriately, GlyphStruct)
{
    const yli::ontology::GlyphStruct test_glyph_struct;
    ASSERT_EQ(test_glyph_struct.glyph_vertex_data, nullptr);
    ASSERT_EQ(test_glyph_struct.glyph_name_pointer, nullptr);
    ASSERT_EQ(test_glyph_struct.unicode_char_pointer, nullptr);
    ASSERT_EQ(test_glyph_struct.universe, nullptr);
    ASSERT_EQ(test_glyph_struct.shader_pointer, nullptr);
    ASSERT_EQ(test_glyph_struct.parent, nullptr);
    ASSERT_EQ(test_glyph_struct.light_position, glm::vec3(0.0f, 0.0f, 0.0f));
}
