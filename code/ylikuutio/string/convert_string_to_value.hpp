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

#ifndef YLIKUUTIO_STRING_CONVERT_STRING_TO_VALUE_HPP_INCLUDED
#define YLIKUUTIO_STRING_CONVERT_STRING_TO_VALUE_HPP_INCLUDED

// Include standard headers
#include <cstdint>     // std::int8_t, std::int16_t, std::int32_t, std::int64_t, std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t
#include <cstdlib>     // std::strtod, std::strtof, std::strtoll, std::strtoull
#include <iostream>    // std::cerr
#include <limits>      // std::numeric_limits
#include <optional>    // std::nullopt, std::optional
#include <string>      // std::string
#include <string_view> // std::string_view

namespace yli::string
{
    template<typename T>
    std::optional<T> convert_string_to_signed_integer(const std::string_view string)
    {
        const std::int64_t value = std::strtoll(std::string(string).c_str(), nullptr, 10); // base 10.

        if (value < std::numeric_limits<T>::min())
        {
            std::cerr << "ERROR: `yli::string::convert_string_to_signed_integer`: value " << value <<
                    " is too small for the type!\n";
            return std::nullopt;
        }
        if (value > std::numeric_limits<T>::max())
        {
            std::cerr << "ERROR: `yli::string::convert_string_to_signed_integer`: value " << value <<
                    " is too big for the type!\n";
            return std::nullopt;
        }

        return static_cast<T>(value);
    }

    template<typename T>
    std::optional<T> convert_string_to_unsigned_integer(std::string_view string)
    {
        const std::uint64_t value = std::strtoull(std::string(string).c_str(), nullptr, 10); // base 10.

        if (value > std::numeric_limits<T>::max())
        {
            std::cerr << "ERROR: `yli::string::convert_string_to_unsigned_integer`: value " << value <<
                    " is too big for the type!\n";
            return std::nullopt;
        }

        return static_cast<T>(value);
    }

    template<typename T>
    std::optional<T> convert_string_to_value(std::string_view string) = delete;

    template<>
    inline std::optional<std::int8_t> convert_string_to_value<std::int8_t>(const std::string_view string)
    {
        return convert_string_to_signed_integer<std::int8_t>(string);
    }

    template<>
    inline std::optional<std::uint8_t> convert_string_to_value<std::uint8_t>(const std::string_view string)
    {
        return convert_string_to_unsigned_integer<std::uint8_t>(string);
    }

    template<>
    inline std::optional<std::int16_t> convert_string_to_value<std::int16_t>(const std::string_view string)
    {
        return convert_string_to_signed_integer<std::int16_t>(string);
    }

    template<>
    inline std::optional<std::uint16_t> convert_string_to_value<std::uint16_t>(const std::string_view string)
    {
        return convert_string_to_unsigned_integer<std::uint16_t>(string);
    }

    template<>
    inline std::optional<std::int32_t> convert_string_to_value<std::int32_t>(const std::string_view string)
    {
        return convert_string_to_signed_integer<std::int32_t>(string);
    }

    template<>
    inline std::optional<std::uint32_t> convert_string_to_value<std::uint32_t>(const std::string_view string)
    {
        return convert_string_to_unsigned_integer<std::uint32_t>(string);
    }

    template<>
    inline std::optional<std::int64_t> convert_string_to_value<std::int64_t>(const std::string_view string)
    {
        return convert_string_to_signed_integer<std::int64_t>(string);
    }

    template<>
    inline std::optional<std::uint64_t> convert_string_to_value<std::uint64_t>(const std::string_view string)
    {
        return convert_string_to_unsigned_integer<std::uint64_t>(string);
    }

    template<>
    inline std::optional<float> convert_string_to_value<float>(const std::string_view string)
    {
        return std::strtof(std::string(string).c_str(), nullptr);
    }

    template<>
    inline std::optional<double> convert_string_to_value<double>(const std::string_view string)
    {
        return std::strtod(std::string(string).c_str(), nullptr);
    }
}

#endif
