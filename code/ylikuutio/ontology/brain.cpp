// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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
#include "movable.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr

namespace yli::ontology
{
    void Brain::bind_movable(yli::ontology::Movable* const movable)
    {
        // get `childID` from `Brain` and set pointer to `movable`.
        yli::hierarchy::bind_apprentice_to_master<yli::ontology::Movable*>(
                movable,
                movable->movableID,
                this->movable_pointer_vector,
                this->free_movableID_queue,
                this->number_of_movables);
    }

    void Brain::unbind_movable(const std::size_t movableID)
    {
        yli::hierarchy::unbind_child_from_parent(
                movableID,
                this->movable_pointer_vector,
                this->free_movableID_queue,
                this->number_of_movables);
    }

    Brain::~Brain()
    {
        // destructor.

        for (std::size_t child_i = 0; child_i < this->movable_pointer_vector.size(); child_i++)
        {
            yli::ontology::Movable* const movable = this->movable_pointer_vector[child_i];

            if (movable != nullptr)
            {
                movable->unbind_from_brain();
            }
        }
    }

    yli::ontology::Entity* Brain::get_parent() const
    {
        return this->child_of_scene.get_parent();
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
        return this->number_of_movables; // `Movable`s controlled by `Brain` are its apprentices.
    }

    void Brain::act()
    {
        if (this->callback_engine == nullptr)
        {
            std::cerr << "ERROR: `Brain::act`: `this->callback_engine` is `nullptr`!\n";
            return;
        }

        for (std::size_t movable_i = 0; movable_i < this->movable_pointer_vector.size(); movable_i++)
        {
            // Apply this `Brain` to the current `Movable`.
            yli::ontology::Movable* movable = this->movable_pointer_vector[movable_i];

            if (movable == nullptr)
            {
                // Do not waste time in calling the callback function for `nullptr` targets.
                continue;
            }

            this->callback_engine->execute(std::make_shared<yli::common::AnyValue>(movable));
        }
    }
}
