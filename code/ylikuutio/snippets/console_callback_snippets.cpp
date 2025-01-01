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

#include "console_callback_snippets.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/callback_magic_numbers.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.

namespace yli::ontology
{
    class Console;
}

namespace yli::snippets
{
    std::optional<yli::data::AnyValue> quit(yli::ontology::Console* const /* console */)
    {
        uint32_t exit_program_magic_number = yli::ontology::CallbackMagicNumber::EXIT_PROGRAM;
        return yli::data::AnyValue(exit_program_magic_number);
    }

    std::optional<yli::data::AnyValue> help(yli::ontology::Console* const console)
    {
        if (console == nullptr)
        {
            return std::nullopt;
        }

        console->print_help();
        return std::nullopt;
    }
}
