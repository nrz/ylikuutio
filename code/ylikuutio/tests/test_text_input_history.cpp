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
#include "code/ylikuutio/console/console_state.hpp"
#include "code/ylikuutio/console/text_input.hpp"
#include "code/ylikuutio/console/text_input_history.hpp"
#include "code/ylikuutio/console/text_input_type.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <string>   // std::string
#include <utility>  // std::move

using yli::console::ConsoleState;

TEST(text_input_history_must_be_initialized_appropriately, text_input_history)
{
    yli::console::TextInputHistory text_input_history;
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 0);
    ASSERT_TRUE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    ASSERT_EQ(text_input_history.get(), nullptr);
}

TEST(moving_to_previous_input_must_fail_appropriately, empty_input_history)
{
    yli::console::TextInputHistory text_input_history;
    ASSERT_FALSE(text_input_history.move_to_previous());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 0);
    ASSERT_TRUE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    ASSERT_EQ(text_input_history.get(), nullptr);
}

TEST(moving_to_next_input_must_fail_appropriately, empty_input_history)
{
    yli::console::TextInputHistory text_input_history;
    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 0);
    ASSERT_TRUE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    ASSERT_EQ(text_input_history.get(), nullptr);
}

TEST(adding_an_input_must_work_appropriately, abc)
{
    yli::console::TextInputHistory text_input_history;

    yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
    text_input.add_characters("abc");

    text_input_history.add_to_history(std::move(text_input));
    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 1);
    ASSERT_FALSE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    ASSERT_EQ(text_input_history.at(0), text_input);

    ASSERT_TRUE(text_input_history.enter_history());
    ASSERT_EQ(text_input_history.get_history_index(), 0);
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().end());
    const yli::console::TextInput* const input_from_history = text_input_history.get();
    ASSERT_NE(input_from_history, nullptr);

    ASSERT_EQ(*text_input_history.get(), text_input);
}

TEST(adding_an_input_capacity_plus_1_times_must_work_appropriately, abc)
{
    yli::console::TextInputHistory text_input_history;

    const std::size_t capacity = text_input_history.data().capacity();

    for (std::size_t i = 0; i < capacity + 1; i++)
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters("abc");

        text_input_history.add_to_history(std::move(text_input));
    }

    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), capacity + 1);
    ASSERT_FALSE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    // TODO: add assertion for the content of `text_input_history`!

    ASSERT_TRUE(text_input_history.enter_history());
    ASSERT_EQ(text_input_history.get_history_index(), capacity);
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin() + capacity);
    const yli::console::TextInput* const input_from_history = text_input_history.get();
    ASSERT_NE(input_from_history, nullptr);

    ASSERT_EQ(*text_input_history.get(), yli::console::TextInput("abc", yli::console::TextInputType::NEW_INPUT));
}

TEST(emplacing_an_input_capacity_plus_1_times_must_work_appropriately, abc)
{
    yli::console::TextInputHistory text_input_history;

    const std::size_t capacity = text_input_history.data().capacity();

    for (std::size_t i = 0; i < capacity + 1; i++)
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters("abc");

        text_input_history.emplace_back(std::move(text_input));
    }

    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), capacity + 1);
    ASSERT_FALSE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    // TODO: add assertion for the content of `text_input_history`!

    ASSERT_TRUE(text_input_history.enter_history());
    ASSERT_EQ(text_input_history.get_history_index(), capacity);
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin() + capacity);
    const yli::console::TextInput* const input_from_history = text_input_history.get();
    ASSERT_NE(input_from_history, nullptr);

    ASSERT_EQ(*text_input_history.get(), yli::console::TextInput("abc", yli::console::TextInputType::NEW_INPUT));
}

TEST(pushing_an_input_capacity_plus_1_times_must_work_appropriately, abc)
{
    yli::console::TextInputHistory text_input_history;

    const std::size_t capacity = text_input_history.data().capacity();

    for (std::size_t i = 0; i < capacity + 1; i++)
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters("abc");

        text_input_history.push_back(std::move(text_input));
    }

    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), capacity + 1);
    ASSERT_FALSE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    // TODO: add assertion for the content of `text_input_history`!

    ASSERT_TRUE(text_input_history.enter_history());
    ASSERT_EQ(text_input_history.get_history_index(), capacity);
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin() + capacity);
    const yli::console::TextInput* const input_from_history = text_input_history.get();
    ASSERT_NE(input_from_history, nullptr);

    ASSERT_EQ(*text_input_history.get(), yli::console::TextInput("abc", yli::console::TextInputType::NEW_INPUT));
}

TEST(adding_an_input_capacity_plus_10_times_must_work_appropriately, abc)
{
    yli::console::TextInputHistory text_input_history;

    const std::size_t capacity = text_input_history.data().capacity();

    for (std::size_t i = 0; i < capacity + 10; i++)
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters("abc");

        text_input_history.add_to_history(std::move(text_input));
    }

    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), capacity + 10);
    ASSERT_FALSE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    // TODO: add assertion for the content of `text_input_history`!

    ASSERT_TRUE(text_input_history.enter_history());
    ASSERT_EQ(text_input_history.get_history_index(), capacity + 9);
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin() + capacity + 9);
    const yli::console::TextInput* const input_from_history = text_input_history.get();
    ASSERT_NE(input_from_history, nullptr);

    ASSERT_EQ(*text_input_history.get(), yli::console::TextInput("abc", yli::console::TextInputType::NEW_INPUT));
}

TEST(emplacing_an_input_capacity_plus_10_times_must_work_appropriately, abc)
{
    yli::console::TextInputHistory text_input_history;

    const std::size_t capacity = text_input_history.data().capacity();

    for (std::size_t i = 0; i < capacity + 10; i++)
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters("abc");

        text_input_history.emplace_back(std::move(text_input));
    }

    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), capacity + 10);
    ASSERT_FALSE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    // TODO: add assertion for the content of `text_input_history`!

    ASSERT_TRUE(text_input_history.enter_history());
    ASSERT_EQ(text_input_history.get_history_index(), capacity + 9);
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin() + capacity + 9);
    const yli::console::TextInput* const input_from_history = text_input_history.get();
    ASSERT_NE(input_from_history, nullptr);

    ASSERT_EQ(*text_input_history.get(), yli::console::TextInput("abc", yli::console::TextInputType::NEW_INPUT));
}

TEST(pushing_an_input_capacity_plus_10_times_must_work_appropriately, abc)
{
    yli::console::TextInputHistory text_input_history;

    const std::size_t capacity = text_input_history.data().capacity();

    for (std::size_t i = 0; i < capacity + 10; i++)
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters("abc");

        text_input_history.push_back(std::move(text_input));
    }

    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), capacity + 10);
    ASSERT_FALSE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().end());
    // TODO: add assertion for the content of `text_input_history`!

    ASSERT_TRUE(text_input_history.enter_history());
    ASSERT_EQ(text_input_history.get_history_index(), capacity + 9);
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin() + capacity + 9);
    const yli::console::TextInput* const input_from_history = text_input_history.get();
    ASSERT_NE(input_from_history, nullptr);

    ASSERT_EQ(*text_input_history.get(), yli::console::TextInput("abc", yli::console::TextInputType::NEW_INPUT));
}

TEST(emplacing_back_an_input_must_work_appropriately, abc)
{
    yli::console::TextInputHistory text_input_history;

    yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
    text_input.add_characters("abc");

    text_input_history.emplace_back(std::move(text_input));
    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 1);
    ASSERT_FALSE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(text_input_history.at(0), text_input);

    ASSERT_TRUE(text_input_history.enter_history());
    ASSERT_EQ(text_input_history.get_history_index(), 0);
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().end());
    const yli::console::TextInput* const input_from_history = text_input_history.get();
    ASSERT_NE(input_from_history, nullptr);

    ASSERT_EQ(*text_input_history.get(), text_input);
}

TEST(pushing_back_an_input_must_work_appropriately, abc)
{
    yli::console::TextInputHistory text_input_history;

    yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
    text_input.add_characters("abc");

    text_input_history.push_back(std::move(text_input));
    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 1);
    ASSERT_FALSE(text_input_history.empty());
    ASSERT_EQ(text_input_history.get_history_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(text_input_history.at(0), text_input);

    ASSERT_TRUE(text_input_history.enter_history());
    ASSERT_EQ(text_input_history.get_history_index(), 0);
    ASSERT_EQ(text_input_history.get_history_it(), text_input_history.data().begin());
    ASSERT_NE(text_input_history.get_history_it(), text_input_history.data().end());
    const yli::console::TextInput* const input_from_history = text_input_history.get();
    ASSERT_NE(input_from_history, nullptr);

    ASSERT_EQ(*text_input_history.get(), text_input);
}

TEST(text_input_history_begin_iterator_must_work_appropriately, text_input_history_begin_iterator)
{
    const std::string abc_char_container { "abc" };
    const std::string def_char_container { "def" };
    const std::string ghi_char_container { "ghi" };

    yli::console::TextInputHistory text_input_history;
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(abc_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(def_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(ghi_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }

    auto it = text_input_history.begin();
    ASSERT_EQ((*it).data(), abc_char_container);
    ++it;
    ASSERT_EQ((*it).data(), def_char_container);
    ++it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    ++it;
    ASSERT_EQ(it, text_input_history.end());
}

TEST(text_input_history_cbegin_const_iterator_must_work_appropriately, text_input_history_cbegin_const_iterator)
{
    const std::string abc_char_container { "abc" };
    const std::string def_char_container { "def" };
    const std::string ghi_char_container { "ghi" };

    yli::console::TextInputHistory text_input_history;
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(abc_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(def_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(ghi_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }

    auto it = text_input_history.cbegin();
    ASSERT_EQ((*it).data(), abc_char_container);
    ++it;
    ASSERT_EQ((*it).data(), def_char_container);
    ++it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    ++it;
    ASSERT_EQ(it, text_input_history.cend());
}

TEST(text_input_history_end_iterator_must_work_appropriately, text_input_history_end_iterator)
{
    const std::string abc_char_container { "abc" };
    const std::string def_char_container { "def" };
    const std::string ghi_char_container { "ghi" };

    yli::console::TextInputHistory text_input_history;
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(abc_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(def_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(ghi_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }

    auto it = text_input_history.end();
    --it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    --it;
    ASSERT_EQ((*it).data(), def_char_container);
    --it;
    ASSERT_EQ((*it).data(), abc_char_container);
    ASSERT_EQ(it, text_input_history.begin());
}

TEST(text_input_history_cend_iterator_must_work_appropriately, text_input_history_cend_iterator)
{
    const std::string abc_char_container { "abc" };
    const std::string def_char_container { "def" };
    const std::string ghi_char_container { "ghi" };

    yli::console::TextInputHistory text_input_history;
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(abc_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(def_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(ghi_char_container);
        text_input_history.add_to_history(std::move(text_input));
    }

    auto it = text_input_history.cend();
    --it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    --it;
    ASSERT_EQ((*it).data(), def_char_container);
    --it;
    ASSERT_EQ((*it).data(), abc_char_container);
    ASSERT_EQ(it, text_input_history.cbegin());
}
