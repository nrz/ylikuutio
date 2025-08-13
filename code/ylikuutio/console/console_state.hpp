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

#ifndef YLIKUUTIO_CONSOLE_STATE_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_STATE_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::console
{
    static const uint32_t active               = 1;
    static const uint32_t in_scrollback_buffer = 1 << 1;
    static const uint32_t in_current_input     = 1 << 2;
    static const uint32_t in_historical_input  = 1 << 3;
    static const uint32_t in_temp_input        = 1 << 4;

    enum ConsoleState : uint32_t
    {
        INACTIVE_IN_CURRENT_INPUT = in_current_input,            // initial state: can activate -> current input
        INACTIVE_IN_HISTORICAL_INPUT = in_historical_input,      // can activate -> historical input
        INACTIVE_IN_TEMP_INPUT = in_temp_input,                  // can activate -> temp input
        INACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_CURRENT_INPUT = in_scrollback_buffer | in_current_input,       // can activate -> scrollback buffer w/current input
        INACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT = in_scrollback_buffer | in_historical_input, // can activate -> scrollback buffer w/historical input
        INACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT = in_scrollback_buffer | in_temp_input,             // can activate -> scrollback buffer w/temp input
        ACTIVE_IN_CURRENT_INPUT = active | in_current_input,       // active in current input
        ACTIVE_IN_HISTORICAL_INPUT = active | in_historical_input, // active in historical input
        ACTIVE_IN_TEMP_INPUT = active | in_temp_input,             // active in temp input
        ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_CURRENT_INPUT = active | in_scrollback_buffer | in_current_input,       // active in scrollback buffer w/current input
        ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT = active | in_scrollback_buffer | in_historical_input, // active in scrollback buffer w/historical input
        ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT = active | in_scrollback_buffer | in_temp_input              // active in scrollback buffer w/temp input
    };
}

#endif
