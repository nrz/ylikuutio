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

            // Go through the command line arguments and store the keys and values.
            for (const std::string argument : this->arg_vector)
            {
                // If the argument begins with `--`, then leave those out of the argument key.
                // If the argument begins with `-`, then each char after `-` is an argument key.
                // If the argument begins with something else, store the argument key as is.
                // If the argument contains `=`, then use the value `=` as the value, and the argument key is the char or chars before `=`.
                // Multiple `=` in the same argument is an error.

                std::size_t n_leading_dashes = 0;
                std::size_t index_of_equal_sign = std::numeric_limits<std::size_t>::max(); // maximum value here means "not found yet".

                for (std::size_t i = 0; i < argument.size(); i++)
                {
                    if (i == n_leading_dashes && argument[i] == '-')
                    {
                        n_leading_dashes++;
                    }
                    else if (argument[i] == '=')
                    {
                        index_of_equal_sign = i;
                        break;
                    }
                }

                if (index_of_equal_sign == std::numeric_limits<std::size_t>::max())
                {
                    // no equal sign.

                    if (n_leading_dashes != 1)
                    {
                        // the entire string is the key, the value is an empty string.
                        this->arg_map[argument] = "";
                    }
                    else
                    {
                        // each character is a key, concatenated with a leading dash.
                        for (std::size_t j = 1; j < argument.size(); j++)
                        {
                            std::string current_argument_string = "-";
                            const std::string current_char_string = argument.substr(j, 1);
                            current_argument_string.append(current_char_string);
                            this->arg_map[current_argument_string] = "";
                        }
                    }
                }
                else
                {
                    if (n_leading_dashes != 1)
                    {
                        // the characters until the equal sign is the key.
                        // the characters after the equal sign is the value.
                        const std::string key = argument.substr(0, index_of_equal_sign);
                        const std::string value = argument.substr(index_of_equal_sign + 1);
                        this->arg_map[key] = value;
                    }
                    else
                    {
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
        }

        void CommandLineMaster::print_keys()
        {
            // Print command line arguments (without the executable name string).
            if (this->argc > 1)
            {
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
