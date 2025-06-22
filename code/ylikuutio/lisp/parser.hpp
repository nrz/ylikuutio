// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_LISP_PARSER_HPP_INCLUDED
#define YLIKUUTIO_LISP_PARSER_HPP_INCLUDED

// Include standard headers
#include <string>  // std::getline
#include <sstream> // std::istringstream
#include <vector>  // std::vector

namespace yli::lisp
{
    template<typename StringType>
        bool parse(const StringType& input_string, StringType& command, std::vector<StringType>& parameter_vector)
        {
            bool is_command = false;

            StringType token;
            std::istringstream input_stringstream(input_string);

            // The reader begins here.

            while (std::getline(input_stringstream, token, ' '))
            {
                if (token.empty())
                {
                    continue;
                }

                if (!is_command)
                {
                    // First non-empty token is the command.
                    command = token;
                    is_command = true;
                }
                else
                {
                    // The rest non-empty tokens are the parameters.
                    parameter_vector.emplace_back(token);
                }
            }

            // The reader ends here.

            return is_command;
        }
}

#endif
