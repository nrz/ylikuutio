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

#ifndef HIRVI_HIRVI_SCENE_HPP_INCLUDED
#define HIRVI_HIRVI_SCENE_HPP_INCLUDED

#include "code/ylikuutio/ontology/scene.hpp"
#include "master_of_polices.hpp"
#include "master_of_emancipated_ones.hpp"

namespace hirvi::ontology
{
    class HirviScene final : public yli::ontology::Scene
    {
    public:
        HirviScene(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::SceneStruct& scene_struct,
            yli::ontology::GenericParentModule* universe_parent_module);

        ~HirviScene() override = default;

    private:
        MasterOfPolices master_of_polices;
        MasterOfEmancipatedOnes master_of_emancipated_ones;
    };
}
#endif
