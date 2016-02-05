#include "callback_engine.hpp"
#include "cpp/hierarchy/hierarchy.hpp"

// Include standard headers
#include <iostream>
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace callback_system
{
    CallbackEngine::CallbackEngine()
    {
        // constructor.
    }

    CallbackEngine::~CallbackEngine()
    {
        // destructor.
    }

    void CallbackEngine::set_callback_object_pointer(uint32_t childID, void* parent_pointer)
    {
        model::set_child_pointer(childID, parent_pointer, this->callback_object_pointer_vector, this->free_callback_objectID_queue);
    }

    // getter functions for callbacks and callback objects.

    bool CallbackEngine::get_bool(std::string name)
    {
        return this->bool_hashmap[name];
    }

    float CallbackEngine::get_float(std::string name)
    {
        return this->float_hashmap[name];
    }

    double CallbackEngine::get_double(std::string name)
    {
        return this->double_hashmap[name];
    }

    int32_t CallbackEngine::get_int32_t(std::string name)
    {
        return this->int32_t_hashmap[name];
    }

    uint32_t CallbackEngine::get_uint32_t(std::string name)
    {
        return this->uint32_t_hashmap[name];
    }

    void* CallbackEngine::get_void_pointer(std::string name)
    {
        return this->void_pointer_hashmap[name];
    }

    // setter functions for callbacks and callback objects.

    void CallbackEngine::set_bool(std::string name, bool value)
    {
        this->bool_hashmap[name] = value;
    }

    void CallbackEngine::set_float(std::string name, float value)
    {
        this->float_hashmap[name] = value;
    }

    void CallbackEngine::set_double(std::string name, double value)
    {
        this->double_hashmap[name] = value;
    }

    void CallbackEngine::set_int32_t(std::string name, int32_t value)
    {
        this->int32_t_hashmap[name] = value;
    }

    void CallbackEngine::set_uint32_t(std::string name, uint32_t value)
    {
        this->uint32_t_hashmap[name] = value;
    }

    void CallbackEngine::set_void_pointer(std::string name, void* value)
    {
        this->void_pointer_hashmap[name] = value;
    }

    AnyValue CallbackEngine::execute()
    {
        std::cout << "Hello from AnyValue CallbackEngine::execute()\n";

        AnyValue any_value;

        /*
        // execute all callbacks.
        for (callback_system::CallbackObject callback_object : this->callback_objects)
        {
            any_value = callback_object.execute();
        }
        */

        return any_value;
    }
}
