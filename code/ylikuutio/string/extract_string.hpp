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

#ifndef YLIKUUTIO_STRING_EXTRACT_STRING_HPP_INCLUDED
#define YLIKUUTIO_STRING_EXTRACT_STRING_HPP_INCLUDED

#include "convert_string_to_value.hpp"

// Include standard headers
#include <cstddef>     // std::size_t
#include <cstdint>     // std::int32_t, std::uint32_t
#include <ios>         // std::hex
#include <iostream>    // std::cout, std::cerr
#include <optional>    // std::nullopt, std::optional
#include <string>      // std::basic_string, std::string
#include <sstream>     // std::stringstream
#include <string_view> // std::basic_string_view, std::string_view

namespace yli::string
{
    // All string extraction functions of `yli::string` advance either
    // `data_index` or `src_data_pointer` to the first character that
    // does not belong in the extracted string.
    // If no string is extracted, then `data_index` or `src_data_pointer`
    // (according to the function) is not modified.

    template<typename CharType>
    std::basic_string<CharType> extract_string_with_several_endings(
        std::basic_string_view<CharType> data_string,
        std::size_t& data_index,
        std::basic_string_view<CharType> char_end_string)
    {
        // This function copies characters from `src_data_pointer` until a character matches.
        if (data_index >= data_string.size())
        {
            return "";
        }

        std::size_t original_data_index = data_index;

        while (data_index < data_string.size())
        {
            typename std::basic_string_view<CharType>::const_iterator end_char_it = char_end_string.begin();
            const CharType current_char = data_string.at(data_index);

            // Check if current character is any of the ending characters.
            while (end_char_it != char_end_string.end())
            {
                if (current_char == *end_char_it)
                {
                    return std::basic_string<CharType>(
                        data_string.substr(original_data_index, data_index - original_data_index));
                }
                ++end_char_it;
            }

            // OK, current character is not any of the ending characters.
            data_index++;
        }

        return std::basic_string<CharType>(data_string.substr(original_data_index, data_index - original_data_index));
    }

    template<typename CharType>
    std::basic_string<CharType> extract_last_part_of_string(
        std::basic_string_view<CharType> data_string,
        const CharType separator)
    {
        auto separator_it = data_string.end(); // by default no last part.

        for (auto it = data_string.begin(); it != data_string.end(); ++it)
        {
            if (*it == separator)
            {
                separator_it = it;
            }
        }

        if (separator_it == data_string.end())
        {
            return "";
        }

        ++separator_it;
        return std::basic_string<CharType>(separator_it, data_string.end());
    }

    template<typename CharType>
    std::basic_string<CharType> extract_string(
        std::basic_string_view<CharType> data_string,
        std::size_t& data_index,
        const CharType separator)
    {
        return extract_string_with_several_endings<CharType>(
            data_string,
            data_index,
            std::basic_string<CharType>(1, separator));
    }

    template<typename CharType>
    std::optional<std::int32_t> extract_unicode_value_from_string(const CharType*& unicode_char_pointer)
    {
        if (*unicode_char_pointer == '\0')
        {
            ++unicode_char_pointer;
            std::cerr << "ERROR: `yli::string::extract_unicode_value_from_string`: Unicode can not begin with \\0!\n";
            return 0xdfff; // invalid unicode!
        }

        if (*unicode_char_pointer != '&')
        {
            // it's just a character, so return its value,
            // and advance to the next character.
            return static_cast<std::int32_t>(*unicode_char_pointer++);
        }

        if (*++unicode_char_pointer != '#')
        {
            // not valid format, must begin `"&#x"`.
            ++unicode_char_pointer;
            std::cerr <<
                    "ERROR: `yli::string::extract_unicode_value_from_string`: Unicode string format not supported!\n";
            return 0xdfff; // invalid unicode!
        }

        if (*++unicode_char_pointer != 'x')
        {
            // not valid format, must begin `"&#x"`.
            ++unicode_char_pointer;
            std::cerr <<
                    "ERROR: `yli::string::extract_unicode_value_from_string`: Unicode string format not supported!\n";
            return 0xdfff; // invalid unicode!
        }

        // valid format.
        std::basic_string<CharType> hex_string;

        // unicode string beginning with '&'
        while (*++unicode_char_pointer != ';')
        {
            if (*unicode_char_pointer == '\0')
            {
                std::cerr << "Error: Null character \\0 reached before end of Unicode string!\n";
                return 0xdfff; // invalid unicode!
            }

            hex_string.append(unicode_char_pointer);
        }

        // Advance to the next character.
        ++unicode_char_pointer;

        // convert hexadecimal string to signed integer.
        // http://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer/1070499#1070499
        std::uint32_t unicode_value;
        std::stringstream unicode_stringstream;
        unicode_stringstream << std::hex << hex_string;
        unicode_stringstream >> unicode_value;
        return unicode_value;
    }

    template<typename CharType, typename ValueType>
    std::optional<ValueType> extract_value_from_string(
        std::string_view data_string,
        std::size_t& data_index,
        std::string_view char_end_string,
        std::string_view description)
    {
        std::string string = extract_string_with_several_endings<CharType>(
            data_string,
            data_index,
            char_end_string);

        std::optional<ValueType> value = convert_string_to_value<ValueType>(string);

        if (!value)
        {
            std::cerr << "ERROR: `yli::string::extract_value_from_string`: converting string to value failed!\n";
            return std::nullopt;
        }

        if (!description.empty())
        {
            std::cout << description << ": " << *value << "\n";
        }
        return value;
    }

    template<typename CharType, typename ValueType>
    ValueType extract_value_or_throw(
        std::basic_string_view<CharType> data_string,
        std::size_t& data_index,
        std::basic_string_view<CharType> char_end_string,
        std::basic_string_view<CharType> description)
    {
        std::optional<ValueType> value = extract_value_from_string<CharType, ValueType>(
            data_string, data_index, char_end_string, description);

        if (!value)
        {
            throw std::runtime_error("ERROR: `yli::string::extract_value_or_throw`: extracting value failed!");
        }

        return *value;
    }
}

#endif
