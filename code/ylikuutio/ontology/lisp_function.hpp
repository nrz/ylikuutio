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

#ifndef YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <optional>   // std::optional
#include <string>     // std::string
#include <vector>     // std::vector

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
    class Universe;
    class Scene;
    struct LispFunctionStruct;

    class LispFunction final : public Entity
    {
        private:
            LispFunction(
                    yli::core::Application& application,
                    Universe& universe,
                    const LispFunctionStruct& lisp_function_struct,
                    GenericParentModule* const context_parent_module);

            ~LispFunction() = default;

        public:
            LispFunction(const LispFunction&) = delete;            // Delete copy constructor.
            LispFunction& operator=(const LispFunction&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            std::optional<yli::data::AnyValue> execute(const std::vector<std::string>& parameter_vector);

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_lisp_context;
            GenericParentModule parent_of_generic_lisp_function_overloads;

            Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
