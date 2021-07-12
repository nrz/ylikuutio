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

#include "movable.hpp"
#include "scene.hpp"
#include "rigid_body_module.hpp"

// Include Bullet
#include <btBulletDynamicsCommon.h>

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::ontology
{
    class Entity;

    RigidBodyModule::~RigidBodyModule()
    {
        // destructor.
    }

    void RigidBodyModule::add_rigid_body_module_to_scene() const
    {
        yli::ontology::Movable* const movable = this->movable;

        if (movable == nullptr)
        {
            std::cerr << "ERROR: `RigidBodyModule::add_rigid_body_module_to_scene`: `movable` is `nullptr`!\n";
            return;
        }

        yli::ontology::Scene* const scene = movable->get_scene();

        if (scene == nullptr)
        {
            std::cerr << "ERROR: `RigidBodyModule::add_rigid_body_module_to_scene`: `scene` is `nullptr`!\n";
            return;
        }

        // Add the rigid body to the dynamics world.
        scene->add_rigid_body_module(*this);
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
