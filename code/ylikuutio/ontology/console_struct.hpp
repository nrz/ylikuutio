// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __CONSOLE_STRUCT_HPP_INCLUDED
#define __CONSOLE_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"

// Include standard headers
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        struct ConsoleStruct
        {
            ConsoleStruct()
                : current_keypress_callback_engine_vector_pointer_pointer(nullptr),
                current_keyrelease_callback_engine_vector_pointer_pointer(nullptr)
            {
                // constructor.
            }

            std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer;
            std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer;
        };
    }
}

#endif
