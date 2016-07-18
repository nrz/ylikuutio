#include "callback_engine.hpp"
#include "callback_object.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
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
        std::cout << "This callback engine will be destroyed.\n";

        // destroy all callback objects of this callback engine.
        std::cout << "All callback objects of this callback engine will be destroyed.\n";
        hierarchy::delete_children<callback_system::CallbackObject*>(this->callback_object_pointer_vector);
    }

    void CallbackEngine::set_callback_object_pointer(uint32_t childID, void* parent_pointer)
    {
        hierarchy::set_child_pointer(childID, parent_pointer, this->callback_object_pointer_vector, this->free_callback_objectID_queue);
    }

    // getter functions for callbacks and callback objects.
    datatypes::AnyValue CallbackEngine::get_any_value(std::string name)
    {
        return this->anyvalue_hashmap[name];
    }

    bool CallbackEngine::get_bool(std::string name)
    {
        return this->anyvalue_hashmap[name].bool_value;
    }

    float CallbackEngine::get_float(std::string name)
    {
        return this->anyvalue_hashmap[name].float_value;
    }

    double CallbackEngine::get_double(std::string name)
    {
        return this->anyvalue_hashmap[name].double_value;
    }

    int32_t CallbackEngine::get_int32_t(std::string name)
    {
        return this->anyvalue_hashmap[name].int32_t_value;
    }

    uint32_t CallbackEngine::get_uint32_t(std::string name)
    {
        return this->anyvalue_hashmap[name].uint32_t_value;
    }

    void* CallbackEngine::get_void_pointer(std::string name)
    {
        return this->anyvalue_hashmap[name].void_pointer;
    }

    // setter functions for callbacks and callback objects.

    void CallbackEngine::set_bool(std::string name, bool value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CallbackEngine::set_float(std::string name, float value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CallbackEngine::set_double(std::string name, double value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CallbackEngine::set_int32_t(std::string name, int32_t value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CallbackEngine::set_uint32_t(std::string name, uint32_t value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CallbackEngine::set_void_pointer(std::string name, void* value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CallbackEngine::set_world_pointer(std::string name, ontology::Universe* value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    datatypes::AnyValue* CallbackEngine::execute()
    {
        datatypes::AnyValue* any_value = new datatypes::AnyValue();

        // execute all callbacks.
        for (uint32_t child_i = 0; child_i < this->callback_object_pointer_vector.size(); child_i++)
        {
            callback_system::CallbackObject* callback_object_pointer = static_cast<callback_system::CallbackObject*>(this->callback_object_pointer_vector[child_i]);
            any_value = callback_object_pointer->execute();
        }

        return any_value;
    }
}
