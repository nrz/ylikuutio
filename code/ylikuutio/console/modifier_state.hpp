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

#ifndef YLIKUUTIO_MODIFIER_STATE_HPP_INCLUDED
#define YLIKUUTIO_MODIFIER_STATE_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::console
{
    static const uint32_t left_ctrl   = 1;
    static const uint32_t right_ctrl  = 1 << 1;
    static const uint32_t left_alt    = 1 << 2;
    static const uint32_t right_alt   = 1 << 3;
    static const uint32_t left_shift  = 1 << 4;
    static const uint32_t right_shift = 1 << 5;

    enum ModifierState : uint32_t
    {
        LEFT_CTRL = left_ctrl,
        RIGHT_CTRL = right_ctrl,
        LEFT_ALT = left_alt,
        RIGHT_ALT = right_alt,
        LEFT_SHIFT = left_shift,
        RIGHT_SHIFT = right_shift,
    };
}

#endif
