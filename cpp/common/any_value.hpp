#ifndef __ANY_VALUE_HPP_INCLUDED
#define __ANY_VALUE_HPP_INCLUDED

// Include standard headers
#include <cmath>    // NAN
#include <cstddef>  // NULL
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.

namespace datatypes
{
    enum datatype
    {
        UNKNOWN,
        BOOL,
        FLOAT,
        DOUBLE,
        INT32_T,
        UINT32_T,
        VOID_POINTER
    };
}

typedef struct AnyValue
{
    AnyValue()
        : type(datatypes::UNKNOWN), bool_value(false), float_value(NAN), double_value(NAN), int32_t_value(0), uint32_t_value(0), void_pointer(NULL)
    {
        // constructor.
    }

    AnyValue(bool bool_value)
        : type(datatypes::BOOL), bool_value(bool_value), float_value(NAN), double_value(NAN), int32_t_value(0), uint32_t_value(0), void_pointer(NULL)
    {
        // constructor.
    }

    AnyValue(float float_value)
        : type(datatypes::FLOAT), bool_value(false), float_value(float_value), double_value(NAN), int32_t_value(0), uint32_t_value(0), void_pointer(NULL)
    {
        // constructor.
    }

    AnyValue(double double_value)
        : type(datatypes::DOUBLE), bool_value(false), float_value(NAN), double_value(double_value), int32_t_value(0), uint32_t_value(0), void_pointer(NULL)
    {
        // constructor.
    }

    AnyValue(int32_t int32_t_value)
        : type(datatypes::INT32_T), bool_value(false), float_value(NAN), double_value(NAN), int32_t_value(int32_t_value), uint32_t_value(0), void_pointer(NULL)
    {
        // constructor.
    }

    AnyValue(uint32_t uint32_t_value)
        : type(datatypes::UINT32_T), bool_value(false), float_value(NAN), double_value(NAN), int32_t_value(0), uint32_t_value(uint32_t_value), void_pointer(NULL)
    {
        // constructor.
    }

    AnyValue(void* void_pointer)
        : type(datatypes::VOID_POINTER), bool_value(false), float_value(NAN), double_value(NAN), int32_t_value(0), uint32_t_value(uint32_t_value), void_pointer(void_pointer)
    {
        // constructor.
    }

    int type;
    bool bool_value;
    float float_value;
    double double_value;
    int32_t int32_t_value;
    uint32_t uint32_t_value;
    void* void_pointer;
} AnyValue;

#endif
