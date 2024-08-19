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
#include "code/ylikuutio/ontology/brain_struct.hpp"

// Include standard headers
#include <string>  // std::string
#include <variant> // std::holds_alternative, std::monostate

namespace yli::ontology
{
    class Scene;
}

TEST(brain_struct_must_be_initialized_appropriately, brain_struct)
{
    const yli::ontology::BrainStruct test_brain_struct;
    ASSERT_FALSE(test_brain_struct.parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<std::monostate>(test_brain_struct.parent));
    ASSERT_FALSE(std::holds_alternative<std::string>(test_brain_struct.parent));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Scene*>(test_brain_struct.parent));
    ASSERT_EQ(test_brain_struct.callback_engine, nullptr);
}
