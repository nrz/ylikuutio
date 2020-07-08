// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "setting.hpp"
#include "entity.hpp"
#include "universe.hpp"
#include "console.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;

    void Setting::bind_to_parent()
    {
        // Requirements:
        // `this->parent` must not be `nullptr`.

        yli::ontology::Entity* const entity = this->parent;

        if (entity == nullptr)
        {
            std::cerr << "ERROR: `Setting::bind_to_parent`: `entity` is `nullptr`!\n";
            return;
        }

        // Get `childID` from `Entity` and set pointer to this `Setting`.
        entity->bind_setting(this);
    }

    Setting::~Setting()
    {
        // destructor.
        std::cout << "This `Setting` will be destroyed.\n";

        if (this->parent == nullptr)
        {
            return;
        }

        this->parent->unbind_setting(this->childID, this->local_name);
    }

    yli::ontology::Entity* Setting::get_parent() const
    {
        return this->parent;
    }

    std::size_t Setting::get_number_of_children() const
    {
        return 0; // `Setting` has no children.
    }

    std::size_t Setting::get_number_of_descendants() const
    {
        return 0; // `Setting` has no children.
    }

    std::string Setting::help() const
    {
        // this function returns the help string for this setting.
        std::string help_string = this->local_name + " TODO: create helptext for " + this->local_name;
        return help_string;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::get()
    {
        if (this->parent == nullptr)
        {
            return nullptr;
        }

        if (this->read_callback == nullptr)
        {
            return this->setting_value;
        }

        return this->read_callback(this->parent);
    }

    void Setting::set(std::shared_ptr<yli::data::AnyValue> new_value)
    {
        if (this->setting_value == nullptr || this->parent == nullptr)
        {
            return;
        }

        this->setting_value = new_value;

        if (this->activate_callback != nullptr)
        {
            this->activate_callback(this->parent, this);
        }
    }

    void Setting::set(const std::string& new_value)
    {
        if (this->setting_value == nullptr || this->parent == nullptr)
        {
            return;
        }

        this->setting_value->set_new_value(new_value);

        if (this->activate_callback != nullptr)
        {
            this->activate_callback(this->parent, this);
        }
    }

    // Public callbacks.

    std::shared_ptr<yli::data::AnyValue> Setting::set2(
            yli::ontology::Setting* const setting,
            std::shared_ptr<std::string> new_value)
    {
        // Usage:
        // to set variable: set2 <variable-name> <setting-value>

        if (setting == nullptr || new_value == nullptr)
        {
            return nullptr;
        }

        // Set a new value and call activate callback if there is such.
        setting->set(*new_value);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::set3(
            yli::ontology::Entity* const context,         // A context is needed so that correct `Setting` is bound to the function call.
            yli::ontology::Setting* const setting,
            std::shared_ptr<std::string> new_value)
    {
        // Usage:
        // to set variable:       set3 <entity-name> <variable-name> <setting-value>

        // Set a new value and call activate callback if there is such.
        return yli::ontology::Setting::set2(setting, new_value);
    }

    std::shared_ptr<yli::data::AnyValue> Setting::print_value1(
            yli::ontology::Console* const console,
            yli::ontology::Universe* const context, // A context is needed so that correct `Setting` is bound to the function call.
            yli::ontology::Setting* const setting)
    {
        // Usage:
        // to get variable value: get1 <variable-name>

        return yli::ontology::Setting::print_value2(console, context, setting);
    }

    std::shared_ptr<yli::data::AnyValue> Setting::print_value2(
            yli::ontology::Console* const console,
            yli::ontology::Entity* const context,  // A context is needed so that correct `Setting` is bound to the function call.
            yli::ontology::Setting* const setting)
    {
        // Usage:
        // to get variable value: get2 <entity-name> <variable-name>

        if (console == nullptr || context == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> setting_value_shared_ptr = setting->get();

        if (setting_value_shared_ptr == nullptr)
        {
            return nullptr;
        }

        console->print_text(setting_value_shared_ptr->get_string());
        return nullptr;
    }

    // Public callbacks end here.

    void Setting::activate()
    {
        if (this->activate_callback != nullptr)
        {
            this->activate_callback(this->parent, this);
        }
    }
}
