// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_MOVABLE_CONTROLLER_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MOVABLE_CONTROLLER_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "apprentice_module.hpp"
#include "generic_master_module.hpp"
#include "movable.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

// `MovableController` is a general purpose AI and controller class for `Movable`s.
// Each `MovableController` instance may do some actions for the `Movable`s bound to the `MovableController`.
// The actions the defined by the `CallbackEngine` master to which `MovableController` binds itself
// with its `apprentice_of_callback_engine`.
//
// There are some callback snippets for `MovableController` in `code/ylikuutio/movable_controller_snippets.hpp`.
// In the future, some of the callbacks will process YliLisp, with an API offered
// to the YliLisp scripts. The API still needs to be defined.
//
// `MovableController` does not own the `Movable`s it controls.
// Therefore, `MovableController`-`Movable` relationship is not a parent-child relationship.
// Instead, `MovableController`-`Movable` relationship is a master-apprentice relationship.
// Therefore, binding is done using `yli::hierarchy::bind_apprentice_to_master`.
//
// Each `MovableController` acts upon its `Movable`s immediately after the physics simulation,
// still before rendering, on each frame.
//
// `MovableController` actions should not be considered limited to the actions of living or
// conscious beings. For example, a planet `Movable` in a solar system may have a `MovableController`
// that makes it orbit its host star, and likewise a moon `Movable` may have a `MovableController` that
// makes it orbit its host planet. An electrical module `Movable` (e.g. a synthetizer module)
// may have a `MovableController` that defines how it processes its inputs and what kind of output it sends.

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
    class GenericParentModule;
    class GenericMasterModule;
    class Universe;
    class CallbackEngine;
    class Scene;
    struct MovableControllerStruct;
    class GenericMasterModule;

    class MovableController final : public Entity
    {
        private:
            MovableController(
                    yli::core::Application& application,
                    Universe& universe,
                    const MovableControllerStruct& movable_controller_struct,
                    GenericParentModule* const scene_parent_module,
                    GenericMasterModule* const callback_engine_master_module);

            ~MovableController() = default;

        public:
            Entity* get_parent() const override;

            CallbackEngine* get_callback_engine_master() const;

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

            std::size_t get_number_of_apprentices() const;

            void update();

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_scene;
            ApprenticeModule apprentice_of_callback_engine;
            GenericMasterModule master_of_movables;

            Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };

    template<>
        inline GenericMasterModule* MovableController::get_generic_master_module<Movable>()
        {
            return &this->master_of_movables;
        }
}

#endif
