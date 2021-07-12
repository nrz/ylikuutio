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

#ifndef __YLIKUUTIO_ONTOLOGY_RIGID_BODY_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_RIGID_BODY_MODULE_HPP_INCLUDED

#include "rigid_body_module_struct.hpp"

// Include Bullet
#include <btBulletDynamicsCommon.h>

// Include standard headers
#include <memory>  // std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr

// `RigidBodyModule` class functions as a rigid body for Bullet physics.

namespace yli::ontology
{
    class Movable;

    class RigidBodyModule
    {
        public:
            RigidBodyModule(
                    const yli::ontology::RigidBodyModuleStruct& rigid_body_module_struct,
                    yli::ontology::Movable* const movable)
                : movable { movable },
                mass { rigid_body_module_struct.mass }
            {
                // constructor.

                if (rigid_body_module_struct.type == "sphere")
                {
                    this->collision_shape = std::make_unique<btSphereShape>(rigid_body_module_struct.radius);
                }
                else if (rigid_body_module_struct.type == "box")
                {
                    // Use box as collision shape
                    btVector3 box_half_extents(
                            static_cast<btScalar>(rigid_body_module_struct.half_extents[0]),
                            static_cast<btScalar>(rigid_body_module_struct.half_extents[1]),
                            static_cast<btScalar>(rigid_body_module_struct.half_extents[2]));
                    this->collision_shape = std::make_unique<btBoxShape>(box_half_extents);
                }

                btTransform transform;
                transform.setIdentity();
                transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));
                this->motion_state = std::make_unique<btDefaultMotionState>(transform);

                btVector3 local_inertia(0, 0, 0); // No local inertia.
                btRigidBody::btRigidBodyConstructionInfo rigid_body_info(this->mass, this->motion_state.get(), this->collision_shape.get(), local_inertia);

                this->bullet_rigid_body = std::make_unique<btRigidBody>(rigid_body_info);

                this->add_rigid_body_module_to_scene();
            }

            RigidBodyModule(const RigidBodyModule&) = delete;            // Delete copy constructor.
            RigidBodyModule &operator=(const RigidBodyModule&) = delete; // Delete copy assignment.

            // destructor.
            ~RigidBodyModule();

            void add_rigid_body_module_to_scene() const;

            btRigidBody* get_bullet_rigid_body() const;

        private:
            yli::ontology::Movable* movable { nullptr };

            std::unique_ptr<btCollisionShape> collision_shape  { nullptr };
            std::unique_ptr<btDefaultMotionState> motion_state { nullptr };
            std::unique_ptr<btRigidBody> bullet_rigid_body     { nullptr };

            float mass { 0.0f }; // An object is static if and only if its mass is 0.
    };
}

#endif
