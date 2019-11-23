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

#ifndef __WORLD_HPP_INCLUDED
#define __WORLD_HPP_INCLUDED

#include "entity.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

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
//    `World::render_WorldShaders(const std::size_t entityID)`.
// 2. `World::render_WorldShaders then calls `WorldShader::render` for
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

namespace yli
{
    namespace ontology
    {
        class Universe;
        class Scene;

        class World: public yli::ontology::Entity
        {
            public:
                void bind_Scene(yli::ontology::Scene* const scene);
                void unbind_Scene(const std::size_t childID);

                World(yli::ontology::Universe* const universe)
                    : Entity(universe)
                {
                    // constructor.

                    this->parent       = universe;
                    this->active_scene = nullptr;

                    this->number_of_scenes = 0;

                    // Get `childID` from `Universe` and set pointer to this `World`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->child_vector_pointers_vector.push_back(&this->scene_pointer_vector);
                    this->type_string = "yli::ontology::World*";
                    this->can_be_erased = true;
                }

                World(const World&) = delete;            // Delete copy constructor.
                World &operator=(const World&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~World();

                // this method processes the physics.
                void do_physics();

                // This method renders the active `Scene` of this `World`.
                void render();

                // This method sets the active `Scene`.
                void set_active_scene(yli::ontology::Scene* const scene);

                yli::ontology::Scene* get_active_scene() const;

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Universe* parent; // pointer to the `Universe`.

                std::vector<yli::ontology::Scene*> scene_pointer_vector;
                std::queue<std::size_t> free_sceneID_queue;
                std::size_t number_of_scenes;

                yli::ontology::Scene* active_scene;
        };
    }
}

#endif
