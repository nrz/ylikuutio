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

#include "console_callback_snippets.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/callback/callback_magic_numbers.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Console;
}

namespace yli::snippets
{
    std::shared_ptr<yli::data::AnyValue> quit(yli::ontology::Console* const console)
    {
        uint32_t exit_program_magic_number = EXIT_PROGRAM_MAGIC_NUMBER;
        return std::make_shared<yli::data::AnyValue>(exit_program_magic_number);
    }

    std::shared_ptr<yli::data::AnyValue> help(yli::ontology::Console* const console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        console->print_help();
        return nullptr;
    }
}
