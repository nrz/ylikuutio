#include "any_value.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.

namespace model
{
    class World;
}

namespace datatypes
{
    AnyValue::AnyValue()
        : type(datatypes::UNKNOWN), bool_value(false), float_value(NAN), double_value(NAN), int32_t_value(0), uint32_t_value(0), void_pointer(nullptr), world_pointer(nullptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(bool bool_value)
        : type(datatypes::BOOL), bool_value(bool_value), float_value(NAN), double_value(NAN), int32_t_value(0), uint32_t_value(0), void_pointer(nullptr), world_pointer(nullptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(float float_value)
        : type(datatypes::FLOAT), bool_value(false), float_value(float_value), double_value(NAN), int32_t_value(0), uint32_t_value(0), void_pointer(nullptr), world_pointer(nullptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(double double_value)
        : type(datatypes::DOUBLE), bool_value(false), float_value(NAN), double_value(double_value), int32_t_value(0), uint32_t_value(0), void_pointer(nullptr), world_pointer(nullptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(int32_t int32_t_value)
        : type(datatypes::INT32_T), bool_value(false), float_value(NAN), double_value(NAN), int32_t_value(int32_t_value), uint32_t_value(0), void_pointer(nullptr), world_pointer(nullptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(uint32_t uint32_t_value)
        : type(datatypes::UINT32_T), bool_value(false), float_value(NAN), double_value(NAN), int32_t_value(0), uint32_t_value(uint32_t_value), void_pointer(nullptr), world_pointer(nullptr)
    {
        // constructor.
    }

    AnyValue::AnyValue(void* void_pointer)
        : type(datatypes::VOID_POINTER), bool_value(false), float_value(NAN), double_value(NAN), int32_t_value(0), uint32_t_value(uint32_t_value), void_pointer(void_pointer), world_pointer(nullptr)
    {
        // constructor.
        std::cout << "creating AnyValue with void* value.\n";
    }

    AnyValue::AnyValue(model::World* world_pointer)
        : type(datatypes::WORLD_POINTER), bool_value(false), float_value(NAN), double_value(NAN), int32_t_value(0), uint32_t_value(uint32_t_value), void_pointer(nullptr), world_pointer(world_pointer)
    {
        // constructor.
        std::cout << "creating AnyValue with model::World* value.\n";
    }
}
