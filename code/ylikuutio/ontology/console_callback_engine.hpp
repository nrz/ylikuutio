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

#include "generic_callback_engine.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "input_parameters_to_any_value_callback_with_console.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <optional> // std::optional
#include <vector>   // std::vector

#ifndef YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_ENGINE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_ENGINE_HPP_INCLUDED

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    class Console;
    class ConsoleCallbackObject;
    struct ConsoleCallbackEngineStruct;

    class ConsoleCallbackEngine final : public GenericCallbackEngine
    {
        private:
            ConsoleCallbackEngine(
                    yli::core::Application& application,
                    Universe& universe,
                    const ConsoleCallbackEngineStruct&,
                    GenericParentModule* const universe_parent_module);

            ~ConsoleCallbackEngine() = default;

        public:
            GenericParentModule* get_generic_parent_module(const int type);

            Entity* get_parent() const override;

            Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            ChildModule child_of_universe;
            GenericParentModule parent_of_console_callback_objects;

            ConsoleCallbackObject* create_console_callback_object(
                    const InputParametersToAnyValueCallbackWithConsole callback,
                    Console* const console_pointer);

            // execute all callbacks with a parameter.
            std::optional<yli::data::AnyValue> execute(const yli::data::AnyValue& any_value) override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

        private:
            std::vector<std::optional<yli::data::AnyValue>> return_values;
    };
}

#endif
