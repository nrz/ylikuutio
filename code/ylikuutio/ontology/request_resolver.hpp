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

#ifndef YLIKUUTIO_ONTOLOGY_REQUEST_RESOLVER_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_REQUEST_RESOLVER_HPP_INCLUDED

#include "registry.hpp"
#include "request.hpp"

// Include standard headers
#include <string>  // std::string
#include <variant> // std::holds_alternative

namespace yli::ontology
{
    template<typename Type>
        Type* resolve_request(const Request<Type>& entity_request, const Registry& registry)
        {
            if (std::holds_alternative<Type*>(entity_request.data))
            {
                return std::get<Type*>(entity_request.data);
            }
            else if (std::holds_alternative<std::string>(entity_request.data))
            {
                const std::string& entity_string = std::get<std::string>(entity_request.data);
                return dynamic_cast<Type*>(registry.get_entity(entity_string));
            }

            return nullptr;
        }
}

#endif
