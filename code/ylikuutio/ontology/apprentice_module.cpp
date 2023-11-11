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

#include "apprentice_module.hpp"
#include "generic_master_module.hpp"
#include "entity.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class Entity;
    class Scene;

    void ApprenticeModule::bind_to_generic_master_module() noexcept
    {
        if (this->generic_master_module != nullptr)
        {
            this->generic_master_module->bind_apprentice_module(*this);
        }
    }

    void ApprenticeModule::unbind_from_any_master_belonging_to_other_scene(
            const yli::ontology::Scene& scene) noexcept
    {
        yli::ontology::Entity* const master = this->get_master();

        if (master != nullptr)
        {
            const yli::ontology::Scene* const master_scene = master->get_scene();

            if (master_scene != nullptr && master_scene != &scene)
            {
                // Master belongs to a different `Scene` compared to what apprentice plans to bind to.
                // Therefore apprentice will unbind from master.
                this->unbind_from_generic_master_module();
            }
        }
    }

    void ApprenticeModule::unbind_from_generic_master_module() noexcept
    {
        if (this->generic_master_module != nullptr && this->apprenticeID != std::numeric_limits<std::size_t>::max())
        {
            this->generic_master_module->unbind_apprentice_module(this->apprenticeID);
        }
    }

    void ApprenticeModule::bind_to_new_generic_master_module(
            yli::ontology::GenericMasterModule* const new_generic_master) noexcept
    {
        this->generic_master_module = new_generic_master;
        this->bind_to_generic_master_module();
    }

    void ApprenticeModule::unbind_and_bind_to_new_generic_master_module(
            yli::ontology::GenericMasterModule* const new_generic_master) noexcept
    {
        if (new_generic_master != this->generic_master_module)
        {
            this->unbind_from_generic_master_module();
            this->bind_to_new_generic_master_module(new_generic_master);
        }
    }

    ApprenticeModule::ApprenticeModule(
            yli::ontology::GenericMasterModule* const generic_master_module,
            yli::ontology::Entity* const apprentice) noexcept
        : generic_master_module(generic_master_module),
        apprentice(apprentice)
    {
        // constructor.

        this->bind_to_generic_master_module();
    }

    ApprenticeModule::~ApprenticeModule() noexcept
    {
        // destructor.

        this->unbind_from_generic_master_module();
    }

    yli::ontology::Entity* ApprenticeModule::get_master() const noexcept
    {
        if (this->generic_master_module != nullptr)
        {
            return this->generic_master_module->get_generic_master();
        }

        return nullptr;
    }

    yli::ontology::Entity* ApprenticeModule::get_apprentice() const noexcept
    {
        return this->apprentice;
    }

    std::size_t ApprenticeModule::get_apprenticeID() const noexcept
    {
        return this->apprenticeID;
    }

    void ApprenticeModule::release() noexcept
    {
        this->generic_master_module = nullptr;
        this->apprenticeID = std::numeric_limits<std::size_t>::max();
    }
}
