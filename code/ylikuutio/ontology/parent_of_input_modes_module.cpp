// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "parent_of_input_modes_module.hpp"
#include "generic_parent_module.hpp"
#include "universe.hpp"

namespace yli::ontology
{
    class InputMode;

    ParentOfInputModesModule::ParentOfInputModesModule(
            yli::ontology::Universe* universe,
            yli::ontology::Registry* const registry,
            const std::string& name) noexcept
        : GenericParentModule(universe, registry, name)
    {
    }

    void ParentOfInputModesModule::set_active_input_mode(yli::ontology::InputMode* const input_mode)
    {
        if (this->active_input_mode != nullptr)
        {
            this->input_mode_stack.push(this->active_input_mode);
        }

        this->active_input_mode = input_mode;
    }

    yli::ontology::InputMode* ParentOfInputModesModule::get_active_input_mode() const
    {
        return this->active_input_mode;
    }

    void ParentOfInputModesModule::pop_input_mode()
    {
        if (!this->input_mode_stack.empty())
        {
            this->active_input_mode = this->input_mode_stack.top();
            this->input_mode_stack.pop();
        }
    }

    yli::input::InputMethod ParentOfInputModesModule::get_input_method() const
    {
        return this->input_method;
    }
}
