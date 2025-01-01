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

#ifndef YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "input_parameters_to_any_value_callback_with_console.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional

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
    class ConsoleCallbackEngine;
    struct ConsoleCallbackObjectStruct;

    class ConsoleCallbackObject final : public Entity
    {
        public:
            ~ConsoleCallbackObject() = default;

            ConsoleCallbackObject(
                    yli::core::Application& application,
                    Universe& universe,
                    const ConsoleCallbackObjectStruct& console_callback_object_struct,
                    GenericParentModule* const console_callback_engine_parent_module);

            GenericParentModule* get_generic_parent_module(const int type);

            Entity* get_parent() const override;
            Scene* get_scene() const override;

            Console* get_console() const;

            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // execute this callback.
            std::optional<yli::data::AnyValue> execute(const yli::data::AnyValue&);

            friend class ConsoleCallbackEngine;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_console_callback_engine;
            GenericParentModule parent_of_console_callback_parameters;

        private:
            InputParametersToAnyValueCallbackWithConsole console_callback;
    };
}

#endif
