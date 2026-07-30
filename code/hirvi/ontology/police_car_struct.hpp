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

#ifndef YLI_ONTOLOGY_POLICE_CAR_STRUCT_HPP_INCLUDED
#define YLI_ONTOLOGY_POLICE_CAR_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/request.hpp"

namespace hirvi::ontology
{
    struct PoliceCarStruct final : yli::ontology::HolobiontStruct
    {
        PoliceCarStruct(
            yli::ontology::Request<yli::ontology::Scene>&& scene_parent,
            yli::ontology::Request<yli::ontology::Symbiosis>&& symbiosis_master)
            : HolobiontStruct(std::move(scene_parent),
                              std::move(symbiosis_master))
        { }

        PoliceCarStruct(
            yli::ontology::Request<yli::ontology::Scene>&& scene_parent,
            yli::ontology::Request<yli::ontology::MovableController>&& movable_controller_master,
            yli::ontology::Request<yli::ontology::Symbiosis>&& symbiosis_master)
            : HolobiontStruct(std::move(scene_parent),
                              std::move(movable_controller_master),
                              std::move(symbiosis_master))
        { }
    };
}

#endif
