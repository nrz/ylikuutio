// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "master_of_input_modes_module.hpp"
#include "generic_master_module.hpp"
#include "input_mode.hpp"

// Include standard headers
#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace yli::ontology
{
    class Registry;
    class Entity;

    MasterOfInputModesModule::MasterOfInputModesModule(
            Entity* const generic_master,
            Registry* const registry,
            const std::string& name) noexcept
        : GenericMasterModule(generic_master, registry, name)
    {
    }

    bool MasterOfInputModesModule::has_current_input_mode() const
    {
        return this->current_input_mode != nullptr;
    }

    void MasterOfInputModesModule::set_current_input_mode(InputMode* const input_mode)
    {
        this->current_input_mode = input_mode;
    }

    InputMode* MasterOfInputModesModule::get_current_input_mode() const
    {
        return this->current_input_mode;
    }

    void MasterOfInputModesModule::activate_current_input_mode()
    {
        if (this->current_input_mode == nullptr) [[unlikely]]
        {
            throw std::runtime_error(
                    "ERROR: `MasterOfInputModesModule::activate_current_input_mode`: `this->current_input_mode` is `nullptr`!");
        }
        else
        {
            this->current_input_mode->activate();
        }
    }

    void MasterOfInputModesModule::deactivate_current_input_mode()
    {
        if (this->current_input_mode == nullptr) [[unlikely]]
        {
            throw std::runtime_error(
                    "ERROR: `MasterOfInputModesModule::deactivate_current_input_mode`: `this->current_input_mode` is `nullptr`!");
        }
        else
        {
            this->current_input_mode->deactivate();
        }
    }
}
