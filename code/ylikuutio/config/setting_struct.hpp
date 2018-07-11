#ifndef __SETTING_STRUCT_HPP_INCLUDED
#define __SETTING_STRUCT_HPP_INCLUDED

#include "activate_callback.hpp"
#include "read_callback.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }
}

typedef struct SettingStruct
{
    SettingStruct(std::shared_ptr<datatypes::AnyValue> initial_value)
        : initial_value(initial_value),
        should_ylikuutio_call_activate_callback_now(true),
        setting_master(nullptr),
        activate_callback(nullptr),
        read_callback(nullptr)
    {
        // constructor.
    }
    std::string name;
    std::shared_ptr<datatypes::AnyValue> initial_value;
    yli::config::SettingMaster* setting_master;
    ActivateCallback activate_callback;
    ReadCallback read_callback;
    bool should_ylikuutio_call_activate_callback_now;
} SettingStruct;

#endif
