// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_LISP_ARG_PROCESSING_TEMPLATES_HPP_INCLUDED
#define __YLIKUUTIO_LISP_ARG_PROCESSING_TEMPLATES_HPP_INCLUDED

#include "lisp_templates.hpp"
#include "code/ylikuutio/data/tuple_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string
#include <tuple>    // std::apply, std::tie, std::tuple, std::tuple_cat
#include <vector>   // std::vector

namespace yli::lisp
{
    class Entity;
    class Universe;
    class Console;

    template<typename None = void>
        static bool process_args(
                yli::ontology::Universe* /* universe */,
                yli::ontology::Console* /* console */,
                yli::ontology::Entity*& /* context */,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                std::tuple<>& /* arg_tuple */)
        {
            // This case ends the recursion.
            // No more arguments to bind.

            if (parameter_i == parameter_vector.size())
            {
                // All parameters were bound. Binding successful.
                return true;
            }

            // Not all parameters were bound. Binding failed.
            return false;
        }

    template<typename T1, typename... Types>
        static bool process_args(
                yli::ontology::Universe* universe,
                yli::ontology::Console* console,
                yli::ontology::Entity*& context,
                const std::vector<std::string>& parameter_vector,
                std::size_t& parameter_i,
                std::tuple<T1, Types...>& arg_tuple)
        {
            T1 value;

            if (!yli::lisp::convert_string_to_value_and_advance_index<T1>(universe, console, context, parameter_vector, parameter_i, value))
            {
                // Binding failed.
                return false;
            }

            // OK, binding successful for this argument.
            // Proceed to the next argument.

            std::tuple<Types...> new_arg_tuple = yli::data::rest(arg_tuple);

            if (!yli::lisp::process_args(universe, console, context, parameter_vector, parameter_i, new_arg_tuple))
            {
                // Binding failed.
                return false;
            }

            arg_tuple = std::tuple_cat(std::make_tuple(value), new_arg_tuple);
            return true; // success.
        }
}

#endif
