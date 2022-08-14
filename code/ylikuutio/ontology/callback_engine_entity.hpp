// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_CALLBACK_ENGINE_ENTITY_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_CALLBACK_ENGINE_ENTITY_HPP_INCLUDED

#include "code/ylikuutio/callback/callback_engine.hpp"
#include "child_module.hpp"
#include "entity.hpp"
#include "entity_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

namespace yli::ontology
{
    class Universe;
    class Scene;
    class GenericParentModule;

    class CallbackEngineEntity final : public yli::callback::CallbackEngine, public yli::ontology::Entity
    {
        public:
            CallbackEngineEntity(
                    yli::ontology::Universe& universe,
                    yli::ontology::GenericParentModule* const parent_module)
                : yli::callback::CallbackEngine(universe),
                Entity(universe, yli::ontology::EntityStruct()),
                child_of_universe(parent_module, this)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::CallbackEngineEntity*";
                this->can_be_erased = true;
            }

            CallbackEngineEntity(const CallbackEngineEntity&) = delete;            // Delete copy constructor.
            CallbackEngineEntity& operator=(const CallbackEngineEntity&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~CallbackEngineEntity() = default;

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::ChildModule child_of_universe;

        private:
            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
