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
#include "generic_master_module.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace yli::ontology
{
    class Entity;

    void ApprenticeModule::bind_to_generic_master_module()
    {
        if (this->generic_master_module != nullptr)
        {
            this->generic_master_module->bind_apprentice_module(this);
        }
    }

    void ApprenticeModule::unbind_from_generic_master_module()
    {
        if (this->generic_master_module != nullptr)
        {
            this->generic_master_module->unbind_apprentice_module(this->apprenticeID);
        }
    }

    void ApprenticeModule::bind_to_new_generic_master_module(yli::ontology::GenericMasterModule* const new_generic_master)
    {
        this->unbind_from_generic_master_module(); // unbind from the current generic master if there is such.

        this->generic_master_module = new_generic_master;
        this->bind_to_generic_master_module();
    }

    ApprenticeModule::ApprenticeModule(yli::ontology::GenericMasterModule* const generic_master_module, yli::ontology::Entity* const apprentice)
        : generic_master_module(generic_master_module),
        apprentice(apprentice)
    {
        // constructor.

        this->bind_to_generic_master_module();
    }

    ApprenticeModule::~ApprenticeModule()
    {
        // destructor.

        this->unbind_from_generic_master_module();
    }

    yli::ontology::Entity* ApprenticeModule::get_master() const
    {
        if (this->generic_master_module != nullptr)
        {
            return this->generic_master_module->generic_master;
        }

        return nullptr;
    }

    yli::ontology::Entity* ApprenticeModule::get_apprentice() const
    {
        return this->apprentice;
    }
}
