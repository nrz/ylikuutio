#ifndef __CALLBACK_HPP_INCLUDED
#define __CALLBACK_HPP_INCLUDED

#include "callback.hpp"

// Include standard headers
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace model
{
    class World;
}

// callback typedefs in alphabetical order.
typedef bool (*BoolToBoolCallback)(bool);
typedef float (*BoolToFloatCallback)(bool);
typedef int (*BoolToIntCallback)(bool);
typedef void (*BoolToVoidCallback)(bool);
typedef bool (*FloatToBoolCallback)(float);
typedef float (*FloatToFloatCallback)(float);
typedef int (*FloatToIntCallback)(float);
typedef void (*FloatToVoidCallback)(float);
typedef bool (*IntToBoolCallback)(int);
typedef float (*IntToFloatCallback)(int);
typedef int (*IntToIntCallback)(int);
typedef void (*IntToVoidCallback)(int);
typedef bool (*VoidToBoolCallback)(void);
typedef float (*VoidToFloatCallback)(void);
typedef int (*VoidToIntCallback)(void);
typedef void (*VoidToVoidCallback)(void);
typedef void (*WorldToVoidCallback)(model::World*);

namespace callback
{
    class CallbackEngine
    {
        // CallbackEngine is an object that contains some callbacks and hashmaps that are used for input and output parameters.

        public:
            // constructor.
            CallbackEngine();

            // execute all callbacks.
            void execute();

            std::unordered_map<std::string, bool> bool_hashmap;
            std::unordered_map<std::string, float> float_hashmap;
            std::unordered_map<std::string, double> double_hashmap;
            std::unordered_map<std::string, int32_t> int32_t_hashmap;
            std::unordered_map<std::string, uint32_t> uint32_t_hashmap;
    };

    class CallbackParameter
    {
        // constructor.
        CallbackParameter();

        std::string type;
        std::string input_variable_name;
        bool is_reference; // if true, the value is read from the hashmap. if false, then the value is read from the union.
        union value
        {
            bool bool_value;
            float float_value;
            double double_value;
            int32_t int32_t_value;
            uint32_t uint32_t_value;
        };
    };

    class BoolCallbackParameter : CallbackParameter
    {
        // constructor.
        BoolCallbackParameter();
    };

    class Callback
    {
        // Callback is an object that contains a single callback.

        public:
        // constructor.
        Callback(callback::CallbackEngine* callback_engine);

        // execute all callbacks.
        void execute();

        // Callback provides a way to create callback chains.
        std::string output_type;
        std::string output_variable_name;
        std::vector<CallbackParameter> input_parameters;
    };
}

#endif
