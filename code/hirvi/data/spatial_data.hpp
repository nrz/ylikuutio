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

#ifndef HIRVI_DATA_SPATIAL_DATA_HPP_INCLUDED
#define HIRVI_DATA_SPATIAL_DATA_HPP_INCLUDED

#include "code/hirvi/data/position_report.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <set>    // std::set
#include <vector> // std::vector

namespace hirvi::data
{
    class DataAnalyzer;

    class SpatialData
    {
    public:
        SpatialData() = default;

        void clear_reports();
        void add_report(const PositionReport& report);
        void determine_position_and_detect_traitors(const DataAnalyzer& data_analyzer);

    private:
        std::vector<PositionReport> position_reports;

        std::set<std::size_t> detected_traitors;
        glm::vec3 determined_position { NAN, NAN, NAN };
    };
}

#endif
