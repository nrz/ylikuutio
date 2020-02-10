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

#ifndef __BRAIN_HPP_INCLUDED
#define __BRAIN_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "brain_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <vector>   // std::vector

// `yli::ontology::Brain` is a general purpose AI and controller class for `Movable`s.
// Each `Brain` instance may do some actions for the `Movable`s bound to the `Brain`.
// The actions the defined in the callback, referenced using `this->callback_engine`.
// Currently there are some example callbacks for `Brain` in `app/app_brain.hpp`.
// In the future, some of the callbacks will process s7 Scheme, with an API offered
// to the s7 Scheme scripts. The API still needs to be defined.
//
// `Brain` does not own the `Movable`s it controls.
// Therefore, `Brain`-`Movable` relationship is not a parent-child relationship.
// Instead, `Brain`-`Movable` relationship is a master-apprentice relationship.
// Therefore, binding is done using `yli::hierarchy::bind_apprentice_to_master`.
//
// Each `Brain` acts upon its `Movable`s immediately after the physics simulation,
// still before rendering, on each frame.
//
// `Brain` actions should not be considered limited to the actions of living or
// conscious beings. For example, a planet `Movable` in a solar system may have a `Brain`
// that makes it orbit its host star, and likewise a moon `Movable` may have a `Brain` that
// makes it orbit its host planet. An electrical module `Movable` (e.g. a synthetizer module)
// may have a `Brain` that defines how it processes its inputs and what kind of output it sends.

namespace yli
{
    namespace callback
    {
        class CallbackEngine;
    }

    namespace ontology
    {
        class Scene;
        class Movable;
        class ParentModule;

        class Brain: public yli::ontology::Entity
        {
            public:
                void bind_Movable(yli::ontology::Movable* const movable);
                void unbind_Movable(const std::size_t movableID);

                Brain(yli::ontology::Universe* const universe, const yli::ontology::BrainStruct& brain_struct, yli::ontology::ParentModule* const parent_module)
                    : Entity(universe),
                    child_of_scene((yli::ontology::Entity*) brain_struct.parent, parent_module, this)
                {
                    // constructor.
                    this->callback_engine    = brain_struct.callback_engine;
                    this->number_of_movables = 0;

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Brain*";
                    this->can_be_erased = true;
                }

                // destructor.
                ~Brain();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                std::size_t get_number_of_apprentices() const;

                void act();

                yli::ontology::ChildModule child_of_scene;

            private:
                std::shared_ptr<yli::callback::CallbackEngine> callback_engine;

                // Currently only `Movable`s can be intentional Entities.
                std::vector<yli::ontology::Movable*> movable_pointer_vector;
                std::queue<std::size_t> free_movableID_queue;
                std::size_t number_of_movables;
        };
    }
}

#endif
