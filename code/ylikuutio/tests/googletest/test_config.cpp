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
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <limits>   // std::numeric_limits
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.

TEST(setting_master_must_be_initialized_appropriately, headless_universe)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();
    ASSERT_NE(setting_master, nullptr);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_bool_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    bool bool_true = true;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(bool_true));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_bool_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    bool bool_true = true;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(bool_true));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(setting_value->data));
    ASSERT_TRUE(std::get<bool>(setting_value->data));
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_bool_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    bool bool_false = false;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(bool_false));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_bool_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    bool bool_false = false;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(bool_false));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(setting_value->data));
    ASSERT_FALSE(std::get<bool>(setting_value->data));
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_char_lowercase_a_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    char char_lowercase_a = 'a';
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(char_lowercase_a));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_char_lowercase_a_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    char char_lowercase_a = 'a';
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(char_lowercase_a));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(setting_value->data));
    ASSERT_EQ(std::get<char>(setting_value->data), 'a');
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_char_lowercase_b_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    char char_lowercase_b = 'b';
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(char_lowercase_b));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_char_lowercase_b_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    char char_lowercase_b = 'b';
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(char_lowercase_b));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(setting_value->data));
    ASSERT_EQ(std::get<char>(setting_value->data), 'b');
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_char_space_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    char char_space = ' ';
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(char_space));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_char_space_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    char char_space = ' ';
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(char_space));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(setting_value->data));
    ASSERT_EQ(std::get<char>(setting_value->data), ' ');
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_char_newline_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    char char_newline = '\n';
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(char_newline));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_char_newline_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    char char_newline = '\n';
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(char_newline));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(setting_value->data));
    ASSERT_EQ(std::get<char>(setting_value->data), '\n');
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_float_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    float float_zero = 0.0f;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(float_zero));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_float_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    float float_zero = 0.0f;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(float_zero));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(setting_value->data));
    ASSERT_EQ(std::get<float>(setting_value->data), 0.0f);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_float_positive_infinity_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    float float_positive_infinity = std::numeric_limits<float>::infinity();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(float_positive_infinity));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(setting_value->data));
    ASSERT_EQ(std::get<float>(setting_value->data), std::numeric_limits<float>::infinity());
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_float_negative_infinity_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    float float_negative_infinity = -1.0f * std::numeric_limits<float>::infinity();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(float_negative_infinity));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(setting_value->data));
    ASSERT_EQ(std::get<float>(setting_value->data), -1.0f * std::numeric_limits<float>::infinity());
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_float_nan_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    float float_nan = NAN;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(float_nan));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(setting_value->data));
    ASSERT_TRUE(std::isnan(std::get<float>(setting_value->data)));
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_double_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    double double_zero = 0.0d;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(double_zero));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_double_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    double double_zero = 0.0d;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(double_zero));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(setting_value->data));
    ASSERT_EQ(std::get<double>(setting_value->data), 0.0d);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_double_positive_infinity_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    double double_positive_infinity = std::numeric_limits<double>::infinity();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(double_positive_infinity));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(setting_value->data));
    ASSERT_EQ(std::get<double>(setting_value->data), std::numeric_limits<double>::infinity());
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_double_negative_infinity_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    double double_negative_infinity = -1.0d * std::numeric_limits<double>::infinity();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(double_negative_infinity));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(setting_value->data));
    ASSERT_EQ(std::get<double>(setting_value->data), -1.0d * std::numeric_limits<double>::infinity());
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_double_nan_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    double double_nan = NAN;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(double_nan));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(setting_value->data));
    ASSERT_TRUE(std::isnan(std::get<double>(setting_value->data)));
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_int32_t_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_zero = 0;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_zero));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_int32_t_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_zero = 0;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_zero));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(setting_value->data));
    ASSERT_EQ(std::get<int32_t>(setting_value->data), 0);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_int32_t_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_plus_1 = 1;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_plus_1));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_int32_t_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_plus_1 = 1;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_plus_1));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(setting_value->data));
    ASSERT_EQ(std::get<int32_t>(setting_value->data), 1);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_int32_t_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_minus_1 = -1;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_minus_1));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_int32_t_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_minus_1 = -1;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_minus_1));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(setting_value->data));
    ASSERT_EQ(std::get<int32_t>(setting_value->data), -1);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_int32_t_max_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_max));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_int32_t_max_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_max));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(setting_value->data));
    ASSERT_EQ(std::get<int32_t>(setting_value->data), std::numeric_limits<int32_t>::max());
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_int32_t_min_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_min));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_int32_t_min_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(int32_t_min));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(setting_value->data));
    ASSERT_EQ(std::get<int32_t>(setting_value->data), std::numeric_limits<int32_t>::min());
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_uint32_t_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    uint32_t uint32_t_zero = 0;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(uint32_t_zero));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_uint32_t_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    uint32_t uint32_t_zero = 0;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(uint32_t_zero));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(setting_value->data));
    ASSERT_EQ(std::get<uint32_t>(setting_value->data), 0);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_uint32_t_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    uint32_t uint32_t_plus_1 = 1;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(uint32_t_plus_1));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_uint32_t_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    uint32_t uint32_t_plus_1 = 1;
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(uint32_t_plus_1));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(setting_value->data));
    ASSERT_EQ(std::get<uint32_t>(setting_value->data), 1);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_unnamed_setting_uint32_t_max_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(uint32_t_max));
    setting_master->create_setting(setting_struct);
    ASSERT_FALSE(setting_master->is_setting("foo"));
    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_EQ(setting_master->get("foo"), nullptr);
}

TEST(setting_must_be_initialized_appropriately, headless_universe_named_setting_uint32_t_max_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::config::SettingMaster* const setting_master = universe->get_setting_master();

    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::config::SettingStruct setting_struct(std::make_shared<yli::common::AnyValue>(uint32_t_max));
    setting_struct.name = "foo";
    setting_master->create_setting(setting_struct);
    ASSERT_TRUE(setting_master->is_setting("foo"));
    ASSERT_NE(setting_master->get("foo"), nullptr);
    ASSERT_FALSE(setting_master->is_setting("bar"));
    ASSERT_EQ(setting_master->get("bar"), nullptr);

    yli::config::Setting* const setting = setting_master->get("foo");
    ASSERT_NE(setting, nullptr);
    std::shared_ptr<yli::common::AnyValue> setting_value = setting->get();
    ASSERT_NE(setting_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(setting_value->data));
    ASSERT_EQ(std::get<uint32_t>(setting_value->data), std::numeric_limits<uint32_t>::max());
}
