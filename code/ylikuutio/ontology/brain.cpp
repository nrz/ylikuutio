// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include "universe.hpp"
#include "callback_engine.hpp"
#include "scene.hpp"
#include "request_resolver.hpp"
#include "brain_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;

    Brain::Brain(
            yli::core::Application& application,
            Universe& universe,
            const BrainStruct& brain_struct,
            GenericParentModule* const scene_parent_module,
            GenericMasterModule* const callback_engine_master_module)
        : Entity(application, universe, brain_struct),
        child_of_scene(scene_parent_module, *this),
        apprentice_of_callback_engine(callback_engine_master_module, this),
        master_of_movables(this, &this->registry, "movables")
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Brain*";
        this->can_be_erased = true;
    }

    Entity* Brain::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    CallbackEngine* Brain::get_callback_engine_master() const
    {
        return static_cast<CallbackEngine*>(this->apprentice_of_callback_engine.get_master());
    }

    std::size_t Brain::get_number_of_children() const
    {
        return 0; // `Brain` has no children. `Movable`s controlled by `Brain` are not its children.
    }

    std::size_t Brain::get_number_of_descendants() const
    {
        return 0; // `Brain` has no children. `Movable`s controlled by `Brain` are not its children.
    }

    Scene* Brain::get_scene() const
    {
        return static_cast<Scene*>(this->get_parent());
    }

    std::size_t Brain::get_number_of_apprentices() const
    {
        return this->master_of_movables.get_number_of_apprentices(); // `Movable`s controlled by `Brain` are its apprentices.
    }

    void Brain::update()
    {
        CallbackEngine* const callback_engine_master = this->get_callback_engine_master();

        if (callback_engine_master == nullptr)
        {
            return;
        }

        for (const ApprenticeModule* movable_apprentice_module : this->master_of_movables.get_apprentice_module_pointer_vector_const_reference())
        {
            if (movable_apprentice_module == nullptr)
            {
                continue;
            }

            Movable* movable = static_cast<Movable*>(movable_apprentice_module->get_apprentice());

            if (movable != nullptr)
            {
                callback_engine_master->execute(yli::data::AnyValue(*movable));
            }
        }
    }
}
