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

#ifndef HIRVI_ONTOLOGY_TRIVIAL_DATA_ANALYZER_HPP_INCLUDED
#define HIRVI_ONTOLOGY_TRIVIAL_DATA_ANALYZER_HPP_INCLUDED

#include "data_analyzer.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#include <cstddef> // std::size_t
#include <utility> // std::pair
#include <vector>  // std::vector

namespace hirvi
{
    class SpatialData;

    class TrivialDataAnalyzer : public DataAnalyzer
    {
    public:
        TrivialDataAnalyzer();

        [[nodiscard]] std::pair<std::vector<std::size_t>, glm::vec3> analyze_data(const std::vector<PositionReport>& reports) const override;
    };
}

#endif
