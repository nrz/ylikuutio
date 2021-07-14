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

#include "brain.hpp"
#include "generic_master_module.hpp"
#include "movable.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr

namespace yli::ontology
{
    Brain::~Brain()
    {
        // destructor.
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
                // Do not waste time in calling the callback function for `nullptr` targets.
                this->callback_engine->execute(std::make_shared<yli::data::AnyValue>(movable));
            }
        }
    }
}
