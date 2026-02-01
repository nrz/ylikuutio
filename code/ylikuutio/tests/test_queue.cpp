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
#include "code/ylikuutio/data/queue.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

TEST(queue_must_be_initialized_appropriately, queue_of_size_1)
{
    yli::data::Queue<1> queue;
    ASSERT_EQ(queue.size(), 0);
    ASSERT_EQ(queue.max_size(), 1);
    ASSERT_EQ(queue.get_head(), 0);
    ASSERT_EQ(queue.get_next_tail(), 0);
}

TEST(queue_must_be_initialized_appropriately, queue_of_size_2)
{
    yli::data::Queue<2> queue;
    ASSERT_EQ(queue.size(), 0);
    ASSERT_EQ(queue.max_size(), 2);
    ASSERT_EQ(queue.get_head(), 0);
    ASSERT_EQ(queue.get_next_tail(), 0);
}

TEST(pushing_to_empty_queue_must_work_appropriately, queue_of_size_1)
{
    yli::data::Queue<1> queue;
    queue.push(0xdeadbeef);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.max_size(), 1);
    ASSERT_EQ(queue.get_head(), 0);
    ASSERT_EQ(queue.get_next_tail(), 0); // Queue full.
    ASSERT_EQ(queue.data().at(0), 0xdeadbeef);
}

TEST(pushing_to_empty_queue_must_work_appropriately, queue_of_size_2)
{
    yli::data::Queue<2> queue;
    queue.push(0xdeadbeef);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.max_size(), 2);
    ASSERT_EQ(queue.get_head(), 0);
    ASSERT_EQ(queue.get_next_tail(), 1);
    ASSERT_EQ(queue.data().at(0), 0xdeadbeef);
}

TEST(pushing_to_empty_queue_must_work_appropriately, queue_of_size_3)
{
    yli::data::Queue<3> queue;
    queue.push(0xdeadbeef);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.max_size(), 3);
    ASSERT_EQ(queue.get_head(), 0);
    ASSERT_EQ(queue.get_next_tail(), 1);
    ASSERT_EQ(queue.data().at(0), 0xdeadbeef);
}

TEST(pushing_twice_to_empty_queue_must_work_appropriately, queue_of_size_2)
{
    yli::data::Queue<2> queue;
    queue.push(0xdeadbeef);
    queue.push(0xbadf00d);
    ASSERT_EQ(queue.size(), 2);
    ASSERT_EQ(queue.max_size(), 2);
    ASSERT_EQ(queue.get_head(), 0);
    ASSERT_EQ(queue.get_next_tail(), 0); // Queue full.
    ASSERT_EQ(queue.data().at(0), 0xdeadbeef);
    ASSERT_EQ(queue.data().at(1), 0xbadf00d);
}

TEST(pushing_twice_to_empty_queue_must_work_appropriately, queue_of_size_3)
{
    yli::data::Queue<3> queue;
    queue.push(0xdeadbeef);
    queue.push(0xbadf00d);
    ASSERT_EQ(queue.size(), 2);
    ASSERT_EQ(queue.max_size(), 3);
    ASSERT_EQ(queue.get_head(), 0);
    ASSERT_EQ(queue.get_next_tail(), 2);
    ASSERT_EQ(queue.data().at(0), 0xdeadbeef);
    ASSERT_EQ(queue.data().at(1), 0xbadf00d);
}

TEST(popping_after_pushing_once_must_give_the_pushed_value, queue_of_size_1)
{
    yli::data::Queue<1> queue;
    queue.push(0xdeadbeef);
    uint32_t value = queue.pop();
    ASSERT_EQ(value, 0xdeadbeef);

    ASSERT_EQ(queue.size(), 0);
    ASSERT_EQ(queue.max_size(), 1);
    ASSERT_EQ(queue.get_head(), 0);
    ASSERT_EQ(queue.get_next_tail(), 0);
}

TEST(popping_after_pushing_twice_must_give_the_last_pushed_value, queue_of_size_2)
{
    yli::data::Queue<2> queue;
    queue.push(0xdeadbeef);
    queue.push(0xbadf00d);
    uint32_t first = queue.pop();
    ASSERT_EQ(first, 0xdeadbeef);

    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.max_size(), 2);
    ASSERT_EQ(queue.get_head(), 1);      // Next pop from index 1.
    ASSERT_EQ(queue.get_next_tail(), 0); // Next push to index 0.
}

TEST(popping_twice_after_pushing_twice_must_give_the_pushed_values_in_same_order, queue_of_size_2)
{
    yli::data::Queue<2> queue;
    queue.push(0xdeadbeef);
    queue.push(0xbadf00d);
    uint32_t first = queue.pop();
    uint32_t second = queue.pop();
    ASSERT_EQ(first, 0xdeadbeef);
    ASSERT_EQ(second, 0xbadf00d);

    ASSERT_EQ(queue.size(), 0);
    ASSERT_EQ(queue.max_size(), 2);
    ASSERT_EQ(queue.get_head(), 0);
    ASSERT_EQ(queue.get_next_tail(), 0);
}

TEST(popping_twice_after_pushing_twice_must_give_the_pushed_values_in_same_order, queue_of_size_3)
{
    yli::data::Queue<3> queue;
    queue.push(0xdeadbeef);
    queue.push(0xbadf00d);
    uint32_t first = queue.pop();
    uint32_t second = queue.pop();
    ASSERT_EQ(first, 0xdeadbeef);
    ASSERT_EQ(second, 0xbadf00d);

    ASSERT_EQ(queue.size(), 0);
    ASSERT_EQ(queue.max_size(), 3);
    ASSERT_EQ(queue.get_head(), 2);
    ASSERT_EQ(queue.get_next_tail(), 2); // Next push to index 2.
}

TEST(pushing_twice_popping_once_pushing_once_popping_once_must_work_appropriately, queue_of_size_2)
{
    yli::data::Queue<2> queue;
    queue.push(0xdeadbeef);
    queue.push(0xbadf00d);
    queue.pop();

    queue.push(0xfeedca7);
    uint32_t second = queue.pop();
    ASSERT_EQ(second, 0xbadf00d);

    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.max_size(), 2);
    ASSERT_EQ(queue.get_head(), 0);      // Next pop from index 0.
    ASSERT_EQ(queue.get_next_tail(), 1); // Next push to index 1.
}

TEST(pushing_twice_popping_once_pushing_once_popping_twice_must_work_appropriately, queue_of_size_2)
{
    yli::data::Queue<2> queue;
    queue.push(0xdeadbeef);
    queue.push(0xbadf00d);
    queue.pop();

    queue.push(0xfeedca7);
    queue.pop();

    uint32_t third = queue.pop();
    ASSERT_EQ(third, 0xfeedca7);

    ASSERT_EQ(queue.size(), 0);
    ASSERT_EQ(queue.max_size(), 2);
    ASSERT_EQ(queue.get_head(), 1);
    ASSERT_EQ(queue.get_next_tail(), 1); // Next push to index 1.
}
