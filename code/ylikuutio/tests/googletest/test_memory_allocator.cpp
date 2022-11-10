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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(memory_allocator_must_be_initialized_appropriately, universe_memory_allocator)
{
    yli::memory::MemoryAllocator<yli::ontology::Universe, 1> universe_allocator;
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 0);
}

TEST(memory_allocator_must_build_universe_in_a_memory_storage, universe_memory_storage_of_size_1)
{
    mock::MockApplication application;
    yli::memory::MemoryAllocator<yli::ontology::Universe, 1> universe_allocator;
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 0);

    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* universe = universe_allocator.build_in(application, universe_struct);
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 1);
    ASSERT_NE(universe, nullptr);
    ASSERT_EQ(application.get_universe().get_type(), "yli::ontology::Universe*");
}

TEST(memory_allocator_must_build_universe_in_a_memory_storage, universe_memory_storage_of_size_2)
{
    mock::MockApplication application;
    yli::memory::MemoryAllocator<yli::ontology::Universe, 2> universe_allocator;
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 0);

    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* universe = universe_allocator.build_in(application, universe_struct);
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 1);
    ASSERT_NE(universe, nullptr);
    ASSERT_EQ(application.get_universe().get_type(), "yli::ontology::Universe*");
}

TEST(memory_allocator_must_build_2_universes_in_the_same_memory_region, universes)
{
    mock::MockApplication application;
    yli::memory::MemoryAllocator<yli::ontology::Universe, 2> universe_allocator;
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 0);

    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
    yli::ontology::Universe* universe1 = universe_allocator.build_in(application, universe_struct);
    yli::ontology::Universe* universe2 = universe_allocator.build_in(application, universe_struct);
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 2);
    ASSERT_NE(universe1, nullptr);
    ASSERT_NE(universe2, nullptr);
    ASSERT_EQ(universe1->get_type(), "yli::ontology::Universe*");
    ASSERT_EQ(universe2->get_type(), "yli::ontology::Universe*");
    const std::ptrdiff_t address_difference = reinterpret_cast<std::byte*>(universe2) - reinterpret_cast<std::byte*>(universe1);
    ASSERT_EQ(address_difference, sizeof(yli::ontology::Universe));
}

TEST(memory_allocator_must_build_3_universes_in_the_same_memory_region, universes)
{
    mock::MockApplication application;
    yli::memory::MemoryAllocator<yli::ontology::Universe, 3> universe_allocator;
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 0);

    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
    yli::ontology::Universe* universe1 = universe_allocator.build_in(application, universe_struct);
    yli::ontology::Universe* universe2 = universe_allocator.build_in(application, universe_struct);
    yli::ontology::Universe* universe3 = universe_allocator.build_in(application, universe_struct);
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 3);
    ASSERT_NE(universe1, nullptr);
    ASSERT_NE(universe2, nullptr);
    ASSERT_NE(universe3, nullptr);
    ASSERT_EQ(universe1->get_type(), "yli::ontology::Universe*");
    ASSERT_EQ(universe2->get_type(), "yli::ontology::Universe*");
    ASSERT_EQ(universe3->get_type(), "yli::ontology::Universe*");
    const std::ptrdiff_t address_difference1 = reinterpret_cast<std::byte*>(universe2) - reinterpret_cast<std::byte*>(universe1);
    const std::ptrdiff_t address_difference2 = reinterpret_cast<std::byte*>(universe3) - reinterpret_cast<std::byte*>(universe2);
    ASSERT_EQ(address_difference1, sizeof(yli::ontology::Universe));
    ASSERT_EQ(address_difference2, sizeof(yli::ontology::Universe));
}
