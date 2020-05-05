// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __CONSOLE_COMMAND_HPP_INCLUDED
#define __CONSOLE_COMMAND_HPP_INCLUDED

#include "generic_console_command.hpp"
#include "console.hpp"
#include "code/ylikuutio/common/data_templates.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <functional> // std::function, std::invoke
#include <memory>     // std::make_shared, std::shared_ptr
#include <string>     // std::string
#include <tuple>      // std::apply, std::tuple, std::tuple_cat
#include <vector>     // std::vector

// This is a bit complicated, as the callback may receive different kinds of arguments.
// 1. If the callback has `yli::ontology::Universe*` as an argument, then the `Universe*` will be provided.
//    This does not consume any parameters.
//
// 2. If the callback has `yli::ontology::Console*` as an argument, then this `Console*` will be provided.
//    This does not consume any parameters. In the future other `Console`s will be made reachable as well,
//    with `yli::ontology::SomeConsole*`.
//
// 3. Otherwise, if the callback has `yli::ontology::Entity*` or some subtype of `Entity` as an argument,
//    then the string will be looked up and converted into that.
//
// 4. If the callback has `bool` as an argument, then the string will be converted into that.
//
// 5. If the callback has `float` as an argument, then the string will be converted into that.
//
// 6. If the callback has `double` as an argument, then the string will be converted into that.
//
// 7. If the callback has `int32_t` as an argument, then the string will be converted into that.
//
// 8. If the callback has `uint32_t` as an argument, then the string will be converted into that.
//
// If any lookup or conversion fails, the callback will not be called.
// If `dynamic_cast` from `yli::ontology::Entity*` into its subtype results in `nullptr`, the callback will not be called.
// If there is not enough parameters for all conversions, the callback will not be called.
// If not all parameters are consumed, the callback will not be called.
//
// Therefore, the number of provided parameters must match the following equation:
//
// number-of-provided-parameters = number-of-function-arguments - number-of-Universe-arguments - number-of-Console-arguments

namespace yli::common
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class ParentModule;

    template<class T1, class T2 = void, class T3 = void>
        class ConsoleCommand: public yli::ontology::GenericConsoleCommand
    {
        public:
            ConsoleCommand(
                    yli::ontology::Universe* const universe,
                    yli::ontology::ParentModule* const parent_module,
                    std::function<std::shared_ptr<yli::common::AnyValue>(T1 arg1, T2 arg2, T3 arg3)> callback)
                : GenericConsoleCommand(universe, parent_module),
                callback(callback)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::ConsoleCommand*";
            }

            ConsoleCommand(const ConsoleCommand&) = delete;            // Delete copy constructor.
            ConsoleCommand &operator=(const ConsoleCommand&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~ConsoleCommand()
            {
                // destructor.
            }

            std::shared_ptr<yli::common::AnyValue> execute(const std::vector<std::string>& parameter_vector) override
            {
                yli::ontology::Universe* const universe = this->get_universe();

                if (universe == nullptr)
                {
                    std::cerr << "ERROR: `ConsoleCommand::execute`: `universe` is `nullptr`!\n";
                    return nullptr;
                }

                yli::ontology::Entity* const console_entity = this->child_of_console.get_parent();

                if (console_entity == nullptr)
                {
                    std::cerr << "ERROR: `ConsoleCommand::execute`: `console_entity` is `nullptr`!\n";
                    return nullptr;
                }

                yli::ontology::Console* const console = dynamic_cast<yli::ontology::Console*>(console_entity);

                if (console == nullptr)
                {
                    std::cerr << "ERROR: `ConsoleCommand::execute`: `console` is `nullptr`!\n";
                    return nullptr;
                }

                bool success1 = true;
                bool success2 = true;
                bool success3 = true;

                std::size_t parameter_i = 0;

                yli::ontology::Entity* context = universe; // `Universe` is the default context.
                T1 value1 = yli::common::convert_string_to_value_and_advance_index<T1>(universe, console, context, parameter_vector, parameter_i, success1);
                T2 value2 = yli::common::convert_string_to_value_and_advance_index<T2>(universe, console, context, parameter_vector, parameter_i, success2);
                T3 value3 = yli::common::convert_string_to_value_and_advance_index<T3>(universe, console, context, parameter_vector, parameter_i, success3);

                if (success1 && success2 && success3)
                {
                    // Call the callback function if binding was successful.
                    std::tuple parameter_tuple = std::make_tuple(value1, value2, value3);
                    return std::apply(this->callback, parameter_tuple);
                }

                return nullptr;
            }

        private:
            // The callback may receive different kinds of arguments.
            const std::function<std::shared_ptr<yli::common::AnyValue>(T1, T2, T3)> callback;
    };

    template<class T1, class T2>
    class ConsoleCommand<T1, T2, void>: public yli::ontology::GenericConsoleCommand
    {
        public:
            ConsoleCommand(
                    yli::ontology::Universe* const universe,
                    yli::ontology::ParentModule* const parent_module,
                    std::function<std::shared_ptr<yli::common::AnyValue>(T1 arg1, T2 arg2)> callback)
                : GenericConsoleCommand(universe, parent_module),
                callback(callback)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::ConsoleCommand*";
            }

            ConsoleCommand(const ConsoleCommand&) = delete;            // Delete copy constructor.
            ConsoleCommand &operator=(const ConsoleCommand&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~ConsoleCommand()
            {
                // destructor.
            }

            std::shared_ptr<yli::common::AnyValue> execute(const std::vector<std::string>& parameter_vector) override
            {
                yli::ontology::Universe* const universe = this->get_universe();

                if (universe == nullptr)
                {
                    std::cerr << "ERROR: `ConsoleCommand::execute`: `universe` is `nullptr`!\n";
                    return nullptr;
                }

                yli::ontology::Entity* const console_entity = this->child_of_console.get_parent();

                if (console_entity == nullptr)
                {
                    std::cerr << "ERROR: `ConsoleCommand::execute`: `console_entity` is `nullptr`!\n";
                    return nullptr;
                }

                yli::ontology::Console* const console = dynamic_cast<yli::ontology::Console*>(console_entity);

                if (console == nullptr)
                {
                    std::cerr << "ERROR: `ConsoleCommand::execute`: `console` is `nullptr`!\n";
                    return nullptr;
                }

                bool success1 = true;
                bool success2 = true;

                std::size_t parameter_i = 0;

                yli::ontology::Entity* context = universe; // `Universe` is the default context.
                T1 value1 = yli::common::convert_string_to_value_and_advance_index<T1>(universe, console, context, parameter_vector, parameter_i, success1);
                T2 value2 = yli::common::convert_string_to_value_and_advance_index<T2>(universe, console, context, parameter_vector, parameter_i, success2);

                if (success1 && success2)
                {
                    // Call the callback function if binding was successful.
                    std::tuple parameter_tuple = std::make_tuple(value1, value2);
                    return std::apply(this->callback, parameter_tuple);
                }

                return nullptr;
            }

        private:
            // The callback may receive different kinds of arguments.
            const std::function<std::shared_ptr<yli::common::AnyValue>(T1, T2)> callback;
    };

    template<class T1>
    class ConsoleCommand<T1, void, void>: public yli::ontology::GenericConsoleCommand
    {
        public:
            ConsoleCommand(
                    yli::ontology::Universe* const universe,
                    yli::ontology::ParentModule* const parent_module,
                    std::function<std::shared_ptr<yli::common::AnyValue>(T1 arg1)> callback)
                : GenericConsoleCommand(universe, parent_module),
                callback(callback)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::ConsoleCommand*";
            }

            ConsoleCommand(const ConsoleCommand&) = delete;            // Delete copy constructor.
            ConsoleCommand &operator=(const ConsoleCommand&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~ConsoleCommand()
            {
                // destructor.
            }

            std::shared_ptr<yli::common::AnyValue> execute(const std::vector<std::string>& parameter_vector) override
            {
                yli::ontology::Universe* const universe = this->get_universe();

                if (universe == nullptr)
                {
                    std::cerr << "ERROR: `ConsoleCommand::execute`: `universe` is `nullptr`!\n";
                    return nullptr;
                }

                yli::ontology::Entity* const console_entity = this->child_of_console.get_parent();

                if (console_entity == nullptr)
                {
                    std::cerr << "ERROR: `ConsoleCommand::execute`: `console_entity` is `nullptr`!\n";
                    return nullptr;
                }

                yli::ontology::Console* const console = dynamic_cast<yli::ontology::Console*>(console_entity);

                if (console == nullptr)
                {
                    std::cerr << "ERROR: `ConsoleCommand::execute`: `console` is `nullptr`!\n";
                    return nullptr;
                }

                bool success1 = true;

                std::size_t parameter_i = 0;

                yli::ontology::Entity* context = universe; // `Universe` is the default context.
                T1 value1 = yli::common::convert_string_to_value_and_advance_index<T1>(universe, console, context, parameter_vector, parameter_i, success1);

                if (success1)
                {
                    // Call the callback function if binding was successful.
                    std::tuple parameter_tuple = std::make_tuple(value1);
                    return std::apply(this->callback, parameter_tuple);
                }

                return nullptr;
            }

        private:
            // The callback may receive different kinds of arguments.
            const std::function<std::shared_ptr<yli::common::AnyValue>(T1)> callback;
    };
}

#endif
