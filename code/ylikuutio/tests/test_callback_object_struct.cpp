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
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/callback_object_struct.hpp"

// Include standard headers
#include <string>  // std::string
#include <variant> // std::holds_alternative

namespace yli::ontology
{
    class CallbackEngine;
}

TEST(callback_object_struct_must_be_initialized_appropriately, parent_provided_as_nullptr)
{
    const yli::ontology::CallbackObjectStruct test_callback_object_struct { yli::ontology::Request<yli::ontology::CallbackEngine>(nullptr) };

    ASSERT_FALSE(test_callback_object_struct.callback_engine_parent.data.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::CallbackEngine*>(test_callback_object_struct.callback_engine_parent.data));
    ASSERT_FALSE(std::holds_alternative<std::string>(test_callback_object_struct.callback_engine_parent.data));
    ASSERT_EQ(std::get<yli::ontology::CallbackEngine*>(test_callback_object_struct.callback_engine_parent.data), nullptr);
}

TEST(callback_object_struct_must_be_initialized_appropriately, parent_provided_as_global_name)
{
    const yli::ontology::CallbackObjectStruct test_callback_object_struct { yli::ontology::Request<yli::ontology::CallbackEngine>("foo") };

    ASSERT_FALSE(test_callback_object_struct.callback_engine_parent.data.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::CallbackEngine*>(test_callback_object_struct.callback_engine_parent.data));
    ASSERT_TRUE(std::holds_alternative<std::string>(test_callback_object_struct.callback_engine_parent.data));
    ASSERT_EQ(std::get<std::string>(test_callback_object_struct.callback_engine_parent.data), "foo");
}
