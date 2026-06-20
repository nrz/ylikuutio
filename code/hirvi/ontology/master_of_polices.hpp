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

#ifndef HIRVI_ONTOLOGY_POLICE_NETWORK_HPP_INCLUDED
#define HIRVI_ONTOLOGY_POLICE_NETWORK_HPP_INCLUDED

#include "code/ylikuutio/ontology/generic_master_module.hpp"
#include "code/hirvi/data/spatial_data.hpp"

// Include standard headers
#include <string> // std::string

namespace yli::ontology
{
    class Scene;
    class Registry;
}

namespace hirvi::ontology
{
    using namespace yli::ontology;

    class MasterOfPolices final : GenericMasterModule
    {
    public:
        MasterOfPolices(
            Scene& master_scene,
            Registry* registry,
            const std::string& name);

        void store_data();

        [[nodiscard]] const data::SpatialData& get_spatial_data() const;

    private:
        data::SpatialData spatial_data;
    };
}

#endif
