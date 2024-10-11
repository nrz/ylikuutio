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
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

namespace yli::ontology
{
    class GenericParentModule;
}

TEST(font_2d_must_be_initialized_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::FontStruct font_struct;
    font_struct.screen_width = application.get_universe().get_window_width();
    font_struct.screen_height = application.get_universe().get_window_height();
    font_struct.text_size = application.get_universe().get_text_size();
    font_struct.font_size = application.get_universe().get_font_size();
    yli::ontology::Font2d* const font_2d = application.get_generic_entity_factory().create_font_2d(
            font_struct);
    ASSERT_NE(font_2d, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(font_2d) % alignof(yli::ontology::Font2d), 0);

    for (int datatype = 0; datatype < yli::data::Datatype::MAX_VALUE; datatype++)
    {
        const yli::ontology::GenericParentModule* const generic_parent_module = font_2d->get_generic_parent_module(datatype);

        if (datatype == yli::data::Datatype::TEXT_2D)
        {
            ASSERT_NE(generic_parent_module, nullptr);
        }
        else
        {
            ASSERT_EQ(generic_parent_module, nullptr);
        }
    }

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Font2d`.
    ASSERT_EQ(font_2d->get_childID(), 0);
    ASSERT_EQ(font_2d->get_type(), "yli::ontology::Font2d*");
    ASSERT_FALSE(font_2d->get_can_be_erased());               // Currently `Font2d`s can not be erased.
    ASSERT_EQ(font_2d->get_scene(), nullptr);
    ASSERT_EQ(font_2d->get_parent(), &application.get_universe());
    ASSERT_EQ(font_2d->get_number_of_non_variable_children(), 0);
}

TEST(font_2d_must_be_initialized_appropriately, headless_holstein)
{
    mock::MockApplication application;
    yli::ontology::FontStruct font_struct;
    font_struct.texture_filename = "Holstein.png";
    font_struct.font_texture_file_format = "PNG";
    font_struct.screen_width = application.get_universe().get_window_width();
    font_struct.screen_height = application.get_universe().get_window_height();
    font_struct.text_size = application.get_universe().get_text_size();
    font_struct.font_size = application.get_universe().get_font_size();
    yli::ontology::Font2d* const font_2d = application.get_generic_entity_factory().create_font_2d(
            font_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Font2d`.
    ASSERT_EQ(font_2d->get_childID(), 0);
    ASSERT_EQ(font_2d->get_type(), "yli::ontology::Font2d*");
    ASSERT_FALSE(font_2d->get_can_be_erased());               // Currently `Font2d`s can not be erased.
    ASSERT_EQ(font_2d->get_scene(), nullptr);
    ASSERT_EQ(font_2d->get_parent(), &application.get_universe());
    ASSERT_EQ(font_2d->get_number_of_non_variable_children(), 0);
}
