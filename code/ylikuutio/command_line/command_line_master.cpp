#include "command_line_master.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli
{
    namespace command_line
    {
        CommandLineMaster::CommandLineMaster(const int argc, const char* argv[])
        {
            this->argc = argc;
            this->arg_vector.assign(argv + 1, argv + argc);
            bool is_previous_argument_available = false;
            std::string previous_argument = ""; // dummy value.

            // Go through the command line arguments and store the keys and values.
            for (std::vector<std::string>::const_iterator it = this->arg_vector.begin(); it != this->arg_vector.end(); it++)
            {
                const std::string argument = *it;

                // If the argument begins with `---`, the the argument is invalid.
                // If the argument begins with `--`, then leave those out of the argument key.
                // If the argument begins with `-`, then each char after `-` is an argument key.
                // If the argument begins with something else and it the 1st argument, discard the argument.
                // If the argument begins with something else and the previous argument contained `=`, discard the current argument.
                // If the argument begins with something else, use it as a value for the previous argument.
                // If the argument contains `=`, then use the value `=` as the value, and the argument key is the char or chars before `=`.

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
                    continue;
                }

                if (is_previous_argument_available)
                {
                    // there was no value available for the previous argument.
                    this->arg_map[previous_argument] = "";
                }

                // arguments without dashes are processed already.
                is_previous_argument_available = false;

                if (n_leading_dashes > 2)
                {
                    // an argument beginning with `---` is invalid, therefore it is discarded.
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
                        for (std::size_t j = 1; j < argument.size() - 1; j++)
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

        bool CommandLineMaster::is_key(const std::string& key)
        {
            return this->arg_map.count(key) == 1;
        }

        std::string CommandLineMaster::get_value(const std::string& key)
        {
            if (this->arg_map.count(key) == 1)
            {
                return this->arg_map[key];
            }

            return "";
        }

        void CommandLineMaster::print_keys()
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

        void CommandLineMaster::print_keys_and_values()
        {
            yli::map::print_keys_and_values<std::string>(&this->arg_map);
        }
    }
}
