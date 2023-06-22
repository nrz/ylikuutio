// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/vector_font.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
#include "code/ylikuutio/ontology/text_struct.hpp"
#include "code/ylikuutio/ontology/vector_font_struct.hpp"
#include "code/ylikuutio/ontology/text_3d_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <functional> // std::reference_wrapper
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <variant>  // std::holds_alternative, std::monostate, std::variant
#include <vector>   // std::vector

TEST(any_value_must_be_initialized_appropriately, default_constructor)
{
    yli::data::AnyValue default_value = yli::data::AnyValue();
    ASSERT_TRUE(std::holds_alternative<std::monostate>(default_value.data));
}

TEST(any_value_must_be_initialized_appropriately, bool_true)
{
    bool bool_true = true;
    yli::data::AnyValue true_value = yli::data::AnyValue(bool_true);
    ASSERT_TRUE(std::holds_alternative<bool>(true_value.data));
    ASSERT_TRUE(std::get<bool>(true_value.data));
    ASSERT_EQ(std::char_traits<char>::length(true_value.get_datatype().c_str()), std::char_traits<char>::length("bool"));
    ASSERT_EQ(std::strcmp(true_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::char_traits<char>::length(true_value.get_string().c_str()), std::char_traits<char>::length("true"));
    ASSERT_EQ(std::strcmp(true_value.get_string().c_str(), "true"), 0);
}

TEST(any_value_must_be_initialized_appropriately, bool_false)
{
    bool bool_false = false;
    yli::data::AnyValue false_value = yli::data::AnyValue(bool_false);
    ASSERT_TRUE(std::holds_alternative<bool>(false_value.data));
    ASSERT_FALSE(std::get<bool>(false_value.data));
    ASSERT_EQ(std::char_traits<char>::length(false_value.get_datatype().c_str()), std::char_traits<char>::length("bool"));
    ASSERT_EQ(std::strcmp(false_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::char_traits<char>::length(false_value.get_string().c_str()), std::char_traits<char>::length("false"));
    ASSERT_EQ(std::strcmp(false_value.get_string().c_str(), "false"), 0);
}

TEST(any_value_must_be_initialized_appropriately, char_lowercase_a)
{
    char char_lowercase_a = 'a';
    yli::data::AnyValue lowercase_a_value = yli::data::AnyValue(char_lowercase_a);
    ASSERT_TRUE(std::holds_alternative<char>(lowercase_a_value.data));
    ASSERT_EQ(std::get<char>(lowercase_a_value.data), 'a');
    ASSERT_EQ(std::char_traits<char>::length(lowercase_a_value.get_datatype().c_str()), std::char_traits<char>::length("char"));
    ASSERT_EQ(std::strcmp(lowercase_a_value.get_datatype().c_str(), "char"), 0);
    ASSERT_EQ(std::char_traits<char>::length(lowercase_a_value.get_string().c_str()), std::char_traits<char>::length("a"));
    ASSERT_EQ(std::strcmp(lowercase_a_value.get_string().c_str(), "a"), 0);
}

TEST(any_value_must_be_initialized_appropriately, char_lowercase_b)
{
    char char_lowercase_b = 'b';
    yli::data::AnyValue lowercase_b_value = yli::data::AnyValue(char_lowercase_b);
    ASSERT_TRUE(std::holds_alternative<char>(lowercase_b_value.data));
    ASSERT_EQ(std::get<char>(lowercase_b_value.data), 'b');
    ASSERT_EQ(std::char_traits<char>::length(lowercase_b_value.get_datatype().c_str()), std::char_traits<char>::length("char"));
    ASSERT_EQ(std::strcmp(lowercase_b_value.get_datatype().c_str(), "char"), 0);
    ASSERT_EQ(std::char_traits<char>::length(lowercase_b_value.get_string().c_str()), std::char_traits<char>::length("b"));
    ASSERT_EQ(std::strcmp(lowercase_b_value.get_string().c_str(), "b"), 0);
}

TEST(any_value_must_be_initialized_appropriately, char_space)
{
    char char_space = ' ';
    yli::data::AnyValue space_value = yli::data::AnyValue(char_space);
    ASSERT_TRUE(std::holds_alternative<char>(space_value.data));
    ASSERT_EQ(std::get<char>(space_value.data), ' ');
    ASSERT_EQ(std::char_traits<char>::length(space_value.get_datatype().c_str()), std::char_traits<char>::length("char"));
    ASSERT_EQ(std::strcmp(space_value.get_datatype().c_str(), "char"), 0);
    ASSERT_EQ(std::char_traits<char>::length(space_value.get_string().c_str()), std::char_traits<char>::length(" "));
    ASSERT_EQ(std::strcmp(space_value.get_string().c_str(), " "), 0);
}

TEST(any_value_must_be_initialized_appropriately, char_newline)
{
    char char_newline = '\n';
    yli::data::AnyValue newline_value = yli::data::AnyValue(char_newline);
    ASSERT_TRUE(std::holds_alternative<char>(newline_value.data));
    ASSERT_EQ(std::get<char>(newline_value.data), '\n');
    ASSERT_EQ(std::char_traits<char>::length(newline_value.get_datatype().c_str()), std::char_traits<char>::length("char"));
    ASSERT_EQ(std::strcmp(newline_value.get_datatype().c_str(), "char"), 0);
    ASSERT_EQ(std::char_traits<char>::length(newline_value.get_string().c_str()), std::char_traits<char>::length("\n"));
    ASSERT_EQ(std::strcmp(newline_value.get_string().c_str(), "\n"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_0)
{
    float float_zero = 0.0f;
    yli::data::AnyValue float_zero_value = yli::data::AnyValue(float_zero);
    ASSERT_TRUE(std::holds_alternative<float>(float_zero_value.data));
    ASSERT_EQ(std::get<float>(float_zero_value.data), 0.0f);
    ASSERT_EQ(std::char_traits<char>::length(float_zero_value.get_datatype().c_str()), std::char_traits<char>::length("float"));
    ASSERT_EQ(std::strcmp(float_zero_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::char_traits<char>::length(float_zero_value.get_string().c_str()), std::char_traits<char>::length("0.000000"));
    ASSERT_EQ(std::char_traits<char>::length(float_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(float_zero_value.get_string().c_str(), "0.000000"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_positive_infinity)
{
    float float_positive_infinity = std::numeric_limits<float>::infinity();
    yli::data::AnyValue float_positive_infinity_value = yli::data::AnyValue(float_positive_infinity);
    ASSERT_TRUE(std::holds_alternative<float>(float_positive_infinity_value.data));
    ASSERT_EQ(std::get<float>(float_positive_infinity_value.data), std::numeric_limits<float>::infinity());
    ASSERT_EQ(std::char_traits<char>::length(float_positive_infinity_value.get_datatype().c_str()), std::char_traits<char>::length("float"));
    ASSERT_EQ(std::strcmp(float_positive_infinity_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::char_traits<char>::length(float_positive_infinity_value.get_string().c_str()), std::char_traits<char>::length("inf"));
    ASSERT_EQ(std::strcmp(float_positive_infinity_value.get_string().c_str(), "inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_negative_infinity)
{
    float float_negative_infinity = -1.0f * std::numeric_limits<float>::infinity();
    yli::data::AnyValue float_negative_infinity_value = yli::data::AnyValue(float_negative_infinity);
    ASSERT_TRUE(std::holds_alternative<float>(float_negative_infinity_value.data));
    ASSERT_EQ(std::get<float>(float_negative_infinity_value.data), float_negative_infinity);
    ASSERT_EQ(std::char_traits<char>::length(float_negative_infinity_value.get_datatype().c_str()), std::char_traits<char>::length("float"));
    ASSERT_EQ(std::strcmp(float_negative_infinity_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::char_traits<char>::length(float_negative_infinity_value.get_string().c_str()), std::char_traits<char>::length("-inf"));
    ASSERT_EQ(std::strcmp(float_negative_infinity_value.get_string().c_str(), "-inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_nan)
{
    float float_nan = NAN;
    yli::data::AnyValue float_nan_value = yli::data::AnyValue(float_nan);
    ASSERT_TRUE(std::holds_alternative<float>(float_nan_value.data));
    ASSERT_TRUE(std::isnan(std::get<float>(float_nan_value.data)));
    ASSERT_EQ(std::char_traits<char>::length(float_nan_value.get_datatype().c_str()), std::char_traits<char>::length("float"));
    ASSERT_EQ(std::strcmp(float_nan_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::char_traits<char>::length(float_nan_value.get_string().c_str()), std::char_traits<char>::length("nan"));
    ASSERT_EQ(std::strcmp(float_nan_value.get_string().c_str(), "nan"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_0)
{
    double double_zero = 0.0f;
    yli::data::AnyValue double_zero_value = yli::data::AnyValue(double_zero);
    ASSERT_TRUE(std::holds_alternative<double>(double_zero_value.data));
    ASSERT_EQ(std::get<double>(double_zero_value.data), 0.0f);
    ASSERT_EQ(std::char_traits<char>::length(double_zero_value.get_datatype().c_str()), std::char_traits<char>::length("double"));
    ASSERT_EQ(std::strcmp(double_zero_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::char_traits<char>::length(double_zero_value.get_string().c_str()), std::char_traits<char>::length("0.000000"));
    ASSERT_EQ(std::char_traits<char>::length(double_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(double_zero_value.get_string().c_str(), "0.000000"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_positive_infinity)
{
    double double_positive_infinity = std::numeric_limits<double>::infinity();
    yli::data::AnyValue double_positive_infinity_value = yli::data::AnyValue(double_positive_infinity);
    ASSERT_TRUE(std::holds_alternative<double>(double_positive_infinity_value.data));
    ASSERT_EQ(std::get<double>(double_positive_infinity_value.data), std::numeric_limits<double>::infinity());
    ASSERT_EQ(std::char_traits<char>::length(double_positive_infinity_value.get_datatype().c_str()), std::char_traits<char>::length("double"));
    ASSERT_EQ(std::strcmp(double_positive_infinity_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::char_traits<char>::length(double_positive_infinity_value.get_string().c_str()), std::char_traits<char>::length("inf"));
    ASSERT_EQ(std::strcmp(double_positive_infinity_value.get_string().c_str(), "inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_negative_infinity)
{
    double double_negative_infinity = -1 * std::numeric_limits<double>::infinity();
    yli::data::AnyValue double_negative_infinity_value = yli::data::AnyValue(double_negative_infinity);
    ASSERT_TRUE(std::holds_alternative<double>(double_negative_infinity_value.data));
    ASSERT_EQ(std::get<double>(double_negative_infinity_value.data), double_negative_infinity);
    ASSERT_EQ(std::char_traits<char>::length(double_negative_infinity_value.get_datatype().c_str()), std::char_traits<char>::length("double"));
    ASSERT_EQ(std::strcmp(double_negative_infinity_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::char_traits<char>::length(double_negative_infinity_value.get_string().c_str()), std::char_traits<char>::length("-inf"));
    ASSERT_EQ(std::strcmp(double_negative_infinity_value.get_string().c_str(), "-inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_nan)
{
    double double_nan = NAN;
    yli::data::AnyValue double_nan_value = yli::data::AnyValue(double_nan);
    ASSERT_TRUE(std::holds_alternative<double>(double_nan_value.data));
    ASSERT_TRUE(std::isnan(std::get<double>(double_nan_value.data)));
    ASSERT_EQ(std::char_traits<char>::length(double_nan_value.get_datatype().c_str()), std::char_traits<char>::length("double"));
    ASSERT_EQ(std::strcmp(double_nan_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::char_traits<char>::length(double_nan_value.get_string().c_str()), std::char_traits<char>::length("nan"));
    ASSERT_EQ(std::strcmp(double_nan_value.get_string().c_str(), "nan"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_zero)
{
    int32_t int32_t_zero = 0;
    yli::data::AnyValue int32_t_zero_value = yli::data::AnyValue(int32_t_zero);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_zero_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_zero_value.data), 0);
    ASSERT_EQ(std::char_traits<char>::length(int32_t_zero_value.get_datatype().c_str()), std::char_traits<char>::length("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::char_traits<char>::length(int32_t_zero_value.get_string().c_str()), std::char_traits<char>::length("0"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_string().c_str(), "0"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_plus_1)
{
    int32_t int32_t_plus_1 = 1;
    yli::data::AnyValue int32_t_plus_1_value = yli::data::AnyValue(int32_t_plus_1);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_plus_1_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_plus_1_value.data), 1);
    ASSERT_EQ(std::char_traits<char>::length(int32_t_plus_1_value.get_datatype().c_str()), std::char_traits<char>::length("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::char_traits<char>::length(int32_t_plus_1_value.get_string().c_str()), std::char_traits<char>::length("1"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_string().c_str(), "1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_minus_1)
{
    int32_t int32_t_minus_1 = -1;
    yli::data::AnyValue int32_t_minus_1_value = yli::data::AnyValue(int32_t_minus_1);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_minus_1_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_minus_1_value.data), -1);
    ASSERT_EQ(std::char_traits<char>::length(int32_t_minus_1_value.get_datatype().c_str()), std::char_traits<char>::length("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::char_traits<char>::length(int32_t_minus_1_value.get_string().c_str()), std::char_traits<char>::length("-1"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_string().c_str(), "-1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_max)
{
    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::data::AnyValue int32_t_max_value = yli::data::AnyValue(int32_t_max);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_max_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), 2147483647);
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), std::numeric_limits<int32_t>::max());
#ifdef __linux__
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), std::numeric_limits<int>::max());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), std::numeric_limits<int>::max());
    ASSERT_EQ(std::get<int32_t>(int32_t_max_value.data), std::numeric_limits<long>::max());
#endif
    ASSERT_EQ(std::char_traits<char>::length(int32_t_max_value.get_datatype().c_str()), std::char_traits<char>::length("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::char_traits<char>::length(int32_t_max_value.get_string().c_str()), std::char_traits<char>::length("2147483647"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_string().c_str(), "2147483647"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_min)
{
    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::data::AnyValue int32_t_min_value = yli::data::AnyValue(int32_t_min);
    ASSERT_TRUE(std::holds_alternative<int32_t>(int32_t_min_value.data));
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), -2147483648);
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), std::numeric_limits<int32_t>::min());
#ifdef __linux__
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), std::numeric_limits<int>::min());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), std::numeric_limits<int>::min());
    ASSERT_EQ(std::get<int32_t>(int32_t_min_value.data), std::numeric_limits<long>::min());
#endif
    ASSERT_EQ(std::char_traits<char>::length(int32_t_min_value.get_datatype().c_str()), std::char_traits<char>::length("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::char_traits<char>::length(int32_t_min_value.get_string().c_str()), std::char_traits<char>::length("-2147483648"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_string().c_str(), "-2147483648"), 0);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_zero)
{
    uint32_t uint32_t_zero = 0;
    yli::data::AnyValue uint32_t_zero_value = yli::data::AnyValue(uint32_t_zero);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(uint32_t_zero_value.data));
    ASSERT_EQ(std::get<uint32_t>(uint32_t_zero_value.data), 0);
    ASSERT_EQ(std::char_traits<char>::length(uint32_t_zero_value.get_datatype().c_str()), std::char_traits<char>::length("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::char_traits<char>::length(uint32_t_zero_value.get_string().c_str()), std::char_traits<char>::length("0"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_string().c_str(), "0"), 0);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_plus_1)
{
    uint32_t uint32_t_plus_1 = 1;
    yli::data::AnyValue uint32_t_plus_1_value = yli::data::AnyValue(uint32_t_plus_1);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(uint32_t_plus_1_value.data));
    ASSERT_EQ(std::get<uint32_t>(uint32_t_plus_1_value.data), 1);
    ASSERT_EQ(std::char_traits<char>::length(uint32_t_plus_1_value.get_datatype().c_str()), std::char_traits<char>::length("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::char_traits<char>::length(uint32_t_plus_1_value.get_string().c_str()), std::char_traits<char>::length("1"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_string().c_str(), "1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_max)
{
    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::data::AnyValue uint32_t_max_value = yli::data::AnyValue(uint32_t_max);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(uint32_t_max_value.data));
    ASSERT_EQ(std::get<uint32_t>(uint32_t_max_value.data), std::numeric_limits<uint32_t>::max());
#ifdef __linux__
    ASSERT_EQ(std::get<uint32_t>(uint32_t_max_value.data), std::numeric_limits<unsigned int>::max());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(std::get<uint32_t>(uint32_t_max_value.data), std::numeric_limits<unsigned int>::max());
    ASSERT_EQ(std::get<uint32_t>(uint32_t_max_value.data), std::numeric_limits<unsigned long>::max());
#endif
    ASSERT_EQ(std::char_traits<char>::length(uint32_t_max_value.get_datatype().c_str()), std::char_traits<char>::length("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::char_traits<char>::length(uint32_t_max_value.get_string().c_str()), std::char_traits<char>::length("4294967295"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_string().c_str(), "4294967295"), 0);
}

TEST(any_value_must_be_initialized_appropriately, universe_as_entity)
{
    mock::MockApplication application;
    yli::ontology::Entity* const universe_entity = &application.get_universe();
    yli::data::AnyValue entity_any_value = yli::data::AnyValue(*universe_entity);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Entity>>(entity_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Entity>>(entity_any_value.data).get(), *universe_entity);
    ASSERT_EQ(std::strcmp(entity_any_value.get_datatype().c_str(), "yli::ontology::Entity&"), 0);
    ASSERT_EQ(entity_any_value.get_entity_ref(), *universe_entity);
}

TEST(any_value_must_be_initialized_appropriately, object_as_movable)
{
    mock::MockApplication application;
    yli::ontology::ObjectStruct object_struct(nullptr);
    yli::ontology::Movable* const object_movable = application.get_entity_factory().create_object(
            object_struct);

    yli::data::AnyValue movable_any_value = yli::data::AnyValue(*object_movable);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Movable>>(movable_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Movable>>(movable_any_value.data).get(), *object_movable);
    ASSERT_EQ(std::strcmp(movable_any_value.get_datatype().c_str(), "yli::ontology::Movable&"), 0);
    ASSERT_EQ(movable_any_value.get_entity_ref(), *object_movable);
    ASSERT_EQ(movable_any_value.get_const_entity_ref(), *object_movable);
}

TEST(any_value_must_be_initialized_appropriately, object_as_const_movable)
{
    mock::MockApplication application;
    yli::ontology::ObjectStruct object_struct(nullptr);
    const yli::ontology::Movable* const const_object_movable = application.get_entity_factory().create_object(
            object_struct);

    yli::data::AnyValue const_movable_any_value = yli::data::AnyValue(*const_object_movable);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<const yli::ontology::Movable>>(const_movable_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<const yli::ontology::Movable>>(const_movable_any_value.data).get(), *const_object_movable);
    ASSERT_EQ(std::strcmp(const_movable_any_value.get_datatype().c_str(), "const yli::ontology::Movable&"), 0);
    ASSERT_EQ(const_movable_any_value.get_const_entity_ref(), *const_object_movable);
}

TEST(any_value_must_be_initialized_appropriately, universe)
{
    mock::MockApplication application;
    yli::ontology::Universe* const universe = &application.get_universe();

    yli::data::AnyValue universe_any_value = yli::data::AnyValue(*universe);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Universe>>(universe_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Universe>>(universe_any_value.data).get(), *universe);
    ASSERT_EQ(std::strcmp(universe_any_value.get_datatype().c_str(), "yli::ontology::Universe&"), 0);
    ASSERT_EQ(universe_any_value.get_entity_ref(), *universe);
    ASSERT_EQ(universe_any_value.get_const_entity_ref(), *universe);
}

TEST(any_value_must_be_initialized_appropriately, ecosystem)
{
    mock::MockApplication application;

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::data::AnyValue ecosystem_any_value = yli::data::AnyValue(*ecosystem);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Ecosystem>>(ecosystem_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Ecosystem>>(ecosystem_any_value.data).get(), *ecosystem);
    ASSERT_EQ(std::strcmp(ecosystem_any_value.get_datatype().c_str(), "yli::ontology::Ecosystem&"), 0);
    ASSERT_EQ(ecosystem_any_value.get_entity_ref(), *ecosystem);
    ASSERT_EQ(ecosystem_any_value.get_const_entity_ref(), *ecosystem);
}

TEST(any_value_must_be_initialized_appropriately, scene)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);

    yli::data::AnyValue scene_any_value = yli::data::AnyValue(*scene);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Scene>>(scene_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Scene>>(scene_any_value.data).get(), *scene);
    ASSERT_EQ(std::strcmp(scene_any_value.get_datatype().c_str(), "yli::ontology::Scene&"), 0);
    ASSERT_EQ(scene_any_value.get_entity_ref(), *scene);
    ASSERT_EQ(scene_any_value.get_const_entity_ref(), *scene);
}

TEST(any_value_must_be_initialized_appropriately, pipeline)
{
    mock::MockApplication application;
    yli::ontology::PipelineStruct pipeline_struct;
    yli::ontology::Pipeline* const pipeline = application.get_entity_factory().create_pipeline(
            pipeline_struct);

    yli::data::AnyValue pipeline_any_value = yli::data::AnyValue(*pipeline);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Pipeline>>(pipeline_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Pipeline>>(pipeline_any_value.data).get(), *pipeline);
    ASSERT_EQ(std::strcmp(pipeline_any_value.get_datatype().c_str(), "yli::ontology::Pipeline&"), 0);
    ASSERT_EQ(pipeline_any_value.get_entity_ref(), *pipeline);
    ASSERT_EQ(pipeline_any_value.get_const_entity_ref(), *pipeline);
}

TEST(any_value_must_be_initialized_appropriately, material)
{
    mock::MockApplication application;
    yli::ontology::MaterialStruct material_struct;
    yli::ontology::Material* const material = application.get_entity_factory().create_material(
            material_struct);

    yli::data::AnyValue material_any_value = yli::data::AnyValue(*material);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Material>>(material_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Material>>(material_any_value.data).get(), *material);
    ASSERT_EQ(std::strcmp(material_any_value.get_datatype().c_str(), "yli::ontology::Material&"), 0);
    ASSERT_EQ(material_any_value.get_entity_ref(), *material);
    ASSERT_EQ(material_any_value.get_const_entity_ref(), *material);
}

TEST(any_value_must_be_initialized_appropriately, species)
{
    mock::MockApplication application;
    yli::ontology::ModelStruct model_struct;
    yli::ontology::Species* const species = application.get_entity_factory().create_species(
            model_struct);

    yli::data::AnyValue species_any_value = yli::data::AnyValue(*species);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Species>>(species_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Species>>(species_any_value.data).get(), *species);
    ASSERT_EQ(std::strcmp(species_any_value.get_datatype().c_str(), "yli::ontology::Species&"), 0);
    ASSERT_EQ(species_any_value.get_entity_ref(), *species);
    ASSERT_EQ(species_any_value.get_const_entity_ref(), *species);
}

TEST(any_value_must_be_initialized_appropriately, object)
{
    mock::MockApplication application;
    yli::ontology::ObjectStruct object_struct(nullptr);
    yli::ontology::Object* const object = application.get_entity_factory().create_object(
            object_struct);

    yli::data::AnyValue object_any_value = yli::data::AnyValue(*object);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Object>>(object_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Object>>(object_any_value.data).get(), *object);
    ASSERT_EQ(std::strcmp(object_any_value.get_datatype().c_str(), "yli::ontology::Object&"), 0);
    ASSERT_EQ(object_any_value.get_entity_ref(), *object);
    ASSERT_EQ(object_any_value.get_const_entity_ref(), *object);
}

TEST(any_value_must_be_initialized_appropriately, symbiosis)
{
    mock::MockApplication application;
    yli::ontology::ModelStruct model_struct;
    yli::ontology::Symbiosis* const symbiosis = application.get_entity_factory().create_symbiosis(
            model_struct);

    yli::data::AnyValue symbiosis_any_value = yli::data::AnyValue(*symbiosis);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Symbiosis>>(symbiosis_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Symbiosis>>(symbiosis_any_value.data).get(), *symbiosis);
    ASSERT_EQ(std::strcmp(symbiosis_any_value.get_datatype().c_str(), "yli::ontology::Symbiosis&"), 0);
    ASSERT_EQ(symbiosis_any_value.get_entity_ref(), *symbiosis);
    ASSERT_EQ(symbiosis_any_value.get_const_entity_ref(), *symbiosis);
}

TEST(any_value_must_be_initialized_appropriately, holobiont)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    yli::ontology::Symbiosis* const symbiosis = application.get_entity_factory().create_symbiosis(
            model_struct);

    yli::ontology::HolobiontStruct holobiont_struct(*scene, *symbiosis);
    yli::ontology::Holobiont* const holobiont = application.get_entity_factory().create_holobiont(
            holobiont_struct);

    yli::data::AnyValue holobiont_any_value = yli::data::AnyValue(*holobiont);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Holobiont>>(holobiont_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Holobiont>>(holobiont_any_value.data).get(), *holobiont);
    ASSERT_EQ(std::strcmp(holobiont_any_value.get_datatype().c_str(), "yli::ontology::Holobiont&"), 0);
    ASSERT_EQ(holobiont_any_value.get_entity_ref(), *holobiont);
    ASSERT_EQ(holobiont_any_value.get_const_entity_ref(), *holobiont);
}

TEST(any_value_must_be_initialized_appropriately, font_2d)
{
    mock::MockApplication application;
    yli::ontology::FontStruct font_struct;
    yli::ontology::Font2D* const font_2d = application.get_entity_factory().create_font_2d(
            font_struct);

    yli::data::AnyValue font_2d_any_value = yli::data::AnyValue(*font_2d);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Font2D>>(font_2d_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Font2D>>(font_2d_any_value.data).get(), *font_2d);
    ASSERT_EQ(std::strcmp(font_2d_any_value.get_datatype().c_str(), "yli::ontology::Font2D&"), 0);
    ASSERT_EQ(font_2d_any_value.get_entity_ref(), *font_2d);
    ASSERT_EQ(font_2d_any_value.get_const_entity_ref(), *font_2d);
}

TEST(any_value_must_be_initialized_appropriately, text_2d)
{
    mock::MockApplication application;
    yli::ontology::TextStruct text_struct;
    yli::ontology::Text2D* const text_2d = application.get_entity_factory().create_text_2d(
            text_struct);

    yli::data::AnyValue text_2d_any_value = yli::data::AnyValue(*text_2d);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Text2D>>(text_2d_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Text2D>>(text_2d_any_value.data).get(), *text_2d);
    ASSERT_EQ(std::strcmp(text_2d_any_value.get_datatype().c_str(), "yli::ontology::Text2D&"), 0);
    ASSERT_EQ(text_2d_any_value.get_entity_ref(), *text_2d);
    ASSERT_EQ(text_2d_any_value.get_const_entity_ref(), *text_2d);
}

TEST(any_value_must_be_initialized_appropriately, vector_font)
{
    mock::MockApplication application;
    yli::ontology::VectorFontStruct vector_font_struct;
    yli::ontology::VectorFont* const vector_font = application.get_entity_factory().create_vector_font(
            vector_font_struct);

    yli::data::AnyValue vector_font_any_value = yli::data::AnyValue(*vector_font);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::VectorFont>>(vector_font_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::VectorFont>>(vector_font_any_value.data).get(), *vector_font);
    ASSERT_EQ(std::strcmp(vector_font_any_value.get_datatype().c_str(), "yli::ontology::VectorFont&"), 0);
    ASSERT_EQ(vector_font_any_value.get_entity_ref(), *vector_font);
    ASSERT_EQ(vector_font_any_value.get_const_entity_ref(), *vector_font);
}

TEST(any_value_must_be_initialized_appropriately, text_3d)
{
    mock::MockApplication application;
    yli::ontology::Text3DStruct text_3d_struct;
    yli::ontology::Text3D* const text_3d = application.get_entity_factory().create_text_3d(
            text_3d_struct);

    yli::data::AnyValue text_3d_any_value = yli::data::AnyValue(*text_3d);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Text3D>>(text_3d_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Text3D>>(text_3d_any_value.data).get(), *text_3d);
    ASSERT_EQ(std::strcmp(text_3d_any_value.get_datatype().c_str(), "yli::ontology::Text3D&"), 0);
    ASSERT_EQ(text_3d_any_value.get_entity_ref(), *text_3d);
    ASSERT_EQ(text_3d_any_value.get_const_entity_ref(), *text_3d);
}

TEST(any_value_must_be_initialized_appropriately, console)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_entity_factory().create_console(
            console_struct);

    yli::data::AnyValue console_any_value = yli::data::AnyValue(*console);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Console>>(console_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Console>>(console_any_value.data).get(), *console);
    ASSERT_EQ(std::strcmp(console_any_value.get_datatype().c_str(), "yli::ontology::Console&"), 0);
    ASSERT_EQ(console_any_value.get_entity_ref(), *console);
    ASSERT_EQ(console_any_value.get_const_entity_ref(), *console);
}

TEST(any_value_must_be_initialized_appropriately, compute_task)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_entity_factory().create_console(
            console_struct);

    yli::data::AnyValue console_any_value = yli::data::AnyValue(*console);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::ontology::Console>>(console_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::ontology::Console>>(console_any_value.data).get(), *console);
    ASSERT_EQ(std::strcmp(console_any_value.get_datatype().c_str(), "yli::ontology::Console&"), 0);
    ASSERT_EQ(console_any_value.get_entity_ref(), *console);
    ASSERT_EQ(console_any_value.get_const_entity_ref(), *console);
}

TEST(any_value_must_be_initialized_appropriately, spherical_coordinates_struct)
{
    yli::data::SphericalCoordinatesStruct spherical_coordinates_struct = yli::data::SphericalCoordinatesStruct(1.0f, 2.0f, 3.0f);
    yli::data::AnyValue any_value(spherical_coordinates_struct);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<yli::data::SphericalCoordinatesStruct>>(any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<yli::data::SphericalCoordinatesStruct>>(any_value.data).get(), spherical_coordinates_struct);
    ASSERT_EQ(std::strcmp(any_value.get_datatype().c_str(), "yli::data::SphericalCoordinatesStruct&"), 0);
    // TODO: add assertions for `AnyValue::get_string` for `yli::data::SphericalCoordinatesStruct`!
}

TEST(any_value_must_be_initialized_appropriately, const_spherical_coordinates_struct)
{
    const yli::data::SphericalCoordinatesStruct spherical_coordinates_struct = yli::data::SphericalCoordinatesStruct(1.0f, 2.0f, 3.0f);
    yli::data::AnyValue any_value(spherical_coordinates_struct);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<const yli::data::SphericalCoordinatesStruct>>(any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<const yli::data::SphericalCoordinatesStruct>>(any_value.data).get(), spherical_coordinates_struct);
    ASSERT_EQ(std::strcmp(any_value.get_datatype().c_str(), "const yli::data::SphericalCoordinatesStruct&"), 0);
    // TODO: add assertions for `AnyValue::get_string` for `yli::data::SphericalCoordinatesStruct`!
}

TEST(any_value_must_be_initialized_appropriately, std_string)
{
    std::string foo_string = "foo";
    yli::data::AnyValue std_string_ref_any_value = yli::data::AnyValue(foo_string);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<std::string>>(std_string_ref_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<std::string>>(std_string_ref_any_value.data).get(), foo_string);
    ASSERT_EQ(std::strcmp(std_string_ref_any_value.get_datatype().c_str(), "std::string&"), 0);
    ASSERT_EQ(std::strcmp(std_string_ref_any_value.get_string().c_str(), "foo"), 0);
}

TEST(any_value_must_be_initialized_appropriately, const_std_string)
{
    const std::string foo_string = "foo";
    yli::data::AnyValue const_std_string_ref_any_value = yli::data::AnyValue(foo_string);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<const std::string>>(const_std_string_ref_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<const std::string>>(const_std_string_ref_any_value.data).get(), foo_string);
    ASSERT_EQ(std::strcmp(const_std_string_ref_any_value.get_datatype().c_str(), "const std::string&"), 0);
    ASSERT_EQ(std::strcmp(const_std_string_ref_any_value.get_string().c_str(), "foo"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_int8_t)
{
    std::vector<int8_t> std_vector_int8_t;
    yli::data::AnyValue std_vector_int8_t_any_value = yli::data::AnyValue(std_vector_int8_t);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<std::vector<int8_t>>>(std_vector_int8_t_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<std::vector<int8_t>>>(std_vector_int8_t_any_value.data).get(), std_vector_int8_t);
    ASSERT_EQ(std::strcmp(std_vector_int8_t_any_value.get_datatype().c_str(), "std::vector<int8_t>&"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_uint8_t)
{
    std::vector<uint8_t> std_vector_uint8_t;
    yli::data::AnyValue std_vector_uint8_t_any_value = yli::data::AnyValue(std_vector_uint8_t);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<std::vector<uint8_t>>>(std_vector_uint8_t_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<std::vector<uint8_t>>>(std_vector_uint8_t_any_value.data).get(), std_vector_uint8_t);
    ASSERT_EQ(std::strcmp(std_vector_uint8_t_any_value.get_datatype().c_str(), "std::vector<uint8_t>&"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_int16_t)
{
    std::vector<int16_t> std_vector_int16_t;
    yli::data::AnyValue std_vector_int16_t_any_value = yli::data::AnyValue(std_vector_int16_t);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<std::vector<int16_t>>>(std_vector_int16_t_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<std::vector<int16_t>>>(std_vector_int16_t_any_value.data).get(), std_vector_int16_t);
    ASSERT_EQ(std::strcmp(std_vector_int16_t_any_value.get_datatype().c_str(), "std::vector<int16_t>&"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_uint16_t)
{
    std::vector<uint16_t> std_vector_uint16_t;
    yli::data::AnyValue std_vector_uint16_t_any_value = yli::data::AnyValue(std_vector_uint16_t);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<std::vector<uint16_t>>>(std_vector_uint16_t_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<std::vector<uint16_t>>>(std_vector_uint16_t_any_value.data).get(), std_vector_uint16_t);
    ASSERT_EQ(std::strcmp(std_vector_uint16_t_any_value.get_datatype().c_str(), "std::vector<uint16_t>&"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_int32_t)
{
    std::vector<int32_t> std_vector_int32_t;
    yli::data::AnyValue std_vector_int32_t_any_value = yli::data::AnyValue(std_vector_int32_t);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<std::vector<int32_t>>>(std_vector_int32_t_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<std::vector<int32_t>>>(std_vector_int32_t_any_value.data).get(), std_vector_int32_t);
    ASSERT_EQ(std::strcmp(std_vector_int32_t_any_value.get_datatype().c_str(), "std::vector<int32_t>&"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_uint32_t)
{
    std::vector<uint32_t> std_vector_uint32_t;
    yli::data::AnyValue std_vector_uint32_t_any_value = yli::data::AnyValue(std_vector_uint32_t);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<std::vector<uint32_t>>>(std_vector_uint32_t_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<std::vector<uint32_t>>>(std_vector_uint32_t_any_value.data).get(), std_vector_uint32_t);
    ASSERT_EQ(std::strcmp(std_vector_uint32_t_any_value.get_datatype().c_str(), "std::vector<uint32_t>&"), 0);
}

TEST(any_value_must_be_initialized_appropriately, std_vector_float)
{
    std::vector<float> std_vector_float;
    yli::data::AnyValue std_vector_float_any_value = yli::data::AnyValue(std_vector_float);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<std::vector<float>>>(std_vector_float_any_value.data));
    ASSERT_EQ(std::get<std::reference_wrapper<std::vector<float>>>(std_vector_float_any_value.data).get(), std_vector_float);
    ASSERT_EQ(std::strcmp(std_vector_float_any_value.get_datatype().c_str(), "std::vector<float>&"), 0);
}

TEST(any_value_must_be_initialized_appropriately, glm_vec3)
{
    glm::vec3 glm_vec3(1.0f, 2.0f, 3.0f);
    yli::data::AnyValue glm_vec3_any_value = yli::data::AnyValue(glm_vec3);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<glm::vec3>>(glm_vec3_any_value.data));
    ASSERT_EQ(&std::get<std::reference_wrapper<glm::vec3>>(glm_vec3_any_value.data).get(), &glm_vec3);
    ASSERT_EQ(std::strcmp(glm_vec3_any_value.get_datatype().c_str(), "glm::vec3&"), 0);
    // TODO: add assertions for `AnyValue::get_string` for `glm::vec3*`!
}

TEST(any_value_must_be_initialized_appropriately, const_glm_vec3)
{
    const glm::vec3 const_glm_vec3(1.0f, 2.0f, 3.0f);
    yli::data::AnyValue const_glm_vec3_any_value = yli::data::AnyValue(const_glm_vec3);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<const glm::vec3>>(const_glm_vec3_any_value.data));
    ASSERT_EQ(&std::get<std::reference_wrapper<const glm::vec3>>(const_glm_vec3_any_value.data).get(), &const_glm_vec3);
    ASSERT_EQ(std::strcmp(const_glm_vec3_any_value.get_datatype().c_str(), "const glm::vec3&"), 0);
    // TODO: add assertions for `AnyValue::get_string` for `glm::vec3*`!
}

TEST(any_value_must_be_initialized_appropriately, glm_vec4)
{
    glm::vec4 glm_vec4(1.0f, 2.0f, 3.0f, 4.0f);
    yli::data::AnyValue glm_vec4_any_value = yli::data::AnyValue(glm_vec4);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<glm::vec4>>(glm_vec4_any_value.data));
    ASSERT_EQ(&std::get<std::reference_wrapper<glm::vec4>>(glm_vec4_any_value.data).get(), &glm_vec4);
    ASSERT_EQ(std::strcmp(glm_vec4_any_value.get_datatype().c_str(), "glm::vec4&"), 0);
    // TODO: add assertions for `AnyValue::get_string` for `glm::vec4*`!
}

TEST(any_value_must_be_initialized_appropriately, const_glm_vec4)
{
    const glm::vec4 const_glm_vec4(1.0f, 2.0f, 3.0f, 4.0f);
    yli::data::AnyValue const_glm_vec4_any_value = yli::data::AnyValue(const_glm_vec4);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<const glm::vec4>>(const_glm_vec4_any_value.data));
    ASSERT_EQ(&std::get<std::reference_wrapper<const glm::vec4>>(const_glm_vec4_any_value.data).get(), &const_glm_vec4);
    ASSERT_EQ(std::strcmp(const_glm_vec4_any_value.get_datatype().c_str(), "const glm::vec4&"), 0);
    // TODO: add assertions for `AnyValue::get_string` for `glm::vec4*`!
}

TEST(set_new_value_must_function_properly, originally_bool_true_new_value_bool_true)
{
    bool bool_true = true;
    yli::data::AnyValue any_value = yli::data::AnyValue(bool_true);
    ASSERT_TRUE(any_value.set_new_value("true"));
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_TRUE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_true_new_value_bool_false)
{
    bool bool_true = true;
    yli::data::AnyValue any_value = yli::data::AnyValue(bool_true);
    ASSERT_TRUE(any_value.set_new_value("false"));
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_FALSE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_true_new_value_foo)
{
    bool bool_true = true;
    yli::data::AnyValue any_value = yli::data::AnyValue(bool_true);
    ASSERT_FALSE(any_value.set_new_value("foo")); // `"foo"` is invalid value and should not change the current value.
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_TRUE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_false_new_value_bool_true)
{
    bool bool_false = false;
    yli::data::AnyValue any_value = yli::data::AnyValue(bool_false);
    ASSERT_TRUE(any_value.set_new_value("true"));
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_TRUE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_false_new_value_bool_false)
{
    bool bool_false = false;
    yli::data::AnyValue any_value = yli::data::AnyValue(bool_false);
    ASSERT_TRUE(any_value.set_new_value("false"));
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_FALSE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_bool_false_new_value_foo)
{
    bool bool_false = false;
    yli::data::AnyValue any_value = yli::data::AnyValue(bool_false);
    ASSERT_FALSE(any_value.set_new_value("foo")); // `"foo"` is invalid value and should not change the current value.
    ASSERT_TRUE(std::holds_alternative<bool>(any_value.data));
    ASSERT_FALSE(std::get<bool>(any_value.data));
}

TEST(set_new_value_must_function_properly, originally_char_lowercase_a_new_value_a)
{
    char char_lowercase_a = 'a';
    yli::data::AnyValue any_value = yli::data::AnyValue(char_lowercase_a);
    ASSERT_TRUE(any_value.set_new_value("a"));
    ASSERT_TRUE(std::holds_alternative<char>(any_value.data));
    ASSERT_EQ(std::get<char>(any_value.data), 'a');
}

TEST(set_new_value_must_function_properly, originally_char_lowercase_a_new_value_b)
{
    char char_lowercase_a = 'a';
    yli::data::AnyValue any_value = yli::data::AnyValue(char_lowercase_a);
    ASSERT_TRUE(any_value.set_new_value("b"));
    ASSERT_TRUE(std::holds_alternative<char>(any_value.data));
    ASSERT_EQ(std::get<char>(any_value.data), 'b');
}

TEST(set_new_value_must_function_properly, originally_char_lowercase_a_new_value_bb)
{
    char char_lowercase_a = 'a';
    yli::data::AnyValue any_value = yli::data::AnyValue(char_lowercase_a);
    ASSERT_FALSE(any_value.set_new_value("bb")); // `"bb"` is invalid value and should not change the current value.
    ASSERT_TRUE(std::holds_alternative<char>(any_value.data));
    ASSERT_EQ(std::get<char>(any_value.data), 'a');
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_0)
{
    float float_zero = 0.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 0.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_0_dot_0)
{
    float float_zero = 0.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("0.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 0.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_plus_1)
{
    float float_zero = 0.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("1"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_plus_1_dot_0)
{
    float float_zero = 0.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("1.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_minus_1_dot_0)
{
    float float_zero = 0.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("-1.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), -1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_plus_1234)
{
    float float_zero = 0.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("1234"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1234.0f);
}

TEST(set_new_value_must_function_properly, originally_float_0_new_value_float_plus_1234_dot_0)
{
    float float_zero = 0.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_zero);
    ASSERT_TRUE(any_value.set_new_value("1234.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1234.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_0)
{
    float float_plus_1 = 1.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 0.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_0_dot_0)
{
    float float_plus_1 = 1.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("0.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 0.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_plus_1)
{
    float float_plus_1 = 1.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("1"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_plus_1_dot_0)
{
    float float_plus_1 = 1.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("1.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_minus_1_dot_0)
{
    float float_plus_1 = 1.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("-1.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), -1.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_plus_1234)
{
    float float_plus_1 = 1.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("1234"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1234.0f);
}

TEST(set_new_value_must_function_properly, originally_float_plus_1_new_value_float_plus_1234_dot_0)
{
    float float_plus_1 = 1.0f;
    yli::data::AnyValue any_value = yli::data::AnyValue(float_plus_1);
    ASSERT_TRUE(any_value.set_new_value("1234.0"));
    ASSERT_TRUE(std::holds_alternative<float>(any_value.data));
    ASSERT_EQ(std::get<float>(any_value.data), 1234.0f);
}
