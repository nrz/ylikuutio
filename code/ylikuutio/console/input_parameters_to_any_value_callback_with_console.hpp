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

#ifndef __INPUT_PARAMETERS_TO_ANY_VALUE_CALLBACK_WITH_CONSOLE_HPP_INCLUDED
#define __INPUT_PARAMETERS_TO_ANY_VALUE_CALLBACK_WITH_CONSOLE_HPP_INCLUDED

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace yli
{
    namespace callback
    {
        class CallbackEngine;
        class CallbackObject;
        class CallbackParameter;
    }

    namespace common
    {
        class AnyValue;
    }

    namespace ontology
    {
        class Console;
    }
}

typedef std::shared_ptr<yli::common::AnyValue> (*InputParametersToAnyValueCallbackWithConsole) (
        yli::callback::CallbackEngine*,
        yli::callback::CallbackObject*,
        std::vector<yli::callback::CallbackParameter*>&,
        yli::ontology::Console*);

#endif
