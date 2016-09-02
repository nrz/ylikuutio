#include "setting_master.hpp"
#include "setting.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <string>        // std::string
#include <vector>        // std::vector
#include <unordered_map> // std::unordered_map

namespace config
{
    SettingMaster::SettingMaster(ontology::Universe* universe_pointer)
    {
        // costructor.
        this->parent_pointer = universe_pointer;

        // bind to parent.
        // there can be only 1 `SettingMaster`.
        this->parent_pointer->setting_master_pointer = this;
    }

    SettingMaster::~SettingMaster()
    {
        // destructor.
    }

    bool SettingMaster::is_setting(std::string setting_name)
    {
        return (this->setting_pointer_map.count(setting_name) == 1);
    }

    std::string SettingMaster::help()
    {
        std::string help_string = "TODO: create general helptext";
        return help_string;
    }

    std::string SettingMaster::help(std::string setting_name)
    {
        if (this->is_setting(setting_name))
        {
            config::Setting* setting = this->setting_pointer_map[setting_name];

            if (setting != nullptr)
            {
                return setting->help();
            }
        }
        return this->help();
    }

    // public callbacks.

    datatypes::AnyValue* SettingMaster::set(
            console::Console* console,
            ontology::Universe* universe,
            std::vector<std::string>& command_parameters)
    {
        // Usage:
        // to get variable names: set
        // to get valid values:   set <variable>
        // to set variable:       set <variable> value[s]

        config::SettingMaster* setting_master = universe->setting_master_pointer;

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string setting_name = command_parameters.at(0);

            // One (1) command parameter.
            // Check the validity of the variable name.
            if (setting_master->is_setting(setting_name))
            {
                config::Setting* setting = setting_master->setting_pointer_map[setting_name];

                if (setting != nullptr)
                {
                    // Print variable value.
                    console->print_text(setting->setting_value.get_string());
                }
            }
            else
            {
                // Invalid variable name.
                console->print_text("invalid variable name");
                console->print_text(setting_master->help());
            }
        }
        else
        {
            std::string setting_name = command_parameters.at(0);

            // At least 2 variables.
            // Check the validity of the variable name.
            if (setting_master->is_setting(setting_name))
            {
                // OK, this is a valid variable name.
                // Set the variable value and activate it by
                // calling the corresponding activate callback.
                config::Setting* setting = setting_master->setting_pointer_map[setting_name];

                // create empty `AnyValue` (there is no suitable constructor yet).
                datatypes::AnyValue setting_any_value = datatypes::AnyValue();
                setting_any_value.type = setting->setting_value.type;

                // set a new value.
                bool success = setting_any_value.set_value(command_parameters.at(1));

                if (success)
                {
                    setting->setting_value = setting_any_value;
                    setting->activate_callback(universe, setting_master);
                }
            }
            else
            {
                console->print_text(setting_master->help());
            }
        }

        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::get(
            console::Console* console,
            ontology::Universe* universe,
            std::vector<std::string>& command_parameters)
    {
        // Usage:
        // to get variable names: get
        // to get variable value: get <variable>
        config::SettingMaster* setting_master = universe->setting_master_pointer;

        if (command_parameters.size() == 0)
        {
            // No command parameters.
            // Print variable names.
            console->print_text(setting_master->help());
        }
        else if (command_parameters.size() == 1)
        {
            std::string setting_name = command_parameters.at(0);

            // One (1) command parameter.
            // Print valid values of the given variable.
            if (setting_master->is_setting(setting_name))
            {
                config::Setting* setting = setting_master->setting_pointer_map[setting_name];

                if (setting != nullptr)
                {
                    // Print variable value.
                    console->print_text(setting->setting_value.get_string());
                }
            }
            else
            {
                // Invalid variable name.
                console->print_text("invalid variable name");
                console->print_text(setting_master->help());
            }
        }
        else
        {
            // More than 1 command parameter.
            // Print variable names.
            console->print_text(setting_master->help());
        }

        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_world_radius(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("world_radius") != 1)
        {
            return nullptr;
        }

        datatypes::AnyValue* world_radius_any_value = &setting_master->setting_pointer_map["world_radius"]->setting_value;

        if (world_radius_any_value == nullptr || world_radius_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        universe->world_radius = world_radius_any_value->float_value;
        return nullptr;
    }

    datatypes::AnyValue* SettingMaster::activate_background_color(ontology::Universe* universe, config::SettingMaster* setting_master)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        SettingMaster* setting_master_pointer = universe->setting_master_pointer;

        if (setting_master_pointer == nullptr)
        {
            return nullptr;
        }

        if (setting_master_pointer->setting_pointer_map.count("red") != 1 ||
                setting_master_pointer->setting_pointer_map.count("green") != 1 ||
                setting_master_pointer->setting_pointer_map.count("blue") != 1 ||
                setting_master_pointer->setting_pointer_map.count("alpha") != 1)
        {
            return nullptr;
        }

        // red.
        datatypes::AnyValue* red_any_value = &setting_master_pointer->setting_pointer_map["red"]->setting_value;

        if (red_any_value == nullptr || red_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf red = static_cast<GLclampf>(red_any_value->float_value);

        // green.
        datatypes::AnyValue* green_any_value = &setting_master_pointer->setting_pointer_map["green"]->setting_value;

        if (green_any_value == nullptr || green_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf green = static_cast<GLclampf>(green_any_value->float_value);

        // blue.
        datatypes::AnyValue* blue_any_value = &setting_master_pointer->setting_pointer_map["blue"]->setting_value;

        if (blue_any_value == nullptr || blue_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf blue = static_cast<GLclampf>(blue_any_value->float_value);

        // alpha.
        datatypes::AnyValue* alpha_any_value = &setting_master_pointer->setting_pointer_map["alpha"]->setting_value;

        if (alpha_any_value == nullptr || alpha_any_value->type != datatypes::FLOAT)
        {
            return nullptr;
        }

        GLclampf alpha = static_cast<GLclampf>(alpha_any_value->float_value);

        glClearColor(red, green, blue, alpha);
        return nullptr;
    }
}
