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

#ifndef __VEHICLE_HPP_INCLUDED
#define __VEHICLE_HPP_INCLUDED

#include "object.hpp"

namespace yli
{
    namespace ontology
    {
        class Universe;

        class Vehicle: public yli::ontology::Object
        {
            public:
                // constructor.
                Vehicle(yli::ontology::Universe* const universe, const yli::ontology::ObjectStruct& object_struct)
                    : Object(universe, object_struct)
                {
                    // constructor.

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Vehicle*";
                }

                Vehicle(const Vehicle&) = delete;            // Delete copy constructor.
                Vehicle &operator=(const Vehicle&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Vehicle();
        };
    }
}

#endif
