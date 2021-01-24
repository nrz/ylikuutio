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

#ifndef __YLIKUUTIO_SNIPPETS_BACKGROUND_COLOR_SNIPPETS_HPP_INCLUDED
#define __YLIKUUTIO_SNIPPETS_BACKGROUND_COLOR_SNIPPETS_HPP_INCLUDED

namespace yli::ontology
{
    class Universe;
}

namespace yli::snippets
{
    void set_background_colors(yli::ontology::Universe* const universe, const float red, const float green, const float blue, const float alpha);
}

#endif
