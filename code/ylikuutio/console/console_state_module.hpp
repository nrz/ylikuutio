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

#ifndef YLIKUUTIO_CONSOLE_CONSOLE_STATE_MODULE_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_CONSOLE_STATE_MODULE_HPP_INCLUDED

#include "code/ylikuutio/console/console_state.hpp"

namespace yli::console
{
    class CurrentInput;
    class TempInput;

    class ConsoleStateModule
    {
        public:
            void enter_current_input();
            void enter_historical_input();
            void enter_temp_input();
            void enter_scrollback_buffer();

            void register_current_input(CurrentInput* const current_input);
            void register_temp_input(TempInput* const temp_input);

            ConsoleState get() const;
            CurrentInput* get_current_input() const;
            TempInput* get_temp_input() const;

        private:
            ConsoleState state { ConsoleState::NOT_IN_CONSOLE };
            CurrentInput* current_input { nullptr };
            TempInput*    temp_input    { nullptr };
    };
}

#endif
