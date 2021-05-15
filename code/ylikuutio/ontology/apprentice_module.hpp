// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_APPRENTICE_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_APPRENTICE_MODULE_HPP_INCLUDED

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

    template<class M>
        class MasterModule;

    class ApprenticeModule
    {
        public:
            void bind_to_generic_master_module();
            void unbind_from_generic_master_module();
            void bind_to_new_generic_master_module(yli::ontology::GenericMasterModule* const new_generic_master);

            // constructor.
            ApprenticeModule(yli::ontology::GenericMasterModule* const generic_master_module, yli::ontology::Entity* const apprentice);

            // destructor.
            ~ApprenticeModule();

            yli::ontology::Entity* get_master() const;
            yli::ontology::Entity* get_apprentice() const;

            ApprenticeModule(const ApprenticeModule&) = delete;            // Delete copy constructor.
            ApprenticeModule& operator=(const ApprenticeModule&) = delete; // Delete copy assignment.

            friend class yli::ontology::GenericMasterModule;

            template<class M>
                friend class yli::ontology::MasterModule;

            template<class T1>
                friend void yli::hierarchy::set_child_pointer(
                        const std::size_t childID,
                        const T1 child_pointer,
                        std::vector<T1>& child_pointer_vector,
                        std::queue<std::size_t>& free_childID_queue,
                        std::size_t& number_of_children);


            template<class T1>
                friend std::size_t yli::hierarchy::request_childID(std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue);

            template<class T1>
                friend void yli::hierarchy::bind_apprentice_to_master(
                        const T1 apprentice_pointer,
                        std::vector<T1>& apprentice_pointer_vector,
                        std::queue<std::size_t>& free_apprenticeID_queue,
                        std::size_t& number_of_apprentices);

        private:
            yli::ontology::GenericMasterModule* generic_master_module;

            yli::ontology::Entity* const apprentice;
            std::size_t apprenticeID { std::numeric_limits<std::size_t>::max() };
    };
}

#endif
