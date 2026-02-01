// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_ENTITY_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_ENTITY_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string> // std::string

namespace yli::ontology
{
    struct EntityStruct
    {
        EntityStruct() = default;

        EntityStruct(const EntityStruct& entity_struct) = default;

        EntityStruct(const std::string& global_name, const std::string& local_name) noexcept
            : global_name { global_name },
            local_name { local_name }
        {
        }

        ~EntityStruct() = default;

        std::string global_name;
        std::string local_name;
        bool is_universe    { false };
        bool is_variable    { false };
    };
}

#endif
