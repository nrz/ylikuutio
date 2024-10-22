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

#ifndef YLIKUUTIO_ONTOLOGY_REQUEST_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_REQUEST_HPP_INCLUDED

// Include standard headers
#include <string>  // std::string
#include <utility> // std::move
#include <variant> // std::monostate, std::variant

namespace yli::ontology
{
    template<typename Type>
        struct Request
        {
            Request() = default;

            explicit Request(Type* pointer)
                : data { pointer }
            {
            }

            explicit Request(std::string&& name)
                : data { std::move(name) }
            {
            }

            std::variant<std::monostate, Type*, std::string> data;
        };
}

#endif
