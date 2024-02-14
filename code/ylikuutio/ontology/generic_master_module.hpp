// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_GENERIC_MASTER_MODULE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GENERIC_MASTER_MODULE_HPP_INCLUDED

// `yli::ontology::GenericMasterModule` is a module that implements
// the master part of a master-apprentice relationship.
//
// In Ylikuutio terminology, master-apprentice relationship
// exists so that the master provides some functionality to
// the apprentice without being a direct ancestor in the
// ontological graph.
//
// Each master may have several apprentices,
// unless specifically restricted by the master.
//
// Each apprentice may have several masters of
// different types.
//
// If the master of a master-apprentice relation dies,
// the apprentice will survice.
//
// If the apprentice of a master-apprentice relation dies,
// the master will survice.

#include "indexable.hpp"
#include "apprentice_iterator.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::queue
#include <string>  // std::string
#include <vector>  // std::vector

namespace yli::ontology
{
    class Registry;
    class ApprenticeModule;
    class Entity;
    class Scene;

    class GenericMasterModule : public yli::ontology::Indexable
    {
        public:
            // Iterator typedefs.
            typedef ApprenticeIterator       iterator;
            typedef ApprenticeIterator const_iterator;

            void bind_apprentice_module(yli::ontology::ApprenticeModule& apprentice_module);
            void unbind_apprentice_module(const std::size_t apprenticeID) noexcept;
            void unbind_all_apprentice_modules_belonging_to_other_scenes(const yli::ontology::Scene* const scene) noexcept;

            // constructor.
            GenericMasterModule(yli::ontology::Entity* const generic_master, yli::ontology::Registry* const registry, const std::string& name) noexcept;

            GenericMasterModule(const GenericMasterModule&) = delete;            // Delete copy constructor.
            GenericMasterModule& operator=(const GenericMasterModule&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~GenericMasterModule() noexcept;

            yli::ontology::Entity* get_generic_master() const noexcept;

            std::vector<yli::ontology::ApprenticeModule*>& get_apprentice_module_pointer_vector_reference() noexcept;
            const std::vector<yli::ontology::ApprenticeModule*>& get_apprentice_module_pointer_vector_const_reference() const noexcept;

            std::size_t get_number_of_apprentices() const noexcept;

            yli::ontology::Entity* get(const std::size_t index) const noexcept override;

            // Iterator functions.
            iterator begin()
            {
                return iterator(this->apprentice_module_pointer_vector.begin());
            }

            iterator end()
            {
                return iterator(this->apprentice_module_pointer_vector.end());
            }

            const_iterator cbegin()
            {
                return const_iterator(this->apprentice_module_pointer_vector.begin());
            }

            const_iterator cend()
            {
                return const_iterator(this->apprentice_module_pointer_vector.end());
            }

        private:
            yli::ontology::Entity* const generic_master; // The `Entity` that owns this `GenericMasterModule`.

        protected:
            std::vector<yli::ontology::ApprenticeModule*> apprentice_module_pointer_vector;

        private:
            std::queue<std::size_t> free_apprenticeID_queue;
            std::size_t number_of_apprentices { 0 };
    };
}

#endif
