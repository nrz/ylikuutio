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

#ifndef YLIKUUTIO_ONTOLOGY_LISP_CONTEXT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_LISP_CONTEXT_HPP_INCLUDED

#include "generic_parent_module.hpp"
#include "entity.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    class LispFunction;
    struct LispContextStruct;

    class LispContext : public Entity
    {
        public:
            LispContext(
                    yli::core::Application& application,
                    Universe& universe,
                    const LispContextStruct& lisp_context_struct);

            LispContext(const LispContext&) = delete;            // Delete copy constructor.
            LispContext &operator=(const LispContext&) = delete; // Delete copy assignment.

            virtual ~LispContext() = default;

            Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            Scene* get_scene() const override;

            template<typename ChildType>
                GenericParentModule* get_generic_parent_module() = delete;

            GenericParentModule parent_of_lisp_functions;
    };

    template<>
        inline GenericParentModule* LispContext::get_generic_parent_module<LispFunction>()
        {
            return &this->parent_of_lisp_functions;
        }
}

#endif
