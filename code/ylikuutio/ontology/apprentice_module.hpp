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

#ifndef YLIKUUTIO_ONTOLOGY_APPRENTICE_MODULE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_APPRENTICE_MODULE_HPP_INCLUDED

#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::queue
#include <limits>  // std::numeric_limits
#include <vector>  // std::vector

namespace yli::ontology
{
    class GenericMasterModule;
    class Entity;
    class Scene;

    template<typename M>
        class MasterModule;

    class ApprenticeModule
    {
        public:
            void bind_to_generic_master_module() noexcept;
            void unbind_from_generic_master_module() noexcept;

        private:
            void bind_to_new_generic_master_module(
                    yli::ontology::GenericMasterModule* const new_generic_master) noexcept;

        public:
            void unbind_from_any_master_belonging_to_other_scene(
                    const yli::ontology::Scene& scene) noexcept;

            void unbind_and_bind_to_new_generic_master_module(
                    yli::ontology::GenericMasterModule* const new_generic_master) noexcept;

            // constructor.
            ApprenticeModule(
                    yli::ontology::GenericMasterModule* const generic_master_module,
                    yli::ontology::Entity* const apprentice) noexcept;

            // destructor.
            virtual ~ApprenticeModule() noexcept;

            yli::ontology::Entity* get_master() const noexcept;
            yli::ontology::Entity* get_apprentice() const noexcept;
            std::size_t get_apprenticeID() const noexcept;

            void release() noexcept;

            ApprenticeModule(const ApprenticeModule&) = delete;            // Delete copy constructor.
            ApprenticeModule& operator=(const ApprenticeModule&) = delete; // Delete copy assignment.

            friend class yli::ontology::GenericMasterModule;

            template<typename M>
                friend class yli::ontology::MasterModule;

            template<typename T1>
                friend void yli::hierarchy::set_child_pointer(
                        const std::size_t childID,
                        const T1 child_pointer,
                        std::vector<T1>& child_pointer_vector,
                        std::queue<std::size_t>& free_childID_queue,
                        std::size_t& number_of_children) noexcept;

            template<typename T1>
                friend std::size_t yli::hierarchy::request_childID(std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue) noexcept;

            template<typename T1>
                friend void yli::hierarchy::bind_apprentice_to_master(
                        T1& apprentice,
                        std::vector<T1*>& apprentice_pointer_vector,
                        std::queue<std::size_t>& free_apprenticeID_queue,
                        std::size_t& number_of_apprentices) noexcept;

        private:
            yli::ontology::GenericMasterModule* generic_master_module { nullptr };

            yli::ontology::Entity* const apprentice;
            std::size_t apprenticeID { std::numeric_limits<std::size_t>::max() };
    };
}

#endif
