#include "gtest/gtest.h"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/ontology/world.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <stdint.h> // uint32_t etc.

TEST(any_value_must_be_initialized_appropriately, no_value)
{
    datatypes::AnyValue no_value = datatypes::AnyValue();
    ASSERT_EQ(no_value.type, datatypes::UNKNOWN);
    ASSERT_FALSE(no_value.bool_value);
    ASSERT_TRUE(isnan(no_value.float_value));
    ASSERT_TRUE(isnan(no_value.double_value));
    ASSERT_EQ(no_value.int32_t_value, 0);
    ASSERT_EQ(no_value.uint32_t_value, 0);
    ASSERT_EQ(no_value.void_pointer, nullptr);
    ASSERT_EQ(no_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, bool_true)
{
    bool bool_true = true;
    datatypes::AnyValue true_value = datatypes::AnyValue(bool_true);
    ASSERT_EQ(true_value.type, datatypes::BOOL);
    ASSERT_TRUE(true_value.bool_value);
    ASSERT_TRUE(isnan(true_value.float_value));
    ASSERT_TRUE(isnan(true_value.double_value));
    ASSERT_EQ(true_value.int32_t_value, 0);
    ASSERT_EQ(true_value.uint32_t_value, 0);
    ASSERT_EQ(true_value.void_pointer, nullptr);
    ASSERT_EQ(true_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, bool_false)
{
    bool bool_false = false;
    datatypes::AnyValue false_value = datatypes::AnyValue(bool_false);
    ASSERT_EQ(false_value.type, datatypes::BOOL);
    ASSERT_FALSE(false_value.bool_value);
    ASSERT_TRUE(isnan(false_value.float_value));
    ASSERT_TRUE(isnan(false_value.double_value));
    ASSERT_EQ(false_value.int32_t_value, 0);
    ASSERT_EQ(false_value.uint32_t_value, 0);
    ASSERT_EQ(false_value.void_pointer, nullptr);
    ASSERT_EQ(false_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, float_0)
{
    float float_zero = 0.0f;
    datatypes::AnyValue float_zero_value = datatypes::AnyValue(float_zero);
    ASSERT_EQ(float_zero_value.type, datatypes::FLOAT);
    ASSERT_FALSE(float_zero_value.bool_value);
    ASSERT_EQ(float_zero_value.float_value, 0.0f);
    ASSERT_TRUE(isnan(float_zero_value.double_value));
    ASSERT_EQ(float_zero_value.int32_t_value, 0);
    ASSERT_EQ(float_zero_value.uint32_t_value, 0);
    ASSERT_EQ(float_zero_value.void_pointer, nullptr);
    ASSERT_EQ(float_zero_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, float_NAN)
{
    float float_NAN = NAN;
    datatypes::AnyValue float_NAN_value = datatypes::AnyValue(float_NAN);
    ASSERT_EQ(float_NAN_value.type, datatypes::FLOAT);
    ASSERT_FALSE(float_NAN_value.bool_value);
    ASSERT_TRUE(isnan(float_NAN_value.float_value));
    ASSERT_TRUE(isnan(float_NAN_value.double_value));
    ASSERT_EQ(float_NAN_value.int32_t_value, 0);
    ASSERT_EQ(float_NAN_value.uint32_t_value, 0);
    ASSERT_EQ(float_NAN_value.void_pointer, nullptr);
    ASSERT_EQ(float_NAN_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, double_0)
{
    double double_zero = 0.0f;
    datatypes::AnyValue double_zero_value = datatypes::AnyValue(double_zero);
    ASSERT_EQ(double_zero_value.type, datatypes::DOUBLE);
    ASSERT_FALSE(double_zero_value.bool_value);
    ASSERT_TRUE(isnan(double_zero_value.float_value));
    ASSERT_EQ(double_zero_value.double_value, 0.0f);
    ASSERT_EQ(double_zero_value.int32_t_value, 0);
    ASSERT_EQ(double_zero_value.uint32_t_value, 0);
    ASSERT_EQ(double_zero_value.void_pointer, nullptr);
    ASSERT_EQ(double_zero_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, double_NAN)
{
    double double_NAN = NAN;
    datatypes::AnyValue double_NAN_value = datatypes::AnyValue(double_NAN);
    ASSERT_EQ(double_NAN_value.type, datatypes::DOUBLE);
    ASSERT_FALSE(double_NAN_value.bool_value);
    ASSERT_TRUE(isnan(double_NAN_value.double_value));
    ASSERT_TRUE(isnan(double_NAN_value.double_value));
    ASSERT_EQ(double_NAN_value.int32_t_value, 0);
    ASSERT_EQ(double_NAN_value.uint32_t_value, 0);
    ASSERT_EQ(double_NAN_value.void_pointer, nullptr);
    ASSERT_EQ(double_NAN_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, int32_t_zero)
{
    int32_t int32_t_zero = 0;
    datatypes::AnyValue int32_t_zero_value = datatypes::AnyValue(int32_t_zero);
    ASSERT_EQ(int32_t_zero_value.type, datatypes::INT32_T);
    ASSERT_FALSE(int32_t_zero_value.bool_value);
    ASSERT_TRUE(isnan(int32_t_zero_value.double_value));
    ASSERT_TRUE(isnan(int32_t_zero_value.double_value));
    ASSERT_EQ(int32_t_zero_value.int32_t_value, 0);
    ASSERT_EQ(int32_t_zero_value.uint32_t_value, 0);
    ASSERT_EQ(int32_t_zero_value.void_pointer, nullptr);
    ASSERT_EQ(int32_t_zero_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, int32_t_plus_1)
{
    int32_t int32_t_plus_1 = 1;
    datatypes::AnyValue int32_t_plus_1_value = datatypes::AnyValue(int32_t_plus_1);
    ASSERT_EQ(int32_t_plus_1_value.type, datatypes::INT32_T);
    ASSERT_FALSE(int32_t_plus_1_value.bool_value);
    ASSERT_TRUE(isnan(int32_t_plus_1_value.double_value));
    ASSERT_TRUE(isnan(int32_t_plus_1_value.double_value));
    ASSERT_EQ(int32_t_plus_1_value.int32_t_value, 1);
    ASSERT_EQ(int32_t_plus_1_value.uint32_t_value, 0);
    ASSERT_EQ(int32_t_plus_1_value.void_pointer, nullptr);
    ASSERT_EQ(int32_t_plus_1_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, int32_t_minus_1)
{
    int32_t int32_t_minus_1 = -1;
    datatypes::AnyValue int32_t_minus_1_value = datatypes::AnyValue(int32_t_minus_1);
    ASSERT_EQ(int32_t_minus_1_value.type, datatypes::INT32_T);
    ASSERT_FALSE(int32_t_minus_1_value.bool_value);
    ASSERT_TRUE(isnan(int32_t_minus_1_value.double_value));
    ASSERT_TRUE(isnan(int32_t_minus_1_value.double_value));
    ASSERT_EQ(int32_t_minus_1_value.int32_t_value, -1);
    ASSERT_EQ(int32_t_minus_1_value.uint32_t_value, 0);
    ASSERT_EQ(int32_t_minus_1_value.void_pointer, nullptr);
    ASSERT_EQ(int32_t_minus_1_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, uint32_t_zero)
{
    uint32_t uint32_t_zero = 0;
    datatypes::AnyValue uint32_t_zero_value = datatypes::AnyValue(uint32_t_zero);
    ASSERT_EQ(uint32_t_zero_value.type, datatypes::UINT32_T);
    ASSERT_FALSE(uint32_t_zero_value.bool_value);
    ASSERT_TRUE(isnan(uint32_t_zero_value.double_value));
    ASSERT_TRUE(isnan(uint32_t_zero_value.double_value));
    ASSERT_EQ(uint32_t_zero_value.int32_t_value, 0);
    ASSERT_EQ(uint32_t_zero_value.uint32_t_value, 0);
    ASSERT_EQ(uint32_t_zero_value.void_pointer, nullptr);
    ASSERT_EQ(uint32_t_zero_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, uint32_t_plus_1)
{
    uint32_t uint32_t_plus_1 = 1;
    datatypes::AnyValue uint32_t_plus_1_value = datatypes::AnyValue(uint32_t_plus_1);
    ASSERT_EQ(uint32_t_plus_1_value.type, datatypes::UINT32_T);
    ASSERT_FALSE(uint32_t_plus_1_value.bool_value);
    ASSERT_TRUE(isnan(uint32_t_plus_1_value.double_value));
    ASSERT_TRUE(isnan(uint32_t_plus_1_value.double_value));
    ASSERT_EQ(uint32_t_plus_1_value.int32_t_value, 0);
    ASSERT_EQ(uint32_t_plus_1_value.uint32_t_value, 1);
    ASSERT_EQ(uint32_t_plus_1_value.void_pointer, nullptr);
    ASSERT_EQ(uint32_t_plus_1_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, void_pointer_zero)
{
    void* void_pointer_zero;
    void_pointer_zero = (void*) 0;
    datatypes::AnyValue void_pointer_zero_value = datatypes::AnyValue(void_pointer_zero);
    ASSERT_EQ(void_pointer_zero_value.type, datatypes::VOID_POINTER);
    ASSERT_FALSE(void_pointer_zero_value.bool_value);
    ASSERT_TRUE(isnan(void_pointer_zero_value.double_value));
    ASSERT_TRUE(isnan(void_pointer_zero_value.double_value));
    ASSERT_EQ(void_pointer_zero_value.int32_t_value, 0);
    ASSERT_EQ(void_pointer_zero_value.uint32_t_value, 0);
    ASSERT_EQ(void_pointer_zero_value.void_pointer, (void*) 0);
    ASSERT_EQ(void_pointer_zero_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, void_pointer_1)
{
    void* void_pointer_1;
    void_pointer_1 = (void*) 1;
    datatypes::AnyValue void_pointer_1_value = datatypes::AnyValue(void_pointer_1);
    ASSERT_EQ(void_pointer_1_value.type, datatypes::VOID_POINTER);
    ASSERT_FALSE(void_pointer_1_value.bool_value);
    ASSERT_TRUE(isnan(void_pointer_1_value.double_value));
    ASSERT_TRUE(isnan(void_pointer_1_value.double_value));
    ASSERT_EQ(void_pointer_1_value.int32_t_value, 0);
    ASSERT_EQ(void_pointer_1_value.uint32_t_value, 0);
    ASSERT_EQ(void_pointer_1_value.void_pointer, (void*) 1);
    ASSERT_EQ(void_pointer_1_value.world_pointer, nullptr);
}
TEST(any_value_must_be_initialized_appropriately, world_pointer_zero)
{
    ontology::World* world_pointer_zero;
    world_pointer_zero = (ontology::World*) 0;
    datatypes::AnyValue world_pointer_zero_value = datatypes::AnyValue(world_pointer_zero);
    ASSERT_EQ(world_pointer_zero_value.type, datatypes::WORLD_POINTER);
    ASSERT_FALSE(world_pointer_zero_value.bool_value);
    ASSERT_TRUE(isnan(world_pointer_zero_value.double_value));
    ASSERT_TRUE(isnan(world_pointer_zero_value.double_value));
    ASSERT_EQ(world_pointer_zero_value.int32_t_value, 0);
    ASSERT_EQ(world_pointer_zero_value.uint32_t_value, 0);
    ASSERT_EQ(world_pointer_zero_value.void_pointer, nullptr);
    ASSERT_EQ(world_pointer_zero_value.world_pointer, (ontology::World*) 0);
}
TEST(any_value_must_be_initialized_appropriately, world_pointer_1)
{
    ontology::World* world_pointer_1;
    world_pointer_1 = (ontology::World*) 1;
    datatypes::AnyValue world_pointer_1_value = datatypes::AnyValue(world_pointer_1);
    ASSERT_EQ(world_pointer_1_value.type, datatypes::WORLD_POINTER);
    ASSERT_FALSE(world_pointer_1_value.bool_value);
    ASSERT_TRUE(isnan(world_pointer_1_value.double_value));
    ASSERT_TRUE(isnan(world_pointer_1_value.double_value));
    ASSERT_EQ(world_pointer_1_value.int32_t_value, 0);
    ASSERT_EQ(world_pointer_1_value.uint32_t_value, 0);
    ASSERT_EQ(world_pointer_1_value.void_pointer, nullptr);
    ASSERT_EQ(world_pointer_1_value.world_pointer, (ontology::World*) 1);
}
