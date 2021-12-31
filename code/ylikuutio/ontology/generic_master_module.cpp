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
#include "generic_master_module.hpp"
#include "apprentice_module.hpp"
#include "entity.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace yli::ontology
{
    class Scene;

    void GenericMasterModule::bind_apprentice_module(yli::ontology::ApprenticeModule* const apprentice_module)
    {
        yli::hierarchy::bind_apprentice_to_master<yli::ontology::ApprenticeModule*>(
                apprentice_module,
                this->apprentice_module_pointer_vector,
                this->free_apprenticeID_queue,
                this->number_of_apprentices);
    }

    void GenericMasterModule::unbind_apprentice_module(const std::size_t apprenticeID)
    {
        yli::hierarchy::unbind_child_from_parent<yli::ontology::ApprenticeModule*>(
                apprenticeID,
                this->apprentice_module_pointer_vector,
                this->free_apprenticeID_queue,
                this->number_of_apprentices);
    }

    void GenericMasterModule::unbind_all_apprentice_modules()
    {
        for (std::size_t apprenticeID = 0; apprenticeID < this->apprentice_module_pointer_vector.size(); apprenticeID++)
        {
            this->unbind_apprentice_module(apprenticeID);
        }
    }

    void GenericMasterModule::unbind_all_apprentice_modules_belonging_to_other_scenes(yli::ontology::Scene* const scene)
    {
        for (std::size_t apprenticeID = 0; apprenticeID < this->apprentice_module_pointer_vector.size(); apprenticeID++)
        {
            yli::ontology::ApprenticeModule* const apprentice_module = this->apprentice_module_pointer_vector.at(apprenticeID);

            if (apprentice_module != nullptr)
            {
                yli::ontology::Entity* const apprentice = apprentice_module->get_apprentice();

                if (apprentice->get_scene() != scene)
                {
                    // If the `Scene` of the apprentice is some other `Scene` or `nullptr`,
                    // then unbind the apprentice from this `GenericMasterModule`.
                    this->unbind_apprentice_module(apprenticeID);
                }
            }
        }
    }

    GenericMasterModule::GenericMasterModule(yli::ontology::Entity* const generic_master, yli::ontology::Registry* const registry, const std::string& name)
        : generic_master { generic_master },
        number_of_apprentices { 0 }
    {
        // constructor.

        registry->add_indexable(this, name);
    }

    GenericMasterModule::~GenericMasterModule()
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

    yli::ontology::Entity* GenericMasterModule::get_generic_master() const
    {
        return this->generic_master;
    }

    std::vector<yli::ontology::ApprenticeModule*>& GenericMasterModule::get_apprentice_module_pointer_vector_reference()
    {
        return this->apprentice_module_pointer_vector;
    }

    const std::vector<yli::ontology::ApprenticeModule*>& GenericMasterModule::get_apprentice_module_pointer_vector_const_reference() const
    {
        return this->apprentice_module_pointer_vector;
    }

    std::size_t GenericMasterModule::get_number_of_apprentices() const
    {
        return this->number_of_apprentices;
    }

    yli::ontology::Entity* GenericMasterModule::get(const std::size_t index) const
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
