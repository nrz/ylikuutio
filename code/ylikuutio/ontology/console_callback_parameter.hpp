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

#ifndef YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_PARAMETER_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_PARAMETER_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string

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
    class ConsoleCallbackObject;
    struct ConsoleCallbackParameterStruct;

    class ConsoleCallbackParameter final : public Entity
    {
        private:
            ConsoleCallbackParameter(
                    yli::core::Application& application,
                    Universe& universe,
                    const ConsoleCallbackParameterStruct& console_callback_parameter_struct,
                    GenericParentModule* const console_callback_object_parent_module,
                    const yli::data::AnyValue& any_value);

            ~ConsoleCallbackParameter() = default;

        public:
            const yli::data::AnyValue& get_any_value() const;

            Entity* get_parent() const override;
            Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_console_callback_object;

            friend class ConsoleCallbackObject;

        private:
            yli::data::AnyValue any_value;  // this is `private` to make sure that someone does not overwrite it.
    };
}

#endif
