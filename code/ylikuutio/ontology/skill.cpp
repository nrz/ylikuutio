// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#include "skill.hpp"
#include "capability.hpp"
#include "holobiont.hpp"
#include "skill_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;

    Holobiont* Skill::get_holobiont() const
    {
        return static_cast<Holobiont*>(this->get_parent());
    }

    Entity* Skill::get_parent() const
    {
        return this->child_of_holobiont.get_parent();
    }

    Skill::Skill(
            yli::core::Application& application,
            Universe& universe,
            const SkillStruct& skill_struct,
            GenericParentModule* const parent_module)
        : Capability(application, universe, skill_struct),
        child_of_holobiont(parent_module, *this)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Skill*";
    }

    std::size_t Skill::get_number_of_children() const
    {
        return 0; // `Skill` has no children.
    }

    std::size_t Skill::get_number_of_descendants() const
    {
        return 0; // `Skill` has no children.
    }

    Scene* Skill::get_scene() const
    {
        return this->child_of_holobiont.get_scene();
    }
}
