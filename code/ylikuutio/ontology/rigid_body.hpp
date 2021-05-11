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

#ifndef __YLIKUUTIO_ONTOLOGY_RIGID_BODY_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_RIGID_BODY_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "scene.hpp"
#include "rigid_body_struct.hpp"

// Include Bullet
#include <btBulletDynamicsCommon.h>

// Include standard headers
#include <cstddef> // std::size_t
#include <memory>  // std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr

// `RigidBody` class functions as a rigid body for Bullet physics.
// Each `RigidBody` has 0 or more apprentices that are `Movable`s.

namespace yli::ontology
{
    class Universe;
    class Entity;
    class ParentModule; // TODO: delete this line if `ParentModule` is not needed!

    class RigidBody: public yli::ontology::Entity
    {
        public:
            RigidBody(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::RigidBodyStruct& rigid_body_struct,
                    yli::ontology::ParentModule* const parent_module)
                : Entity(universe, rigid_body_struct),
                child_of_scene(parent_module, this),
                parent { rigid_body_struct.parent },
                mass { rigid_body_struct.mass }
            {
                // constructor.

                if (rigid_body_struct.type == "sphere")
                {
                    this->collision_shape = std::make_unique<btSphereShape>(rigid_body_struct.radius);
                }
                else if (rigid_body_struct.type == "box")
                {
                    // Use box as collision shape
                    btVector3 box_half_extents(
                            static_cast<btScalar>(rigid_body_struct.half_extents[0]),
                            static_cast<btScalar>(rigid_body_struct.half_extents[1]),
                            static_cast<btScalar>(rigid_body_struct.half_extents[2]));
                    this->collision_shape = std::make_unique<btBoxShape>(box_half_extents);
                }

                btTransform transform;
                transform.setIdentity();
                transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));
                this->motion_state = std::make_unique<btDefaultMotionState>(transform);

                btVector3 local_inertia(0, 0, 0); // No local inertia.
                btRigidBody::btRigidBodyConstructionInfo rigid_body_info(this->mass, this->motion_state.get(), this->collision_shape.get(), local_inertia);

                this->bullet_rigid_body = std::make_unique<btRigidBody>(rigid_body_info);

                yli::ontology::Scene* const scene = static_cast<yli::ontology::Scene*>(this->child_of_scene.get_parent());

                if (scene != nullptr)
                {
                    // Add the rigid body to the dynamics world.
                    scene->add_rigid_body(this);
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::RigidBody*";
                this->can_be_erased = true;
            }

            RigidBody(const RigidBody&) = delete;            // Delete copy constructor.
            RigidBody &operator=(const RigidBody&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~RigidBody();

            yli::ontology::Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            btRigidBody* get_bullet_rigid_body() const;

            yli::ontology::ChildModule child_of_scene;

        private:
            yli::ontology::Entity* parent { nullptr };

            std::unique_ptr<btCollisionShape> collision_shape  { nullptr };
            std::unique_ptr<btDefaultMotionState> motion_state { nullptr };
            std::unique_ptr<btRigidBody> bullet_rigid_body     { nullptr };

            float mass { 0.0f }; // An object is static if and only if its mass is 0.
    };
}

#endif
