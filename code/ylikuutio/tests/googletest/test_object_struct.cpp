#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/glyph.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

TEST(ObjectStruct_must_be_initialized_appropriately, ObjectStruct)
{
    const ObjectStruct test_object_struct;
    ASSERT_EQ(test_object_struct.species_parent, nullptr);
    ASSERT_EQ(test_object_struct.text3D_parent, nullptr);
    ASSERT_EQ(test_object_struct.glyph, nullptr);
    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_EQ(test_object_struct.rotate_angle, 0.0f);
    ASSERT_FALSE(test_object_struct.is_character);
    ASSERT_FALSE(test_object_struct.quaternions_in_use);
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.x));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.y));
    ASSERT_TRUE(std::isnan(test_object_struct.cartesian_coordinates.z));
    ASSERT_EQ(test_object_struct.rotate_vector, glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(test_object_struct.translate_vector, glm::vec3(0.0f, 0.0f, 0.0f));
}
