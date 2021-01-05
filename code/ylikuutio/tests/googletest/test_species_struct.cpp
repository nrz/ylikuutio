// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/species_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath> // NAN, std::isnan, std::pow

TEST(SpeciesStruct_must_be_initialized_appropriately, SpeciesStruct)
{
    const yli::ontology::SpeciesStruct test_species_struct;
    ASSERT_EQ(test_species_struct.scene, nullptr);
    ASSERT_EQ(test_species_struct.shader, nullptr);
    ASSERT_EQ(test_species_struct.material, nullptr);
    ASSERT_EQ(test_species_struct.symbiont_material, nullptr);
    ASSERT_FALSE(test_species_struct.is_terrain);
    ASSERT_TRUE(std::isnan(test_species_struct.planet_radius));
    ASSERT_TRUE(test_species_struct.model_file_format.empty());
    ASSERT_TRUE(test_species_struct.model_filename.empty());
    ASSERT_TRUE(test_species_struct.color_channel.empty());
    ASSERT_EQ(test_species_struct.light_position, glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(test_species_struct.latitude, 0.0f);
    ASSERT_EQ(test_species_struct.longitude, 0.0f);
}
