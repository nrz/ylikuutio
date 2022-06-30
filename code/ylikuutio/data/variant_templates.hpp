// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_DATA_VARIANT_TEMPLATES_HPP_INCLUDED
#define __YLIKUUTIO_DATA_VARIANT_TEMPLATES_HPP_INCLUDED

#include "any_value.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <variant>  // std::holds_alternative, std::variant

namespace yli::data
{
    // Get a variant based on `std::variant` type, a type string and a value string.
    template<typename... V>
        std::variant<V...> get_variant(const std::string& type, const std::string& value_string)
        {
            std::stringstream value_stringstream;
            std::variant<V...> my_variant;

            if (type == "bool")
            {
                if (value_string == "true")       // Ylikuutio is case sensitive!
                {
                    my_variant = true;
                }
                else if (value_string == "false") // Ylikuutio is case sensitive!
                {
                    my_variant = false;
                }
            }
            else if (type == "char")
            {
                if (value_string.size() == 1)
                {
                    my_variant = value_string[0];
                }
            }
            else if (type == "float")
            {
                if (yli::string::check_if_float_string(value_string))
                {
                    float float_value;
                    value_stringstream << value_string;
                    value_stringstream >> float_value;
                    my_variant = float_value;
                }
            }
            else if (type == "double")
            {
                if (yli::string::check_if_double_string(value_string))
                {
                    double double_value;
                    value_stringstream << value_string;
                    value_stringstream >> double_value;
                    my_variant = double_value;
                }
            }
            else if (type == "int32_t")
            {
                if (yli::string::check_if_signed_integer_string(value_string))
                {
                    int32_t int32_t_value;
                    value_stringstream << value_string;
                    value_stringstream >> int32_t_value;
                    my_variant = int32_t_value;
                }
            }
            else if (type == "uint32_t")
            {
                if (yli::string::check_if_unsigned_integer_string(value_string))
                {
                    uint32_t uint32_t_value;
                    value_stringstream << value_string;
                    value_stringstream >> uint32_t_value;
                    my_variant = uint32_t_value;
                }
            }

            return my_variant;
        }
}

#endif
