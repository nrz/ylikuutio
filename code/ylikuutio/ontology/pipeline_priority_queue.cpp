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

#include "pipeline_priority_queue.hpp"
#include "pipeline.hpp"
#include "pipeline_compare.hpp"

// Include standard headers
#include <algorithm> // std::make_heap etc.
#include <cstddef>   // std::size_t

namespace yli::ontology
{
    // Inspired by https://stackoverflow.com/questions/19467485/how-to-remove-element-not-at-top-from-priority-queue/36711682#36711682
    //
    // Heap-based priority queue.
    // Random access read: O(1)
    // Insert:             O(log(n))
    // Delete:             O(log(n))

    bool PipelinePriorityQueue::remove(const std::size_t childID)
    {
        for (auto it = this->c.begin(); it != this->c.end(); ++it)
        {
            if ((*it)->get_childID() == childID)
            {
                this->c.erase(it);
                std::make_heap(this->c.begin(), this->c.end(), PipelineCompare());
                return true;
            }
        }

        return false;
    }
}
