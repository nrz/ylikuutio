// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/any_struct.hpp"
#include "code/ylikuutio/common/spherical_coordinates_struct.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <limits>   // std::numeric_limits
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <variant>  // std::variant
#include <vector>   // std::vector

TEST(any_value_must_be_initialized_appropriately, bool_true)
{
    bool bool_true = true;
    yli::common::AnyValue true_value = yli::common::AnyValue(bool_true);
    ASSERT_TRUE(std::holds_alternative<bool>(true_value.data));
    ASSERT_TRUE(std::get<bool>(true_value.data));
    ASSERT_EQ(std::strlen(true_value.get_datatype().c_str()), std::strlen("bool"));
    ASSERT_EQ(std::strcmp(true_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::strlen(true_value.get_string().c_str()), std::strlen("true"));
    ASSERT_EQ(std::strcmp(true_value.get_string().c_str(), "true"), 0);
    ASSERT_EQ(true_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, bool_false)
{
    bool bool_false = false;
    yli::common::AnyValue false_value = yli::common::AnyValue(bool_false);
    ASSERT_TRUE(std::holds_alternative<bool>(false_value.data));
    ASSERT_FALSE(std::get<bool>(false_value.data));
    ASSERT_EQ(std::strlen(false_value.get_datatype().c_str()), std::strlen("bool"));
    ASSERT_EQ(std::strcmp(false_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::strlen(false_value.get_string().c_str()), std::strlen("false"));
    ASSERT_EQ(std::strcmp(false_value.get_string().c_str(), "false"), 0);
    ASSERT_EQ(false_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, char_lowercase_a)
{
    char char_lowercase_a = 'a';
    yli::common::AnyValue lowercase_a_value = yli::common::AnyValue(char_lowercase_a);
    ASSERT_TRUE(std::holds_alternative<char>(lowercase_a_value.data));
    ASSERT_EQ(std::get<char>(lowercase_a_value.data), 'a');
    ASSERT_EQ(std::strlen(lowercase_a_value.get_datatype().c_str()), std::strlen("char"));
    ASSERT_EQ(std::strcmp(lowercase_a_value.get_datatype().c_str(), "char"), 0);
    ASSERT_EQ(std::strlen(lowercase_a_value.get_string().c_str()), std::strlen("a"));
    ASSERT_EQ(std::strcmp(lowercase_a_value.get_string().c_str(), "a"), 0);
    ASSERT_EQ(lowercase_a_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, char_lowercase_b)
{
    char char_lowercase_b = 'b';
    yli::common::AnyValue lowercase_b_value = yli::common::AnyValue(char_lowercase_b);
    ASSERT_TRUE(std::holds_alternative<char>(lowercase_b_value.data));
    ASSERT_EQ(std::get<char>(lowercase_b_value.data), 'b');
    ASSERT_EQ(std::strlen(lowercase_b_value.get_datatype().c_str()), std::strlen("char"));
    ASSERT_EQ(std::strcmp(lowercase_b_value.get_datatype().c_str(), "char"), 0);
    ASSERT_EQ(std::strlen(lowercase_b_value.get_string().c_str()), std::strlen("b"));
    ASSERT_EQ(std::strcmp(lowercase_b_value.get_string().c_str(), "b"), 0);
    ASSERT_EQ(lowercase_b_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, char_space)
{
    char char_space = ' ';
    yli::common::AnyValue space_value = yli::common::AnyValue(char_space);
    ASSERT_TRUE(std::holds_alternative<char>(space_value.data));
    ASSERT_EQ(std::get<char>(space_value.data), ' ');
    ASSERT_EQ(std::strlen(space_value.get_datatype().c_str()), std::strlen("char"));
    ASSERT_EQ(std::strcmp(space_value.get_datatype().c_str(), "char"), 0);
    ASSERT_EQ(std::strlen(space_value.get_string().c_str()), std::strlen(" "));
    ASSERT_EQ(std::strcmp(space_value.get_string().c_str(), " "), 0);
    ASSERT_EQ(space_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, char_newline)
{
    char char_newline = '\n';
    yli::common::AnyValue newline_value = yli::common::AnyValue(char_newline);
    ASSERT_TRUE(std::holds_alternative<char>(newline_value.data));
    ASSERT_EQ(std::get<char>(newline_value.data), '\n');
    ASSERT_EQ(std::strlen(newline_value.get_datatype().c_str()), std::strlen("char"));
    ASSERT_EQ(std::strcmp(newline_value.get_datatype().c_str(), "char"), 0);
    ASSERT_EQ(std::strlen(newline_value.get_string().c_str()), std::strlen("\n"));
    ASSERT_EQ(std::strcmp(newline_value.get_string().c_str(), "\n"), 0);
    ASSERT_EQ(newline_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, float_0)
{
    float float_zero = 0.0f;
    yli::common::AnyValue float_zero_value = yli::common::AnyValue(float_zero);
    ASSERT_TRUE(std::holds_alternative<float>(float_zero_value.data));
    ASSERT_EQ(std::get<float>(float_zero_value.data), 0.0f);
    ASSERT_EQ(std::strlen(float_zero_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_zero_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_zero_value.get_string().c_str()), std::strlen("0.000000"));
    ASSERT_EQ(std::strlen(float_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(float_zero_value.get_string().c_str(), "0.000000"), 0);
    ASSERT_EQ(float_zero_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, float_positive_infinity)
{
    float float_positive_infinity = std::numeric_limits<float>::infinity();
    yli::common::AnyValue float_positive_infinity_value = yli::common::AnyValue(float_positive_infinity);
    ASSERT_TRUE(std::holds_alternative<float>(float_positive_infinity_value.data));
    ASSERT_EQ(std::get<float>(float_positive_infinity_value.data), std::numeric_limits<float>::infinity());
    ASSERT_EQ(std::strlen(float_positive_infinity_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_positive_infinity_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_positive_infinity_value.get_string().c_str()), std::strlen("inf"));
    ASSERT_EQ(std::strcmp(float_positive_infinity_value.get_string().c_str(), "inf"), 0);
    ASSERT_EQ(float_positive_infinity_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, float_negative_infinity)
{
    float float_negative_infinity = -1.0f * std::numeric_limits<float>::infinity();
    yli::common::AnyValue float_negative_infinity_value = yli::common::AnyValue(float_negative_infinity);
    ASSERT_TRUE(std::holds_alternative<float>(float_negative_infinity_value.data));
    ASSERT_EQ(std::get<float>(float_negative_infinity_value.data), float_negative_infinity);
    ASSERT_EQ(std::strlen(float_negative_infinity_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_negative_infinity_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_negative_infinity_value.get_string().c_str()), std::strlen("-inf"));
    ASSERT_EQ(std::strcmp(float_negative_infinity_value.get_string().c_str(), "-inf"), 0);
    ASSERT_EQ(float_negative_infinity_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, float_NAN)
{
    float float_NAN = NAN;
    yli::common::AnyValue float_nan_value = yli::common::AnyValue(float_NAN);
    ASSERT_TRUE(std::holds_alternative<float>(float_nan_value.data));
    ASSERT_TRUE(std::isnan(std::get<float>(float_nan_value.data)));
    ASSERT_EQ(std::strlen(float_nan_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_nan_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_nan_value.get_string().c_str()), std::strlen("nan"));
    ASSERT_EQ(std::strcmp(float_nan_value.get_string().c_str(), "nan"), 0);
    ASSERT_EQ(float_nan_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, double_0)
{
    double double_zero = 0.0f;
    yli::common::AnyValue double_zero_value = yli::common::AnyValue(double_zero);
    ASSERT_TRUE(std::holds_alternative<double>(double_zero_value.data));
    ASSERT_EQ(std::get<double>(double_zero_value.data), 0.0f);
    ASSERT_EQ(std::strlen(double_zero_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_zero_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_zero_value.get_string().c_str()), std::strlen("0.000000"));
    ASSERT_EQ(std::strlen(double_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(double_zero_value.get_string().c_str(), "0.000000"), 0);
    ASSERT_EQ(double_zero_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, double_positive_infinity)
{
    double double_positive_infinity = std::numeric_limits<double>::infinity();
    yli::common::AnyValue double_positive_infinity_value = yli::common::AnyValue(double_positive_infinity);
    ASSERT_TRUE(std::holds_alternative<double>(double_positive_infinity_value.data));
    ASSERT_EQ(std::get<double>(double_positive_infinity_value.data), std::numeric_limits<double>::infinity());
    ASSERT_EQ(std::strlen(double_positive_infinity_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_positive_infinity_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_positive_infinity_value.get_string().c_str()), std::strlen("inf"));
    ASSERT_EQ(std::strcmp(double_positive_infinity_value.get_string().c_str(), "inf"), 0);
    ASSERT_EQ(double_positive_infinity_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, double_negative_infinity)
{
    double double_negative_infinity = -1 * std::numeric_limits<double>::infinity();
    yli::common::AnyValue double_negative_infinity_value = yli::common::AnyValue(double_negative_infinity);
    ASSERT_TRUE(std::holds_alternative<double>(double_negative_infinity_value.data));
    ASSERT_EQ(std::get<double>(double_negative_infinity_value.data), double_negative_infinity);
    ASSERT_EQ(std::strlen(double_negative_infinity_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_negative_infinity_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_negative_infinity_value.get_string().c_str()), std::strlen("-inf"));
    ASSERT_EQ(std::strcmp(double_negative_infinity_value.get_string().c_str(), "-inf"), 0);
    ASSERT_EQ(double_negative_infinity_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, double_NAN)
{
    double double_NAN = NAN;
    yli::common::AnyValue double_NAN_value = yli::common::AnyValue(double_NAN);
    ASSERT_TRUE(std::holds_alternative<double>(double_NAN_value.data));
    ASSERT_TRUE(std::isnan(std::get<double>(double_NAN_value.data)));
    ASSERT_EQ(std::strlen(double_NAN_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_NAN_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_NAN_value.get_string().c_str()), std::strlen("nan"));
    ASSERT_EQ(std::strcmp(double_NAN_value.get_string().c_str(), "nan"), 0);
    ASSERT_EQ(double_NAN_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_zero)
{
    int32_t int32_t_zero = 0;
    yli::common::AnyValue int32_t_zero_value = yli::common::AnyValue(int32_t_zero);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_zero_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_zero_value.data), 0);
    ASSERT_EQ(std::strlen(int32_t_zero_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_zero_value.get_string().c_str()), std::strlen("0"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_string().c_str(), "0"), 0);
    ASSERT_EQ(int32_t_zero_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_plus_1)
{
    int32_t int32_t_plus_1 = 1;
    yli::common::AnyValue int32_t_plus_1_value = yli::common::AnyValue(int32_t_plus_1);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_plus_1_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_plus_1_value.data), 1);
    ASSERT_EQ(std::strlen(int32_t_plus_1_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_plus_1_value.get_string().c_str()), std::strlen("1"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_string().c_str(), "1"), 0);
    ASSERT_EQ(int32_t_plus_1_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_minus_1)
{
    int32_t int32_t_minus_1 = -1;
    yli::common::AnyValue int32_t_minus_1_value = yli::common::AnyValue(int32_t_minus_1);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_minus_1_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_minus_1_value.data), -1);
    ASSERT_EQ(std::strlen(int32_t_minus_1_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_minus_1_value.get_string().c_str()), std::strlen("-1"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_string().c_str(), "-1"), 0);
    ASSERT_EQ(int32_t_minus_1_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_max)
{
    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::common::AnyValue int32_t_max_value = yli::common::AnyValue(int32_t_max);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_max_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), 2147483647);
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), std::numeric_limits<int32_t>::max());
#ifdef __linux__
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), std::numeric_limits<int>::max());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), std::numeric_limits<int>::max());
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), std::numeric_limits<long>::max());
#endif
    ASSERT_EQ(std::strlen(int32_t_max_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_max_value.get_string().c_str()), std::strlen("2147483647"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_string().c_str(), "2147483647"), 0);
    ASSERT_EQ(int32_t_max_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_min)
{
    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::common::AnyValue int32_t_min_value = yli::common::AnyValue(int32_t_min);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_min_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), -2147483648);
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), std::numeric_limits<int32_t>::min());
#ifdef __linux__
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), std::numeric_limits<int>::min());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), std::numeric_limits<int>::min());
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), std::numeric_limits<long>::min());
#endif
    ASSERT_EQ(std::strlen(int32_t_min_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_min_value.get_string().c_str()), std::strlen("-2147483648"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_string().c_str(), "-2147483648"), 0);
    ASSERT_EQ(int32_t_min_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_zero)
{
    uint32_t uint32_t_zero = 0;
    yli::common::AnyValue uint32_t_zero_value = yli::common::AnyValue(uint32_t_zero);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(uint32_t_zero_value.data));
    ASSERT_EQ(std::get<uint32_t>(uint32_t_zero_value.data), 0);
    ASSERT_EQ(std::strlen(uint32_t_zero_value.get_datatype().c_str()), std::strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_zero_value.get_string().c_str()), std::strlen("0"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_string().c_str(), "0"), 0);
    ASSERT_EQ(uint32_t_zero_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_plus_1)
{
    uint32_t uint32_t_plus_1 = 1;
    yli::common::AnyValue uint32_t_plus_1_value = yli::common::AnyValue(uint32_t_plus_1);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(uint32_t_plus_1_value.data));
    ASSERT_EQ(std::get<uint32_t>(uint32_t_plus_1_value.data), 1);
    ASSERT_EQ(std::strlen(uint32_t_plus_1_value.get_datatype().c_str()), std::strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_plus_1_value.get_string().c_str()), std::strlen("1"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_string().c_str(), "1"), 0);
    ASSERT_EQ(uint32_t_plus_1_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_max)
{
    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::common::AnyValue uint32_t_max_value = yli::common::AnyValue(uint32_t_max);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(uint32_t_max_value.data));
    ASSERT_EQ(std::get<uint32_t>(uint32_t_max_value.data), std::numeric_limits<uint32_t>::max());
#ifdef __linux__
    ASSERT_EQ(std::get<uint32_t>(uint32_t_max_value.data), std::numeric_limits<unsigned int>::max());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(std::get<uint32_t>(uint32_t_max_value.data), std::numeric_limits<unsigned int>::max());
    ASSERT_EQ(std::get<uint32_t>(uint32_t_max_value.data), std::numeric_limits<unsigned long>::max());
#endif
    ASSERT_EQ(std::strlen(uint32_t_max_value.get_datatype().c_str()), std::strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_max_value.get_string().c_str()), std::strlen("4294967295"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_string().c_str(), "4294967295"), 0);
    ASSERT_EQ(uint32_t_max_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, bool_pointer_true)
{
    bool bool_true = true;
    yli::common::AnyValue true_value = yli::common::AnyValue(&bool_true);
    ASSERT_TRUE(std::holds_alternative<bool*>(true_value.data));
    ASSERT_EQ(std::get<bool*>(true_value.data), &bool_true);
    ASSERT_EQ(std::strlen(true_value.get_datatype().c_str()), std::strlen("bool*"));
    ASSERT_EQ(std::strcmp(true_value.get_datatype().c_str(), "bool*"), 0);
    ASSERT_EQ(true_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, bool_pointer_false)
{
    bool bool_false = false;
    yli::common::AnyValue false_value = yli::common::AnyValue(&bool_false);
    ASSERT_TRUE(std::holds_alternative<bool*>(false_value.data));
    ASSERT_EQ(std::get<bool*>(false_value.data), &bool_false);
    ASSERT_EQ(std::strlen(false_value.get_datatype().c_str()), std::strlen("bool*"));
    ASSERT_EQ(std::strcmp(false_value.get_datatype().c_str(), "bool*"), 0);
    ASSERT_EQ(false_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, char_pointer_lowercase_a)
{
    char char_lowercase_a = 'a';
    yli::common::AnyValue lowercase_a_value = yli::common::AnyValue(&char_lowercase_a);
    ASSERT_TRUE(std::holds_alternative<char*>(lowercase_a_value.data));
    ASSERT_EQ(std::get<char*>(lowercase_a_value.data), &char_lowercase_a);
    ASSERT_EQ(std::strlen(lowercase_a_value.get_datatype().c_str()), std::strlen("char*"));
    ASSERT_EQ(std::strcmp(lowercase_a_value.get_datatype().c_str(), "char*"), 0);
    ASSERT_EQ(lowercase_a_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, char_pointer_lowercase_b)
{
    char char_lowercase_b = 'b';
    yli::common::AnyValue lowercase_b_value = yli::common::AnyValue(&char_lowercase_b);
    ASSERT_TRUE(std::holds_alternative<char*>(lowercase_b_value.data));
    ASSERT_EQ(std::get<char*>(lowercase_b_value.data), &char_lowercase_b);
    ASSERT_EQ(std::strlen(lowercase_b_value.get_datatype().c_str()), std::strlen("char*"));
    ASSERT_EQ(std::strcmp(lowercase_b_value.get_datatype().c_str(), "char*"), 0);
    ASSERT_EQ(lowercase_b_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, char_pointer_space)
{
    char char_space = ' ';
    yli::common::AnyValue space_value = yli::common::AnyValue(&char_space);
    ASSERT_TRUE(std::holds_alternative<char*>(space_value.data));
    ASSERT_EQ(std::get<char*>(space_value.data), &char_space);
    ASSERT_EQ(std::strlen(space_value.get_datatype().c_str()), std::strlen("char*"));
    ASSERT_EQ(std::strcmp(space_value.get_datatype().c_str(), "char*"), 0);
    ASSERT_EQ(space_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, char_pointer_newline)
{
    char char_newline = '\n';
    yli::common::AnyValue newline_value = yli::common::AnyValue(&char_newline);
    ASSERT_TRUE(std::holds_alternative<char*>(newline_value.data));
    ASSERT_EQ(std::get<char*>(newline_value.data), &char_newline);
    ASSERT_EQ(std::strlen(newline_value.get_datatype().c_str()), std::strlen("char*"));
    ASSERT_EQ(std::strcmp(newline_value.get_datatype().c_str(), "char*"), 0);
    ASSERT_EQ(newline_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, float_pointer_0)
{
    float float_zero = 0.0f;
    yli::common::AnyValue float_zero_value = yli::common::AnyValue(&float_zero);
    ASSERT_TRUE(std::holds_alternative<float*>(float_zero_value.data));
    ASSERT_EQ(std::get<float*>(float_zero_value.data), &float_zero);
    ASSERT_EQ(std::strlen(float_zero_value.get_datatype().c_str()), std::strlen("float*"));
    ASSERT_EQ(std::strcmp(float_zero_value.get_datatype().c_str(), "float*"), 0);
    ASSERT_EQ(float_zero_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, float_pointer_positive_infinity)
{
    float float_positive_infinity = std::numeric_limits<float>::infinity();
    yli::common::AnyValue float_positive_infinity_value = yli::common::AnyValue(&float_positive_infinity);
    ASSERT_TRUE(std::holds_alternative<float*>(float_positive_infinity_value.data));
    ASSERT_EQ(std::get<float*>(float_positive_infinity_value.data), &float_positive_infinity);
    ASSERT_EQ(std::strlen(float_positive_infinity_value.get_datatype().c_str()), std::strlen("float*"));
    ASSERT_EQ(std::strcmp(float_positive_infinity_value.get_datatype().c_str(), "float*"), 0);
    ASSERT_EQ(float_positive_infinity_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, float_pointer_negative_infinity)
{
    float float_negative_infinity = -1.0f * std::numeric_limits<float>::infinity();
    yli::common::AnyValue float_negative_infinity_value = yli::common::AnyValue(&float_negative_infinity);
    ASSERT_TRUE(std::holds_alternative<float*>(float_negative_infinity_value.data));
    ASSERT_EQ(std::get<float*>(float_negative_infinity_value.data), &float_negative_infinity);
    ASSERT_EQ(std::strlen(float_negative_infinity_value.get_datatype().c_str()), std::strlen("float*"));
    ASSERT_EQ(std::strcmp(float_negative_infinity_value.get_datatype().c_str(), "float*"), 0);
    ASSERT_EQ(float_negative_infinity_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, float_pointer_NAN)
{
    float float_NAN = NAN;
    yli::common::AnyValue float_nan_value = yli::common::AnyValue(&float_NAN);
    ASSERT_TRUE(std::holds_alternative<float*>(float_nan_value.data));
    ASSERT_EQ(std::get<float*>(float_nan_value.data), &float_NAN);
    ASSERT_EQ(std::strlen(float_nan_value.get_datatype().c_str()), std::strlen("float*"));
    ASSERT_EQ(std::strcmp(float_nan_value.get_datatype().c_str(), "float*"), 0);
    ASSERT_EQ(float_nan_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, double_pointer_0)
{
    double double_zero = 0.0f;
    yli::common::AnyValue double_zero_value = yli::common::AnyValue(&double_zero);
    ASSERT_TRUE(std::holds_alternative<double*>(double_zero_value.data));
    ASSERT_EQ(std::get<double*>(double_zero_value.data), &double_zero);
    ASSERT_EQ(std::strlen(double_zero_value.get_datatype().c_str()), std::strlen("double*"));
    ASSERT_EQ(std::strcmp(double_zero_value.get_datatype().c_str(), "double*"), 0);
    ASSERT_EQ(double_zero_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, double_pointer_positive_infinity)
{
    double double_positive_infinity = std::numeric_limits<double>::infinity();
    yli::common::AnyValue double_positive_infinity_value = yli::common::AnyValue(&double_positive_infinity);
    ASSERT_TRUE(std::holds_alternative<double*>(double_positive_infinity_value.data));
    ASSERT_EQ(std::get<double*>(double_positive_infinity_value.data), &double_positive_infinity);
    ASSERT_EQ(std::strlen(double_positive_infinity_value.get_datatype().c_str()), std::strlen("double*"));
    ASSERT_EQ(std::strcmp(double_positive_infinity_value.get_datatype().c_str(), "double*"), 0);
    ASSERT_EQ(double_positive_infinity_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, double_pointer_negative_infinity)
{
    double double_negative_infinity = -1 * std::numeric_limits<double>::infinity();
    yli::common::AnyValue double_negative_infinity_value = yli::common::AnyValue(&double_negative_infinity);
    ASSERT_TRUE(std::holds_alternative<double*>(double_negative_infinity_value.data));
    ASSERT_EQ(std::get<double*>(double_negative_infinity_value.data), &double_negative_infinity);
    ASSERT_EQ(std::strlen(double_negative_infinity_value.get_datatype().c_str()), std::strlen("double*"));
    ASSERT_EQ(std::strcmp(double_negative_infinity_value.get_datatype().c_str(), "double*"), 0);
    ASSERT_EQ(double_negative_infinity_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, double_pointer_NAN)
{
    double double_NAN = NAN;
    yli::common::AnyValue double_NAN_value = yli::common::AnyValue(&double_NAN);
    ASSERT_TRUE(std::holds_alternative<double*>(double_NAN_value.data));
    ASSERT_EQ(std::get<double*>(double_NAN_value.data), &double_NAN);
    ASSERT_EQ(std::strlen(double_NAN_value.get_datatype().c_str()), std::strlen("double*"));
    ASSERT_EQ(std::strcmp(double_NAN_value.get_datatype().c_str(), "double*"), 0);
    ASSERT_EQ(double_NAN_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_pointer_zero)
{
    int32_t int32_t_zero = 0;
    yli::common::AnyValue int32_t_zero_value = yli::common::AnyValue(&int32_t_zero);
    ASSERT_TRUE(std::holds_alternative<int32_t*>(int32_t_zero_value.data));
    ASSERT_EQ(std::get<int32_t*>(int32_t_zero_value.data), &int32_t_zero);
    ASSERT_EQ(std::strlen(int32_t_zero_value.get_datatype().c_str()), std::strlen("int32_t*"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_datatype().c_str(), "int32_t*"), 0);
    ASSERT_EQ(int32_t_zero_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_pointer_plus_1)
{
    int32_t int32_t_plus_1 = 1;
    yli::common::AnyValue int32_t_plus_1_value = yli::common::AnyValue(&int32_t_plus_1);
    ASSERT_TRUE(std::holds_alternative<int32_t*>(int32_t_plus_1_value.data));
    ASSERT_EQ(std::get<int32_t*>(int32_t_plus_1_value.data), &int32_t_plus_1);
    ASSERT_EQ(std::strlen(int32_t_plus_1_value.get_datatype().c_str()), std::strlen("int32_t*"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_datatype().c_str(), "int32_t*"), 0);
    ASSERT_EQ(int32_t_plus_1_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_pointer_minus_1)
{
    int32_t int32_t_minus_1 = -1;
    yli::common::AnyValue int32_t_minus_1_value = yli::common::AnyValue(&int32_t_minus_1);
    ASSERT_TRUE(std::holds_alternative<int32_t*>(int32_t_minus_1_value.data));
    ASSERT_EQ(std::get<int32_t*>(int32_t_minus_1_value.data), &int32_t_minus_1);
    ASSERT_EQ(std::strlen(int32_t_minus_1_value.get_datatype().c_str()), std::strlen("int32_t*"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_datatype().c_str(), "int32_t*"), 0);
    ASSERT_EQ(int32_t_minus_1_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_pointer_max)
{
    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::common::AnyValue int32_t_max_value = yli::common::AnyValue(&int32_t_max);
    ASSERT_TRUE(std::holds_alternative<int32_t*>(int32_t_max_value.data));
    ASSERT_EQ(std::get<int32_t*>(int32_t_max_value.data), &int32_t_max);
    ASSERT_EQ(std::strlen(int32_t_max_value.get_datatype().c_str()), std::strlen("int32_t*"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_datatype().c_str(), "int32_t*"), 0);
    ASSERT_EQ(int32_t_max_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_pointer_min)
{
    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::common::AnyValue int32_t_min_value = yli::common::AnyValue(&int32_t_min);
    ASSERT_TRUE(std::holds_alternative<int32_t*>(int32_t_min_value.data));
    ASSERT_EQ(std::get<int32_t*>(int32_t_min_value.data), &int32_t_min);
    ASSERT_EQ(std::strlen(int32_t_min_value.get_datatype().c_str()), std::strlen("int32_t*"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_datatype().c_str(), "int32_t*"), 0);
    ASSERT_EQ(int32_t_min_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_pointer_zero)
{
    uint32_t uint32_t_zero = 0;
    yli::common::AnyValue uint32_t_zero_value = yli::common::AnyValue(&uint32_t_zero);
    ASSERT_TRUE(std::holds_alternative<uint32_t*>(uint32_t_zero_value.data));
    ASSERT_EQ(std::get<uint32_t*>(uint32_t_zero_value.data), &uint32_t_zero);
    ASSERT_EQ(std::strlen(uint32_t_zero_value.get_datatype().c_str()), std::strlen("uint32_t*"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_datatype().c_str(), "uint32_t*"), 0);
    ASSERT_EQ(uint32_t_zero_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_pointer_plus_1)
{
    uint32_t uint32_t_plus_1 = 1;
    yli::common::AnyValue uint32_t_plus_1_value = yli::common::AnyValue(&uint32_t_plus_1);
    ASSERT_TRUE(std::holds_alternative<uint32_t*>(uint32_t_plus_1_value.data));
    ASSERT_EQ(std::get<uint32_t*>(uint32_t_plus_1_value.data), &uint32_t_plus_1);
    ASSERT_EQ(std::strlen(uint32_t_plus_1_value.get_datatype().c_str()), std::strlen("uint32_t*"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_datatype().c_str(), "uint32_t*"), 0);
    ASSERT_EQ(uint32_t_plus_1_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_pointer_max)
{
    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::common::AnyValue uint32_t_max_value = yli::common::AnyValue(&uint32_t_max);
    ASSERT_TRUE(std::holds_alternative<uint32_t*>(uint32_t_max_value.data));
    ASSERT_EQ(std::get<uint32_t*>(uint32_t_max_value.data), &uint32_t_max);
    ASSERT_EQ(std::strlen(uint32_t_max_value.get_datatype().c_str()), std::strlen("uint32_t*"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_datatype().c_str(), "uint32_t*"), 0);
    ASSERT_EQ(uint32_t_max_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, entity)
{
    yli::ontology::Entity* entity = static_cast<yli::ontology::Entity*>((void*) 0xdeadbeef);
    yli::common::AnyValue entity_any_value = yli::common::AnyValue(entity);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Entity*>(entity_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Entity*>(entity_any_value.data), entity);
    ASSERT_EQ(std::strlen(entity_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Entity*"));
    ASSERT_EQ(std::strcmp(entity_any_value.get_datatype().c_str(), "yli::ontology::Entity*"), 0);
    ASSERT_EQ(std::strlen(entity_any_value.get_string().c_str()), std::strlen("deadbeef"));
    ASSERT_EQ(std::strcmp(entity_any_value.get_string().c_str(), "deadbeef"), 0);
    ASSERT_EQ(entity_any_value.get_entity_pointer(), entity);
}

TEST(any_value_must_be_initialized_appropriately, movable)
{
    yli::ontology::Movable* movable = static_cast<yli::ontology::Movable*>((void*) 0xdeadbeef);
    yli::common::AnyValue movable_any_value = yli::common::AnyValue(movable);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Movable*>(movable_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Movable*>(movable_any_value.data), movable);
    ASSERT_EQ(std::strlen(movable_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Movable*"));
    ASSERT_EQ(std::strcmp(movable_any_value.get_datatype().c_str(), "yli::ontology::Movable*"), 0);
    ASSERT_EQ(std::strlen(movable_any_value.get_string().c_str()), std::strlen("deadbeef"));
    ASSERT_EQ(std::strcmp(movable_any_value.get_string().c_str(), "deadbeef"), 0);
    ASSERT_EQ(movable_any_value.get_entity_pointer(), (yli::ontology::Entity*) movable);
}

TEST(any_value_must_be_initialized_appropriately, const_movable)
{
    const yli::ontology::Movable* const_movable = static_cast<yli::ontology::Movable*>((void*) 0xdeadbeef);
    yli::common::AnyValue const_movable_any_value = yli::common::AnyValue(const_movable);
    ASSERT_TRUE(std::holds_alternative<const yli::ontology::Movable*>(const_movable_any_value.data));
    ASSERT_EQ(std::get<const yli::ontology::Movable*>(const_movable_any_value.data), const_movable);
    ASSERT_EQ(std::strlen(const_movable_any_value.get_datatype().c_str()), std::strlen("const yli::ontology::Movable*"));
    ASSERT_EQ(std::strcmp(const_movable_any_value.get_datatype().c_str(), "const yli::ontology::Movable*"), 0);
    ASSERT_EQ(std::strlen(const_movable_any_value.get_string().c_str()), std::strlen("deadbeef"));
    ASSERT_EQ(std::strcmp(const_movable_any_value.get_string().c_str(), "deadbeef"), 0);
    ASSERT_EQ(const_movable_any_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, universe)
{
    yli::ontology::Universe* universe = static_cast<yli::ontology::Universe*>((void*) 0xdeadbeef);
    yli::common::AnyValue universe_any_value = yli::common::AnyValue(universe);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Universe*>(universe_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Universe*>(universe_any_value.data), universe);
    ASSERT_EQ(std::strlen(universe_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Universe*"));
    ASSERT_EQ(std::strcmp(universe_any_value.get_datatype().c_str(), "yli::ontology::Universe*"), 0);
    ASSERT_EQ(std::strlen(universe_any_value.get_string().c_str()), std::strlen("deadbeef"));
    ASSERT_EQ(std::strcmp(universe_any_value.get_string().c_str(), "deadbeef"), 0);
    ASSERT_EQ(universe_any_value.get_entity_pointer(), (yli::ontology::Entity*) universe);
}

TEST(any_value_must_be_initialized_appropriately, world)
{
    yli::ontology::World* world = static_cast<yli::ontology::World*>((void*) 0xdeadbeef);
    yli::common::AnyValue world_any_value = yli::common::AnyValue(world);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::World*>(world_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::World*>(world_any_value.data), world);
    ASSERT_EQ(std::strlen(world_any_value.get_datatype().c_str()), std::strlen("yli::ontology::World*"));
    ASSERT_EQ(std::strcmp(world_any_value.get_datatype().c_str(), "yli::ontology::World*"), 0);
    ASSERT_EQ(std::strlen(world_any_value.get_string().c_str()), std::strlen("deadbeef"));
    ASSERT_EQ(std::strcmp(world_any_value.get_string().c_str(), "deadbeef"), 0);
    ASSERT_EQ(world_any_value.get_entity_pointer(), (yli::ontology::Entity*) world);
}

TEST(any_value_must_be_initialized_appropriately, scene)
{
    yli::ontology::Scene* scene = static_cast<yli::ontology::Scene*>((void*) 0xbad5ce6e);
    yli::common::AnyValue scene_pointer_any_value = yli::common::AnyValue(scene);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Scene*>(scene_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Scene*>(scene_pointer_any_value.data), scene);
    ASSERT_EQ(std::strlen(scene_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Scene*"));
    ASSERT_EQ(std::strcmp(scene_pointer_any_value.get_datatype().c_str(), "yli::ontology::Scene*"), 0);
    ASSERT_EQ(std::strlen(scene_pointer_any_value.get_string().c_str()), std::strlen("bad5ce6e"));
    ASSERT_EQ(std::strcmp(scene_pointer_any_value.get_string().c_str(), "bad5ce6e"), 0);
    ASSERT_EQ(scene_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) scene);
}

TEST(any_value_must_be_initialized_appropriately, shader)
{
    yli::ontology::Shader* shader = static_cast<yli::ontology::Shader*>((void*) 0xbad5bade7);
    yli::common::AnyValue shader_pointer_any_value = yli::common::AnyValue(shader);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Shader*>(shader_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Shader*>(shader_pointer_any_value.data), shader);
    ASSERT_EQ(std::strlen(shader_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Shader*"));
    ASSERT_EQ(std::strcmp(shader_pointer_any_value.get_datatype().c_str(), "yli::ontology::Shader*"), 0);
    ASSERT_EQ(std::strlen(shader_pointer_any_value.get_string().c_str()), std::strlen("bad5bade7"));
    ASSERT_EQ(std::strcmp(shader_pointer_any_value.get_string().c_str(), "bad5bade7"), 0);
    ASSERT_EQ(shader_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) shader);
}

TEST(any_value_must_be_initialized_appropriately, material)
{
    yli::ontology::Material* material = static_cast<yli::ontology::Material*>((void*) 0xbad6a7e71a1);
    yli::common::AnyValue material_pointer_any_value = yli::common::AnyValue(material);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Material*>(material_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Material*>(material_pointer_any_value.data), material);
    ASSERT_EQ(std::strlen(material_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Material*"));
    ASSERT_EQ(std::strcmp(material_pointer_any_value.get_datatype().c_str(), "yli::ontology::Material*"), 0);
    ASSERT_EQ(std::strlen(material_pointer_any_value.get_string().c_str()), std::strlen("bad6a7e71a1"));
    ASSERT_EQ(std::strcmp(material_pointer_any_value.get_string().c_str(), "bad6a7e71a1"), 0);
    ASSERT_EQ(material_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) material);
}

TEST(any_value_must_be_initialized_appropriately, species)
{
    yli::ontology::Species* species = static_cast<yli::ontology::Species*>((void*) 0xbad5bec1e5);
    yli::common::AnyValue species_pointer_any_value = yli::common::AnyValue(species);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Species*>(species_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Species*>(species_pointer_any_value.data), species);
    ASSERT_EQ(std::strlen(species_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Species*"));
    ASSERT_EQ(std::strcmp(species_pointer_any_value.get_datatype().c_str(), "yli::ontology::Species*"), 0);
    ASSERT_EQ(std::strlen(species_pointer_any_value.get_string().c_str()), std::strlen("bad5bec1e5"));
    ASSERT_EQ(std::strcmp(species_pointer_any_value.get_string().c_str(), "bad5bec1e5"), 0);
    ASSERT_EQ(species_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) species);
}

TEST(any_value_must_be_initialized_appropriately, object)
{
    yli::ontology::Object* object = static_cast<yli::ontology::Object*>((void*) 0xbad0b1ec7);
    yli::common::AnyValue object_pointer_any_value = yli::common::AnyValue(object);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Object*>(object_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Object*>(object_pointer_any_value.data), object);
    ASSERT_EQ(std::strlen(object_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Object*"));
    ASSERT_EQ(std::strcmp(object_pointer_any_value.get_datatype().c_str(), "yli::ontology::Object*"), 0);
    ASSERT_EQ(std::strlen(object_pointer_any_value.get_string().c_str()), std::strlen("bad0b1ec7"));
    ASSERT_EQ(std::strcmp(object_pointer_any_value.get_string().c_str(), "bad0b1ec7"), 0);
    ASSERT_EQ(object_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) object);
}

TEST(any_value_must_be_initialized_appropriately, symbiosis)
{
    yli::ontology::Symbiosis* symbiosis = static_cast<yli::ontology::Symbiosis*>((void*) 0xbad51b10515);
    yli::common::AnyValue symbiosis_pointer_any_value = yli::common::AnyValue(symbiosis);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Symbiosis*>(symbiosis_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Symbiosis*>(symbiosis_pointer_any_value.data), symbiosis);
    ASSERT_EQ(std::strlen(symbiosis_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Symbiosis*"));
    ASSERT_EQ(std::strcmp(symbiosis_pointer_any_value.get_datatype().c_str(), "yli::ontology::Symbiosis*"), 0);
    ASSERT_EQ(std::strlen(symbiosis_pointer_any_value.get_string().c_str()), std::strlen("bad51b10515"));
    ASSERT_EQ(std::strcmp(symbiosis_pointer_any_value.get_string().c_str(), "bad51b10515"), 0);
    ASSERT_EQ(symbiosis_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) symbiosis);
}

TEST(any_value_must_be_initialized_appropriately, symbiont_material)
{
    yli::ontology::SymbiontMaterial* symbiont_material = static_cast<yli::ontology::SymbiontMaterial*>((void*) 0xbad51b10ba7e71a1);
    yli::common::AnyValue symbiont_material_pointer_any_value = yli::common::AnyValue(symbiont_material);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::SymbiontMaterial*>(symbiont_material_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::SymbiontMaterial*>(symbiont_material_pointer_any_value.data), symbiont_material);
    ASSERT_EQ(std::strlen(symbiont_material_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::SymbiontMaterial*"));
    ASSERT_EQ(std::strcmp(symbiont_material_pointer_any_value.get_datatype().c_str(), "yli::ontology::SymbiontMaterial*"), 0);
    ASSERT_EQ(std::strlen(symbiont_material_pointer_any_value.get_string().c_str()), std::strlen("bad51b10ba7e71a1"));
    ASSERT_EQ(std::strcmp(symbiont_material_pointer_any_value.get_string().c_str(), "bad51b10ba7e71a1"), 0);
    ASSERT_EQ(symbiont_material_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) symbiont_material);
}

TEST(any_value_must_be_initialized_appropriately, symbiont_species)
{
    yli::ontology::SymbiontSpecies* symbiont_species = static_cast<yli::ontology::SymbiontSpecies*>((void*) 0xbad51b105bec1e5);
    yli::common::AnyValue symbiont_species_pointer_any_value = yli::common::AnyValue(symbiont_species);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::SymbiontSpecies*>(symbiont_species_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::SymbiontSpecies*>(symbiont_species_pointer_any_value.data), symbiont_species);
    ASSERT_EQ(std::strlen(symbiont_species_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::SymbiontSpecies*"));
    ASSERT_EQ(std::strcmp(symbiont_species_pointer_any_value.get_datatype().c_str(), "yli::ontology::SymbiontSpecies*"), 0);
    ASSERT_EQ(std::strlen(symbiont_species_pointer_any_value.get_string().c_str()), std::strlen("bad51b105bec1e5"));
    ASSERT_EQ(std::strcmp(symbiont_species_pointer_any_value.get_string().c_str(), "bad51b105bec1e5"), 0);
    ASSERT_EQ(symbiont_species_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) symbiont_species);
}

TEST(any_value_must_be_initialized_appropriately, holobiont)
{
    yli::ontology::Holobiont* holobiont = static_cast<yli::ontology::Holobiont*>((void*) 0xbad010b107);
    yli::common::AnyValue holobiont_pointer_any_value = yli::common::AnyValue(holobiont);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Holobiont*>(holobiont_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Holobiont*>(holobiont_pointer_any_value.data), holobiont);
    ASSERT_EQ(std::strlen(holobiont_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Holobiont*"));
    ASSERT_EQ(std::strcmp(holobiont_pointer_any_value.get_datatype().c_str(), "yli::ontology::Holobiont*"), 0);
    ASSERT_EQ(std::strlen(holobiont_pointer_any_value.get_string().c_str()), std::strlen("bad010b107"));
    ASSERT_EQ(std::strcmp(holobiont_pointer_any_value.get_string().c_str(), "bad010b107"), 0);
    ASSERT_EQ(holobiont_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) holobiont);
}

TEST(any_value_must_be_initialized_appropriately, biont)
{
    yli::ontology::Biont* biont = static_cast<yli::ontology::Biont*>((void*) 0xbadb107);
    yli::common::AnyValue biont_pointer_any_value = yli::common::AnyValue(biont);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Biont*>(biont_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Biont*>(biont_pointer_any_value.data), biont);
    ASSERT_EQ(std::strlen(biont_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Biont*"));
    ASSERT_EQ(std::strcmp(biont_pointer_any_value.get_datatype().c_str(), "yli::ontology::Biont*"), 0);
    ASSERT_EQ(std::strlen(biont_pointer_any_value.get_string().c_str()), std::strlen("badb107"));
    ASSERT_EQ(std::strcmp(biont_pointer_any_value.get_string().c_str(), "badb107"), 0);
    ASSERT_EQ(biont_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) biont);
}

TEST(any_value_must_be_initialized_appropriately, font2D)
{
    yli::ontology::Font2D* font2D = static_cast<yli::ontology::Font2D*>((void*) 0xbadf072d);
    yli::common::AnyValue font2D_pointer_any_value = yli::common::AnyValue(font2D);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Font2D*>(font2D_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Font2D*>(font2D_pointer_any_value.data), font2D);
    ASSERT_EQ(std::strlen(font2D_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Font2D*"));
    ASSERT_EQ(std::strcmp(font2D_pointer_any_value.get_datatype().c_str(), "yli::ontology::Font2D*"), 0);
    ASSERT_EQ(std::strlen(font2D_pointer_any_value.get_string().c_str()), std::strlen("badf072d"));
    ASSERT_EQ(std::strcmp(font2D_pointer_any_value.get_string().c_str(), "badf072d"), 0);
    ASSERT_EQ(font2D_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) font2D);
}

TEST(any_value_must_be_initialized_appropriately, text2D)
{
    yli::ontology::Text2D* text2D = static_cast<yli::ontology::Text2D*>((void*) 0xbad7e72d);
    yli::common::AnyValue text2D_pointer_any_value = yli::common::AnyValue(text2D);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Text2D*>(text2D_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Text2D*>(text2D_pointer_any_value.data), text2D);
    ASSERT_EQ(std::strlen(text2D_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Text2D*"));
    ASSERT_EQ(std::strcmp(text2D_pointer_any_value.get_datatype().c_str(), "yli::ontology::Text2D*"), 0);
    ASSERT_EQ(std::strlen(text2D_pointer_any_value.get_string().c_str()), std::strlen("bad7e72d"));
    ASSERT_EQ(std::strcmp(text2D_pointer_any_value.get_string().c_str(), "bad7e72d"), 0);
    ASSERT_EQ(text2D_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) text2D);
}

TEST(any_value_must_be_initialized_appropriately, vector_font)
{
    yli::ontology::VectorFont* vector_font = static_cast<yli::ontology::VectorFont*>((void*) 0xbadec70f07);
    yli::common::AnyValue vector_font_pointer_any_value = yli::common::AnyValue(vector_font);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::VectorFont*>(vector_font_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::VectorFont*>(vector_font_pointer_any_value.data), vector_font);
    ASSERT_EQ(std::strlen(vector_font_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::VectorFont*"));
    ASSERT_EQ(std::strcmp(vector_font_pointer_any_value.get_datatype().c_str(), "yli::ontology::VectorFont*"), 0);
    ASSERT_EQ(std::strlen(vector_font_pointer_any_value.get_string().c_str()), std::strlen("badec70f07"));
    ASSERT_EQ(std::strcmp(vector_font_pointer_any_value.get_string().c_str(), "badec70f07"), 0);
    ASSERT_EQ(vector_font_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) vector_font);
}

TEST(any_value_must_be_initialized_appropriately, glyph)
{
    yli::ontology::Glyph* glyph = static_cast<yli::ontology::Glyph*>((void*) 0xbad11f);
    yli::common::AnyValue glyph_pointer_any_value = yli::common::AnyValue(glyph);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Glyph*>(glyph_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Glyph*>(glyph_pointer_any_value.data), glyph);
    ASSERT_EQ(std::strlen(glyph_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Glyph*"));
    ASSERT_EQ(std::strcmp(glyph_pointer_any_value.get_datatype().c_str(), "yli::ontology::Glyph*"), 0);
    ASSERT_EQ(std::strlen(glyph_pointer_any_value.get_string().c_str()), std::strlen("bad11f"));
    ASSERT_EQ(std::strcmp(glyph_pointer_any_value.get_string().c_str(), "bad11f"), 0);
    ASSERT_EQ(glyph_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) glyph);
}

TEST(any_value_must_be_initialized_appropriately, text3D)
{
    yli::ontology::Text3D* text3D = static_cast<yli::ontology::Text3D*>((void*) 0xbad7e73d);
    yli::common::AnyValue text3D_pointer_any_value = yli::common::AnyValue(text3D);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Text3D*>(text3D_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Text3D*>(text3D_pointer_any_value.data), text3D);
    ASSERT_EQ(std::strlen(text3D_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Text3D*"));
    ASSERT_EQ(std::strcmp(text3D_pointer_any_value.get_datatype().c_str(), "yli::ontology::Text3D*"), 0);
    ASSERT_EQ(std::strlen(text3D_pointer_any_value.get_string().c_str()), std::strlen("bad7e73d"));
    ASSERT_EQ(std::strcmp(text3D_pointer_any_value.get_string().c_str(), "bad7e73d"), 0);
    ASSERT_EQ(text3D_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) text3D);
}

TEST(any_value_must_be_initialized_appropriately, console)
{
    yli::ontology::Console* console = static_cast<yli::ontology::Console*>((void*) 0xbadc0501e);
    yli::common::AnyValue console_pointer_any_value = yli::common::AnyValue(console);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Console*>(console_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::Console*>(console_pointer_any_value.data), console);
    ASSERT_EQ(std::strlen(console_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Console*"));
    ASSERT_EQ(std::strcmp(console_pointer_any_value.get_datatype().c_str(), "yli::ontology::Console*"), 0);
    ASSERT_EQ(std::strlen(console_pointer_any_value.get_string().c_str()), std::strlen("badc0501e"));
    ASSERT_EQ(std::strcmp(console_pointer_any_value.get_string().c_str(), "badc0501e"), 0);
    ASSERT_EQ(console_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) console);
}

TEST(any_value_must_be_initialized_appropriately, compute_task)
{
    yli::ontology::ComputeTask* compute_task = static_cast<yli::ontology::ComputeTask*>((void*) 0xbad7a5c);
    yli::common::AnyValue compute_task_pointer_any_value = yli::common::AnyValue(compute_task);
    ASSERT_TRUE(std::holds_alternative<yli::ontology::ComputeTask*>(compute_task_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::ontology::ComputeTask*>(compute_task_pointer_any_value.data), compute_task);
    ASSERT_EQ(std::strlen(compute_task_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::ComputeTask*"));
    ASSERT_EQ(std::strcmp(compute_task_pointer_any_value.get_datatype().c_str(), "yli::ontology::ComputeTask*"), 0);
    ASSERT_EQ(std::strlen(compute_task_pointer_any_value.get_string().c_str()), std::strlen("bad7a5c"));
    ASSERT_EQ(std::strcmp(compute_task_pointer_any_value.get_string().c_str(), "bad7a5c"), 0);
    ASSERT_EQ(compute_task_pointer_any_value.get_entity_pointer(), (yli::ontology::Entity*) compute_task);
}

TEST(any_value_must_be_initialized_appropriately, any_value_shader_ptr)
{
    std::shared_ptr<yli::common::AnyValue> any_value_shared_ptr =
        std::make_shared<yli::common::AnyValue>();
    yli::common::AnyValue any_value_shared_ptr_any_value = yli::common::AnyValue(any_value_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<yli::common::AnyValue>>(any_value_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<yli::common::AnyValue>>(any_value_shared_ptr_any_value.data), any_value_shared_ptr);
    ASSERT_EQ(std::strlen(any_value_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<yli::common::AnyValue>"));
    ASSERT_EQ(std::strcmp(any_value_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<yli::common::AnyValue>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, any_struct_shader_ptr)
{
    std::shared_ptr<yli::common::AnyStruct> any_struct_shared_ptr =
        std::make_shared<yli::common::AnyStruct>();
    yli::common::AnyValue any_struct_shared_ptr_any_value = yli::common::AnyValue(any_struct_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<yli::common::AnyStruct>>(any_struct_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<yli::common::AnyStruct>>(any_struct_shared_ptr_any_value.data), any_struct_shared_ptr);
    ASSERT_EQ(std::strlen(any_struct_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<yli::common::AnyStruct>"));
    ASSERT_EQ(std::strcmp(any_struct_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<yli::common::AnyStruct>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, spherical_coordinates_struct)
{
    yli::common::SphericalCoordinatesStruct spherical_coordinates_struct = yli::common::SphericalCoordinatesStruct(1.0f, 2.0f, 3.0f);
    yli::common::AnyValue spherical_coordinates_struct_pointer_any_value = yli::common::AnyValue(&spherical_coordinates_struct);
    ASSERT_TRUE(std::holds_alternative<yli::common::SphericalCoordinatesStruct*>(spherical_coordinates_struct_pointer_any_value.data));
    ASSERT_EQ(std::get<yli::common::SphericalCoordinatesStruct*>(spherical_coordinates_struct_pointer_any_value.data), &spherical_coordinates_struct);
    ASSERT_EQ(std::strlen(spherical_coordinates_struct_pointer_any_value.get_datatype().c_str()), std::strlen("yli::common::SphericalCoordinatesStruct*"));
    ASSERT_EQ(std::strcmp(spherical_coordinates_struct_pointer_any_value.get_datatype().c_str(), "yli::common::SphericalCoordinatesStruct*"), 0);
    // TODO: add assertions for `AnyValue::get_string` for `yli::common::SphericalCoordinatesStruct`!
    ASSERT_EQ(spherical_coordinates_struct_pointer_any_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, std_string)
{
    std::string foo_string = "foo";
    std::string* const foo_string_pointer = &foo_string;
    yli::common::AnyValue std_string_pointer_any_value = yli::common::AnyValue(foo_string_pointer);
    ASSERT_TRUE(std::holds_alternative<std::string*>(std_string_pointer_any_value.data));
    ASSERT_EQ(std::get<std::string*>(std_string_pointer_any_value.data), foo_string_pointer);
    ASSERT_EQ(std::strlen(std_string_pointer_any_value.get_datatype().c_str()), std::strlen("std::string*"));
    ASSERT_EQ(std::strcmp(std_string_pointer_any_value.get_datatype().c_str(), "std::string*"), 0);
    ASSERT_EQ(std::strlen(std_string_pointer_any_value.get_string().c_str()), std::strlen("foo"));
    ASSERT_EQ(std::strcmp(std_string_pointer_any_value.get_string().c_str(), "foo"), 0);
}

TEST(any_value_must_be_initialized_appropriately, const_std_string)
{
    const std::string foo_string = "foo";
    const std::string* const foo_string_pointer = &foo_string;
    yli::common::AnyValue const_std_string_pointer_any_value = yli::common::AnyValue(foo_string_pointer);
    ASSERT_TRUE(std::holds_alternative<const std::string*>(const_std_string_pointer_any_value.data));
    ASSERT_EQ(std::get<const std::string*>(const_std_string_pointer_any_value.data), foo_string_pointer);
    ASSERT_EQ(std::strlen(const_std_string_pointer_any_value.get_datatype().c_str()), std::strlen("const std::string*"));
    ASSERT_EQ(std::strcmp(const_std_string_pointer_any_value.get_datatype().c_str(), "const std::string*"), 0);
    ASSERT_EQ(std::strlen(const_std_string_pointer_any_value.get_string().c_str()), std::strlen("foo"));
    ASSERT_EQ(std::strcmp(const_std_string_pointer_any_value.get_string().c_str(), "foo"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_int8_t_shared_ptr)
{
    std::shared_ptr<std::vector<int8_t>> std_vector_int8_t_shared_ptr =
        std::make_shared<std::vector<int8_t>>();
    yli::common::AnyValue std_vector_int8_t_shared_ptr_any_value = yli::common::AnyValue(std_vector_int8_t_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<std::vector<int8_t>>>(std_vector_int8_t_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<std::vector<int8_t>>>(std_vector_int8_t_shared_ptr_any_value.data), std_vector_int8_t_shared_ptr);
    ASSERT_EQ(std::strlen(std_vector_int8_t_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<std::vector<int8_t>>"));
    ASSERT_EQ(std::strcmp(std_vector_int8_t_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<std::vector<int8_t>>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_uint8_t_shared_ptr)
{
    std::shared_ptr<std::vector<uint8_t>> std_vector_uint8_t_shared_ptr =
        std::make_shared<std::vector<uint8_t>>();
    yli::common::AnyValue std_vector_uint8_t_shared_ptr_any_value = yli::common::AnyValue(std_vector_uint8_t_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<std::vector<uint8_t>>>(std_vector_uint8_t_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<std::vector<uint8_t>>>(std_vector_uint8_t_shared_ptr_any_value.data), std_vector_uint8_t_shared_ptr);
    ASSERT_EQ(std::strlen(std_vector_uint8_t_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<std::vector<uint8_t>>"));
    ASSERT_EQ(std::strcmp(std_vector_uint8_t_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<std::vector<uint8_t>>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_int16_t_shared_ptr)
{
    std::shared_ptr<std::vector<int16_t>> std_vector_int16_t_shared_ptr =
        std::make_shared<std::vector<int16_t>>();
    yli::common::AnyValue std_vector_int16_t_shared_ptr_any_value = yli::common::AnyValue(std_vector_int16_t_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<std::vector<int16_t>>>(std_vector_int16_t_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<std::vector<int16_t>>>(std_vector_int16_t_shared_ptr_any_value.data), std_vector_int16_t_shared_ptr);
    ASSERT_EQ(std::strlen(std_vector_int16_t_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<std::vector<int16_t>>"));
    ASSERT_EQ(std::strcmp(std_vector_int16_t_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<std::vector<int16_t>>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_uint16_t_shared_ptr)
{
    std::shared_ptr<std::vector<uint16_t>> std_vector_uint16_t_shared_ptr =
        std::make_shared<std::vector<uint16_t>>();
    yli::common::AnyValue std_vector_uint16_t_shared_ptr_any_value = yli::common::AnyValue(std_vector_uint16_t_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<std::vector<uint16_t>>>(std_vector_uint16_t_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<std::vector<uint16_t>>>(std_vector_uint16_t_shared_ptr_any_value.data), std_vector_uint16_t_shared_ptr);
    ASSERT_EQ(std::strlen(std_vector_uint16_t_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<std::vector<uint16_t>>"));
    ASSERT_EQ(std::strcmp(std_vector_uint16_t_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<std::vector<uint16_t>>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_int32_t_shared_ptr)
{
    std::shared_ptr<std::vector<int32_t>> std_vector_int32_t_shared_ptr =
        std::make_shared<std::vector<int32_t>>();
    yli::common::AnyValue std_vector_int32_t_shared_ptr_any_value = yli::common::AnyValue(std_vector_int32_t_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<std::vector<int32_t>>>(std_vector_int32_t_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<std::vector<int32_t>>>(std_vector_int32_t_shared_ptr_any_value.data), std_vector_int32_t_shared_ptr);
    ASSERT_EQ(std::strlen(std_vector_int32_t_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<std::vector<int32_t>>"));
    ASSERT_EQ(std::strcmp(std_vector_int32_t_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<std::vector<int32_t>>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_uint32_t_shared_ptr)
{
    std::shared_ptr<std::vector<uint32_t>> std_vector_uint32_t_shared_ptr =
        std::make_shared<std::vector<uint32_t>>();
    yli::common::AnyValue std_vector_uint32_t_shared_ptr_any_value = yli::common::AnyValue(std_vector_uint32_t_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<std::vector<uint32_t>>>(std_vector_uint32_t_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<std::vector<uint32_t>>>(std_vector_uint32_t_shared_ptr_any_value.data), std_vector_uint32_t_shared_ptr);
    ASSERT_EQ(std::strlen(std_vector_uint32_t_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<std::vector<uint32_t>>"));
    ASSERT_EQ(std::strcmp(std_vector_uint32_t_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<std::vector<uint32_t>>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_float_shared_ptr)
{
    std::shared_ptr<std::vector<float>> std_vector_float_shared_ptr =
        std::make_shared<std::vector<float>>();
    yli::common::AnyValue std_vector_float_shared_ptr_any_value = yli::common::AnyValue(std_vector_float_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<std::vector<float>>>(std_vector_float_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<std::vector<float>>>(std_vector_float_shared_ptr_any_value.data), std_vector_float_shared_ptr);
    ASSERT_EQ(std::strlen(std_vector_float_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<std::vector<float>>"));
    ASSERT_EQ(std::strcmp(std_vector_float_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<std::vector<float>>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_string_shared_ptr)
{
    std::shared_ptr<std::string> std_string_shared_ptr = std::make_shared<std::string>("foo");
    yli::common::AnyValue std_string_shared_ptr_any_value = yli::common::AnyValue(std_string_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<std::string>>(std_string_shared_ptr_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<std::string>>(std_string_shared_ptr_any_value.data), std_string_shared_ptr);
    ASSERT_EQ(std::strlen(std_string_shared_ptr_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<std::string>"));
    ASSERT_EQ(std::strcmp(std_string_shared_ptr_any_value.get_datatype().c_str(), "std::shared_ptr<std::string>"), 0);
}

TEST(any_value_must_be_initialized_appropriately, glm_vec3_shared_ptr)
{
    std::shared_ptr<glm::vec3> glm_vec3_shared_ptr = std::make_shared<glm::vec3>(1.0f, 2.0f, 3.0f);
    yli::common::AnyValue glm_vec3_pointer_any_value = yli::common::AnyValue(glm_vec3_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<glm::vec3>>(glm_vec3_pointer_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<glm::vec3>>(glm_vec3_pointer_any_value.data), glm_vec3_shared_ptr);
    ASSERT_EQ(std::strlen(glm_vec3_pointer_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<glm::vec3>"));
    ASSERT_EQ(std::strcmp(glm_vec3_pointer_any_value.get_datatype().c_str(), "std::shared_ptr<glm::vec3>"), 0);
    // TODO: add assertions for `AnyValue::get_string` for `glm::vec3*`!
    ASSERT_EQ(glm_vec3_pointer_any_value.get_entity_pointer(), nullptr);
}

TEST(any_value_must_be_initialized_appropriately, glm_vec4_shared_ptr)
{
    std::shared_ptr<glm::vec4> glm_vec4_shared_ptr = std::make_shared<glm::vec4>(1.0f, 2.0f, 3.0f, 4.0f);
    yli::common::AnyValue glm_vec4_pointer_any_value = yli::common::AnyValue(glm_vec4_shared_ptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<glm::vec4>>(glm_vec4_pointer_any_value.data));
    ASSERT_EQ(std::get<std::shared_ptr<glm::vec4>>(glm_vec4_pointer_any_value.data), glm_vec4_shared_ptr);
    ASSERT_EQ(std::strlen(glm_vec4_pointer_any_value.get_datatype().c_str()), std::strlen("std::shared_ptr<glm::vec4>"));
    ASSERT_EQ(std::strcmp(glm_vec4_pointer_any_value.get_datatype().c_str(), "std::shared_ptr<glm::vec4>"), 0);
    // TODO: add assertions for `AnyValue::get_string` for `glm::vec4*`!
    ASSERT_EQ(glm_vec4_pointer_any_value.get_entity_pointer(), nullptr);
}

TEST(set_new_value_must_function_properly, originally_bool_true_new_value_bool_true)
{
    bool bool_true = true;
    yli::common::AnyValue any_value = yli::common::AnyValue(bool_true);
    ASSERT_TRUE(any_value.set_new_value("true"));
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_TRUE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_true_new_value_bool_false)
{
    bool bool_true = true;
    yli::common::AnyValue any_value = yli::common::AnyValue(bool_true);
    ASSERT_TRUE(any_value.set_new_value("false"));
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_FALSE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_true_new_value_foo)
{
    bool bool_true = true;
    yli::common::AnyValue any_value = yli::common::AnyValue(bool_true);
    ASSERT_FALSE(any_value.set_new_value("foo")); // `"foo"` is invalid value and should not change the current value.
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_TRUE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_false_new_value_bool_true)
{
    bool bool_false = false;
    yli::common::AnyValue any_value = yli::common::AnyValue(bool_false);
    ASSERT_TRUE(any_value.set_new_value("true"));
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_TRUE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_false_new_value_bool_false)
{
    bool bool_false = false;
    yli::common::AnyValue any_value = yli::common::AnyValue(bool_false);
    ASSERT_TRUE(any_value.set_new_value("false"));
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_FALSE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_false_new_value_foo)
{
    bool bool_false = false;
    yli::common::AnyValue any_value = yli::common::AnyValue(bool_false);
    ASSERT_FALSE(any_value.set_new_value("foo")); // `"foo"` is invalid value and should not change the current value.
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_FALSE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_char_lowercase_a_new_value_a)
{
    char char_lowercase_a = 'a';
    yli::common::AnyValue any_value = yli::common::AnyValue(char_lowercase_a);
    ASSERT_TRUE(any_value.set_new_value("a"));
    ASSERT_TRUE(std::holds_alternative<char>(any_value.data));
    ASSERT_EQ(std::get<char>(any_value.data), 'a');
}

TEST(set_new_value_must_function_properly, originally_char_lowercase_a_new_value_b)
{
    char char_lowercase_a = 'a';
    yli::common::AnyValue any_value = yli::common::AnyValue(char_lowercase_a);
    ASSERT_TRUE(any_value.set_new_value("b"));
    ASSERT_TRUE(std::holds_alternative<char>(any_value.data));
    ASSERT_EQ(std::get<char>(any_value.data), 'b');
}

TEST(set_new_value_must_function_properly, originally_char_lowercase_a_new_value_bb)
{
    char char_lowercase_a = 'a';
    yli::common::AnyValue any_value = yli::common::AnyValue(char_lowercase_a);
    ASSERT_FALSE(any_value.set_new_value("bb")); // `"bb"` is invalid value and should not change the current value.
    ASSERT_TRUE(std::holds_alternative<char>(any_value.data));
    ASSERT_EQ(std::get<char>(any_value.data), 'a');
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_0)
{
    float float_zero = 0.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 0.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_0_dot_0)
{
    float float_zero = 0.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("0.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 0.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_plus_1)
{
    float float_zero = 0.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("1"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_plus_1_dot_0)
{
    float float_zero = 0.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("1.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_minus_1_dot_0)
{
    float float_zero = 0.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("-1.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), -1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_plus_1234)
{
    float float_zero = 0.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("1234"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1234.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_plus_1234_dot_0)
{
    float float_zero = 0.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("1234.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1234.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_0)
{
    float float_plus_1 = 1.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 0.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_0_dot_0)
{
    float float_plus_1 = 1.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("0.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 0.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_plus_1)
{
    float float_plus_1 = 1.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("1"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_plus_1_dot_0)
{
    float float_plus_1 = 1.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("1.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_minus_1_dot_0)
{
    float float_plus_1 = 1.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("-1.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), -1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_plus_1234)
{
    float float_plus_1 = 1.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("1234"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1234.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_plus_1234_dot_0)
{
    float float_plus_1 = 1.0f;
    yli::common::AnyValue any_value = yli::common::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("1234.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1234.0f);
}
