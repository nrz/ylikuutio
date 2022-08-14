// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_MASTER_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MASTER_MODULE_HPP_INCLUDED

// `yli::ontology::MasterModule` is a module that implements
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

#include "generic_master_module.hpp"
#include "apprentice_module.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <functional> // std::function
#include <string>     // std::string

namespace yli::ontology
{
    class Registry;
    class Entity;

    template<typename M>
        class MasterModule final : public yli::ontology::GenericMasterModule
    {
        public:
            // constructor.
            MasterModule(
                    M const master,
                    yli::ontology::Registry* const registry,
                    const std::string& name,
                    std::function<void (const M&, yli::ontology::Entity*)> unbind_callback)
                : GenericMasterModule(master, registry, name),
                unbind_callback { unbind_callback }
            {
                // constructor.
            }

            MasterModule(const MasterModule&) = delete;            // Delete copy constructor.
            MasterModule& operator=(const MasterModule&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~MasterModule()
            {
                // destructor.

                for (std::size_t apprentice_i = 0; apprentice_i < this->apprentice_module_pointer_vector.size(); apprentice_i++)
                {
                    yli::ontology::ApprenticeModule* const apprentice_module = this->apprentice_module_pointer_vector[apprentice_i];

                    if (apprentice_module != nullptr)
                    {
                        // Call the unbind callback.
                        this->unbind_apprentice_module(apprentice_module->apprenticeID);
                    }
                }
            }

            M get_master() const
            {
                return this->master;
            }

            friend class yli::ontology::ApprenticeModule;

            std::function<void (const M&, yli::ontology::Entity*)> unbind_callback;
    };
}

#endif
