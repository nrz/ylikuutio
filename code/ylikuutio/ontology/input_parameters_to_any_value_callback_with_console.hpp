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

#ifndef YLIKUUTIO_ONTOLOGY_INPUT_PARAMETERS_TO_ANY_VALUE_CALLBACK_WITH_CONSOLE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_INPUT_PARAMETERS_TO_ANY_VALUE_CALLBACK_WITH_CONSOLE_HPP_INCLUDED

#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <optional> // std::optional

namespace yli::ontology
{
    class GenericParentModule;
    class Console;
    class ConsoleCallbackEngine;
    class ConsoleCallbackObject;
}

typedef std::optional<yli::data::AnyValue> (*InputParametersToAnyValueCallbackWithConsole) (
        yli::ontology::ConsoleCallbackEngine*,
        yli::ontology::ConsoleCallbackObject*,
        yli::ontology::GenericParentModule&,
        yli::ontology::Console&);

#endif
