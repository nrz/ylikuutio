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

#include "apprentice_module.hpp"
#include "master_module.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace yli::ontology
{
    class Entity;

    void ApprenticeModule::bind_to_master_module()
    {
        if (this->master_module != nullptr)
        {
            yli::hierarchy::bind_apprentice_to_master<yli::ontology::ApprenticeModule*>(
                    this,
                    this->master_module->apprentice_module_pointer_vector,
                    this->master_module->free_apprenticeID_queue,
                    this->master_module->number_of_apprentices);
        }
    }

    void ApprenticeModule::unbind_from_master_module()
    {
        if (this->master_module != nullptr)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::ApprenticeModule*>(
                    this->apprenticeID,
                    this->master_module->apprentice_module_pointer_vector,
                    this->master_module->free_apprenticeID_queue,
                    this->master_module->number_of_apprentices);
        }
    }

    void ApprenticeModule::bind_to_new_master_module(yli::ontology::MasterModule* const new_master)
    {
        this->unbind_from_master_module(); // unbind from the current master if there is such.

        this->master_module = new_master;
        this->bind_to_master_module();
    }

    ApprenticeModule::ApprenticeModule(yli::ontology::MasterModule* const master_module, yli::ontology::Entity* const apprentice)
        : master_module(master_module),
        apprentice(apprentice)
    {
        // constructor.

        this->bind_to_master_module();
    }

    ApprenticeModule::~ApprenticeModule()
    {
        // destructor.

        this->unbind_from_master_module();
    }

    yli::ontology::Entity* ApprenticeModule::get_master() const
    {
        if (this->master_module != nullptr)
        {
            return this->master_module->master;
        }

        return nullptr;
    }

    yli::ontology::Entity* ApprenticeModule::get_apprentice() const
    {
        return this->apprentice;
    }
}
