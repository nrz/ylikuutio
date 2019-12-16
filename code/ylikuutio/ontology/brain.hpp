// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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
#include "brain_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <vector>   // std::vector

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

        class Brain: public yli::ontology::Entity
        {
            public:
                void bind_Movable(yli::ontology::Movable* const movable);
                void unbind_Movable(const std::size_t childID);

                Brain(yli::ontology::Universe* const universe, const yli::ontology::BrainStruct& brain_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent = brain_struct.parent;

                    // Get `childID` from the `Scene` and set pointer to this `Camera`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Brain*";
                }

                // destructor.
                ~Brain();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                void act();

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Scene* parent;

                yli::callback::CallbackEngine* callback_engine;

                // Currently only `Movable`s can be intentional Entities.
                std::vector<yli::ontology::Movable*> movable_pointer_vector;
                std::queue<std::size_t> free_movableID_queue;
                std::size_t number_of_movables;
        };
    }
}

#endif
