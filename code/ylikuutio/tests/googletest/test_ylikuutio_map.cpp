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
#include "code/ylikuutio/map/ylikuutio_map.hpp"

// Include standard headers
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_no_keys)
{
    std::unordered_map<std::string, std::string> string_string_map;
    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_TRUE(keys.empty());
    ASSERT_EQ(keys.size(), 0);
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 1);
    ASSERT_EQ(keys[0], "a");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 1);
    ASSERT_EQ(keys[0], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"];
    string_string_map["b"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"];
    string_string_map["a"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a_b_c)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"];
    string_string_map["b"];
    string_string_map["c"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 3);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
    ASSERT_EQ(keys[2], "c");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a_c_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"];
    string_string_map["c"];
    string_string_map["b"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 3);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
    ASSERT_EQ(keys[2], "c");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b_a_c)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"];
    string_string_map["a"];
    string_string_map["c"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 3);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
    ASSERT_EQ(keys[2], "c");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b_c_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"];
    string_string_map["c"];
    string_string_map["a"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 3);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
    ASSERT_EQ(keys[2], "c");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_c_a_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["c"];
    string_string_map["a"];
    string_string_map["b"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 3);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
    ASSERT_EQ(keys[2], "c");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_c_b_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["c"];
    string_string_map["b"];
    string_string_map["a"];

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 3);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
    ASSERT_EQ(keys[2], "c");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a_values_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"] = "a";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 1);
    ASSERT_EQ(keys[0], "a");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a_values_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"] = "b";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 1);
    ASSERT_EQ(keys[0], "a");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b_values_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"] = "a";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 1);
    ASSERT_EQ(keys[0], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b_values_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"] = "b";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 1);
    ASSERT_EQ(keys[0], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a_b_values_a_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"] = "a";
    string_string_map["b"] = "a";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a_b_values_a_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"] = "a";
    string_string_map["b"] = "b";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a_b_values_b_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"] = "b";
    string_string_map["b"] = "a";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_a_b_values_b_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["a"] = "b";
    string_string_map["b"] = "b";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b_a_values_a_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"] = "a";
    string_string_map["a"] = "a";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b_a_values_a_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"] = "a";
    string_string_map["a"] = "b";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b_a_values_b_a)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"] = "b";
    string_string_map["a"] = "a";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}

TEST(ylikuutio_map_must_function_properly, ylikuutio_map_keys_b_a_values_b_b)
{
    std::unordered_map<std::string, std::string> string_string_map;
    string_string_map["b"] = "b";
    string_string_map["a"] = "b";

    std::vector<std::string> keys = yli::map::get_keys(string_string_map);
    ASSERT_EQ(keys.size(), 2);
    ASSERT_EQ(keys[0], "a");
    ASSERT_EQ(keys[1], "b");
}
