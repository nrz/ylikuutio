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

#include "ajokki_console_callbacks.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/console.hpp"

// Include standard headers
#include <optional> // std::optional
#include <string>   // std::string

namespace ajokki
{
    std::optional<yli::data::AnyValue> version(
            const yli::ontology::Universe& universe,
            yli::ontology::Console& console)
    {
        console.print_text("Ajokki " + yli::ontology::Universe::version + " / Ylikuutio " + yli::ontology::Universe::version);
        return std::nullopt;
    }
}
