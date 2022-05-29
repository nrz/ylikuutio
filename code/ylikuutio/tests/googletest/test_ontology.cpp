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
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/shapeshifter_form.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence_struct.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <limits>  // std::numeric_limits

TEST(font_2d_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::FontStruct font_struct;
    font_struct.screen_width = universe->get_window_width();
    font_struct.screen_height = universe->get_window_height();
    font_struct.text_size = universe->get_text_size();
    font_struct.font_size = universe->get_font_size();
    yli::ontology::Font2D* const font_2d = new yli::ontology::Font2D(
            *universe,
            font_struct,
            &universe->parent_of_font_2ds);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Font2D`.
    ASSERT_EQ(font_2d->get_childID(), 0);
    ASSERT_EQ(font_2d->get_type(), "yli::ontology::Font2D*");
    ASSERT_FALSE(font_2d->get_can_be_erased());               // Currently `Font2D`s can not be erased.
    ASSERT_EQ(&(font_2d->get_universe()), universe);
    ASSERT_EQ(font_2d->get_scene(), nullptr);
    ASSERT_EQ(font_2d->get_parent(), universe);
    ASSERT_EQ(font_2d->get_number_of_non_variable_children(), 0);
}

TEST(font_2d_must_be_initialized_appropriately, headless_holstein)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::FontStruct font_struct;
    font_struct.texture_filename = "Holstein.png";
    font_struct.font_texture_file_format = "PNG";
    font_struct.screen_width = universe->get_window_width();
    font_struct.screen_height = universe->get_window_height();
    font_struct.text_size = universe->get_text_size();
    font_struct.font_size = universe->get_font_size();
    yli::ontology::Font2D* const font_2d = new yli::ontology::Font2D(
            *universe,
            font_struct,
            &universe->parent_of_font_2ds);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Font2D`.
    ASSERT_EQ(font_2d->get_childID(), 0);
    ASSERT_EQ(font_2d->get_type(), "yli::ontology::Font2D*");
    ASSERT_FALSE(font_2d->get_can_be_erased());               // Currently `Font2D`s can not be erased.
    ASSERT_EQ(&(font_2d->get_universe()), universe);
    ASSERT_EQ(font_2d->get_scene(), nullptr);
    ASSERT_EQ(font_2d->get_parent(), universe);
    ASSERT_EQ(font_2d->get_number_of_non_variable_children(), 0);
}

TEST(input_system_must_be_set_to_nullptr_in_headless_mode, universe)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    ASSERT_EQ(universe->get_input_system(), nullptr);
    ASSERT_EQ(universe->get_input_method(), yli::input::InputMethod::KEYBOARD);
}

TEST(input_system_must_be_set_to_nullptr_when_using_software_rendering, universe)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::SOFTWARE);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    ASSERT_EQ(universe->get_input_system(), nullptr);
    ASSERT_EQ(universe->get_input_method(), yli::input::InputMethod::KEYBOARD);
}
