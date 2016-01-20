#ifndef __CALLBACK_HPP_INCLUDED
#define __CALLBACK_HPP_INCLUDED

#include "callback.hpp"
#include "any_value.hpp"

// Include standard headers
#include <cmath>         // NAN
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

namespace callback_system
{
    class CallbackParameter;
}

typedef AnyValue (*InputParametersToAnyValueCallback)(std::vector<callback_system::CallbackParameter*>); 

namespace callback_system
{
    class CallbackObject;

    class CallbackEngine
    {
        // `CallbackEngine` is an object that contains some callbacks and hashmaps that are used for input and output parameters.
        // `CallbackEngine` provides a way to create callback chains.
        //
        // How to use:
        // 1. Create a new `CallbackEngine`.
        // 2. Create a new `CallbackObject`, give pointer to the
        //    recently created `CallbackEngine` as input parameter.
        // 3. If the newly created `CallbackObject` has
        //    input parameter[s], create the first input parameter
        //    by calling `add_input_parameter`.

        public:
            // constructor.
            CallbackEngine();

            // setter functions for callbacks and callback objects.
            bool get_bool(std::string name);
            float get_float(std::string name);
            double get_double(std::string name);
            int32_t get_int32_t(std::string name);
            uint32_t get_uint32_t(std::string name);
            void* get_void_pointer(std::string name);

            // setter functions for callbacks and callback objects.
            void set_bool(std::string name, bool value);
            void set_float(std::string name, float value);
            void set_double(std::string name, double value);
            void set_int32_t(std::string name, int32_t value);
            void set_uint32_t(std::string name, uint32_t value);
            void set_void_pointer(std::string name, void* value);

            // execute all callbacks.
            AnyValue execute();

        private:
            std::vector<callback_system::CallbackObject> callback_objects;

            std::unordered_map<std::string, bool> bool_hashmap;
            std::unordered_map<std::string, float> float_hashmap;
            std::unordered_map<std::string, double> double_hashmap;
            std::unordered_map<std::string, int32_t> int32_t_hashmap;
            std::unordered_map<std::string, uint32_t> uint32_t_hashmap;
            std::unordered_map<std::string, void*> void_pointer_hashmap;
    };

    class CallbackObject
    {
        // CallbackObject is an object that contains a single callback.

        public:
            // constructor.
            CallbackObject(callback_system::CallbackEngine* callback_engine_pointer);

            // constructor.
            CallbackObject(InputParametersToAnyValueCallback callback, callback_system::CallbackEngine* callback_engine_pointer);

            // add reference to an input variable.
            // this does not store the value to an appropriate hashmap.
            // storing the value must be done before or after this call.
            // each type has its own namespace!
            void add_input_parameter(std::string name, AnyValue any_value, bool is_reference);

            // execute this callback.
            AnyValue execute();

            callback_system::CallbackEngine* callback_engine_pointer;

            std::string output_type;
            std::string output_variable_name;
            std::vector<callback_system::CallbackParameter*> input_parameters;

            InputParametersToAnyValueCallback callback;
    };

    class CallbackParameter
    {
        public:

            // constructor.
            CallbackParameter(std::string name, AnyValue any_value, bool is_reference, callback_system::CallbackObject* callback_object);

            std::string name;
            AnyValue any_value;
            bool is_reference; // if true, the value is read from the hashmap. if false, then the value is read from the union.
    };

    class BoolCallbackParameter : CallbackParameter
    {
        public:

            // constructor.
            BoolCallbackParameter();
    };
}

#endif
