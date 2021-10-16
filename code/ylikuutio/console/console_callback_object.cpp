// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#include "console_callback_object.hpp"
#include "code/ylikuutio/callback/callback_parameter.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <optional> // std::optional

namespace yli::console
{
    ConsoleCallbackObject::~ConsoleCallbackObject()
    {
        // destroy all callback parameters of this callback object.
        std::cout << "All callback parameters of this console callback object will be destroyed.\n";
        for (std::size_t child_i = 0; child_i < this->callback_parameter_pointer_vector.size(); child_i++)
        {
            delete this->callback_parameter_pointer_vector[child_i];
        }
    }

    std::optional<yli::data::AnyValue> ConsoleCallbackObject::execute(const yli::data::AnyValue&)
    {
        if (this->console_callback != nullptr)
        {
            return yli::data::AnyValue(this->console_callback(this->parent, this, this->callback_parameter_pointer_vector, this->console_pointer));
        }
        return std::nullopt;
    }
}
