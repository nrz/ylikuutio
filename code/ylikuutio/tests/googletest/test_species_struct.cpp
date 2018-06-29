#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/species_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

TEST(SpeciesStruct_must_be_initialized_appropriately, SpeciesStruct)
{
    const SpeciesStruct test_species_struct;
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
