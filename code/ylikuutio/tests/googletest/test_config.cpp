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
#include <limits>   // std::numeric_limits
#include <memory>   // std::make_shared, std::shared_ptr

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
}
