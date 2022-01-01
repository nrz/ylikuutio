// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_ENTITY_VARIABLE_READ_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_ENTITY_VARIABLE_READ_HPP_INCLUDED

// Include standard headers
#include <optional> // std::optional

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> read_should_be_rendered(yli::ontology::Entity& entity);
}

#endif
