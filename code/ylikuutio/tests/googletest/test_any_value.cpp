#include "gtest/gtest.h"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.

TEST(any_value_must_be_initialized_appropriately, no_value)
{
    yli::datatypes::AnyValue no_value = yli::datatypes::AnyValue();
    ASSERT_EQ(no_value.type, yli::datatypes::UNKNOWN);
}

TEST(any_value_must_be_initialized_appropriately, bool_true)
{
    bool bool_true = true;
    yli::datatypes::AnyValue true_value = yli::datatypes::AnyValue(bool_true);
    ASSERT_EQ(true_value.type, yli::datatypes::BOOL);
    ASSERT_TRUE(true_value.bool_value);
    ASSERT_EQ(std::strlen(true_value.get_datatype().c_str()), std::strlen("bool"));
    ASSERT_EQ(std::strcmp(true_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::strlen(true_value.get_string().c_str()), std::strlen("bool"));
    ASSERT_EQ(std::strcmp(true_value.get_string().c_str(), "true"), 0);
}

TEST(any_value_must_be_initialized_appropriately, bool_false)
{
    bool bool_false = false;
    yli::datatypes::AnyValue false_value = yli::datatypes::AnyValue(bool_false);
    ASSERT_EQ(false_value.type, yli::datatypes::BOOL);
    ASSERT_FALSE(false_value.bool_value);
    ASSERT_EQ(std::strlen(false_value.get_datatype().c_str()), std::strlen("bool"));
    ASSERT_EQ(std::strcmp(false_value.get_datatype().c_str(), "bool"), 0);
    ASSERT_EQ(std::strlen(false_value.get_string().c_str()), std::strlen("false"));
    ASSERT_EQ(std::strcmp(false_value.get_string().c_str(), "false"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_0)
{
    float float_zero = 0.0f;
    yli::datatypes::AnyValue float_zero_value = yli::datatypes::AnyValue(float_zero);
    ASSERT_EQ(float_zero_value.type, yli::datatypes::FLOAT);
    ASSERT_EQ(float_zero_value.float_value, 0.0f);
    uint32_t* IEEE_754_0_uint32_t_pointer = reinterpret_cast<uint32_t*>(&float_zero_value.float_value);
    ASSERT_EQ(*IEEE_754_0_uint32_t_pointer, 0);
    ASSERT_EQ(std::strlen(float_zero_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_zero_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_zero_value.get_string().c_str()), std::strlen("0.000000"));
    ASSERT_EQ(std::strlen(float_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(float_zero_value.get_string().c_str(), "0.000000"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_positive_infinity)
{
    float float_positive_infinity = std::numeric_limits<float>::infinity();
    yli::datatypes::AnyValue float_positive_infinity_value = yli::datatypes::AnyValue(float_positive_infinity);
    ASSERT_EQ(float_positive_infinity_value.type, yli::datatypes::FLOAT);
    ASSERT_EQ(float_positive_infinity_value.float_value, std::numeric_limits<float>::infinity());
    uint32_t* IEEE_754_0_uint32_t_pointer = reinterpret_cast<uint32_t*>(&float_positive_infinity_value.float_value);
    ASSERT_EQ(*IEEE_754_0_uint32_t_pointer, 0x7f800000);
    ASSERT_EQ(std::strlen(float_positive_infinity_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_positive_infinity_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_positive_infinity_value.get_string().c_str()), std::strlen("inf"));
    ASSERT_EQ(std::strcmp(float_positive_infinity_value.get_string().c_str(), "inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_negative_infinity)
{
    float float_negative_infinity = -1.0f * std::numeric_limits<float>::infinity();
    yli::datatypes::AnyValue float_negative_infinity_value = yli::datatypes::AnyValue(float_negative_infinity);
    ASSERT_EQ(float_negative_infinity_value.type, yli::datatypes::FLOAT);
    ASSERT_EQ(float_negative_infinity_value.float_value, float_negative_infinity);
    uint32_t* IEEE_754_0_uint32_t_pointer = reinterpret_cast<uint32_t*>(&float_negative_infinity_value.float_value);
    ASSERT_EQ(*IEEE_754_0_uint32_t_pointer, 0xff800000);
    ASSERT_EQ(std::strlen(float_negative_infinity_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_negative_infinity_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_negative_infinity_value.get_string().c_str()), std::strlen("-inf"));
    ASSERT_EQ(std::strcmp(float_negative_infinity_value.get_string().c_str(), "-inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, float_NAN)
{
    float float_NAN = NAN;
    yli::datatypes::AnyValue float_NAN_value = yli::datatypes::AnyValue(float_NAN);
    ASSERT_EQ(float_NAN_value.type, yli::datatypes::FLOAT);
    ASSERT_TRUE(std::isnan(float_NAN_value.float_value));
    uint32_t* IEEE_754_NAN_uint32_t_pointer = reinterpret_cast<uint32_t*>(&float_NAN_value.float_value);
    ASSERT_GT(*IEEE_754_NAN_uint32_t_pointer & 0x7fffffff, 0x7f800000);
    ASSERT_EQ(std::strlen(float_NAN_value.get_datatype().c_str()), std::strlen("float"));
    ASSERT_EQ(std::strcmp(float_NAN_value.get_datatype().c_str(), "float"), 0);
    ASSERT_EQ(std::strlen(float_NAN_value.get_string().c_str()), std::strlen("nan"));
    ASSERT_EQ(std::strcmp(float_NAN_value.get_string().c_str(), "nan"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_0)
{
    double double_zero = 0.0f;
    yli::datatypes::AnyValue double_zero_value = yli::datatypes::AnyValue(double_zero);
    ASSERT_EQ(double_zero_value.type, yli::datatypes::DOUBLE);
    ASSERT_EQ(double_zero_value.double_value, 0.0f);
    uint64_t* IEEE_754_0_uint64_t_pointer = reinterpret_cast<uint64_t*>(&double_zero_value.double_value);
    ASSERT_EQ(*IEEE_754_0_uint64_t_pointer, 0);
    ASSERT_EQ(std::strlen(double_zero_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_zero_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_zero_value.get_string().c_str()), std::strlen("0.000000"));
    ASSERT_EQ(std::strlen(double_zero_value.get_string().c_str()), 8);
    ASSERT_EQ(std::strcmp(double_zero_value.get_string().c_str(), "0.000000"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_positive_infinity)
{
    double double_positive_infinity = std::numeric_limits<double>::infinity();
    yli::datatypes::AnyValue double_positive_infinity_value = yli::datatypes::AnyValue(double_positive_infinity);
    ASSERT_EQ(double_positive_infinity_value.type, yli::datatypes::DOUBLE);
    ASSERT_EQ(double_positive_infinity_value.double_value, std::numeric_limits<double>::infinity());
    uint64_t* IEEE_754_NAN_uint64_t_pointer = reinterpret_cast<uint64_t*>(&double_positive_infinity_value.double_value);
    ASSERT_EQ(*IEEE_754_NAN_uint64_t_pointer, 0x7ff0000000000000);
    ASSERT_EQ(std::strlen(double_positive_infinity_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_positive_infinity_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_positive_infinity_value.get_string().c_str()), std::strlen("inf"));
    ASSERT_EQ(std::strcmp(double_positive_infinity_value.get_string().c_str(), "inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_negative_infinity)
{
    double double_negative_infinity = -1 * std::numeric_limits<double>::infinity();
    yli::datatypes::AnyValue double_negative_infinity_value = yli::datatypes::AnyValue(double_negative_infinity);
    ASSERT_EQ(double_negative_infinity_value.type, yli::datatypes::DOUBLE);
    ASSERT_EQ(double_negative_infinity_value.double_value, double_negative_infinity);
    uint64_t* IEEE_754_NAN_uint64_t_pointer = reinterpret_cast<uint64_t*>(&double_negative_infinity_value.double_value);
    ASSERT_EQ(*IEEE_754_NAN_uint64_t_pointer, 0xfff0000000000000);
    ASSERT_EQ(std::strlen(double_negative_infinity_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_negative_infinity_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_negative_infinity_value.get_string().c_str()), std::strlen("-inf"));
    ASSERT_EQ(std::strcmp(double_negative_infinity_value.get_string().c_str(), "-inf"), 0);
}

TEST(any_value_must_be_initialized_appropriately, double_NAN)
{
    double double_NAN = NAN;
    yli::datatypes::AnyValue double_NAN_value = yli::datatypes::AnyValue(double_NAN);
    ASSERT_EQ(double_NAN_value.type, yli::datatypes::DOUBLE);
    ASSERT_TRUE(std::isnan(double_NAN_value.double_value));
    uint64_t* IEEE_754_NAN_uint64_t_pointer = reinterpret_cast<uint64_t*>(&double_NAN_value.double_value);
    ASSERT_GT(*IEEE_754_NAN_uint64_t_pointer & 0x7fffffffffffffff, 0x7ff0000000000000);
    ASSERT_EQ(std::strlen(double_NAN_value.get_datatype().c_str()), std::strlen("double"));
    ASSERT_EQ(std::strcmp(double_NAN_value.get_datatype().c_str(), "double"), 0);
    ASSERT_EQ(std::strlen(double_NAN_value.get_string().c_str()), std::strlen("nan"));
    ASSERT_EQ(std::strcmp(double_NAN_value.get_string().c_str(), "nan"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_zero)
{
    int32_t int32_t_zero = 0;
    yli::datatypes::AnyValue int32_t_zero_value = yli::datatypes::AnyValue(int32_t_zero);
    ASSERT_EQ(int32_t_zero_value.type, yli::datatypes::INT32_T);
    ASSERT_EQ(int32_t_zero_value.int32_t_value, 0);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_zero_value.int32_t_value), 0);
    ASSERT_EQ(std::strlen(int32_t_zero_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_zero_value.get_string().c_str()), std::strlen("0"));
    ASSERT_EQ(std::strcmp(int32_t_zero_value.get_string().c_str(), "0"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_plus_1)
{
    int32_t int32_t_plus_1 = 1;
    yli::datatypes::AnyValue int32_t_plus_1_value = yli::datatypes::AnyValue(int32_t_plus_1);
    ASSERT_EQ(int32_t_plus_1_value.type, yli::datatypes::INT32_T);
    ASSERT_EQ(int32_t_plus_1_value.int32_t_value, 1);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_plus_1_value.int32_t_value), 1);
    ASSERT_EQ(std::strlen(int32_t_plus_1_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_plus_1_value.get_string().c_str()), std::strlen("1"));
    ASSERT_EQ(std::strcmp(int32_t_plus_1_value.get_string().c_str(), "1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_minus_1)
{
    int32_t int32_t_minus_1 = -1;
    yli::datatypes::AnyValue int32_t_minus_1_value = yli::datatypes::AnyValue(int32_t_minus_1);
    ASSERT_EQ(int32_t_minus_1_value.type, yli::datatypes::INT32_T);
    ASSERT_EQ(int32_t_minus_1_value.int32_t_value, -1);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_minus_1_value.int32_t_value), 4294967295);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_minus_1_value.int32_t_value), 0xffffffff);
    ASSERT_EQ(std::strlen(int32_t_minus_1_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_minus_1_value.get_string().c_str()), std::strlen("-1"));
    ASSERT_EQ(std::strcmp(int32_t_minus_1_value.get_string().c_str(), "-1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_max)
{
    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::datatypes::AnyValue int32_t_max_value = yli::datatypes::AnyValue(int32_t_max);
    ASSERT_EQ(int32_t_max_value.type, yli::datatypes::INT32_T);
    ASSERT_EQ(int32_t_max_value.int32_t_value, 2147483647);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_max_value.int32_t_value), 2147483647);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_max_value.int32_t_value), 0x7fffffff);
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<int32_t>::max());
#ifdef __linux__
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<int>::max());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<int>::max());
    ASSERT_EQ(int32_t_max_value.int32_t_value, std::numeric_limits<long>::max());
#endif
    ASSERT_EQ(std::strlen(int32_t_max_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_max_value.get_string().c_str()), std::strlen("2147483647"));
    ASSERT_EQ(std::strcmp(int32_t_max_value.get_string().c_str(), "2147483647"), 0);
}

TEST(any_value_must_be_initialized_appropriately, int32_t_min)
{
    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::datatypes::AnyValue int32_t_min_value = yli::datatypes::AnyValue(int32_t_min);
    ASSERT_EQ(int32_t_min_value.type, yli::datatypes::INT32_T);
    ASSERT_EQ(int32_t_min_value.int32_t_value, -2147483648);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_min_value.int32_t_value), 2147483648);
    ASSERT_EQ(static_cast<uint32_t>(int32_t_min_value.int32_t_value), 0x80000000);
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<int32_t>::min());
#ifdef __linux__
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<int>::min());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<int>::min());
    ASSERT_EQ(int32_t_min_value.int32_t_value, std::numeric_limits<long>::min());
#endif
    ASSERT_EQ(std::strlen(int32_t_min_value.get_datatype().c_str()), std::strlen("int32_t"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_datatype().c_str(), "int32_t"), 0);
    ASSERT_EQ(std::strlen(int32_t_min_value.get_string().c_str()), std::strlen("-2147483648"));
    ASSERT_EQ(std::strcmp(int32_t_min_value.get_string().c_str(), "-2147483648"), 0);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_zero)
{
    uint32_t uint32_t_zero = 0;
    yli::datatypes::AnyValue uint32_t_zero_value = yli::datatypes::AnyValue(uint32_t_zero);
    ASSERT_EQ(uint32_t_zero_value.type, yli::datatypes::UINT32_T);
    ASSERT_EQ(uint32_t_zero_value.uint32_t_value, 0);
    ASSERT_EQ(std::strlen(uint32_t_zero_value.get_datatype().c_str()), std::strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_zero_value.get_string().c_str()), std::strlen("0"));
    ASSERT_EQ(std::strcmp(uint32_t_zero_value.get_string().c_str(), "0"), 0);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_plus_1)
{
    uint32_t uint32_t_plus_1 = 1;
    yli::datatypes::AnyValue uint32_t_plus_1_value = yli::datatypes::AnyValue(uint32_t_plus_1);
    ASSERT_EQ(uint32_t_plus_1_value.type, yli::datatypes::UINT32_T);
    ASSERT_EQ(uint32_t_plus_1_value.uint32_t_value, 1);
    ASSERT_EQ(std::strlen(uint32_t_plus_1_value.get_datatype().c_str()), std::strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_plus_1_value.get_string().c_str()), std::strlen("1"));
    ASSERT_EQ(std::strcmp(uint32_t_plus_1_value.get_string().c_str(), "1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, uint32_t_max)
{
    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::datatypes::AnyValue uint32_t_max_value = yli::datatypes::AnyValue(uint32_t_max);
    ASSERT_EQ(uint32_t_max_value.type, yli::datatypes::UINT32_T);
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, std::numeric_limits<uint32_t>::max());
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, 4294967295);
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, 0xffffffff);
    ASSERT_EQ(static_cast<int32_t>(uint32_t_max_value.uint32_t_value), -1);
#ifdef __linux__
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, std::numeric_limits<unsigned int>::max());
#elif defined(_WIN32) || defined(WIN32)
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, std::numeric_limits<unsigned int>::max());
    ASSERT_EQ(uint32_t_max_value.uint32_t_value, std::numeric_limits<unsigned long>::max());
#endif
    ASSERT_EQ(std::strlen(uint32_t_max_value.get_datatype().c_str()), std::strlen("uint32_t"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_datatype().c_str(), "uint32_t"), 0);
    ASSERT_EQ(std::strlen(uint32_t_max_value.get_string().c_str()), std::strlen("4294967295"));
    ASSERT_EQ(std::strcmp(uint32_t_max_value.get_string().c_str(), "4294967295"), 0);
}

TEST(any_value_must_be_initialized_appropriately, universe)
{
    yli::ontology::Universe* universe = static_cast<yli::ontology::Universe*>((void*) 0xdeadbeef);
    yli::datatypes::AnyValue universe_any_value = yli::datatypes::AnyValue(universe);
    ASSERT_EQ(universe_any_value.type, yli::datatypes::UNIVERSE_POINTER);
    ASSERT_EQ(universe_any_value.universe, universe);
    ASSERT_EQ(std::strlen(universe_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Universe*"));
    ASSERT_EQ(std::strcmp(universe_any_value.get_datatype().c_str(), "yli::ontology::Universe*"), 0);
    ASSERT_EQ(std::strlen(universe_any_value.get_string().c_str()), std::strlen("deadbeef"));
    ASSERT_EQ(std::strcmp(universe_any_value.get_string().c_str(), "deadbeef"), 0);
}

TEST(any_value_must_be_initialized_appropriately, scene)
{
    yli::ontology::Scene* scene = static_cast<yli::ontology::Scene*>((void*) 0xbad5ce6e);
    yli::datatypes::AnyValue scene_pointer_any_value = yli::datatypes::AnyValue(scene);
    ASSERT_EQ(scene_pointer_any_value.type, yli::datatypes::SCENE_POINTER);
    ASSERT_EQ(scene_pointer_any_value.scene_pointer, scene);
    ASSERT_EQ(std::strlen(scene_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Scene*"));
    ASSERT_EQ(std::strcmp(scene_pointer_any_value.get_datatype().c_str(), "yli::ontology::Scene*"), 0);
    ASSERT_EQ(std::strlen(scene_pointer_any_value.get_string().c_str()), std::strlen("bad5ce6e"));
    ASSERT_EQ(std::strcmp(scene_pointer_any_value.get_string().c_str(), "bad5ce6e"), 0);
}

TEST(any_value_must_be_initialized_appropriately, shader)
{
    yli::ontology::Shader* shader = static_cast<yli::ontology::Shader*>((void*) 0xbad5bade7);
    yli::datatypes::AnyValue shader_pointer_any_value = yli::datatypes::AnyValue(shader);
    ASSERT_EQ(shader_pointer_any_value.type, yli::datatypes::SHADER_POINTER);
    ASSERT_EQ(shader_pointer_any_value.shader_pointer, shader);
    ASSERT_EQ(std::strlen(shader_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Shader*"));
    ASSERT_EQ(std::strcmp(shader_pointer_any_value.get_datatype().c_str(), "yli::ontology::Shader*"), 0);
    ASSERT_EQ(std::strlen(shader_pointer_any_value.get_string().c_str()), std::strlen("bad5bade7"));
    ASSERT_EQ(std::strcmp(shader_pointer_any_value.get_string().c_str(), "bad5bade7"), 0);
}

TEST(any_value_must_be_initialized_appropriately, material)
{
    yli::ontology::Material* material = static_cast<yli::ontology::Material*>((void*) 0xbad6a7e71a1);
    yli::datatypes::AnyValue material_pointer_any_value = yli::datatypes::AnyValue(material);
    ASSERT_EQ(material_pointer_any_value.type, yli::datatypes::MATERIAL_POINTER);
    ASSERT_EQ(material_pointer_any_value.material_pointer, material);
    ASSERT_EQ(std::strlen(material_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Material*"));
    ASSERT_EQ(std::strcmp(material_pointer_any_value.get_datatype().c_str(), "yli::ontology::Material*"), 0);
    ASSERT_EQ(std::strlen(material_pointer_any_value.get_string().c_str()), std::strlen("bad6a7e71a1"));
    ASSERT_EQ(std::strcmp(material_pointer_any_value.get_string().c_str(), "bad6a7e71a1"), 0);
}

TEST(any_value_must_be_initialized_appropriately, species)
{
    yli::ontology::Species* species = static_cast<yli::ontology::Species*>((void*) 0xbad5bec1e5);
    yli::datatypes::AnyValue species_pointer_any_value = yli::datatypes::AnyValue(species);
    ASSERT_EQ(species_pointer_any_value.type, yli::datatypes::SPECIES_POINTER);
    ASSERT_EQ(species_pointer_any_value.species_pointer, species);
    ASSERT_EQ(std::strlen(species_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Species*"));
    ASSERT_EQ(std::strcmp(species_pointer_any_value.get_datatype().c_str(), "yli::ontology::Species*"), 0);
    ASSERT_EQ(std::strlen(species_pointer_any_value.get_string().c_str()), std::strlen("bad5bec1e5"));
    ASSERT_EQ(std::strcmp(species_pointer_any_value.get_string().c_str(), "bad5bec1e5"), 0);
}

TEST(any_value_must_be_initialized_appropriately, object)
{
    yli::ontology::Object* object = static_cast<yli::ontology::Object*>((void*) 0xbad0b1ec7);
    yli::datatypes::AnyValue object_pointer_any_value = yli::datatypes::AnyValue(object);
    ASSERT_EQ(object_pointer_any_value.type, yli::datatypes::OBJECT_POINTER);
    ASSERT_EQ(object_pointer_any_value.object_pointer, object);
    ASSERT_EQ(std::strlen(object_pointer_any_value.get_datatype().c_str()), std::strlen("yli::ontology::Object*"));
    ASSERT_EQ(std::strcmp(object_pointer_any_value.get_datatype().c_str(), "yli::ontology::Object*"), 0);
    ASSERT_EQ(std::strlen(object_pointer_any_value.get_string().c_str()), std::strlen("bad0b1ec7"));
    ASSERT_EQ(std::strcmp(object_pointer_any_value.get_string().c_str(), "bad0b1ec7"), 0);
}
