// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
#include "code/hirvi/hirvi.hpp"
#include "code/ylikuutio/memory/constructible_module.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

TEST(ecosystem_must_be_initialized_appropriately, hirvi_ecosystem)
{
    const int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    yli::ontology::EcosystemStruct earth_ecosystem_struct;
    yli::ontology::Ecosystem* const earth_ecosystem = hirvi_application.get_entity_factory().create_ecosystem(earth_ecosystem_struct);
    ASSERT_NE(earth_ecosystem, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(earth_ecosystem) % alignof(yli::ontology::Ecosystem), 0);
    yli::memory::ConstructibleModule ecosystem_constructible_module = earth_ecosystem->get_constructible_module();
    ASSERT_EQ(ecosystem_constructible_module.storage_i, 0);
    ASSERT_EQ(ecosystem_constructible_module.slot_i, 0);
    ASSERT_EQ(ecosystem_constructible_module.alive, true);
}
