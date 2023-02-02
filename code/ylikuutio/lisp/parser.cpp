// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "parser.hpp"

// Include standard headers
#include <string>  // std::string, std::getline
#include <sstream> // std::istringstream, std::ostringstream, std::stringstream
#include <vector>  // std::vector

namespace yli::lisp
{
    bool parse(const std::string& input_string, std::string& command, std::vector<std::string>& parameter_vector)
    {
        bool is_command = false;

        std::string token;
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
