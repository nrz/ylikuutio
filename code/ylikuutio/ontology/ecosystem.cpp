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

#include "ecosystem.hpp"
#include "ecosystem_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/datatype.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

namespace yli::ontology
{
    class Universe;
    class Scene;

    Ecosystem::Ecosystem(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::EcosystemStruct& ecosystem_struct,
            yli::ontology::GenericParentModule* const parent_module)
        : Entity(application, universe, ecosystem_struct),
        child_of_universe(parent_module, this),
        parent_of_pipelines(
                this,
                &this->registry,
                application.get_memory_allocator(yli::data::Datatype::PIPELINE),
                "pipelines"),
        parent_of_materials(
                this,
                &this->registry,
                application.get_memory_allocator(yli::data::Datatype::MATERIAL),
                "materials"),
        parent_of_species(
                this,
                &this->registry,
                application.get_memory_allocator(yli::data::Datatype::SPECIES),
                "species"),
        parent_of_symbioses(
                this,
                &this->registry,
                application.get_memory_allocator(yli::data::Datatype::SYMBIOSIS),
                "symbioses")
    {
        // constructor.

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Ecosystem*";
        this->can_be_erased = true;
    }

    yli::ontology::Entity* Ecosystem::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    yli::ontology::Scene* Ecosystem::get_scene() const
    {
        // `Ecosystem` does not belong in any `Scene`.
        return nullptr;
    }

    std::size_t Ecosystem::get_number_of_children() const
    {
        return this->parent_of_pipelines.get_number_of_children() +
            this->parent_of_materials.get_number_of_children() +
            this->parent_of_species.get_number_of_children() +
            this->parent_of_symbioses.get_number_of_children();
    }

    std::size_t Ecosystem::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_pipelines.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_materials.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_species.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_symbioses.child_pointer_vector);
    }
}
