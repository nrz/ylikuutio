// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_DATA_TUPLE_TEMPLATES_HPP_INCLUDED
#define YLIKUUTIO_DATA_TUPLE_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <tuple>    // std::apply, std::tie, std::tuple, std::tuple_cat
#include <utility>  // std::index_sequence, std::integer_sequence

namespace yli::data
{
    // Inspired by https://stackoverflow.com/questions/10626856/how-to-split-a-tuple

    template<typename T1, typename... Types>
        auto first(std::tuple<T1, Types...>& my_tuple)
        {
            return std::get<0>(my_tuple);
        }

    template<std::size_t... Numbers, typename... Types>
        auto rest_impl(std::index_sequence<Numbers...>, std::tuple<Types...>& my_tuple)
        {
            return std::make_tuple(std::get<Numbers + 1u>(my_tuple)...);
        }

    template<typename... Types>
        auto rest(std::tuple<Types...>& my_tuple)
        {
            return yli::data::rest_impl(std::make_index_sequence<sizeof...(Types) - 1u>(), my_tuple);
        }
}

#endif
