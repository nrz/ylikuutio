// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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
#include "brain.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// `Movable` is a mixin class, not intended to be instantiated.

namespace yli
{
    namespace ontology
    {
        void Movable::bind_to_Brain()
        {
            // requirements:
            // `this->brain` must not be `nullptr`.
            yli::ontology::Brain* const brain = this->brain;

            if (brain == nullptr)
            {
                std::cerr << "ERROR: `Movable::bind_to_Brain`: `brain` is `nullptr`!\n";
                return;
            }

            // get `movableID` from `Brain` and set pointer to this `Movable`.
            this->brain->bind_Movable(this);
        }

        void Movable::unbind_from_Brain()
        {
            if (this->brain != nullptr)
            {
                this->brain->unbind_Movable(this->movableID);
            }
        }

        void Movable::bind_to_new_Brain(yli::ontology::Brain* const new_brain)
        {
            // This method sets pointer to this `Movable` to `nullptr`, sets `brain` according to the input,
            // and requests a new `movableID` from the new `Brain`.

            this->unbind_from_Brain(); // unbind from the current `Brain` if there is such.

            this->brain = new_brain;
            this->bind_to_Brain();
        }

        Movable::~Movable()
        {
            // destructor.

            this->unbind_from_Brain();
        }

        yli::ontology::Entity* Movable::get_parent() const
        {
            return this->child.get_parent();
        }

        const glm::vec3& Movable::get_cartesian_coordinates() const
        {
            return this->cartesian_coordinates;
        }

        void Movable::set_cartesian_coordinates(const glm::vec3& cartesian_coordinates)
        {
            this->cartesian_coordinates = cartesian_coordinates;
        }

        float Movable::get_horizontal_angle() const
        {
            return this->horizontal_angle;
        }

        void Movable::set_horizontal_angle(const float horizontal_angle)
        {
            this->horizontal_angle = horizontal_angle;
        }

        float Movable::get_vertical_angle() const
        {
            return this->vertical_angle;
        }

        void Movable::set_vertical_angle(const float vertical_angle)
        {
            this->vertical_angle = vertical_angle;
        }

        // Public callbacks (to be called from AI scripts written in Chibi-Scheme).

        void Movable::set_dest(yli::ontology::Movable* const movable, const float x, const float y, const float z)
        {
            // Set target towards which to move.
            movable->cartesian_coordinates = glm::vec3(x, y, z);
        }

        float Movable::get_x(const yli::ontology::Movable* const movable)
        {
            // Get x coordinate of `movable`.
            return movable->cartesian_coordinates.x;
        }

        float Movable::get_y(const yli::ontology::Movable* const movable)
        {
            // Get y coordinate of `movable`.
            return movable->cartesian_coordinates.y;
        }

        float Movable::get_z(const yli::ontology::Movable* const movable)
        {
            // Get z coordinate of `movable`.
            return movable->cartesian_coordinates.z;
        }

        float Movable::get_dest_x(const yli::ontology::Movable* const movable)
        {
            // Get x destination coordinate of `movable`.
            return movable->dest_cartesian_coordinates.x;
        }

        float Movable::get_dest_y(const yli::ontology::Movable* const movable)
        {
            // Get y destination coordinate of `movable`.
            return movable->dest_cartesian_coordinates.y;
        }

        float Movable::get_dest_z(const yli::ontology::Movable* const movable)
        {
            // Get z destination coordinate of `movable`.
            return movable->dest_cartesian_coordinates.z;
        }

        // Public callbacks end here.
    }
}
