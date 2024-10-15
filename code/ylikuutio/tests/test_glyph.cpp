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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/glyph_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class Object;
}

TEST(glyph_must_be_initialized_appropriately, vector_font_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::VectorFontStruct vector_font_struct(nullptr);
    yli::ontology::VectorFont* const vector_font = application.get_generic_entity_factory().create_vector_font(
            vector_font_struct);
    yli::ontology::GlyphStruct glyph_struct(vector_font);
    yli::ontology::Glyph* const glyph = application.get_generic_entity_factory().create_glyph(
            glyph_struct);
    ASSERT_NE(glyph, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(glyph) % alignof(yli::ontology::Glyph), 0);

    ASSERT_NE(glyph->get_generic_master_module<yli::ontology::Object>(), nullptr);

    // `Entity` member functions of `VectorFont`.
    ASSERT_EQ(vector_font->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(glyph->get_childID(), 0);
    ASSERT_EQ(glyph->get_type(), "yli::ontology::Glyph*");
    ASSERT_FALSE(glyph->get_can_be_erased());
    ASSERT_EQ(glyph->get_parent(), vector_font);
    ASSERT_EQ(glyph->get_number_of_non_variable_children(), 0);
}

TEST(glyph_must_be_initialized_appropriately, vector_font_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::GlyphStruct glyph_struct(nullptr);
    yli::ontology::Glyph* const glyph = application.get_generic_entity_factory().create_glyph(
            glyph_struct);
    ASSERT_NE(glyph, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(glyph) % alignof(yli::ontology::Glyph), 0);

    // `Entity` member functions.
    ASSERT_EQ(glyph->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(glyph->get_type(), "yli::ontology::Glyph*");
    ASSERT_FALSE(glyph->get_can_be_erased());
    ASSERT_EQ(glyph->get_parent(), nullptr);
    ASSERT_EQ(glyph->get_number_of_non_variable_children(), 0);
}
