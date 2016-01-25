#ifndef __CALLBACK_ENGINE_HPP_INCLUDED
#define __CALLBACK_ENGINE_HPP_INCLUDED

#include "any_value.hpp"

// Include standard headers
#include <cmath>         // NAN
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
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
    class CallbackObject;

    class CallbackEngine
    {
        // `CallbackEngine` is an object that contains some callbacks and hashmaps that are used for input and output parameters.
        // `CallbackEngine` provides a way to create callback chains.
        //
        // How to use.
        // 1. Create a new `CallbackEngine`. No callbacks have been
        //    defined yet. Calling `CallbackEngine.execute()` at this
        //    point will simply go through an empty vector and
        //    practically won't do anything interesting.
        // 2. Create a new `CallbackObject`, give pointer to the
        //    recently created `CallbackEngine` as input parameter.
        // 3. If the callback has parameter[s], create a new
        //    `CallbackParameter` for each parameter, give `CallbackObject`
        //    as input parameter for the `CallbackParameter` constructor.

        public:
            // constructor.
            CallbackEngine();

            // destructor.
            ~CallbackEngine();

            // this method sets a callback object pointer.
            void set_callback_object_pointer(uint32_t childID, void* parent_pointer);

            // getter functions for callbacks and callback objects.
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
            std::vector<void*> callback_object_pointer_vector;
            std::queue<uint32_t> free_callback_objectID_queue;

            std::unordered_map<std::string, bool> bool_hashmap;
            std::unordered_map<std::string, float> float_hashmap;
            std::unordered_map<std::string, double> double_hashmap;
            std::unordered_map<std::string, int32_t> int32_t_hashmap;
            std::unordered_map<std::string, uint32_t> uint32_t_hashmap;
            std::unordered_map<std::string, void*> void_pointer_hashmap;
    };
}

#endif
