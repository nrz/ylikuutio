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
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"

namespace yli::ontology
{
    class Ecosystem;
    class Scene;
    class Pipeline;
}

// Include standard headers
#include <string>  // std::string
#include <variant> // std::get, std::holds_alternative

TEST(symbiosis_struct_must_be_initialized_appropriately, symbiosis_struct_ecosystem_parent_provided_as_nullptr)
{
    yli::ontology::SymbiosisStruct symbiosis_struct(
            static_cast<yli::ontology::Ecosystem*>(nullptr),
            static_cast<yli::ontology::Pipeline*>(nullptr));

    ASSERT_FALSE(symbiosis_struct.parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Ecosystem*>(symbiosis_struct.parent));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Scene*>(symbiosis_struct.parent));
    ASSERT_FALSE(std::holds_alternative<std::string>(symbiosis_struct.parent));
    ASSERT_EQ(std::get<yli::ontology::Ecosystem*>(symbiosis_struct.parent), nullptr);
}

TEST(symbiosis_struct_must_be_initialized_appropriately, symbiosis_struct_scene_parent_provided_as_nullptr)
{
    yli::ontology::SymbiosisStruct symbiosis_struct(
            static_cast<yli::ontology::Scene*>(nullptr),
            static_cast<yli::ontology::Pipeline*>(nullptr));

    ASSERT_FALSE(symbiosis_struct.parent.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Ecosystem*>(symbiosis_struct.parent));
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Scene*>(symbiosis_struct.parent));
    ASSERT_FALSE(std::holds_alternative<std::string>(symbiosis_struct.parent));
    ASSERT_EQ(std::get<yli::ontology::Scene*>(symbiosis_struct.parent), nullptr);
}

TEST(symbiosis_struct_must_be_initialized_appropriately, symbiosis_struct_string_parent)
{
    yli::ontology::SymbiosisStruct symbiosis_struct(
            "foo",
            static_cast<yli::ontology::Pipeline*>(nullptr));

    ASSERT_FALSE(symbiosis_struct.parent.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Ecosystem*>(symbiosis_struct.parent));
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Scene*>(symbiosis_struct.parent));
    ASSERT_TRUE(std::holds_alternative<std::string>(symbiosis_struct.parent));
    ASSERT_EQ(std::get<std::string>(symbiosis_struct.parent), "foo");
}
