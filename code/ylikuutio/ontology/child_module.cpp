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

#include "child_module.hpp"
#include "parent_module.hpp"
#include "entity.hpp"

namespace yli
{
    namespace ontology
    {
        void ChildModule::bind_to_parent_module()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            if (this->parent_module == nullptr)
            {
                return;
            }

            // get `childID` from the `World` and set pointer to this `Scene`.
            this->parent_module->bind_child(this->self);
        }

        ChildModule::~ChildModule()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.

            if (this->parent_module == nullptr)
            {
                return;
            }

            if (this->self == nullptr)
            {
                return;
            }

            // Set pointer to this `Entity` to `nullptr`.
            this->parent_module->unbind_child(this->self->childID);
        }
    }
}
