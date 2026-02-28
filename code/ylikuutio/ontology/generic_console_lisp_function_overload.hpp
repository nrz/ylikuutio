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

#ifndef YLIKUUTIO_ONTOLOGY_GENERIC_CONSOLE_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GENERIC_CONSOLE_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED

#include "generic_lisp_function_overload.hpp"
#include "child_module.hpp"

// Include standard headers
#include <cstddef> // std::size_t

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
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;

    class GenericConsoleLispFunctionOverload : public GenericLispFunctionOverload
    {
        public:
            GenericConsoleLispFunctionOverload(
                    yli::core::Application& application,
                    Universe& universe,
                    GenericParentModule* const console_lisp_function_parent_module);

            GenericConsoleLispFunctionOverload(const GenericConsoleLispFunctionOverload&) = delete;            // Delete copy constructor.
            GenericConsoleLispFunctionOverload &operator=(const GenericConsoleLispFunctionOverload&) = delete; // Delete copy assignment.

            virtual ~GenericConsoleLispFunctionOverload() = default;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryAllocator;

            Entity* get_parent() const override;

            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            Scene* get_scene() const override;

            ChildModule child_of_console_lisp_function;
    };
}

#endif
