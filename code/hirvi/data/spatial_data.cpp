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

#include "spatial_data.hpp"
#include "code/hirvi/data/data_analyzer.hpp"

// Include standard headers
#include <algorithm> // std::ranges::copy
#include <iterator>  // std::inserter

namespace hirvi
{
    struct PositionReport;

    void SpatialData::clear_reports()
    {
        this->position_reports.clear();
    }

    void SpatialData::add_report(const PositionReport& report)
    {
        this->position_reports.emplace_back(report);
    }

    void SpatialData::determine_position_and_detect_traitors(const DataAnalyzer& data_analyzer)
    {
        const auto& [traitors, position] = data_analyzer.analyze_data(this->position_reports);
        std::ranges::copy(traitors, std::inserter(this->detected_traitors, this->detected_traitors.end()));
        this->determined_position = position;
    }
}
