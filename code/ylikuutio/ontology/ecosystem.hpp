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

#ifndef __YLIKUUTIO_ONTOLOGY_ECOSYSTEM_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_ECOSYSTEM_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "ecosystem_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

// `Ecosystem`s can be owners of some common resources, like `VectorFont`s.
// Compared to `Scene`s which are actual game/simulation locations,
// `Ecosystem`s only function as owners of resources shared between `Scene`s.
//
// Most child classes of `Scene` and below classes can be converted
// into corresponding ecosystem-bound classes:
// * `Shader` -> `EcosystemShader`.
// * `Material` -> `EcosystemMaterial`.
// * `Species` -> `EcosystemSpecies`.
// * `Symbiosis` -> `EcosystemSymbiosis`.
// * `Brain` -> `EcosystemBrain`.
// * etc.
//
// Each `Ecosystem`-bound `Entity` class inherits its base class.
//
// This conversion does not affect already existing children.
// They function just like before their parent's or parent's parent's etc.
// conversion into a `Ecosystem`-bound `Entity`.
//
// So, e.g. `EcosystemShader` may have the following kinds of children:
// 1. `Material`,
// 2. `Symbiosis`,
// 3. `ComputeTask`,
// 4. `EcosystemMaterial`,
// 5. `EcosystemSymbiosis`,
// 6. `EcosystemComputeTask`.
//
// The storage of `Material`, `Symbiosis`, and `ComputeTask` entities is
// inherited from the `Shader` base class.
//
// Rendering of `EcosystemShader`s works as follows:
// 1. `Scene::render` calls the following function:
//    `Ecosystem::render_ecosystem_shaders(const std::size_t entityID)`.
// 2. `Ecosystem::render_ecosystem_shaders then calls `EcosystemShader::render` for
//    its every `EcosystemShader` child.
// 3. `EcosystemShader::render` then renders only those `Material`, `Symbiosis`,
//    and `ComputeTask` entities which belong to the `Scene` with that
//    specific `entityID`.
// 4. `EcosystemShader::render` also renders all `EcosystemMaterial`, `EcosystemSymbiosis`,
//    and `EcosystemComputeTask` entities. Each of these renders only those regular
//    children entities, i.e. not `Ecosystem`-bound entities, that belong to
//    the `Scene` with the specific `entityID`, and also all `Ecosystem`-bound
//    entities, in a similar fashion compared to `EcosystemShader`.
//
// TODO: implement `Ecosystem`-bound entities!

namespace yli::ontology
{
    class ParentModule;
    class Universe;
    class Scene;

    class Ecosystem: public yli::ontology::Entity
    {
        public:
            Ecosystem(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::EcosystemStruct& ecosystem_struct,
                    yli::ontology::ParentModule* const parent_module)
                : Entity(universe, ecosystem_struct),
                child_of_universe(parent_module, this)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Ecosystem*";
                this->can_be_erased = true;
            }

            Ecosystem(const Ecosystem&) = delete;            // Delete copy constructor.
            Ecosystem& operator=(const Ecosystem&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Ecosystem();

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::ChildModule child_of_universe;

            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
