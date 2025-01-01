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
#include "code/ylikuutio/load/symbiosis_loader_struct.hpp"

// Include standard headers
#include <string> // std::string

TEST(symbiosis_loader_struct_must_be_initialized_appropriately, symbiosis_loader_struct)
{
    const std::string model_filename    { "foo" };
    const std::string model_file_format { "bar" };
    const yli::load::SymbiosisLoaderStruct symbiosis_loader_struct(model_filename, model_file_format);

    ASSERT_EQ(symbiosis_loader_struct.model_filename, "foo");
    ASSERT_EQ(symbiosis_loader_struct.model_file_format, "bar");
}
