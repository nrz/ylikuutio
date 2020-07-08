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
#include "movable.hpp"
#include "child_module.hpp"
#include "master_module.hpp"
#include "brain_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <vector>   // std::vector

// `yli::ontology::Brain` is a general purpose AI and controller class for `Movable`s.
// Each `Brain` instance may do some actions for the `Movable`s bound to the `Brain`.
// The actions the defined in the callback, referenced using `this->callback_engine`.
// There are some callback snippets for `Brain` in `code/ylikuutio/brain_snippets.hpp`.
// In the future, some of the callbacks will process YliLisp, with an API offered
// to the YliLisp scripts. The API still needs to be defined.
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

namespace yli::callback
{
    class CallbackEngine;
}

namespace yli::ontology
{
    class Universe;
    class Scene;
    class ParentModule;

    class Brain: public yli::ontology::Entity
    {
        public:
            Brain(yli::ontology::Universe* const universe, const yli::ontology::BrainStruct& brain_struct, yli::ontology::ParentModule* const parent_module)
                : Entity(universe, brain_struct),
                child_of_scene(parent_module, this),
                master_of_movables(this)
            {
                // constructor.
                this->callback_engine    = brain_struct.callback_engine;

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Brain*";
                this->can_be_erased = true;
            }

            // destructor.
            ~Brain();

            yli::ontology::Entity* get_parent() const override;

            std::size_t get_number_of_apprentices() const;

            void act();

            yli::ontology::ChildModule child_of_scene;
            yli::ontology::MasterModule<yli::ontology::Brain*, yli::ontology::Movable*> master_of_movables;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            std::shared_ptr<yli::callback::CallbackEngine> callback_engine;
    };
}

#endif
