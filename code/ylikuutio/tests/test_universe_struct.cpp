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
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(universe_struct_must_be_initialized_appropriately, universe_struct_opengl)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
    ASSERT_EQ(universe_struct.graphics_api_backend, yli::render::GraphicsApiBackend::OPENGL);
    ASSERT_TRUE(universe_struct.is_universe);
}

TEST(universe_struct_must_be_initialized_appropriately, universe_struct_vulkan)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::VULKAN);
    ASSERT_EQ(universe_struct.graphics_api_backend, yli::render::GraphicsApiBackend::VULKAN);
    ASSERT_TRUE(universe_struct.is_universe);
}

TEST(universe_struct_must_be_initialized_appropriately, universe_struct_software)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::SOFTWARE);
    ASSERT_EQ(universe_struct.graphics_api_backend, yli::render::GraphicsApiBackend::SOFTWARE);
    ASSERT_TRUE(universe_struct.is_universe);
}

TEST(universe_struct_must_be_initialized_appropriately, universe_struct_headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    ASSERT_EQ(universe_struct.graphics_api_backend, yli::render::GraphicsApiBackend::HEADLESS);
    ASSERT_TRUE(universe_struct.is_universe);
}
