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

#include "brain.hpp"
#include "generic_master_module.hpp"
#include "callback_engine.hpp"
#include "scene.hpp"
#include "movable.hpp"
#include "brain_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;

    Brain::Brain(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::BrainStruct& brain_struct,
            yli::ontology::GenericParentModule* const parent_module)
        : Entity(application, universe, brain_struct),
        child_of_scene(parent_module, this),
        master_of_movables(this, &this->registry, "movables")
    {
        // constructor.
        this->callback_engine    = brain_struct.callback_engine;

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Brain*";
        this->can_be_erased = true;
    }

    yli::ontology::Entity* Brain::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    yli::ontology::GenericMasterModule* Brain::get_generic_master_module() const
    {
        return const_cast<yli::ontology::GenericMasterModule*>(&this->master_of_movables);
    }

    std::size_t Brain::get_number_of_children() const
    {
        return 0; // `Brain` has no children. `Movable`s controlled by `Brain` are not its children.
    }

    std::size_t Brain::get_number_of_descendants() const
    {
        return 0; // `Brain` has no children. `Movable`s controlled by `Brain` are not its children.
    }

    yli::ontology::Scene* Brain::get_scene() const
    {
        return static_cast<yli::ontology::Scene*>(this->get_parent());
    }

    std::size_t Brain::get_number_of_apprentices() const
    {
        return this->master_of_movables.get_number_of_apprentices(); // `Movable`s controlled by `Brain` are its apprentices.
    }

    void Brain::act()
    {
        if (this->callback_engine == nullptr)
        {
            std::cerr << "ERROR: `Brain::act`: `this->callback_engine` is `nullptr`!\n";
            return;
        }

        for (const yli::ontology::ApprenticeModule* apprentice_module : this->master_of_movables.get_apprentice_module_pointer_vector_const_reference())
        {
            if (apprentice_module == nullptr)
            {
                continue;
            }

            yli::ontology::Movable* movable = static_cast<yli::ontology::Movable*>(apprentice_module->get_apprentice());

            if (movable != nullptr)
            {
                this->callback_engine->execute(yli::data::AnyValue(*movable));
            }
        }
    }
}
