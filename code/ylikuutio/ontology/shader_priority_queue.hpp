// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_SHADER_PRIORITY_QUEUE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SHADER_PRIORITY_QUEUE_HPP_INCLUDED

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::priority_queue, std::queue
#include <vector>  // std::vector

namespace yli::ontology
{
    class Shader;

    // Inspired by https://stackoverflow.com/questions/19467485/how-to-remove-element-not-at-top-from-priority-queue/36711682#36711682
    //
    // Heap-based priority queue.
    // Random access read: O(1)
    // Insert:             O(log(n))
    // Delete:             O(log(n))

    class ShaderPriorityQueue: public std::priority_queue<yli::ontology::Shader*, std::vector<yli::ontology::Shader*>>
    {
        public:
            bool remove(const std::size_t childID);
    };
}

#endif
