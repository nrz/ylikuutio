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
#include "code/ylikuutio/console/scrollback_buffer.hpp"
#include "code/ylikuutio/console/text_input.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <optional> // std::optional
#include <span>     // std::span
#include <string>   // std::string

TEST(scrollback_buffer_must_be_initialized_appropriately, n_columns_0_n_rows_0)
{
    yli::console::ScrollbackBuffer scrollback_buffer(0, 0);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_TRUE(scrollback_buffer.get_view(0, 0).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view(0, 1).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(0).empty()); // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(1).empty()); // Initially scrollback buffer is empty.
}

TEST(scrollback_buffer_must_be_initialized_appropriately, n_columns_0_n_rows_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(0, 1);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_TRUE(scrollback_buffer.get_view(0, 0).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view(0, 1).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(0).empty()); // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(1).empty()); // Initially scrollback buffer is empty.
}

TEST(scrollback_buffer_must_be_initialized_appropriately, n_columns_1_n_rows_0)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 0);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_TRUE(scrollback_buffer.get_view(0, 0).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view(0, 1).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(0).empty()); // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(1).empty()); // Initially scrollback buffer is empty.
}

TEST(scrollback_buffer_must_be_initialized_appropriately, n_columns_1_n_rows_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 1);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_TRUE(scrollback_buffer.get_view(0, 0).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view(0, 1).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(0).empty()); // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(1).empty()); // Initially scrollback buffer is empty.
}

TEST(scrollback_buffer_must_be_initialized_appropriately, n_columns_2_n_rows_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(2, 1);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 2);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_TRUE(scrollback_buffer.get_view(0, 0).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view(0, 1).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(0).empty()); // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(1).empty()); // Initially scrollback buffer is empty.
}

TEST(scrollback_buffer_must_be_initialized_appropriately, n_columns_2_n_rows_2)
{
    yli::console::ScrollbackBuffer scrollback_buffer(2, 2);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 2);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_TRUE(scrollback_buffer.get_view(0, 0).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view(0, 1).empty());      // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(0).empty()); // Initially scrollback buffer is empty.
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(1).empty()); // Initially scrollback buffer is empty.
}

TEST(moving_to_previous_input_must_fail_appropriately, empty_scrollback_buffer_n_columns_1_n_rows_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 1);
    ASSERT_FALSE(scrollback_buffer.move_to_previous());
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(1).empty());
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(2).empty());
}

TEST(moving_to_next_input_must_fail_appropriately, empty_scrollback_buffer_n_columns_1_n_rows_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 1);
    ASSERT_FALSE(scrollback_buffer.move_to_next());
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(1).empty());
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(2).empty());
}

TEST(adding_empty_line_must_not_do_anything, scrollback_buffer_with_n_columns_1_n_rows_1_text_n_columns_0)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 1);
    scrollback_buffer.add_to_buffer(std::string(""));
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());

    ASSERT_FALSE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(1).empty());
    ASSERT_TRUE(scrollback_buffer.get_view_to_last(2).empty());
}

TEST(adding_a_line_of_n_columns_of_1_must_work_properly, scrollback_buffer_with_n_columns_1_n_rows_1_text_n_columns_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 1);
    const std::string text_line("a");
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
}

TEST(adding_a_line_of_n_columns_of_1_must_work_properly, scrollback_buffer_with_n_columns_2_n_rows_2_text_n_columns_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(2, 2);
    const std::string text_line("a");
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 2);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
}

TEST(adding_a_line_of_n_columns_of_1_must_work_properly, scrollback_buffer_with_n_columns_3_n_rows_2_text_n_columns_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(3, 2);
    const std::string text_line("a");
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 3);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
}

TEST(adding_a_line_of_n_columns_of_2_must_work_properly, scrollback_buffer_with_n_columns_1_n_rows_2_text_n_columns_2)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 2);
    const std::string text_line("ab");
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 2);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), std::string("a"));
    ASSERT_EQ(scrollback_buffer.at(1), std::string("b"));
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
        const std::string& text_line_1_from_buffer = buffer_view_top_index_0_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("b"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("b"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
        const std::string& text_line_1_from_buffer = buffer_view_bottom_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("b"));
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 1);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("b"));
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("b"));
    }
}

TEST(adding_a_line_of_n_columns_of_2_must_work_properly, scrollback_buffer_with_n_columns_2_n_rows_2_text_n_columns_2)
{
    yli::console::ScrollbackBuffer scrollback_buffer(2, 2);
    const std::string text_line("ab");
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 2);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
}

TEST(adding_a_line_of_n_columns_of_2_must_work_properly, scrollback_buffer_with_n_columns_3_n_rows_2_text_n_columns_2)
{
    yli::console::ScrollbackBuffer scrollback_buffer(3, 2);
    const std::string text_line("ab");
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 3);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
}

TEST(adding_a_line_of_n_columns_of_3_must_work_properly, scrollback_buffer_with_n_columns_1_n_rows_2_text_n_columns_3)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 2);
    const std::string text_line("abc");
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 3);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), std::string("a"));
    ASSERT_EQ(scrollback_buffer.at(1), std::string("b"));
    ASSERT_EQ(scrollback_buffer.at(2), std::string("c"));
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
        const std::string& text_line_1_from_buffer = buffer_view_top_index_0_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("b"));
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 3 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 3);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 3);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
        const std::string& text_line_1_from_buffer = buffer_view_top_index_0_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("b"));
        const std::string& text_line_2_from_buffer = buffer_view_top_index_0_max_size_2.data()[2];
        ASSERT_EQ(text_line_2_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("b"));
        const std::string& text_line_1_from_buffer = buffer_view_bottom_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("c"));
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 2);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
}

TEST(adding_a_line_of_n_columns_of_3_must_work_properly, scrollback_buffer_with_n_columns_2_n_rows_2_text_n_columns_3)
{
    yli::console::ScrollbackBuffer scrollback_buffer(2, 2);
    const std::string text_line("abc");
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 2);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 2);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), std::string("ab"));
    ASSERT_EQ(scrollback_buffer.at(1), std::string("c"));
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("ab"));
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("ab"));
        const std::string& text_line_1_from_buffer = buffer_view_top_index_0_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 3 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_3 = scrollback_buffer.get_view(0, 3);
        ASSERT_EQ(buffer_view_top_index_0_max_size_3.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_3.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("ab"));
        const std::string& text_line_1_from_buffer = buffer_view_top_index_0_max_size_3.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("ab"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 3 lines.
        std::span<const std::string> buffer_view_bottom_max_size_3 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_3.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_3.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("ab"));
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 1);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
}

TEST(adding_a_line_of_n_columns_of_3_must_work_properly, scrollback_buffer_with_n_columns_3_n_rows_2_text_n_columns_3)
{
    yli::console::ScrollbackBuffer scrollback_buffer(3, 2);
    const std::string text_line("abc");
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 3);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
}

TEST(adding_a_line_of_n_columns_of_3_must_work_properly, scrollback_buffer_with_n_columns_1_n_rows_2_text_input_width_3)
{
    yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
    const std::string text_line("abc");
    text_input.add_characters(text_line.data());

    yli::console::ScrollbackBuffer scrollback_buffer(1, 2);
    scrollback_buffer.add_to_buffer(text_input.data());
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 3);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), std::string("a"));
    ASSERT_EQ(scrollback_buffer.at(1), std::string("b"));
    ASSERT_EQ(scrollback_buffer.at(2), std::string("c"));
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
        const std::string& text_line_1_from_buffer = buffer_view_top_index_0_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("b"));
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 3 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 3);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 3);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
        const std::string& text_line_1_from_buffer = buffer_view_top_index_0_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("b"));
        const std::string& text_line_2_from_buffer = buffer_view_top_index_0_max_size_2.data()[2];
        ASSERT_EQ(text_line_2_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("b"));
        const std::string& text_line_1_from_buffer = buffer_view_bottom_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 3 lines.
        std::span<const std::string> buffer_view_bottom_max_size_3 = scrollback_buffer.get_view_to_last(3);
        ASSERT_EQ(buffer_view_bottom_max_size_3.size(), 3);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_3.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("a"));
        const std::string& text_line_1_from_buffer = buffer_view_bottom_max_size_3.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("b"));
        const std::string& text_line_2_from_buffer = buffer_view_bottom_max_size_3.data()[2];
        ASSERT_EQ(text_line_2_from_buffer, std::string("c"));
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 2);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
}

TEST(adding_a_line_of_n_columns_of_3_must_work_properly, scrollback_buffer_with_n_columns_2_n_rows_2_text_input_width_3)
{
    yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
    const std::string text_line("abc");
    text_input.add_characters(text_line.data());

    yli::console::ScrollbackBuffer scrollback_buffer(2, 2);
    scrollback_buffer.add_to_buffer(text_input.data());
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 2);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 2);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), std::string("ab"));
    ASSERT_EQ(scrollback_buffer.at(1), std::string("c"));
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("ab"));
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("ab"));
        const std::string& text_line_1_from_buffer = buffer_view_top_index_0_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 2);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("ab"));
        const std::string& text_line_1_from_buffer = buffer_view_bottom_max_size_2.data()[1];
        ASSERT_EQ(text_line_1_from_buffer, std::string("c"));
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 1);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, std::string("c"));
    }
}

TEST(adding_a_line_of_n_columns_of_3_must_work_properly, scrollback_buffer_with_n_columns_3_n_rows_2_text_input_width_3)
{
    yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
    const std::string text_line("abc");
    text_input.add_characters(text_line.data());

    yli::console::ScrollbackBuffer scrollback_buffer(3, 2);
    scrollback_buffer.add_to_buffer(text_input.data());
    ASSERT_FALSE(scrollback_buffer.get_is_active_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 3);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
    {
        // Get view to scrollback buffer from the top (start index = 0), max 0 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_0 = scrollback_buffer.get_view(0, 0);
        ASSERT_TRUE(buffer_view_top_index_0_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 1 line.
        std::span<const std::string> buffer_view_top_index_0_max_size_1 = scrollback_buffer.get_view(0, 1);
        ASSERT_EQ(buffer_view_top_index_0_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the top (start index = 0), max 2 lines.
        std::span<const std::string> buffer_view_top_index_0_max_size_2 = scrollback_buffer.get_view(0, 2);
        ASSERT_EQ(buffer_view_top_index_0_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_top_index_0_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 0 lines.
        std::span<const std::string> buffer_view_bottom_max_size_0 = scrollback_buffer.get_view_to_last(0);
        ASSERT_TRUE(buffer_view_bottom_max_size_0.empty());
    }
    {
        // Get view to scrollback buffer from the bottom, max 1 line.
        std::span<const std::string> buffer_view_bottom_max_size_1 = scrollback_buffer.get_view_to_last(1);
        ASSERT_EQ(buffer_view_bottom_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the bottom, max 2 lines.
        std::span<const std::string> buffer_view_bottom_max_size_2 = scrollback_buffer.get_view_to_last(2);
        ASSERT_EQ(buffer_view_bottom_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_bottom_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Enter scrollback buffer.
        ASSERT_TRUE(scrollback_buffer.enter_buffer());
        ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
    }
    {
        // Get view to scrollback buffer from the current index, max 1 line.
        std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 1);
        ASSERT_EQ(buffer_view_max_size_1.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_1.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
    {
        // Get view to scrollback buffer from the current index, max 2 lines.
        std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view(scrollback_buffer.get_buffer_index(), 2);
        ASSERT_EQ(buffer_view_max_size_2.size(), 1);
        const std::string& text_line_0_from_buffer = buffer_view_max_size_2.data()[0];
        ASSERT_EQ(text_line_0_from_buffer, text_line);
    }
}

TEST(scrollback_buffer_begin_iterator_must_work_appropriately, scrollback_buffer_n_columns_3_n_rows_2_begin_iterator)
{
    const std::string abc_char_container { "abc" };
    const std::string def_char_container { "def" };
    const std::string ghi_char_container { "ghi" };

    yli::console::ScrollbackBuffer scrollback_buffer(3, 2);
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(abc_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(def_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(ghi_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }

    auto it = scrollback_buffer.begin();
    ASSERT_EQ((*it).data(), abc_char_container);
    ++it;
    ASSERT_EQ((*it).data(), def_char_container);
    ++it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    ++it;
    ASSERT_EQ(it, scrollback_buffer.end());
}

TEST(scrollback_buffer_cbegin_iterator_must_work_appropriately, scrollback_buffer_n_columns_3_n_rows_2_cbegin_iterator)
{
    const std::string abc_char_container { "abc" };
    const std::string def_char_container { "def" };
    const std::string ghi_char_container { "ghi" };

    yli::console::ScrollbackBuffer scrollback_buffer(3, 2);
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(abc_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(def_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(ghi_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }

    auto it = scrollback_buffer.cbegin();
    ASSERT_EQ((*it).data(), abc_char_container);
    ++it;
    ASSERT_EQ((*it).data(), def_char_container);
    ++it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    ++it;
    ASSERT_EQ(it, scrollback_buffer.cend());
}

TEST(scrollback_buffer_end_iterator_must_work_appropriately, scrollback_buffer_n_columns_3_n_rows_2_end_iterator)
{
    const std::string abc_char_container { "abc" };
    const std::string def_char_container { "def" };
    const std::string ghi_char_container { "ghi" };

    yli::console::ScrollbackBuffer scrollback_buffer(3, 2);
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(abc_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(def_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(ghi_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }

    auto it = scrollback_buffer.end();
    --it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    --it;
    ASSERT_EQ((*it).data(), def_char_container);
    --it;
    ASSERT_EQ((*it).data(), abc_char_container);
    ASSERT_EQ(it, scrollback_buffer.begin());
}

TEST(scrollback_buffer_cend_iterator_must_work_appropriately, scrollback_buffer_n_columns_3_n_rows_2_cend_iterator)
{
    const std::string abc_char_container { "abc" };
    const std::string def_char_container { "def" };
    const std::string ghi_char_container { "ghi" };

    yli::console::ScrollbackBuffer scrollback_buffer(3, 2);
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(abc_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(def_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }
    {
        yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
        text_input.add_characters(ghi_char_container);
        scrollback_buffer.add_to_buffer(text_input.data());
    }

    auto it = scrollback_buffer.cend();
    --it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    --it;
    ASSERT_EQ((*it).data(), def_char_container);
    --it;
    ASSERT_EQ((*it).data(), abc_char_container);
    ASSERT_EQ(it, scrollback_buffer.cbegin());
}

TEST(emplacing_back_a_n_columns_of_1_must_work_properly, scrollback_buffer_with_n_columns_1_n_rows_2_text_n_columns_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 2);
    const std::string text_line("a");
    scrollback_buffer.emplace_back(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view_to_last(1);
    ASSERT_EQ(buffer_view_max_size_1.size(), 1);
    ASSERT_EQ(buffer_view_max_size_1[0], text_line);
    std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view_to_last(2);
    ASSERT_EQ(buffer_view_max_size_2.size(), 1);
    ASSERT_EQ(buffer_view_max_size_2[0], text_line);
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
}

TEST(pushing_back_a_n_columns_of_1_must_work_properly, scrollback_buffer_with_n_columns_1_n_rows_2_text_n_columns_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1, 2);
    const std::string text_line("a");
    scrollback_buffer.push_back(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_n_columns(), 1);
    ASSERT_EQ(scrollback_buffer.get_n_rows(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    std::span<const std::string> buffer_view_max_size_1 = scrollback_buffer.get_view_to_last(1);
    ASSERT_EQ(buffer_view_max_size_1.size(), 1);
    ASSERT_EQ(buffer_view_max_size_1[0], text_line);
    std::span<const std::string> buffer_view_max_size_2 = scrollback_buffer.get_view_to_last(2);
    ASSERT_EQ(buffer_view_max_size_2.size(), 1);
    ASSERT_EQ(buffer_view_max_size_2[0], text_line);
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
}
