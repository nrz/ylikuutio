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

#ifndef YLIKUUTIO_PARENT_OF_SKILLS_MODULE_HPP_INCLUDED
#define YLIKUUTIO_PARENT_OF_SKILLS_MODULE_HPP_INCLUDED

#include "generic_parent_module.hpp"

// Include standard headers
#include <string> // std::string

namespace yli::ontology
{
    class Registry;
    class Universe;
    class Skill;

    class ParentOfSkillsModule final : public GenericParentModule
    {
        public:
            ParentOfSkillsModule(
                    Universe& universe,
                    Registry& registry,
                    const std::string& name) noexcept;

            ParentOfSkillsModule(const ParentOfSkillsModule&) = delete;            // Delete copy constructor.
            ParentOfSkillsModule& operator=(const ParentOfSkillsModule&) = delete; // Delete copy assignment.

            ~ParentOfSkillsModule() = default;
    };
}

#endif
