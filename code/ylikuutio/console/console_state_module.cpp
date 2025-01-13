// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "console_state_module.hpp"
#include "console_state.hpp"

namespace yli::console
{
    class CurrentInput;
    class TempInput;

    void ConsoleStateModule::enter_current_input()
    {
        this->state = ConsoleState::IN_CURRENT_INPUT;
    }

    void ConsoleStateModule::enter_historical_input()
    {
        this->state = ConsoleState::IN_HISTORICAL_INPUT;
    }

    void ConsoleStateModule::enter_temp_input()
    {
        this->state = ConsoleState::IN_TEMP_INPUT;
    }

    void ConsoleStateModule::enter_scrollback_buffer()
    {
        this->state = ConsoleState::IN_SCROLLBACK_BUFFER;
    }

    void ConsoleStateModule::register_current_input(CurrentInput* const current_input)
    {
        this->current_input = current_input;
    }

    void ConsoleStateModule::register_temp_input(TempInput* const temp_input)
    {
        this->temp_input = temp_input;
    }

    yli::console::ConsoleState ConsoleStateModule::get() const
    {
        return this->state;
    }

    CurrentInput* ConsoleStateModule::get_current_input() const
    {
        return this->current_input;
    }

    TempInput* ConsoleStateModule::get_temp_input() const
    {
        return this->temp_input;
    }
}
