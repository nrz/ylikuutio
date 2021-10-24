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

#ifndef __YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED

#include "generic_lisp_function_overload.hpp"
#include "console.hpp"
#include "lisp_function.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/tuple_templates.hpp"
#include "code/ylikuutio/data/wrap.hpp"
#include "code/ylikuutio/lisp/function_arg_extractor.hpp"
#include "code/ylikuutio/lisp/lisp_templates.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <functional> // std::function, std::invoke
#include <iostream>   // std::cout, std::cin, std::cerr
#include <optional>   // std::optional
#include <string>     // std::string
#include <tuple>      // std::apply, std::tuple, std::tuple_cat
#include <vector>     // std::vector

// This is a bit complicated, as the callback may receive different kinds of arguments.
//
// The default context is `Universe`.
//
// 1. If the callback has `yli::ontology::Universe*` as an argument, then the `Universe*` will be provided.
//    This does not consume any parameters. The `Universe` is set as context.
//
// 2. If the callback has `yli::ontology::Console*` as an argument, then this `Console*` will be provided.
//    This does not consume any parameters. In the future other `Console`s will be made reachable as well,
//    with `yli::ontology::SomeConsole*`. The `Console` is set as context.
//
// 3. Otherwise, if the callback has `yli::ontology::Entity*` or some subtype of `Entity` as an argument,
//    then the string will be looked up and converted into that. The `Entity` is set as context.
//
// 4. If the callback has `yli::ontology::Variable*` as an argument, then the `Variable` with that name
//    will be looked up from the current context.
//
// 5. If the callback has `bool` as an argument, then the string will be converted into that.
//
// 6. If the callback has `float` as an argument, then the string will be converted into that.
//
// 7. If the callback has `double` as an argument, then the string will be converted into that.
//
// 8. If the callback has `int32_t` as an argument, then the string will be converted into that.
//
// 9. If the callback has `uint32_t` as an argument, then the string will be converted into that.
//
// If any lookup or conversion fails, the callback will not be called.
// If `dynamic_cast` from `yli::ontology::Entity*` into its subtype results in `nullptr`, the callback will not be called.
// If there is not enough parameters for all conversions, the callback will not be called.
// If not all parameters are consumed, the callback will not be called.
//
// Therefore, the number of provided parameters must match the following equation:
//
// number-of-provided-parameters = number-of-function-arguments - number-of-Universe-arguments - number-of-Console-arguments

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Console;
    class ParentModule;

    template<typename... Types>
        class LispFunctionOverload: public yli::ontology::GenericLispFunctionOverload
    {
        public:
        private:
            template<typename Tag>
                std::optional<std::tuple<>> process_args(
                        std::size_t,
                        yli::ontology::Universe&,
                        yli::ontology::Console&,
                        yli::ontology::Entity*&,
                        const std::vector<std::string>& parameter_vector,
                        std::size_t& parameter_i)
                {
                    // This case ends the recursion.
                    // No more arguments to bind.

                    if (parameter_i == parameter_vector.size())
                    {
                        // All parameters were bound. Binding successful.
                        return std::tuple<>();
                    }

                    // Not all parameters were bound. Binding failed.
                    return std::nullopt;
                }

            template<typename Tag, typename T1, typename... RestTypes>
                std::optional<std::tuple<typename yli::data::WrapAllButStrings<T1>::type, typename yli::data::WrapAllButStrings<RestTypes>::type...>> process_args(
                        std::size_t tag,
                        yli::ontology::Universe& universe,
                        yli::ontology::Console& console,
                        yli::ontology::Entity*& context,
                        const std::vector<std::string>& parameter_vector,
                        std::size_t& parameter_i)
                {
                    std::optional<typename yli::data::WrapAllButStrings<T1>::type> value = yli::lisp::convert_string_to_value_and_advance_index<T1>(
                        universe, console, context, parameter_vector, parameter_i);

                    if (!value)
                    {
                        // Binding failed.
                        return std::nullopt;
                    }

                    // OK, binding successful for this argument.
                    // Proceed to the next argument.

                    std::optional<std::tuple<typename yli::data::WrapAllButStrings<RestTypes>::type...>> arg_tuple = this->process_args<
                        std::size_t, RestTypes...>(
                                tag, universe, console, context, parameter_vector, parameter_i);

                    if (arg_tuple)
                    {
                        return std::tuple_cat(std::make_tuple(*value), *arg_tuple); // success.
                    }

                    // Binding failed.
                    return std::nullopt;
                }

            std::optional<yli::data::AnyValue> process_args_and_call(const std::vector<std::string>& parameter_vector)
            {
                // Start processing the arguments.

                if (this->universe == nullptr)
                {
                    return std::nullopt;
                }

                yli::ontology::LispFunction* const lisp_function = static_cast<yli::ontology::LispFunction*>(this->get_parent());

                if (lisp_function == nullptr)
                {
                    return std::nullopt;
                }

                yli::ontology::Console* const console = static_cast<yli::ontology::Console*>(lisp_function->get_parent());

                if (console == nullptr)
                {
                    return std::nullopt;
                }

                std::size_t parameter_i = 0;                     // Start from the first parameter.
                yli::ontology::Entity* context = this->universe; // `Universe` is the default context.

                std::optional<std::tuple<typename yli::data::Wrap<Types>::type...>> arg_tuple = this->process_args<
                    std::size_t, Types...>(
                        std::size_t {},
                        *this->universe,
                        *console,
                        context,
                        parameter_vector,
                        parameter_i);

                if (arg_tuple)
                {
                    return std::apply(this->callback, *arg_tuple);
                }

                std::cout << "ERROR: `LispFunctionOverload::process_args_and_call`: binding failed!\n";
                return std::nullopt;
            }

        public:
            LispFunctionOverload(
                    yli::ontology::Universe* const universe,
                    yli::ontology::ParentModule* const parent_module,
                    std::function<std::optional<yli::data::AnyValue>(Types...)> callback)
                : GenericLispFunctionOverload(universe, parent_module),
                callback(callback)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::LispFunctionOverload*";
            }

            LispFunctionOverload(const LispFunctionOverload&) = delete;            // Delete copy constructor.
            LispFunctionOverload& operator=(const LispFunctionOverload&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~LispFunctionOverload()
            {
                // destructor.
            }

            std::optional<yli::data::AnyValue> execute(const std::vector<std::string>& parameter_vector) override
            {
                yli::ontology::Universe* const universe = this->get_universe();

                if (universe == nullptr)
                {
                    std::cerr << "ERROR: `LispFunctionOverload::execute`: `universe` is `nullptr`!\n";
                    return std::nullopt;
                }

                yli::ontology::Entity* const lisp_function_entity = this->child_of_lisp_function.get_parent();

                yli::ontology::LispFunction* const lisp_function = dynamic_cast<yli::ontology::LispFunction*>(lisp_function_entity);

                if (lisp_function == nullptr)
                {
                    std::cerr << "ERROR: `LispFunctionOverload::execute`: `lisp_function` is `nullptr`!\n";
                    return std::nullopt;
                }

                yli::ontology::Entity* const console_entity = lisp_function->get_parent();

                if (console_entity == nullptr)
                {
                    std::cerr << "ERROR: `LispFunctionOverload::execute`: `console_entity` is `nullptr`!\n";
                    return std::nullopt;
                }

                yli::ontology::Console* const console = dynamic_cast<yli::ontology::Console*>(console_entity);

                if (console == nullptr)
                {
                    std::cerr << "ERROR: `LispFunctionOverload::execute`: `console` is `nullptr`!\n";
                    return std::nullopt;
                }

                // OK, all preconditions for a successful argument binding are met.
                // Now, process the arguments and call.

                return this->process_args_and_call(parameter_vector);
            }

        private:
            // The callback may receive different kinds of arguments.
            const std::function<std::optional<yli::data::AnyValue>(Types...)> callback;
    };
}

#endif
