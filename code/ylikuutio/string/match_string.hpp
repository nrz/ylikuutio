// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_STRING_MATCH_STRING_HPP_INCLUDED
#define YLIKUUTIO_STRING_MATCH_STRING_HPP_INCLUDED

// Include standard headers
#include <cstddef>     // std::byte, std::size_t
#include <string>      // std::basic_string
#include <string_view> // std::basic_string_view
#include <vector>      // std::vector

namespace yli::string
{
    template<typename CharType>
    bool check_and_report_if_some_string_matches(
        const std::basic_string_view<CharType> data_string,
        const std::size_t data_index,
        const std::vector<std::basic_string<CharType>>& identifier_strings_vector)
    {
        for (const std::basic_string<CharType>& identifier_string : identifier_strings_vector)
        {
            if (data_index + identifier_string.size() > data_string.size())
            {
                // If current `identifier_string` can't fit in the memory region,
                // proceed to the next `identifier_string`, if there is any left.
                continue;
            }

            if (data_string.compare(data_index, identifier_string.size(), identifier_string) == 0)
            {
                return true;
            }
        }

        return false;
    }
}

#endif
