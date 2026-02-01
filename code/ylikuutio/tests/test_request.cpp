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
#include "code/ylikuutio/ontology/request.hpp"

// Include standard headers
#include <string>  // std::string
#include <utility> // std::move
#include <variant> // std::holds_alternative, std::monostate

namespace foo
{
    class Bar;
}

TEST(request_must_be_initialized_appropriately, uninitialized_request_must_have_a_valid_empty_state)
{
    yli::ontology::Request<foo::Bar> request;
    ASSERT_TRUE(std::holds_alternative<std::monostate>(request.data));
}

TEST(request_must_be_initialized_appropriately, pointer)
{
    foo::Bar* const bar_pointer1 { nullptr };
    yli::ontology::Request request(bar_pointer1);
    ASSERT_TRUE(std::holds_alternative<foo::Bar*>(request.data));
    foo::Bar* const bar_pointer2 = std::get<foo::Bar*>(request.data);
    ASSERT_EQ(bar_pointer1, bar_pointer2);
}

TEST(request_must_be_initialized_appropriately, string)
{
    yli::ontology::Request<foo::Bar> request("baz");
    ASSERT_TRUE(std::holds_alternative<std::string>(request.data));
    std::string baz_string = std::get<std::string>(request.data);
    ASSERT_EQ(baz_string, "baz");
}

TEST(request_must_be_initialized_appropriately, const_string)
{
    const std::string baz_const_string { "baz" };
    yli::ontology::Request<foo::Bar> request(baz_const_string);
    ASSERT_TRUE(std::holds_alternative<std::string>(request.data));
    std::string baz_string = std::get<std::string>(request.data);
    ASSERT_EQ(baz_string, "baz");
}
