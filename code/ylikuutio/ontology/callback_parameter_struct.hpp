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

#ifndef YLIKUUTIO_ONTOLOGY_CALLBACK_PARAMETER_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CALLBACK_PARAMETER_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include standard headers
#include <string>  // std::string
#include <variant> // std::variant

namespace yli::ontology
{
    class CallbackObject;

    struct CallbackParameterStruct final : public EntityStruct
    {
        explicit CallbackParameterStruct(CallbackObject* const callback_object_parent)
            : callback_object_parent { callback_object_parent }
        {
        }

        explicit CallbackParameterStruct(const std::string& callback_object_parent)
            : callback_object_parent { callback_object_parent }
        {
        }

        std::variant<CallbackObject*, std::string> callback_object_parent {};
    };
}

#endif
