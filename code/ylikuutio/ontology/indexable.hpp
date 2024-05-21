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

#ifndef YLIKUUTIO_ONTOLOGY_INDEXABLE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_INDEXABLE_HPP_INCLUDED

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::ontology
{
    class Entity;

    class Indexable
    {
        public:
            Indexable()
            {
            }

            Indexable(const Indexable&) = delete;            // Delete copy constructor.
            Indexable& operator=(const Indexable&) = delete; // Delete copy assignment.

            virtual ~Indexable()
            {
            }

            virtual yli::ontology::Entity* get(const std::size_t index) const = 0;
    };
}

#endif
