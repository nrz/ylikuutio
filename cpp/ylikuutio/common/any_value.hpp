#ifndef __ANY_VALUE_HPP_INCLUDED
#define __ANY_VALUE_HPP_INCLUDED

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <stdint.h> // uint32_t etc.

namespace ontology
{
    class World;
}

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
        VOID_POINTER,
        WORLD_POINTER
    };
}

namespace datatypes
{
    typedef class AnyValue
    {
        public:
            AnyValue();
            AnyValue(bool bool_value);
            AnyValue(float float_value);
            AnyValue(double double_value);
            AnyValue(int32_t int32_t_value);
            AnyValue(uint32_t uint32_t_value);
            AnyValue(void* void_pointer);
            AnyValue(ontology::World* world_pointer);

            AnyValue(std::string type, bool bool_value);
            AnyValue(std::string type, float float_value);
            AnyValue(std::string type, double double_value);
            AnyValue(std::string type, int32_t int32_t_value);
            AnyValue(std::string type, uint32_t uint32_t_value);
            AnyValue(std::string type, void* void_pointer);
            AnyValue(std::string type, ontology::World* world_pointer);

            int type;
            bool bool_value;
            float float_value;
            double double_value;
            int32_t int32_t_value;
            uint32_t uint32_t_value;
            void* void_pointer;
            ontology::World* world_pointer;

        private:
            void set_default_values();
    } AnyValue;
}

#endif
