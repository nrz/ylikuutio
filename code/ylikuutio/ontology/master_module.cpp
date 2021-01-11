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

#include "registry.hpp"
#include "master_module.hpp"
#include "apprentice_module.hpp"
#include "entity.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string

namespace yli::ontology
{
    void MasterModule::bind_apprentice_module(yli::ontology::ApprenticeModule* const apprentice_module)
    {
        yli::hierarchy::bind_apprentice_to_master<yli::ontology::ApprenticeModule*>(
                apprentice_module,
                this->apprentice_module_pointer_vector,
                this->free_apprenticeID_queue,
                this->number_of_apprentices);
    }

    void MasterModule::unbind_apprentice_module(std::size_t apprenticeID)
    {
        yli::hierarchy::unbind_child_from_parent<yli::ontology::ApprenticeModule*>(
                apprenticeID,
                this->apprentice_module_pointer_vector,
                this->free_apprenticeID_queue,
                this->number_of_apprentices);
    }

    MasterModule::MasterModule(yli::ontology::Entity* const master, yli::ontology::Registry* const registry, const std::string& name)
        : master { master },
        number_of_apprentices { 0 }
    {
        // constructor.

        registry->add_indexable(this, name);
    }

    MasterModule::~MasterModule()
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

    yli::ontology::Entity* MasterModule::get_master() const
    {
        return this->master;
    }

    std::size_t MasterModule::get_number_of_apprentices() const
    {
        return this->number_of_apprentices;
    }

    yli::ontology::Entity* MasterModule::get(const std::size_t index) const
    {
        if (index < this->apprentice_module_pointer_vector.size())
        {
            yli::ontology::ApprenticeModule* const apprentice_module = this->apprentice_module_pointer_vector.at(index);

            if (apprentice_module != nullptr)
            {
                return apprentice_module->get_apprentice();
            }
        }

        return nullptr;
    }
}
