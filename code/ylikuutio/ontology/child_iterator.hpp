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

#ifndef YLIKUUTIO_ONTOLOGY_CHILD_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CHILD_ITERATOR_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;

    class ChildIterator final
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = yli::ontology::Entity*;
            using difference_type   = std::ptrdiff_t;
            using pointer           = yli::ontology::Entity**;
            using reference         = yli::ontology::Entity*&;

            ChildIterator(std::vector<yli::ontology::Entity*>::iterator it)
                : it { it }
            {
                // constructor.
            }

            // copy constructor.
            ChildIterator(const ChildIterator&) = default;

            // copy assignment.
            ChildIterator& operator=(const ChildIterator&) = default;

            // assignment of `std::vector` iterator.
            ChildIterator& operator=(std::vector<yli::ontology::Entity*>::iterator it)
            {
                this->it = it;
                return *this;
            }

            ~ChildIterator() = default;

            bool operator==(const ChildIterator& other_it) const
            {
                return this->it == other_it.it;
            }

            bool operator!=(const ChildIterator& other_it) const = default;

            ChildIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            ChildIterator& operator--()
            {
                --this->it;
                return *this;
            }

            ChildIterator& operator++(int)
            {
                ChildIterator& temp { *this };
                ++this->it;
                return temp;
            }

            ChildIterator& operator--(int)
            {
                ChildIterator& temp { *this };
                --this->it;
                return temp;
            }

            yli::ontology::Entity* operator*()
            {
                return *(this->it);
            }

        private:
            // Note: `GenericParentModule` stores pointers to Entities directly!
            // This is different compared to `GenericMasterModule`!
            std::vector<yli::ontology::Entity*>::iterator it;
    };
}

#endif
