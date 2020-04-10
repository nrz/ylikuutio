// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "angelscript_callbacks.hpp"

#include "angelscript.h"
#include "scriptstdstring/scriptstdstring.h"
#include "scriptbuilder/scriptbuilder.h"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string

namespace yli
{
    namespace angelscript
    {
        void message_callback(const asSMessageInfo* message, void* parameters)
        {
            if (message == nullptr)
            {
                std::cerr << "ERROR: `message_callback`: `message` is `nullptr`!\n";
                return;
            }

            std::string type;

            if (message->type == asMSGTYPE_ERROR)
            {
                type = "ERROR";
            }
            else if (message->type == asMSGTYPE_WARNING)
            {
                type = "WARNING";
            }
            else if (message->type == asMSGTYPE_INFORMATION)
            {
                type = "INFORMATION";
            }

            std::stringstream output_stringstream;
            output_stringstream << type << " " << message->section << " (" << message->row << ", " << message->col << ") : " << type << " : " << message->message << "\n";
            std::cout << output_stringstream.str();
        }

        void print(const std::string& my_message)
        {
            std::cout << my_message;
        }

        void print(const float value)
        {
            std::cout << value;
        }
    }
}
