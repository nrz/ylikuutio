// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include <cstddef>  // std::size_t
#include <iostream> // std::cerr
#include <limits>   // std::numeric_limits
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Scene;

    void GenericMasterModule::bind_apprentice_module(ApprenticeModule& apprentice_module)
    {
        yli::hierarchy::bind_apprentice_to_master<ApprenticeModule>(
                apprentice_module,
                this->apprentice_module_pointer_vector,
                this->free_apprenticeID_queue,
                this->number_of_apprentices);
    }

    void GenericMasterModule::unbind_apprentice_module(const std::size_t apprenticeID) noexcept
    {
        if (apprenticeID == std::numeric_limits<std::size_t>::max())
        {
            return; // No changes happened.
        }

        if (apprenticeID >= this->apprentice_module_pointer_vector.size())
        {
            std::cerr << "ERROR: `GenericMasterModule::unbind_apprentice_module`: `apprenticeID` " << apprenticeID <<
                " is out of bounds, size is " << this->apprentice_module_pointer_vector.size() << "\n";
            return; // No changes happened.
        }

        // `ApprenticeModule*` must be read into a pointer before unbinding otherwise it will be out of bounds access.
        ApprenticeModule* const apprentice_module = this->apprentice_module_pointer_vector.at(apprenticeID);

        if (apprentice_module == nullptr)
        {
            return; // No changes happened.
        }

        yli::hierarchy::unbind_child_from_parent<ApprenticeModule*>(
                apprenticeID,
                this->apprentice_module_pointer_vector,
                this->free_apprenticeID_queue,
                this->number_of_apprentices);

        apprentice_module->release();
    }

    void GenericMasterModule::unbind_all_apprentice_modules_belonging_to_other_scenes(const Scene* const scene) noexcept
    {
        for (std::size_t apprenticeID = 0; apprenticeID < this->apprentice_module_pointer_vector.size(); apprenticeID++)
        {
            const ApprenticeModule* const apprentice_module = this->apprentice_module_pointer_vector.at(apprenticeID);

            if (apprentice_module != nullptr)
            {
                const Entity* const apprentice = apprentice_module->get_apprentice();

                if (apprentice->get_scene() != scene)
                {
                    // If the `Scene` of the apprentice is some other `Scene` or `nullptr`,
                    // then unbind the apprentice from this `GenericMasterModule`.
                    this->unbind_apprentice_module(apprenticeID);
                }
            }
        }
    }

    GenericMasterModule::GenericMasterModule(Entity* const generic_master, Registry* const registry, const std::string& name) noexcept
        : generic_master { generic_master }
    {
        registry->add_indexable(*this, name);
    }

    GenericMasterModule::~GenericMasterModule()
    {
        for (std::size_t apprentice_i = 0; apprentice_i < this->apprentice_module_pointer_vector.size(); apprentice_i++)
        {
            const ApprenticeModule* const apprentice_module = this->apprentice_module_pointer_vector.at(apprentice_i);

            if (apprentice_module != nullptr)
            {
                // Call the unbind callback.
                this->unbind_apprentice_module(apprentice_module->apprenticeID);
            }
        }
    }

    Entity* GenericMasterModule::get_generic_master() const noexcept
    {
        return this->generic_master;
    }

    std::vector<ApprenticeModule*>& GenericMasterModule::get_apprentice_module_pointer_vector_reference() noexcept
    {
        return this->apprentice_module_pointer_vector;
    }

    const std::vector<ApprenticeModule*>& GenericMasterModule::get_apprentice_module_pointer_vector_const_reference() const noexcept
    {
        return this->apprentice_module_pointer_vector;
    }

    std::size_t GenericMasterModule::get_number_of_apprentices() const noexcept
    {
        return this->number_of_apprentices;
    }

    Entity* GenericMasterModule::get(const std::size_t index) const noexcept
    {
        if (index < this->apprentice_module_pointer_vector.size())
        {
            const ApprenticeModule* const apprentice_module = this->apprentice_module_pointer_vector.at(index);

            if (apprentice_module != nullptr)
            {
                return apprentice_module->get_apprentice();
            }
        }

        return nullptr;
    }
}
