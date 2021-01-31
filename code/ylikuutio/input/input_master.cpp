// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#include "input_master.hpp"
#include "input_mode.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace yli::input
{
    void InputMaster::bind_input_mode(yli::input::InputMode* const input_mode)
    {
        // get `childID` from `InputMaster` and set pointer to `input_mode`.
        yli::hierarchy::bind_child_to_parent<yli::input::InputMode*>(
                input_mode,
                this->input_mode_pointer_vector,
                this->free_input_modeID_queue,
                this->number_of_input_modes);
    }

    InputMaster::InputMaster(yli::ontology::Universe* const universe)
        : universe { universe }
    {
        // constructor.

        this->input_method = yli::input::InputMethod::KEYBOARD;
    }

    InputMaster::~InputMaster()
    {
        // destructor.

        // destroy all `InputMode`s of this `InputMaster`.
        yli::hierarchy::delete_children<yli::input::InputMode*>(this->input_mode_pointer_vector, this->number_of_input_modes);
    }

    yli::input::InputMode* InputMaster::create_input_mode()
    {
        return new yli::input::InputMode(this);
    }

    void InputMaster::set_active_input_mode(yli::input::InputMode* const input_mode)
    {
        if (this->active_input_mode != nullptr)
        {
            this->input_mode_stack.push(this->active_input_mode);
        }

        this->active_input_mode = input_mode;
    }

    yli::input::InputMode* InputMaster::get_active_input_mode() const
    {
        return this->active_input_mode;
    }

    void InputMaster::pop_input_mode()
    {
        if (!this->input_mode_stack.empty())
        {
            this->active_input_mode = this->input_mode_stack.top();
            this->input_mode_stack.pop();
        }
    }

    yli::input::InputMethod InputMaster::get_input_method() const
    {
        return this->input_method;
    }
}
