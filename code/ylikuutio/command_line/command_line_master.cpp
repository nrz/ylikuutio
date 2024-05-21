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

#include "command_line_master.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cerr
#include <limits>        // std::numeric_limits
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::command_line
{
    CommandLineMaster::CommandLineMaster(const int argc, const char* const argv[])
    {
        if (argv == nullptr)
        {
            // Entrypoint code expects that arguments are valid.
            this->are_arguments_valid = true;
            return;
        }

        this->argc = argc;
        this->arg_vector.assign(argv + 1, argv + argc); // Copy all arguments except the executable name.
        this->are_arguments_valid = true;               // Arguments are valid if their syntax is valid.
        bool is_previous_argument_available = false;
        std::string previous_argument = ""; // dummy value.

        // Go through the command line arguments and store the keys and values.
        for (std::vector<std::string>::const_iterator it = this->arg_vector.begin(); it != this->arg_vector.end(); ++it)
        {
            const std::string argument = *it;

            // The following rules apply to the arguments (excluding the executable name which is in `argv[0]`):
            //
            // If the argument begins with 3 or more dashes (`---`), then ignore that argument, and mark arguments as invalid.
            // If the argument begins with exactly 2 dashes (`--`), then leave those dashes out of the argument key.
            // If the argument begins with exactly 1 dash (`-`), then each char after `-` is an argument key.
            // If the argument does not begin with a dash and is the 1st argument, then ignore that argument and mark arguments as invalid.
            // If the argument does not begin with a dash and the previous argument contained `=`, then ignore that argument and mark arguments as invalid.
            // If the argument does not begin with a dash and there is previous argument available, use current argument as the value for the previous argument.
            // If the argument contains `=`, then use the chars before `=` as the argument key, and chars after `=` as the value.

            std::size_t n_leading_dashes = 0;
            std::size_t index_of_equal_sign = std::numeric_limits<std::size_t>::max(); // maximum value here means "not found yet".

            // count the number of leading dashes and check the location of potential equal sign.
            for (std::size_t i = 0; i < argument.size(); i++)
            {
                if (i == n_leading_dashes && argument[i] == '-')
                {
                    n_leading_dashes++;
                }
                else if (argument[i] == '=')
                {
                    // only first equal sign `=` matters.
                    // the rest equal signs (if any) are part of the value.
                    index_of_equal_sign = i;
                    break;
                }
            }

            if (n_leading_dashes == 0 && is_previous_argument_available)
            {
                this->arg_map[previous_argument] = argument;
                is_previous_argument_available = false;
                continue;
            }
            else if (n_leading_dashes == 0)
            {
                // there is no previous argument available for this value.
                // therefore arguments are invalid.
                this->are_arguments_valid = false;
                continue;
            }

            // arguments without dashes are processed already.

            if (is_previous_argument_available)
            {
                // there was no value available for the previous argument.
                this->arg_map[previous_argument] = "";
            }

            is_previous_argument_available = false;

            if (n_leading_dashes > 2)
            {
                // an argument beginning with `---` is invalid, therefore it is discarded.
                this->are_arguments_valid = false;
                continue;
            }

            if (index_of_equal_sign == std::numeric_limits<std::size_t>::max())
            {
                // no equal sign.

                if (n_leading_dashes == 2)
                {
                    // the string without dashes is the key, the value is an empty string.
                    const std::string string_without_dashes = argument.substr(2); // the string without 2 leading dashes.
                    previous_argument = string_without_dashes;
                    is_previous_argument_available = true;
                }
                else
                {
                    // 1 leading dash.
                    // each character is a key, concatenated with a leading dash.
                    // the last one may have a value.
                    for (std::size_t j = 1; j + 1 < argument.size(); j++)
                    {
                        std::string current_argument_string = "-";
                        const std::string current_char_string = argument.substr(j, 1);
                        current_argument_string.append(current_char_string);
                        this->arg_map[current_argument_string] = "";
                    }

                    previous_argument = argument[argument.size() - 1];
                    is_previous_argument_available = true;
                }
            }
            else
            {
                // there was at least 1 equal sign.

                if (n_leading_dashes == 2)
                {
                    // the characters between leading dashes and the equal sign are the key.
                    // the characters after the equal sign are the value.
                    const std::string key = argument.substr(2, index_of_equal_sign - 2); // the characters between leading dashes and the equal sign.
                    const std::string value = argument.substr(index_of_equal_sign + 1);
                    this->arg_map[key] = value;
                }
                else
                {
                    // 1 leading dash.
                    // each character is a key, concatenated with a leading dash.
                    // the value of the last key is the characters after the equal sign.
                    // the value of the other keys is an empty string.
                    for (std::size_t j = 1; j < index_of_equal_sign; j++)
                    {
                        std::string current_argument_string = "-";
                        const std::string current_char_string = argument.substr(j, 1);
                        current_argument_string.append(current_char_string);

                        if (j < index_of_equal_sign - 1)
                        {
                            this->arg_map[current_argument_string] = "";
                        }
                        else
                        {
                            const std::string value = argument.substr(index_of_equal_sign + 1);
                            this->arg_map[current_argument_string] = value;
                        }
                    }
                }
            }
        }

        if (is_previous_argument_available)
        {
            this->arg_map[previous_argument] = "";
        }
    }

    bool CommandLineMaster::get_are_arguments_valid() const
    {
        return this->are_arguments_valid;
    }

    bool CommandLineMaster::check_keys(const std::vector<std::string>& valid_keys) const
    {
        return this->get_invalid_keys(valid_keys).empty(); // Keys are valid if all keys belong to valid keys.
    }

    std::vector<std::string> CommandLineMaster::get_invalid_keys(const std::vector<std::string>& valid_keys) const
    {
        // This function returns the keys that are invalid.
        // Keys are valid if all keys belong to valid keys.
        // Note that arguments entered with invalid syntax are not keys.

        std::vector<std::string> invalid_keys;

        const std::vector<std::string> args = yli::map::get_keys(this->arg_map);

        for (auto arg_it = args.begin(); arg_it != args.end(); ++arg_it)
        {
            bool is_valid_key = false;

            for (auto valid_keys_it = valid_keys.begin(); valid_keys_it != valid_keys.end(); ++valid_keys_it)
            {
                if (*arg_it == *valid_keys_it)
                {
                    is_valid_key = true;
                    break;
                }
            }

            if (!is_valid_key)
            {
                invalid_keys.emplace_back(*arg_it);
            }
        }

        return invalid_keys;
    }

    bool CommandLineMaster::is_key(const std::string& key) const
    {
        return this->arg_map.count(key) == 1;
    }

    std::string CommandLineMaster::get_value(const std::string& key) const
    {
        if (this->arg_map.count(key) == 1)
        {
            return this->arg_map.at(key);
        }

        return "";
    }

    void CommandLineMaster::print_keys() const
    {
        if (this->argc > 1)
        {
            // Print command line arguments (without the executable name string).

            for (std::string argument : arg_vector)
            {
                std::cout << argument << "\n";
            }
        }
        else
        {
            std::cout << "no command line arguments.\n";
        }
    }

    void CommandLineMaster::print_keys_and_values() const
    {
        yli::map::print_keys_and_values<std::string>(this->arg_map);
    }
}
