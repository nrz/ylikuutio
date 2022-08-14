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

#include "scene.hpp"
#include "rigid_body_module.hpp"
#include "scene.hpp"

// Include Bullet
#include <btBulletDynamicsCommon.h>

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class Entity;

    void RigidBodyModule::add_rigid_body_module_to_scene(yli::ontology::Scene* const scene) const
    {
        // `RigidBodyModule` can not ask the `Scene` using `Entity::get_scene`, because `Movable`
        // is not initialized before initialization of `RigidBodyModule` composited in it.
        // Trying to do that would lead to calling pure virtual method and program termination.
        // Therefore `scene` needs to be passed to `Movable` constructor.

        if (scene == nullptr)
        {
            std::cerr << "ERROR: `RigidBodyModule::add_rigid_body_module_to_scene`: `scene` is `nullptr`!\n";
            return;
        }

        // Add the rigid body to the dynamics world.
        scene->add_rigid_body_module(*this, scene);
    }

    btRigidBody* RigidBodyModule::get_bullet_rigid_body() const
    {
        if (this->bullet_rigid_body == nullptr)
        {
            return nullptr;
        }

        return this->bullet_rigid_body.get();
    }
}
