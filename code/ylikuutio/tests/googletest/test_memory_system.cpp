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
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/data/type_enum_provider.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_storage.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"

// Include standard headers
#include <cstddef> // std::ptrdiff_t

namespace yli::memory
{
    class GenericMemoryAllocator;
}

TEST(memory_system_must_be_initialized_appropriately, default_memory_system_no_application)
{
    yli::memory::MemorySystem memory_system(nullptr, yli::data::Datatype::UNIVERSE);
    ASSERT_FALSE(memory_system.has_allocator(yli::data::Datatype::UNIVERSE));
    ASSERT_EQ(memory_system.get_number_of_allocators(), 0);
    ASSERT_EQ(memory_system.get_universe_datatype(), yli::data::Datatype::UNIVERSE);
}

TEST(memory_system_must_store_allocator_for_universe, scene_default_memory_system_no_application)
{
    yli::memory::MemorySystem memory_system(nullptr, yli::data::Datatype::UNIVERSE);

    memory_system.store_allocator(
            yli::data::Datatype::UNIVERSE,
            new yli::memory::MemoryAllocator<yli::ontology::Universe, 1>());
    ASSERT_EQ(memory_system.get_number_of_allocators(), 1); // `Universe` allocator.

    yli::memory::GenericMemoryAllocator& generic_universe_allocator = memory_system.get_allocator(yli::data::Datatype::UNIVERSE);

    yli::memory::MemoryAllocator<yli::ontology::Universe, 1>& universe_allocator =
        dynamic_cast<yli::memory::MemoryAllocator<yli::ontology::Universe, 1>&>(generic_universe_allocator);
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 0);
}

TEST(memory_system_must_store_allocator_for_scene, scene_default_memory_system_no_application)
{
    yli::memory::MemorySystem memory_system(nullptr, yli::data::Datatype::UNIVERSE);

    memory_system.store_allocator(
            yli::data::Datatype::SCENE,
            new yli::memory::MemoryAllocator<yli::ontology::Scene, 1>());
    ASSERT_EQ(memory_system.get_number_of_allocators(), 1); // `Scene` allocator.

    yli::memory::GenericMemoryAllocator& generic_scene_allocator = memory_system.get_allocator(yli::data::Datatype::SCENE);

    yli::memory::MemoryAllocator<yli::ontology::Scene, 1>& scene_allocator =
        dynamic_cast<yli::memory::MemoryAllocator<yli::ontology::Scene, 1>&>(generic_scene_allocator);
    ASSERT_EQ(scene_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(scene_allocator.get_number_of_instances(), 0);
}
