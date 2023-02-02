// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_RIGID_BODY_MODULE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_RIGID_BODY_MODULE_HPP_INCLUDED

#include "rigid_body_module_struct.hpp"

// `RigidBodyModule` class functions as a rigid body for physics.

namespace yli::ontology
{
    class Scene;
    class Movable;
    class Scene;

    class RigidBodyModule final
    {
        public:
            RigidBodyModule(
                    const yli::ontology::RigidBodyModuleStruct& rigid_body_module_struct,
                    yli::ontology::Scene* const scene,
                    yli::ontology::Movable* const movable)
                : movable { movable },
                mass { rigid_body_module_struct.mass }
            {
                // constructor.

                this->add_rigid_body_module_to_scene(scene);
            }

            RigidBodyModule(const RigidBodyModule&) = delete;            // Delete copy constructor.
            RigidBodyModule &operator=(const RigidBodyModule&) = delete; // Delete copy assignment.

            // destructor.
            ~RigidBodyModule() = default;

            void add_rigid_body_module_to_scene(yli::ontology::Scene* const scene) const;

        private:
            yli::ontology::Movable* movable { nullptr };

            float mass { 0.0f }; // An object is static if and only if its mass is 0.
    };
}

#endif
