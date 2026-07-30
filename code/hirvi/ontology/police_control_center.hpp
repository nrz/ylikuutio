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

#ifndef YLI_ONTOLOGY_POLICE_CONTROL_CENTER_HPP_INCLUDED
#define YLI_ONTOLOGY_POLICE_CONTROL_CENTER_HPP_INCLUDED

#include "code/ylikuutio/ontology/child_module.hpp"
#include "code/ylikuutio/ontology/generic_master_module.hpp"
#include "code/ylikuutio/ontology/entity.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Movable;
    class Universe;
    class Scene;
}

namespace hirvi::ontology
{
    class HirviScene;
    struct PoliceControlCenterStruct;

    class PoliceControlCenter final : public yli::ontology::Entity
    {
    public:
        PoliceControlCenter(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const PoliceControlCenterStruct& police_control_center_struct,
            yli::ontology::GenericParentModule* hirvi_scene_parent_module);

        PoliceControlCenter(const PoliceControlCenter&) = delete;            // Delete copy constructor.
        PoliceControlCenter& operator=(const PoliceControlCenter&) = delete; // Delete copy assignment.

        ~PoliceControlCenter() override = default;

        template<typename ApprenticeType>
        yli::ontology::GenericMasterModule* get_generic_master_module() = delete;

        Entity* get_parent() const override;

        std::size_t get_number_of_children() const override;

        std::size_t get_number_of_descendants() const override;

        yli::ontology::Scene* get_scene() const override;

        yli::ontology::ChildModule child_of_hirvi_scene;
        yli::ontology::GenericMasterModule master_of_polices;
    };

    template<>
    inline yli::ontology::GenericMasterModule* PoliceControlCenter::get_generic_master_module<yli::ontology::Movable>()
    {
        return &this->master_of_polices;
    }
}

#endif
