#include "any_value.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.

namespace datatypes
{
    void AnyValue::set_default_values()
    {
        this->type = datatypes::UNKNOWN;
        this->bool_value = false;
        this->float_value = NAN;
        this->double_value = NAN;
        this->int32_t_value = 0;
        this->uint32_t_value = 0;
        this->bool_pointer = nullptr;
        this->float_pointer = nullptr;
        this->double_pointer = nullptr;
        this->int32_t_pointer = nullptr;
        this->uint32_t_pointer = nullptr;
        this->universe_pointer = nullptr;
        this->void_pointer = nullptr;
    }

    AnyValue::AnyValue()
    {
        // constructor.
        this->set_default_values();
    }

    AnyValue::AnyValue(bool bool_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::BOOL;
        this->bool_value = bool_value;
    }

    AnyValue::AnyValue(std::string type, bool bool_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "bool"))
        {
            this->type = datatypes::BOOL;
            this->bool_value = bool_value;
        }
    }

    AnyValue::AnyValue(float float_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::FLOAT;
        this->float_value = float_value;
    }

    AnyValue::AnyValue(std::string type, float float_value)
    {
        // constructor.
        this->set_default_values();

        if (std::strcmp(type.c_str(), "float"))
        {
            this->type = datatypes::FLOAT;
            this->float_value = float_value;
        }
    }

    AnyValue::AnyValue(double double_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::DOUBLE;
        this->double_value = double_value;
    }

    AnyValue::AnyValue(std::string type, double double_value)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "double"))
        {
            this->type = datatypes::DOUBLE;
            this->double_value = double_value;
        }
    }

    AnyValue::AnyValue(int32_t int32_t_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::INT32_T;
        this->int32_t_value = int32_t_value;
    }

    AnyValue::AnyValue(std::string type, int32_t int32_t_value)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "int32_t"))
        {
            this->type = datatypes::INT32_T;
            this->int32_t_value = int32_t_value;
        }
    }

    AnyValue::AnyValue(uint32_t uint32_t_value)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::UINT32_T;
        this->uint32_t_value = uint32_t_value;
    }

    AnyValue::AnyValue(std::string type, uint32_t uint32_t_value)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "uint32_t"))
        {
            this->type = datatypes::UINT32_T;
            this->uint32_t_value = uint32_t_value;
        }
    }

    AnyValue::AnyValue(bool* bool_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::BOOL_POINTER;
        this->bool_pointer = bool_pointer;
    }

    AnyValue::AnyValue(std::string type, bool* bool_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "bool*"))
        {
            this->type = datatypes::BOOL_POINTER;
            this->bool_pointer = bool_pointer;
        }
    }

    AnyValue::AnyValue(float* float_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::FLOAT_POINTER;
        this->float_pointer = float_pointer;
    }

    AnyValue::AnyValue(std::string type, float* float_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "float*"))
        {
            this->type = datatypes::FLOAT_POINTER;
            this->float_pointer = float_pointer;
        }
    }

    AnyValue::AnyValue(double* double_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::DOUBLE_POINTER;
        this->double_pointer = double_pointer;
    }

    AnyValue::AnyValue(std::string type, double* double_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "double*"))
        {
            this->type = datatypes::DOUBLE_POINTER;
            this->double_pointer = double_pointer;
        }
    }

    AnyValue::AnyValue(int32_t* int32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::INT32_T_POINTER;
        this->int32_t_pointer = int32_t_pointer;
    }

    AnyValue::AnyValue(std::string type, int32_t* int32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "int32_t*"))
        {
            this->type = datatypes::INT32_T_POINTER;
            this->int32_t_pointer = int32_t_pointer;
        }
    }

    AnyValue::AnyValue(uint32_t* uint32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::UINT32_T_POINTER;
        this->uint32_t_pointer = uint32_t_pointer;
    }

    AnyValue::AnyValue(std::string type, uint32_t* uint32_t_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "uint32_t*"))
        {
            this->type = datatypes::UINT32_T_POINTER;
            this->uint32_t_pointer = uint32_t_pointer;
        }
    }

    AnyValue::AnyValue(ontology::Universe* universe_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::UNIVERSE_POINTER;
        this->universe_pointer = universe_pointer;
    }

    AnyValue::AnyValue(std::string type, ontology::Universe* universe_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "ontology::Universe*"))
        {
            this->type = datatypes::UNIVERSE_POINTER;
            this->universe_pointer = universe_pointer;
        }
    }

    AnyValue::AnyValue(void* void_pointer)
    {
        // constructor.
        this->set_default_values();
        this->type = datatypes::VOID_POINTER;
        this->void_pointer = void_pointer;
    }

    AnyValue::AnyValue(std::string type, void* void_pointer)
    {
        // constructor.
        this->set_default_values();
        if (std::strcmp(type.c_str(), "void*"))
        {
            this->type = datatypes::VOID_POINTER;
            this->void_pointer = void_pointer;
        }
    }
}
