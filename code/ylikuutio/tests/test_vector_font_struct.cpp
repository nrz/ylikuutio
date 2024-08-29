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
#include "code/ylikuutio/ontology/vector_font_struct.hpp"

TEST(vector_font_struct_must_be_initialized_appropriately, vector_font_struct)
{
    const float default_vertex_scaling_factor = 0.001f;

    const yli::ontology::VectorFontStruct test_vector_font_struct;
    ASSERT_EQ(test_vector_font_struct.material_parent, nullptr);
    ASSERT_EQ(test_vector_font_struct.vertex_scaling_factor, default_vertex_scaling_factor);
    ASSERT_TRUE(test_vector_font_struct.font_file_format.empty());
    ASSERT_TRUE(test_vector_font_struct.font_filename.empty());
}
