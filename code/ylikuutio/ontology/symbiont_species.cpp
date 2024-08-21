// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "symbiont_species.hpp"
#include "symbiont_species_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;

    SymbiontSpecies::SymbiontSpecies(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::SymbiontSpeciesStruct& symbiont_species_struct,
            yli::ontology::GenericParentModule* const symbiont_material_parent_module)
        : Entity(application, universe, symbiont_species_struct),
        child_of_symbiont_material(symbiont_material_parent_module, *this),
        master_of_bionts(this, &this->registry, "bionts"),
        mesh(universe, symbiont_species_struct)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::SymbiontSpecies*";
    }

    yli::ontology::Entity* SymbiontSpecies::get_parent() const
    {
        return this->child_of_symbiont_material.get_parent();
    }

    std::size_t SymbiontSpecies::get_number_of_apprentices() const
    {
        return this->master_of_bionts.get_number_of_apprentices(); // `Biont`s belonging to `SymbiontSpecies` are its apprentices.
    }

    yli::ontology::GenericMasterModule* SymbiontSpecies::get_renderables_container() const
    {
        return const_cast<yli::ontology::GenericMasterModule*>(&this->master_of_bionts);
    }

    yli::ontology::Scene* SymbiontSpecies::get_scene() const
    {
        const yli::ontology::Entity* const symbiont_material_parent = this->get_parent();

        if (symbiont_material_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `SymbiontSpecies::get_scene`: `symbiont_material_parent` is `nullptr`!");
        }

        return symbiont_material_parent->get_scene();
    }

    std::size_t SymbiontSpecies::get_number_of_children() const
    {
        return 0; // `SymbiontSpecies` has no children.
    }

    std::size_t SymbiontSpecies::get_number_of_descendants() const
    {
        return 0; // `SymbiontSpecies` has no children.
    }
}
