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

#ifndef YLIKUUTIO_ONTOLOGY_APPRENTICE_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_APPRENTICE_ITERATOR_HPP_INCLUDED

#include "apprentice_module.hpp"

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;

    class ApprenticeIterator final
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = Entity*;
            using difference_type   = std::ptrdiff_t;
            using pointer           = Entity**;
            using reference         = Entity*&;

            explicit ApprenticeIterator(std::vector<ApprenticeModule*>::iterator it)
                : it { it }
            {
            }

            // copy constructor.
            ApprenticeIterator(const ApprenticeIterator&) = default;

            // copy assignment.
            ApprenticeIterator& operator=(const ApprenticeIterator&) = default;

            // assignment of `std::vector` iterator.
            ApprenticeIterator& operator=(std::vector<ApprenticeModule*>::iterator it)
            {
                this->it = it;
                return *this;
            }

            ~ApprenticeIterator() = default;

            bool operator==(const ApprenticeIterator& other_it) const noexcept
            {
                return this->it == other_it.it;
            }

            bool operator!=(const ApprenticeIterator& other_it) const = default;

            ApprenticeIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            ApprenticeIterator& operator--()
            {
                --this->it;
                return *this;
            }

            ApprenticeIterator& operator++(int)
            {
                ApprenticeIterator& temp { *this };
                ++this->it;
                return temp;
            }

            ApprenticeIterator& operator--(int)
            {
                ApprenticeIterator& temp { *this };
                --this->it;
                return temp;
            }

            Entity* operator*()
            {
                ApprenticeModule* const apprentice_module = *(this->it);

                if (apprentice_module != nullptr)
                {
                    return apprentice_module->get_apprentice();
                }

                return nullptr;
            }

        private:
            // Note: `GenericMasterModule` stores pointers to `ApprenticeModule`s,
            // not pointers to Entities directly, like `GenericParentModule` does!
            std::vector<ApprenticeModule*>::iterator it;
    };
}

#endif
