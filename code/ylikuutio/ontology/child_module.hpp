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

#ifndef YLIKUUTIO_ONTOLOGY_CHILD_MODULE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CHILD_MODULE_HPP_INCLUDED

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::ontology
{
    class Entity;
    class GenericParentModule;
    class Scene;

    class ChildModule
    {
        public:
            ChildModule(GenericParentModule* const parent_module, Entity& entity) noexcept
                : parent_module { parent_module },
                entity { entity }
            {
                this->bind_to_parent_module();
            }

            ChildModule(const ChildModule&) = delete;            // Delete copy constructor.
            ChildModule& operator=(const ChildModule&) = delete; // Delete copy assignment.

            ~ChildModule();

            Entity* get_parent() const noexcept;
            Entity* get_child() const noexcept;
            void release() noexcept;

            Scene* get_scene() const noexcept;
            std::size_t get_childID() const noexcept;

        private:
            void unbind_child() const noexcept;
            void set_parent_module_and_bind_to_new_parent(
                    GenericParentModule* const new_parent_module) noexcept;

        public:
            void unbind_and_bind_to_new_parent(
                    GenericParentModule* const new_parent_module) noexcept;

        private:
            void bind_to_parent_module() noexcept;

            GenericParentModule* parent_module;
            Entity& entity;
    };
}

#endif
