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

#ifndef __WORLD_HPP_INCLUDED
#define __WORLD_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "parent_module.hpp"
#include "entity_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <vector>   // std::vector

// `World` is a collection of `Scene`s which share some common resources,
// like `VectorFont`s. In addition to `Scene`s, each `World` may contain
// `World`-bound Entities. World-bound Entities are Entities, which simply
// bind to a `World` instead of some ontological descendant of a `World`.
//
// Most child classes of `Scene` and below classes can be converted
// into corresponding world-bound classes:
// * `Shader` -> `WorldShader`.
// * `Material` -> `WorldMaterial`.
// * `Species` -> `WorldSpecies`.
// * `Symbiosis` -> `WorldSymbiosis`.
// * `Brain` -> `WorldBrain`.
// * etc.
//
// Each `World`-bound `Entity` class inherits its base class.
//
// This conversion does not affect already existing children.
// They function just like before their parent's or parent's parent's etc.
// conversion into a `World`-bound `Entity`.
//
// So, e.g. `WorldShader` may have the following kinds of children:
// 1. `Material`,
// 2. `Symbiosis`,
// 3. `ComputeTask`,
// 4. `WorldMaterial`,
// 5. `WorldSymbiosis`,
// 6. `WorldComputeTask`.
//
// The storage of `Material`, `Symbiosis`, and `ComputeTask` entities is
// inherited from the `Shader` base class.
//
// Rendering of `WorldShader`s works as follows:
// 1. `Scene::render` calls the following function:
//    `World::render_world_shaders(const std::size_t entityID)`.
// 2. `World::render_world_shaders then calls `WorldShader::render` for
//    its every `WorldShader` child.
// 3. `WorldShader::render` then renders only those `Material`, `Symbiosis`,
//    and `ComputeTask` entities which belong to the `Scene` with that
//    specific `entityID`.
// 4. `WorldShader::render` also renders all `WorldMaterial`, `WorldSymbiosis`,
//    and `WorldComputeTask` entities. Each of these renders only those regular
//    children entities, i.e. not `World`-bound entities, that belong to
//    the `Scene` with the specific `entityID`, and also all `World`-bound
//    entities, in a similar fashion compared to `WorldShader`.
//
// TODO: implement `World`-bound entities!

namespace yli::ontology
{
    class Universe;

    class World: public yli::ontology::Entity
    {
        public:
            World(yli::ontology::Universe* const universe, yli::ontology::ParentModule* const parent_module)
                : Entity(universe, yli::ontology::EntityStruct()),
                child_of_universe(parent_module, this),
                parent_of_scenes(this)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::World*";
                this->can_be_erased = true;
            }

            World(const World&) = delete;            // Delete copy constructor.
            World &operator=(const World&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~World();

            yli::ontology::Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            yli::ontology::ChildModule child_of_universe;
            yli::ontology::ParentModule parent_of_scenes;
    };
}

#endif
