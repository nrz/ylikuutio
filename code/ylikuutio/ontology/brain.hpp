// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_BRAIN_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_BRAIN_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_master_module.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

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

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
    class CallbackEngine;
    class Scene;
    class GenericParentModule;
    struct BrainStruct;

    class Brain final : public yli::ontology::Entity
    {
        private:
            Brain(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::BrainStruct& brain_struct,
                    yli::ontology::GenericParentModule* const scene_parent_module);

            // destructor.
            ~Brain() = default;

        public:
            yli::ontology::Entity* get_parent() const override;

            yli::ontology::GenericMasterModule* get_generic_master_module() const;

            std::size_t get_number_of_apprentices() const;

            void act();

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            yli::ontology::ChildModule child_of_scene;
            yli::ontology::GenericMasterModule master_of_movables;

            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            yli::ontology::CallbackEngine* callback_engine { nullptr };
    };
}

#endif
