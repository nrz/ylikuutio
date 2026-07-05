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

#ifndef YLIKUUTIO_STRING_YLIKUUTIO_STRING_HPP_INCLUDED
#define YLIKUUTIO_STRING_YLIKUUTIO_STRING_HPP_INCLUDED

// Include standard headers
#include <cstddef>     // std::size_t
#include <string>      // std::string
#include <string_view> // std::basic_string_view
#include <vector>      // std::vector

namespace yli::string
{
    template<typename Alloc, template<typename, typename> typename T1>
    std::string convert_char_container_to_std_string(
        const T1<char, Alloc>& char_container,
        const std::size_t first_line_length,
        const std::size_t line_length)
    {
        std::string my_string;
        std::size_t remaining_characters_on_this_line = first_line_length;

        for (auto it = char_container.begin(); it != char_container.end(); ++it)
        {
            if (remaining_characters_on_this_line == 0)
            {
                my_string.push_back('\\');
                my_string.push_back('n');
                remaining_characters_on_this_line = line_length;
            }

            my_string.push_back(*it);
            remaining_characters_on_this_line--;
        }

        return my_string;
    }

    template<typename Alloc, template<typename, typename> typename T1>
    std::vector<std::string> convert_char_container_to_std_vector_std_string(
        const T1<char, Alloc>& char_container,
        const std::size_t line_length)
    {
        std::vector<std::string> my_vector;
        std::string my_string;
        std::size_t remaining_characters_on_this_line = line_length;

        for (auto it = char_container.begin(); it != char_container.end(); ++it)
        {
            if (remaining_characters_on_this_line == 0)
            {
                my_vector.emplace_back(my_string);
                my_string.clear();
                remaining_characters_on_this_line = line_length;
            }

            my_string.push_back(*it);
            remaining_characters_on_this_line--;
        }

        if (!my_string.empty())
        {
            my_vector.emplace_back(my_string);
        }

        return my_vector;
    }

    template<typename CharType>
    bool check_if_floating_point_string(std::basic_string_view<CharType> my_string,
                                        const std::size_t safe_number_of_chars)
    {
        std::size_t n_chars = 0;

        if (my_string.empty())
        {
            return false;
        }

        bool is_dot_found = false;

        for (std::size_t i = 0; i < my_string.size(); i++)
        {
            // Each of the characters must be one of the following:
            // 0123456789.-
            //
            // Besides, there may be only 1 dot. The dot may not be the last character.
            // Besides, there may be only 1 minus sign. The minus sign must be the first character.

            if (my_string.at(i) == '-' && i == 0)
            {
                // Minus sign is OK.
                continue;
            }

            if (my_string.at(i) == '.')
            {
                if (is_dot_found)
                {
                    // Two or more dots.
                    return false;
                }

                if (i == my_string.size() - 1)
                {
                    // Last character is dot.
                    return false;
                }

                // OK, decimal point here.
                is_dot_found = true;
                continue;
            }

            if (my_string.at(i) < '0' || my_string.at(i) > '9')
            {
                return false;
            }

            if (!is_dot_found)
            {
                if (++n_chars > safe_number_of_chars)
                {
                    // Too many characters, maximum safe number is 38 characters for float, 308 for double.
                    return false;
                }
            }
        }

        return true;
    }

    template<typename CharType>
    bool check_if_signed_integer_string(std::basic_string_view<CharType> my_string)
    {
        if (my_string.empty())
        {
            return false;
        }

        for (std::size_t i = 0; i < my_string.size(); i++)
        {
            // Each of the characters must be one of the following:
            // 0123456789
            if (my_string.at(i) == '-' && i == 0)
            {
                // Minus sign is OK.
                continue;
            }

            if (my_string.at(i) < '0' || my_string.at(i) > '9')
            {
                return false;
            }
        }

        return true;
    }

    template<typename CharType>
    bool check_if_unsigned_integer_string(std::basic_string_view<CharType> my_string)
    {
        if (my_string.empty())
        {
            return false;
        }

        for (std::size_t i = 0; i < my_string.size(); i++)
        {
            // Each of the characters must be one of the following:
            // 0123456789

            if (my_string.at(i) < '0' || my_string.at(i) > '9')
            {
                return false;
            }
        }

        return true;
    }

    template<typename CharType>
    bool check_if_float_string(std::basic_string_view<CharType> my_string)
    {
        constexpr std::size_t maximum_safe_length_for_float_string = 38;
        return check_if_floating_point_string(my_string, maximum_safe_length_for_float_string);
    }

    template<typename CharType>
    bool check_if_double_string(std::basic_string_view<CharType> my_string)
    {
        constexpr std::size_t maximum_safe_length_for_double_string = 308;
        return check_if_floating_point_string(my_string, maximum_safe_length_for_double_string);
    }
}

#endif
