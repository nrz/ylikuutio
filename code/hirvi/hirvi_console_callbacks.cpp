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

#include "hirvi_console_callbacks.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/callback/callback_magic_numbers.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/ontology/universe.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Entity;
        class Console;
    }
}

namespace hirvi
{
    std::shared_ptr<yli::common::AnyValue> version(
            yli::ontology::Console* const console,
            yli::ontology::Entity* const universe_entity,
            const std::vector<std::string>& command_parameters)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(universe_entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::stringstream version_stringstream;
        version_stringstream << "Hirvi " << universe->version << " / Ylikuutio " << universe->version;
        console->print_text(version_stringstream.str());
        return nullptr;
    }
}
