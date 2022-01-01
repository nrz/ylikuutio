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
#include "code/ylikuutio/data/any_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <variant>  // std::holds_alternative, std::variant
#include <vector>   // std::vector

TEST(any_struct_must_be_initialized_appropriately, no_fields)
{
    yli::data::AnyStruct empty_any_struct = yli::data::AnyStruct();
    std::vector<std::string> fieldnames = empty_any_struct.get_fieldnames();
    ASSERT_TRUE(fieldnames.empty());
}

TEST(any_struct_must_be_initialized_appropriately, field_must_not_exist)
{
    yli::data::AnyStruct empty_any_struct = yli::data::AnyStruct();
    const std::string foo_target = "foo";
    ASSERT_FALSE(empty_any_struct.check_if_exist(foo_target));
}

TEST(any_struct_must_be_initialized_appropriately, erase_data_must_fail_for_nonexisting_field)
{
    yli::data::AnyStruct empty_any_struct = yli::data::AnyStruct();
    const std::string foo_target = "foo";
    ASSERT_FALSE(empty_any_struct.erase_data(foo_target));
}

TEST(any_struct_must_function_appropriately, enter_data_simple)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    // pseudocode: any_struct.foo = 0xdeadbeef
    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string foo_target = "foo";
    ASSERT_TRUE(any_struct.enter_data(foo_target, deadbeef_any_value_shared_ptr));

    // pseudocode: any_struct.bar = 0xca7f00d
    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string bar_target = "bar";
    ASSERT_TRUE(any_struct.enter_data(bar_target, catfood_any_value_shared_ptr));
}

TEST(any_struct_must_function_appropriately, check_if_exist_simple)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string foo_target = "foo";
    ASSERT_FALSE(any_struct.check_if_exist(foo_target));
    ASSERT_TRUE(any_struct.enter_data(foo_target, deadbeef_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist(foo_target));

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string bar_target = "bar";
    ASSERT_TRUE(any_struct.check_if_exist(foo_target));
    ASSERT_FALSE(any_struct.check_if_exist(bar_target));
    ASSERT_TRUE(any_struct.enter_data(bar_target, catfood_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist(foo_target));
    ASSERT_TRUE(any_struct.check_if_exist(bar_target));
}

TEST(any_struct_must_function_appropriately, get_fieldnames_simple)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();
    std::vector<std::string> fieldnames = any_struct.get_fieldnames();
    ASSERT_TRUE(fieldnames.empty());

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string foo_target = "foo";
    ASSERT_TRUE(any_struct.enter_data(foo_target, deadbeef_any_value_shared_ptr));

    fieldnames = any_struct.get_fieldnames();
    ASSERT_FALSE(fieldnames.empty());
    ASSERT_EQ(fieldnames.size(), 1);
    ASSERT_TRUE(fieldnames[0] == "foo");

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string bar_target = "bar";
    ASSERT_TRUE(any_struct.enter_data(bar_target, catfood_any_value_shared_ptr));

    fieldnames = any_struct.get_fieldnames();
    ASSERT_FALSE(fieldnames.empty());
    ASSERT_EQ(fieldnames.size(), 2);
    ASSERT_TRUE(fieldnames[0] == "bar");
    ASSERT_TRUE(fieldnames[1] == "foo");
}

TEST(any_struct_must_function_appropriately, read_data_simple)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();
    // pseudocode: foo_nonexistent_any_value_shared_ptr1 = any_struct.foo
    std::shared_ptr<yli::data::AnyValue> foo_nonexistent_any_value_shared_ptr1 = any_struct.read_data("foo");
    ASSERT_EQ(foo_nonexistent_any_value_shared_ptr1, nullptr);
    // pseudocode: bar_nonexistent_any_value_shared_ptr1 = any_struct.bar
    std::shared_ptr<yli::data::AnyValue> bar_nonexistent_any_value_shared_ptr1 = any_struct.read_data("bar");
    ASSERT_EQ(bar_nonexistent_any_value_shared_ptr1, nullptr);

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string foo_target = "foo";
    ASSERT_TRUE(any_struct.enter_data(foo_target, deadbeef_any_value_shared_ptr));

    // pseudocode: foo_any_value_shared_ptr1 = any_struct.foo
    std::shared_ptr<yli::data::AnyValue> foo_any_value_shared_ptr1 = any_struct.read_data("foo");
    ASSERT_NE(foo_any_value_shared_ptr1, nullptr);
    ASSERT_EQ(foo_any_value_shared_ptr1->get_datatype(), "uint32_t");
    ASSERT_EQ(std::get<uint32_t>(foo_any_value_shared_ptr1->data), 0xdeadbeef);

    // pseudocode: bar_nonexistent_any_value_shared_ptr2 = any_struct.bar
    std::shared_ptr<yli::data::AnyValue> bar_nonexistent_any_value_shared_ptr2 = any_struct.read_data("bar");
    ASSERT_EQ(bar_nonexistent_any_value_shared_ptr2, nullptr);

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string bar_target = "bar";
    ASSERT_TRUE(any_struct.enter_data(bar_target, catfood_any_value_shared_ptr));

    // pseudocode: foo_any_value_shared_ptr2 = any_struct.foo
    std::shared_ptr<yli::data::AnyValue> foo_any_value_shared_ptr2 = any_struct.read_data("foo");
    ASSERT_NE(foo_any_value_shared_ptr2, nullptr);
    ASSERT_EQ(foo_any_value_shared_ptr2->get_datatype(), "uint32_t");
    ASSERT_EQ(std::get<uint32_t>(foo_any_value_shared_ptr2->data), 0xdeadbeef);

    // pseudocode: bar_any_value_shared_ptr1 = any_struct.bar
    std::shared_ptr<yli::data::AnyValue> bar_any_value_shared_ptr1 = any_struct.read_data("bar");
    ASSERT_NE(bar_any_value_shared_ptr1, nullptr);
    ASSERT_EQ(bar_any_value_shared_ptr1->get_datatype(), "uint32_t");
    ASSERT_EQ(std::get<uint32_t>(bar_any_value_shared_ptr1->data), 0xca7f00d);
}

TEST(any_struct_must_function_appropriately, erase_data_check_if_exist_simple)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string foo_target = "foo";
    ASSERT_FALSE(any_struct.check_if_exist(foo_target));
    ASSERT_TRUE(any_struct.enter_data(foo_target, deadbeef_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist(foo_target));

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string bar_target = "bar";
    ASSERT_TRUE(any_struct.check_if_exist(foo_target));
    ASSERT_FALSE(any_struct.check_if_exist(bar_target));
    ASSERT_TRUE(any_struct.enter_data(bar_target, catfood_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist(foo_target));
    ASSERT_TRUE(any_struct.check_if_exist(bar_target));

    ASSERT_TRUE(any_struct.erase_data(foo_target));
    ASSERT_FALSE(any_struct.check_if_exist(foo_target));
    ASSERT_TRUE(any_struct.check_if_exist(bar_target));

    ASSERT_TRUE(any_struct.erase_data(bar_target));
    ASSERT_FALSE(any_struct.check_if_exist(foo_target));
    ASSERT_FALSE(any_struct.check_if_exist(bar_target));
}

TEST(any_struct_must_function_appropriately, erase_data_read_data_simple)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();
    std::shared_ptr<yli::data::AnyValue> foo_nonexistent_any_value_shared_ptr1 = any_struct.read_data("foo");
    ASSERT_EQ(foo_nonexistent_any_value_shared_ptr1, nullptr);
    std::shared_ptr<yli::data::AnyValue> bar_nonexistent_any_value_shared_ptr1 = any_struct.read_data("bar");
    ASSERT_EQ(bar_nonexistent_any_value_shared_ptr1, nullptr);

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string foo_target = "foo";
    ASSERT_TRUE(any_struct.enter_data(foo_target, deadbeef_any_value_shared_ptr));

    std::shared_ptr<yli::data::AnyValue> foo_any_value_shared_ptr1 = any_struct.read_data("foo");
    ASSERT_NE(foo_any_value_shared_ptr1, nullptr);
    ASSERT_EQ(foo_any_value_shared_ptr1->get_datatype(), "uint32_t");
    ASSERT_EQ(std::get<uint32_t>(foo_any_value_shared_ptr1->data), 0xdeadbeef);

    std::shared_ptr<yli::data::AnyValue> bar_nonexistent_any_value_shared_ptr2 = any_struct.read_data("bar");
    ASSERT_EQ(bar_nonexistent_any_value_shared_ptr2, nullptr);

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string bar_target = "bar";
    ASSERT_TRUE(any_struct.enter_data(bar_target, catfood_any_value_shared_ptr));

    std::shared_ptr<yli::data::AnyValue> foo_any_value_shared_ptr2 = any_struct.read_data("foo");
    ASSERT_NE(foo_any_value_shared_ptr2, nullptr);
    ASSERT_EQ(foo_any_value_shared_ptr2->get_datatype(), "uint32_t");
    ASSERT_EQ(std::get<uint32_t>(foo_any_value_shared_ptr2->data), 0xdeadbeef);

    std::shared_ptr<yli::data::AnyValue> bar_any_value_shared_ptr1 = any_struct.read_data("bar");
    ASSERT_NE(bar_any_value_shared_ptr1, nullptr);
    ASSERT_EQ(bar_any_value_shared_ptr1->get_datatype(), "uint32_t");
    ASSERT_EQ(std::get<uint32_t>(bar_any_value_shared_ptr1->data), 0xca7f00d);

    ASSERT_TRUE(any_struct.erase_data(foo_target));
    std::shared_ptr<yli::data::AnyValue> foo_nonexistent_any_value_shared_ptr2 = any_struct.read_data("foo");
    ASSERT_EQ(foo_nonexistent_any_value_shared_ptr2, nullptr);

    std::shared_ptr<yli::data::AnyValue> bar_any_value_shared_ptr2 = any_struct.read_data("bar");
    ASSERT_NE(bar_any_value_shared_ptr2, nullptr);
    ASSERT_EQ(bar_any_value_shared_ptr2->get_datatype(), "uint32_t");
    ASSERT_EQ(std::get<uint32_t>(bar_any_value_shared_ptr2->data), 0xca7f00d);

    ASSERT_TRUE(any_struct.erase_data(bar_target));
    std::shared_ptr<yli::data::AnyValue> foo_nonexistent_any_value_shared_ptr3 = any_struct.read_data("foo");
    ASSERT_EQ(foo_nonexistent_any_value_shared_ptr3, nullptr);
    std::shared_ptr<yli::data::AnyValue> bar_nonexistent_any_value_shared_ptr3 = any_struct.read_data("bar");
    ASSERT_EQ(bar_nonexistent_any_value_shared_ptr3, nullptr);
}

TEST(any_struct_must_function_appropriately, all_functionality_simple)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();
    std::vector<std::string> fieldnames = any_struct.get_fieldnames();
    ASSERT_TRUE(fieldnames.empty());

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string foo_target = "foo";
    ASSERT_FALSE(any_struct.check_if_exist(foo_target));
    ASSERT_TRUE(any_struct.enter_data(foo_target, deadbeef_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist(foo_target));

    fieldnames = any_struct.get_fieldnames();
    ASSERT_FALSE(fieldnames.empty());
    ASSERT_EQ(fieldnames.size(), 1);
    ASSERT_TRUE(fieldnames[0] == "foo");

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string bar_target = "bar";
    ASSERT_TRUE(any_struct.check_if_exist(foo_target));
    ASSERT_FALSE(any_struct.check_if_exist(bar_target));
    ASSERT_TRUE(any_struct.enter_data(bar_target, catfood_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist(foo_target));
    ASSERT_TRUE(any_struct.check_if_exist(bar_target));

    fieldnames = any_struct.get_fieldnames();
    ASSERT_FALSE(fieldnames.empty());
    ASSERT_EQ(fieldnames.size(), 2);
    ASSERT_TRUE(fieldnames[0] == "bar");
    ASSERT_TRUE(fieldnames[1] == "foo");

    std::shared_ptr<yli::data::AnyValue> foo_any_value_shared_ptr = any_struct.read_data("foo");
    ASSERT_NE(foo_any_value_shared_ptr, nullptr);
    ASSERT_EQ(foo_any_value_shared_ptr->get_datatype(), "uint32_t");
    ASSERT_EQ(std::get<uint32_t>(foo_any_value_shared_ptr->data), 0xdeadbeef);
    std::shared_ptr<yli::data::AnyValue> bar_any_value_shared_ptr = any_struct.read_data("bar");
    ASSERT_NE(bar_any_value_shared_ptr, nullptr);
    ASSERT_EQ(bar_any_value_shared_ptr->get_datatype(), "uint32_t");
    ASSERT_EQ(std::get<uint32_t>(bar_any_value_shared_ptr->data), 0xca7f00d);
}

TEST(any_struct_must_function_appropriately, enter_data_complex_2nd_level)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    // pseudocode: any_struct.foo.bar = 0xdeadbeef
    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string foo_target = "foo.bar";
    ASSERT_TRUE(any_struct.enter_data(foo_target, deadbeef_any_value_shared_ptr));

    // pseudocode: any_struct.baz.qux = 0xca7f00d
    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string bar_target = "baz.qux";
    ASSERT_TRUE(any_struct.enter_data(bar_target, catfood_any_value_shared_ptr));
}

TEST(any_struct_must_function_appropriately, check_if_exist_complex_2nd_level_a_b_c_d)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string a_b_target = "a.b";
    ASSERT_FALSE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("a.b"));
    ASSERT_TRUE(any_struct.enter_data(a_b_target, deadbeef_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b"));

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string c_d_target = "c.d";
    ASSERT_TRUE(any_struct.enter_data(c_d_target, catfood_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_TRUE(any_struct.check_if_exist("c"));
    ASSERT_FALSE(any_struct.check_if_exist("d"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b"));
    ASSERT_TRUE(any_struct.check_if_exist("c.d"));
}

TEST(any_struct_must_function_appropriately, check_if_exist_complex_2nd_level_foo_bar_baz_qux)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string foo_bar_target = "foo.bar";
    ASSERT_FALSE(any_struct.check_if_exist("foo"));
    ASSERT_FALSE(any_struct.check_if_exist("bar"));
    ASSERT_FALSE(any_struct.check_if_exist("foo.bar"));
    ASSERT_TRUE(any_struct.enter_data(foo_bar_target, deadbeef_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("foo"));
    ASSERT_FALSE(any_struct.check_if_exist("bar"));
    ASSERT_TRUE(any_struct.check_if_exist("foo.bar"));

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string baz_qux_target = "baz.qux";
    ASSERT_TRUE(any_struct.enter_data(baz_qux_target, catfood_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("foo"));
    ASSERT_FALSE(any_struct.check_if_exist("bar"));
    ASSERT_TRUE(any_struct.check_if_exist("baz"));
    ASSERT_FALSE(any_struct.check_if_exist("qux"));
    ASSERT_TRUE(any_struct.check_if_exist("foo.bar"));
    ASSERT_TRUE(any_struct.check_if_exist("baz.qux"));
}

TEST(any_struct_must_function_appropriately, check_if_exist_complex_3rd_level_a_b_c_d_e_f)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string a_b_c_target = "a.b.c";
    ASSERT_FALSE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("c"));
    ASSERT_FALSE(any_struct.check_if_exist("a.b"));
    ASSERT_FALSE(any_struct.check_if_exist("a.b.c"));
    ASSERT_TRUE(any_struct.enter_data(a_b_c_target, deadbeef_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("c"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b.c"));

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string d_e_f_target = "d.e.f";
    ASSERT_TRUE(any_struct.enter_data(d_e_f_target, catfood_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b.c"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("b.c"));
    ASSERT_FALSE(any_struct.check_if_exist("c"));
    ASSERT_TRUE(any_struct.check_if_exist("d"));
    ASSERT_TRUE(any_struct.check_if_exist("d.e"));
    ASSERT_TRUE(any_struct.check_if_exist("d.e.f"));
    ASSERT_FALSE(any_struct.check_if_exist("e"));
    ASSERT_FALSE(any_struct.check_if_exist("e.f"));
}

TEST(any_struct_must_function_appropriately, erase_data_check_if_exist_complex_2nd_level_a_b_c_d)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string a_b_target = "a.b";
    ASSERT_FALSE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("a.b"));
    ASSERT_TRUE(any_struct.enter_data(a_b_target, deadbeef_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b"));

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string c_d_target = "c.d";
    ASSERT_TRUE(any_struct.enter_data(c_d_target, catfood_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_TRUE(any_struct.check_if_exist("c"));
    ASSERT_FALSE(any_struct.check_if_exist("d"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b"));
    ASSERT_TRUE(any_struct.check_if_exist("c.d"));

    ASSERT_TRUE(any_struct.erase_data("a.b"));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("a.b"));
    ASSERT_TRUE(any_struct.check_if_exist("c"));
    ASSERT_FALSE(any_struct.check_if_exist("d"));
    ASSERT_TRUE(any_struct.check_if_exist("c.d"));

    ASSERT_TRUE(any_struct.erase_data("c"));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("a.b"));
    ASSERT_FALSE(any_struct.check_if_exist("c"));
    ASSERT_FALSE(any_struct.check_if_exist("d"));
    ASSERT_FALSE(any_struct.check_if_exist("c.d"));

    ASSERT_TRUE(any_struct.erase_data("a"));
    ASSERT_FALSE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("a.b"));
    ASSERT_FALSE(any_struct.check_if_exist("c"));
    ASSERT_FALSE(any_struct.check_if_exist("d"));
    ASSERT_FALSE(any_struct.check_if_exist("c.d"));
}

TEST(any_struct_must_function_appropriately, erase_data_check_if_exist_complex_3rd_level_a_b_c_d_e_f_g_h_i_j_k_l)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);
    const std::string a_b_c_target = "a.b.c";
    ASSERT_FALSE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("c"));
    ASSERT_FALSE(any_struct.check_if_exist("a.b"));
    ASSERT_FALSE(any_struct.check_if_exist("a.b.c"));
    ASSERT_TRUE(any_struct.enter_data(a_b_c_target, deadbeef_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("c"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b.c"));

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string d_e_f_target = "d.e.f";
    ASSERT_TRUE(any_struct.enter_data(d_e_f_target, catfood_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b"));
    ASSERT_TRUE(any_struct.check_if_exist("a.b.c"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("b.c"));
    ASSERT_FALSE(any_struct.check_if_exist("c"));
    ASSERT_TRUE(any_struct.check_if_exist("d"));
    ASSERT_TRUE(any_struct.check_if_exist("d.e"));
    ASSERT_TRUE(any_struct.check_if_exist("d.e.f"));
    ASSERT_FALSE(any_struct.check_if_exist("e"));
    ASSERT_FALSE(any_struct.check_if_exist("e.f"));

    uint32_t toffee_uint32_t = 0x70ffee;
    std::shared_ptr<yli::data::AnyValue> toffee_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(toffee_uint32_t);
    const std::string g_h_i_target = "g.h.i";
    ASSERT_FALSE(any_struct.check_if_exist("g"));
    ASSERT_FALSE(any_struct.check_if_exist("h"));
    ASSERT_FALSE(any_struct.check_if_exist("i"));
    ASSERT_FALSE(any_struct.check_if_exist("g.h"));
    ASSERT_FALSE(any_struct.check_if_exist("g.h.i"));
    ASSERT_TRUE(any_struct.enter_data(g_h_i_target, toffee_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("g"));
    ASSERT_FALSE(any_struct.check_if_exist("h"));
    ASSERT_FALSE(any_struct.check_if_exist("i"));
    ASSERT_TRUE(any_struct.check_if_exist("g.h"));
    ASSERT_TRUE(any_struct.check_if_exist("g.h.i"));

    uint32_t bestfood_uint32_t = 0xbe57f00d;
    std::shared_ptr<yli::data::AnyValue> bestfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(bestfood_uint32_t);
    const std::string j_k_l_target = "j.k.l";
    ASSERT_FALSE(any_struct.check_if_exist("j"));
    ASSERT_FALSE(any_struct.check_if_exist("k"));
    ASSERT_FALSE(any_struct.check_if_exist("l"));
    ASSERT_FALSE(any_struct.check_if_exist("j.k"));
    ASSERT_FALSE(any_struct.check_if_exist("j.k.l"));
    ASSERT_TRUE(any_struct.enter_data(j_k_l_target, bestfood_any_value_shared_ptr));
    ASSERT_TRUE(any_struct.check_if_exist("j"));
    ASSERT_FALSE(any_struct.check_if_exist("k"));
    ASSERT_FALSE(any_struct.check_if_exist("l"));
    ASSERT_TRUE(any_struct.check_if_exist("j.k"));
    ASSERT_TRUE(any_struct.check_if_exist("j.k.l"));

    ASSERT_TRUE(any_struct.erase_data("a.b.c"));

    ASSERT_TRUE(any_struct.check_if_exist("a"));
    ASSERT_FALSE(any_struct.check_if_exist("b"));
    ASSERT_FALSE(any_struct.check_if_exist("c"));

    ASSERT_TRUE(any_struct.check_if_exist("d"));
    ASSERT_FALSE(any_struct.check_if_exist("e"));
    ASSERT_FALSE(any_struct.check_if_exist("f"));

    ASSERT_TRUE(any_struct.check_if_exist("g"));
    ASSERT_FALSE(any_struct.check_if_exist("h"));
    ASSERT_FALSE(any_struct.check_if_exist("i"));

    ASSERT_TRUE(any_struct.check_if_exist("j"));
    ASSERT_FALSE(any_struct.check_if_exist("k"));
    ASSERT_FALSE(any_struct.check_if_exist("l"));

    ASSERT_TRUE(any_struct.check_if_exist("a.b"));
    ASSERT_FALSE(any_struct.check_if_exist("b.c"));
    ASSERT_FALSE(any_struct.check_if_exist("c.d"));

    ASSERT_TRUE(any_struct.check_if_exist("d.e"));
    ASSERT_FALSE(any_struct.check_if_exist("e.f"));
    ASSERT_FALSE(any_struct.check_if_exist("f.g"));

    ASSERT_TRUE(any_struct.check_if_exist("g.h"));
    ASSERT_FALSE(any_struct.check_if_exist("h.i"));
    ASSERT_FALSE(any_struct.check_if_exist("i.j"));

    ASSERT_TRUE(any_struct.check_if_exist("j.k"));
    ASSERT_FALSE(any_struct.check_if_exist("k.l"));

    ASSERT_FALSE(any_struct.erase_data("a.b.c"));
    ASSERT_FALSE(any_struct.erase_data("b.c.d"));
    ASSERT_FALSE(any_struct.erase_data("c.d.e"));

    ASSERT_TRUE(any_struct.erase_data("d.e.f"));
    ASSERT_FALSE(any_struct.erase_data("e.f.g"));
    ASSERT_FALSE(any_struct.erase_data("f.g.h"));

    ASSERT_TRUE(any_struct.erase_data("g.h.i"));
    ASSERT_FALSE(any_struct.erase_data("h.i.j"));
    ASSERT_FALSE(any_struct.erase_data("i.j.k"));

    ASSERT_TRUE(any_struct.erase_data("j.k.l"));
}

TEST(any_struct_must_function_appropriately, erase_data_read_data_complex_2nd_level_a_b_c_d)
{
    yli::data::AnyStruct any_struct = yli::data::AnyStruct();

    uint32_t deadbeef_uint32_t = 0xdeadbeef;
    std::shared_ptr<yli::data::AnyValue> deadbeef_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(deadbeef_uint32_t);

    ASSERT_EQ(any_struct.read_data("a"), nullptr);
    ASSERT_EQ(any_struct.read_data("b"), nullptr);
    ASSERT_EQ(any_struct.read_data("a.b"), nullptr);

    const std::string a_b_target = "a.b";
    ASSERT_TRUE(any_struct.enter_data(a_b_target, deadbeef_any_value_shared_ptr));

    ASSERT_NE(any_struct.read_data("a"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("a")->get_datatype().c_str(), "std::shared_ptr<yli::data::AnyStruct>"), 0);
    ASSERT_NE(std::get<std::shared_ptr<yli::data::AnyStruct>>(any_struct.read_data("a")->data), nullptr);

    ASSERT_EQ(any_struct.read_data("b"), nullptr);

    ASSERT_NE(any_struct.read_data("a.b"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("a.b")->get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::get<uint32_t>(any_struct.read_data("a.b")->data), 0xdeadbeef);

    uint32_t catfood_uint32_t = 0xca7f00d;
    std::shared_ptr<yli::data::AnyValue> catfood_any_value_shared_ptr =
        std::make_shared<yli::data::AnyValue>(catfood_uint32_t);
    const std::string c_d_target = "c.d";
    ASSERT_TRUE(any_struct.enter_data(c_d_target, catfood_any_value_shared_ptr));

    ASSERT_NE(any_struct.read_data("a"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("a")->get_datatype().c_str(), "std::shared_ptr<yli::data::AnyStruct>"), 0);
    ASSERT_NE(std::get<std::shared_ptr<yli::data::AnyStruct>>(any_struct.read_data("a")->data), nullptr);

    ASSERT_EQ(any_struct.read_data("b"), nullptr);

    ASSERT_NE(any_struct.read_data("a.b"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("a.b")->get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::get<uint32_t>(any_struct.read_data("a.b")->data), 0xdeadbeef);

    ASSERT_EQ(any_struct.read_data("b"), nullptr);

    ASSERT_NE(any_struct.read_data("c"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("c")->get_datatype().c_str(), "std::shared_ptr<yli::data::AnyStruct>"), 0);
    ASSERT_NE(std::get<std::shared_ptr<yli::data::AnyStruct>>(any_struct.read_data("c")->data), nullptr);

    ASSERT_EQ(any_struct.read_data("d"), nullptr);

    ASSERT_NE(any_struct.read_data("a.b"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("a.b")->get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::get<uint32_t>(any_struct.read_data("a.b")->data), 0xdeadbeef);

    ASSERT_NE(any_struct.read_data("c.d"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("a.b")->get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::get<uint32_t>(any_struct.read_data("c.d")->data), 0xca7f00d);

    ASSERT_TRUE(any_struct.erase_data("a.b"));

    ASSERT_NE(any_struct.read_data("a"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("a")->get_datatype().c_str(), "std::shared_ptr<yli::data::AnyStruct>"), 0);
    ASSERT_NE(std::get<std::shared_ptr<yli::data::AnyStruct>>(any_struct.read_data("a")->data), nullptr);

    ASSERT_EQ(any_struct.read_data("b"), nullptr);
    ASSERT_EQ(any_struct.read_data("a.b"), nullptr);

    ASSERT_NE(any_struct.read_data("c"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("c")->get_datatype().c_str(), "std::shared_ptr<yli::data::AnyStruct>"), 0);
    ASSERT_NE(std::get<std::shared_ptr<yli::data::AnyStruct>>(any_struct.read_data("c")->data), nullptr);

    ASSERT_EQ(any_struct.read_data("d"), nullptr);

    ASSERT_NE(any_struct.read_data("c.d"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("c.d")->get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::get<uint32_t>(any_struct.read_data("c.d")->data), 0xca7f00d);

    ASSERT_TRUE(any_struct.erase_data("c"));

    ASSERT_NE(any_struct.read_data("a"), nullptr);
    ASSERT_EQ(std::strcmp(any_struct.read_data("a")->get_datatype().c_str(), "std::shared_ptr<yli::data::AnyStruct>"), 0);
    ASSERT_NE(std::get<std::shared_ptr<yli::data::AnyStruct>>(any_struct.read_data("a")->data), nullptr);

    ASSERT_EQ(any_struct.read_data("b"), nullptr);
    ASSERT_EQ(any_struct.read_data("a.b"), nullptr);
    ASSERT_EQ(any_struct.read_data("c"), nullptr);
    ASSERT_EQ(any_struct.read_data("d"), nullptr);
    ASSERT_EQ(any_struct.read_data("c.d"), nullptr);

    ASSERT_TRUE(any_struct.erase_data("a"));
    ASSERT_EQ(any_struct.read_data("a"), nullptr);
    ASSERT_EQ(any_struct.read_data("b"), nullptr);
    ASSERT_EQ(any_struct.read_data("a.b"), nullptr);
    ASSERT_EQ(any_struct.read_data("c"), nullptr);
    ASSERT_EQ(any_struct.read_data("d"), nullptr);
    ASSERT_EQ(any_struct.read_data("c.d"), nullptr);
}
