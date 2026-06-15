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

#include "trivial_data_analyzer.hpp"
#include "position_report.hpp"

#include <glm/gtx/hash.hpp>

// Include standard headers
#include <unordered_map> // std::unordered_map

namespace hirvi
{
    std::pair<std::vector<std::size_t>, glm::vec3> TrivialDataAnalyzer::analyze_data(
        const std::vector<PositionReport>& reports) const
    {
        std::unordered_map<glm::vec3, uint32_t> counts {};
        uint32_t max_count { 0 };

        // Store counts and find max count.
        for (const auto& [position, reporterID] : reports)
        {
            counts[position] = counts[position] + 1;

            if (counts[position] > max_count)
            {
                max_count = counts[position];
            }
        }

        std::vector<std::size_t> traitorIDs;
        glm::vec3 sum_of_coordinates { 0.0f, 0.0f, 0.0f };

        //  Go through reports and add detect traitors.
        for (const auto& [position, reporterID] : reports)
        {
            if (counts[position] == max_count)
            {
                // Valid report!
                sum_of_coordinates += position;
            }
            else
            {
                // Traitor!
                traitorIDs.emplace_back(reporterID);
            }
        }

        // Compute the position based on validated reports.
        // If multiple coordinates are chosen as valid, compute the mean coordinates.
        const uint32_t n_valid_reports = reports.size() - traitorIDs.size();
        const glm::vec3 determined_position = sum_of_coordinates * (1.0f / static_cast<float>(n_valid_reports));
        return { traitorIDs, determined_position };
    }
}
