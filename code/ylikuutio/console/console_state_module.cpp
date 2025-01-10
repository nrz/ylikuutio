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

    yli::console::ConsoleState ConsoleStateModule::get() const
    {
        return this->state;
    }
}
