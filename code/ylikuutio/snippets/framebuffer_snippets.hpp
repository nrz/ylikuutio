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

#ifndef __FRAMEBUFFER_SNIPPETS_HPP_INCLUDED
#define __FRAMEBUFFER_SNIPPETS_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::config
{
    class SettingMaster;
}

namespace yli::snippets
{
    void set_framebuffer_size(yli::config::SettingMaster* setting_master, const uint32_t framebuffer_width, const uint32_t framebuffer_height);
}

#endif
