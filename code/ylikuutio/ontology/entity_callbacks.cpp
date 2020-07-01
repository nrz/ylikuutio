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

#include "entity.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Console;

    std::shared_ptr<yli::data::AnyValue> Entity::print_children(
            yli::ontology::Console* const console,
            yli::ontology::Entity* const entity)
    {
        if (console == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        // OK, let's print the children of this `Entity`.
        yli::map::print_keys_to_console(entity->entity_map, console);

        return nullptr;
    }
}
