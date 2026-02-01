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

#ifndef YLIKUUTIO_ONTOLOGY_RESULT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_RESULT_HPP_INCLUDED

#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <optional> // std::optional
#include <utility>  // std::move
#include <variant>  // std::holds_alternative, std::variant

namespace yli::ontology
{
    struct Result
    {
        // YliLisp functions must always return something.
        // `std::nullopt` can be used as the return value if there is no
        // meaningful return value.
        //
        // For successful function execution:
        // `AnyValue` contains the value returned by the function,
        // and `std::nullopt` stored in `AnyValue` is valid too.
        //
        // For unsuccessful function call (binding failed):
        // `bool` contains `false`.
        explicit Result(std::optional<yli::data::AnyValue>&& any_value)
            : data { std::move(any_value) }
        {
        }

        explicit Result(const bool success)
            : data { success }
        {
        }

        explicit operator bool()
        {
            if (std::holds_alternative<std::optional<yli::data::AnyValue>>(this->data))
            {
                return true;
            }

            return std::get<bool>(this->data);
        }

        std::variant<std::optional<yli::data::AnyValue>, bool> data {};
    };
}

#endif
