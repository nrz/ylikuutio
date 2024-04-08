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

#ifndef YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED

#include "generic_lisp_function_overload.hpp"
#include "console.hpp"
#include "lisp_function.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/wrap.hpp"
#include "code/ylikuutio/lisp/function_arg_extractor.hpp"
#include "code/ylikuutio/lisp/lisp_templates.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <optional>   // std::optional
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string
#include <tuple>      // std::apply, std::tuple, std::tuple_cat
#include <vector>     // std::vector

// This is a bit complicated, as the callback may receive different kinds of arguments.
//
// If any lookup or conversion fails, the callback will not be called.
// If `dynamic_cast` from `yli::ontology::Entity*` into its subtype results in `nullptr`, the callback will not be called.
// If there is not enough parameters for all conversions, the callback will not be called.
// If not all parameters are consumed, the callback will not be called.
//
// Therefore, the number of provided parameters must match the following equation:
//
// number-of-provided-parameters = number-of-function-arguments - number-of-Universe-arguments - number-of-Console-arguments

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryAllocator;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Console;
    class GenericParentModule;

    template<typename... Types>
        class LispFunctionOverload final : public yli::ontology::GenericLispFunctionOverload
    {
        private:
            LispFunctionOverload(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    yli::ontology::GenericParentModule* const lisp_function_parent_module,
                    std::optional<yli::data::AnyValue>(*callback)(Types...))
                : GenericLispFunctionOverload(application, universe, lisp_function_parent_module),
                callback(callback)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::LispFunctionOverload*";
            }

            ~LispFunctionOverload() = default;

        public:
            LispFunctionOverload(const LispFunctionOverload&) = delete;            // Delete copy constructor.
            LispFunctionOverload& operator=(const LispFunctionOverload&) = delete; // Delete copy assignment.

            std::optional<yli::data::AnyValue> execute(const std::vector<std::string>& parameter_vector) override
            {
                yli::ontology::LispFunction* const lisp_function_parent = static_cast<yli::ontology::LispFunction*>(this->get_parent());

                if (lisp_function_parent == nullptr) [[unlikely]]
                {
                    throw std::runtime_error("ERROR: `LispFunctionOverload::execute`: `lisp_function_parent` is `nullptr`!");
                }

                yli::ontology::Console* const console_parent_of_lisp_function = static_cast<yli::ontology::Console*>(lisp_function_parent->get_parent());

                if (console_parent_of_lisp_function == nullptr) [[unlikely]]
                {
                    throw std::runtime_error("ERROR: `LispFunctionOverload::execute`: `console_parent_of_lisp_function` is `nullptr`!");
                }

                // OK, all preconditions for a successful argument binding are met.
                // Now, process the arguments and call.

                std::size_t parameter_i = 0;                      // Start from the first parameter.
                yli::ontology::Entity* context = &this->universe; // `Universe` is the default context.

                std::optional<std::tuple<typename yli::data::Wrap<Types>::type...>> arg_tuple = this->process_args<
                    std::size_t, Types...>(
                            std::size_t {},
                            this->universe,
                            *console_parent_of_lisp_function,
                            context,
                            parameter_vector,
                            parameter_i);

                if (arg_tuple)
                {
                    return std::apply(this->callback, *arg_tuple);
                }

                return std::nullopt;
            }

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

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryAllocator;

            // The callback may receive different kinds of arguments.
            std::optional<yli::data::AnyValue>(* const callback) (Types...);
    };
}

#endif
