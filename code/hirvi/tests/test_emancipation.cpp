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
#include "code/hirvi/ontology/emancipation_module.hpp"
#include "code/hirvi/ontology/police_module.hpp"

TEST(emancipation_must_function_properly, emancipation)
{
    hirvi::ontology::PoliceModule police_module;
    ASSERT_FALSE(police_module.get_is_emancipated());

    hirvi::ontology::EmancipationModule emancipation_module(police_module);
    ASSERT_FALSE(police_module.get_is_emancipated());

    emancipation_module.emancipate();
    ASSERT_TRUE(police_module.get_is_emancipated());
}
