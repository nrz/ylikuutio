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

#ifndef YLIKUUTIO_DATA_TUPLE_TEMPLATES_HPP_INCLUDED
#define YLIKUUTIO_DATA_TUPLE_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <tuple>    // std::apply, std::tie, std::tuple, std::tuple_cat
#include <utility>  // std::index_sequence, std::integer_sequence

namespace yli::data
{
    template<typename T1, typename... Types>
        auto first(std::tuple<T1, Types...>& my_tuple)
        {
            // Inspired by https://stackoverflow.com/questions/10626856/how-to-split-a-tuple
            return std::get<0>(my_tuple);
        }

    template<std::size_t... Numbers, typename... Types>
        auto rest_impl(std::index_sequence<Numbers...>, std::tuple<Types...>& my_tuple)
        {
            // Inspired by https://stackoverflow.com/questions/10626856/how-to-split-a-tuple
            return std::make_tuple(std::get<Numbers + 1u>(my_tuple)...);
        }

    template<typename... Types>
        auto rest(std::tuple<Types...>& my_tuple)
        {
            // Inspired by https://stackoverflow.com/questions/10626856/how-to-split-a-tuple
            return rest_impl(std::make_index_sequence<sizeof...(Types) - 1u>(), my_tuple);
        }

    template<typename TupleType, typename FunctionType, std::size_t... Is>
        auto visit_tuple_helper(TupleType&& tuple, FunctionType&& func, std::index_sequence<Is...>)
        {
            return std::tuple(func(Is, std::get<Is>(std::forward<TupleType>(tuple)))...);
        }

    template<typename TupleType, typename FunctionType>
        auto visit_tuple(TupleType&& tuple, FunctionType&& func)
        {
            using index_seq = std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<TupleType>>>;
            return visit_tuple_helper<TupleType, FunctionType>(std::forward<TupleType>(tuple), std::forward<FunctionType>(func), index_seq());
        }

    template<typename Type, typename TupleType, typename FunctionType, std::size_t... Is>
        auto visit_tuple_with_type_helper(TupleType&& tuple, FunctionType&& func, std::index_sequence<Is...>)
        {
            return std::tuple(func<Type>(Is, std::get<Is>(std::forward<TupleType>(tuple)))...);
        }

    template<typename Type, typename TupleType, typename FunctionType>
        auto visit_tuple_with_type(TupleType&& tuple, FunctionType&& func)
        {
            using index_seq = std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<TupleType>>>;
            return visit_tuple_with_type_helper<Type, TupleType, FunctionType>(std::forward<TupleType>(tuple), std::forward<FunctionType>(func), index_seq());
        }
}

#endif
