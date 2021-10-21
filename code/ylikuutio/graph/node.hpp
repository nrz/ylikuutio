// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_GRAPH_NODE_HPP_INCLUDED
#define __YLIKUUTIO_GRAPH_NODE_HPP_INCLUDED

#include "graph.hpp"
#include "node_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <vector>    // std::vector
#include <queue>     // std::queue
#include <algorithm> // std::find

namespace yli::graph
{
    class Node
    {
        public:
            // constructor.
            explicit Node(const yli::graph::NodeStruct& node_struct);

            // destructor.
            ~Node();

            friend class yli::graph::Graph;
            template<typename T1>
                friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

        private:
            void bind_to_parent();

            // This method transfers this `Node` to a new `Graph`.
            // Links will not be changed.
            // All `Node`s that are to be transferred must be transferred separately.
            // Before transfering any node to a new `Graph`, all links to `Node`s
            // that do not belong to the new `Graph` of this `Node`
            // must be deleted with separate `delete_bidirectional_link` calls.
            void bind_to_new_graph_parent(yli::graph::Graph* const new_parent);

            // this method creates a bidirectional link.
            // creating of bidirectional links is not possible before all nodes are created.
            void create_bidirectional_link(std::size_t nodeID);

            // this method deletes a bidirectional link.
            // deleting of links is not possible before all nodes are created.
            void delete_bidirectional_link(std::size_t nodeID);

            std::size_t childID;
            yli::graph::Graph* parent;

            // nodes do not keep pointers to neighbor nodes, because all pointer values are not known yet before all nodes are created.
            std::vector<std::size_t> neighbor_nodeIDs;

            // this method creates an unidirectional link.
            // in the constructor only unidirectional links can be created.
            void create_unidirectional_link(std::size_t nodeID);

            // this method deletes an unidirectional link.
            void delete_unidirectional_link(std::size_t nodeID);
    };
}

#endif
