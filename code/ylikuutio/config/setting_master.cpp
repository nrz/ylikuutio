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

#include "setting_master.hpp"
#include "setting.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <variant>       // std::variant
#include <vector>        // std::vector

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Console;
}

namespace yli::config
{
    struct SettingStruct;

    SettingMaster::SettingMaster(yli::ontology::Entity* const entity)
    {
        // constructor.
        this->parent = entity;
        this->number_of_settings = 0;
    }

    SettingMaster::~SettingMaster()
    {
        // destructor.

        // destroy all `Setting`s of this `SettingMaster`.
        std::cout << "All `Setting`s of this `SettingMaster` will be destroyed.\n";
        yli::hierarchy::delete_children<yli::config::Setting*>(this->setting_pointer_vector, this->number_of_settings);
    }

    void SettingMaster::create_setting(const yli::config::SettingStruct& setting_struct)
    {
        new yli::config::Setting(this, setting_struct);
    }

    bool SettingMaster::is_setting(const std::string& setting_name) const
    {
        return this->setting_pointer_map.count(setting_name) == 1;
    }

    std::string SettingMaster::help() const
    {
        std::string help_string = "TODO: create general helptext";
        return help_string;
    }

    std::string SettingMaster::help(const std::string& setting_name) const
    {
        if (this->is_setting(setting_name))
        {
            yli::config::Setting* setting = this->setting_pointer_map.at(setting_name);

            if (setting != nullptr)
            {
                return setting->help();
            }
        }
        return this->help();
    }

    bool SettingMaster::set(const std::string& setting_name, std::shared_ptr<yli::data::AnyValue> setting_new_any_value)
    {
        if (!this->is_setting(setting_name))
        {
            return false;
        }

        // OK, this is a valid variable name.
        // Set the variable value and activate it by
        // calling the corresponding activate callback.
        yli::config::Setting* setting = this->setting_pointer_map[setting_name];

        setting->set(setting_new_any_value);
        return true;
    }

    yli::config::Setting* SettingMaster::get(const std::string& setting_name) const
    {
        if (this->setting_pointer_map.count(setting_name) != 1)
        {
            return nullptr;
        }

        return this->setting_pointer_map.at(setting_name);
    }

    // public callbacks.

    std::shared_ptr<yli::data::AnyValue> SettingMaster::print_settings0(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console)
    {
        if (universe == nullptr || console == nullptr)
        {
            return nullptr;
        }

        // Print global variable names.
        yli::config::SettingMaster* setting_master = universe->get_setting_master();

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        yli::map::print_keys_to_console<yli::config::Setting*>(setting_master->setting_pointer_map, console);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> SettingMaster::print_settings1(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console,
            yli::ontology::Entity* const entity)
    {
        if (universe == nullptr || console == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        // Print the variable names of the `Entity`.

        yli::config::SettingMaster* const setting_master = entity->get_setting_master();

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        yli::map::print_keys_to_console<yli::config::Setting*>(setting_master->setting_pointer_map, console);

        return nullptr;
    }
}
