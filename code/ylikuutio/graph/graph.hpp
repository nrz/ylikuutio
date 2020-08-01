// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_GRAPH_GRAPH_HPP_INCLUDED
#define __YLIKUUTIO_GRAPH_GRAPH_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <vector>   // std::vector

namespace yli::graph
{
    class Node;

    class Graph
    {
        public:
            void bind_node(yli::graph::Node* const node);
            void unbind_node(const std::size_t childID);

            // constructor.
            Graph();

            // destructor.
            ~Graph();

            friend class Node;

        private:
            // this method gets a node pointer.
            yli::graph::Node* get_node_pointer(std::size_t nodeID);

            std::vector<yli::graph::Node*> node_pointer_vector;
            std::queue<std::size_t> free_nodeID_queue;
            std::size_t number_of_nodes;
    };
}

#endif
