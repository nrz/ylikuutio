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

#ifndef YLIKUUTIO_DATA_CODEPOINT_HPP_INCLUDED
#define YLIKUUTIO_DATA_CODEPOINT_HPP_INCLUDED

// Include standard headers
#include <compare>  // <=>
#include <stdint.h> // uint32_t

namespace yli::data
{
    struct Codepoint
    {
        explicit Codepoint(const char codepoint)
            : codepoint { static_cast<uint32_t>(codepoint) }
        {
        }

        ~Codepoint() = default;

        Codepoint(const Codepoint& original) = default;
        Codepoint& operator=(const Codepoint&) = default;

        bool operator==(const Codepoint& other) const
        {
            return this->codepoint == other.codepoint;
        }

        bool operator!=(const Codepoint& other) const
        {
            return this->codepoint != other.codepoint;
        }

        uint32_t codepoint;
    };
}

#endif
