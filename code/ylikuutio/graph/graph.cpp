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

#include "graph.hpp"
#include "node.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <vector>   // std::vector

namespace yli::graph
{
    void Graph::bind_node(yli::graph::Node* const node)
    {
        // get `childID` from `Symbiosis` and set pointer to `symbiont_material`.
        yli::hierarchy::bind_child_to_parent<yli::graph::Node*>(
                node,
                this->node_pointer_vector,
                this->free_nodeID_queue,
                this->number_of_nodes);
    }

    void Graph::unbind_node(const std::size_t childID)
    {
        yli::hierarchy::unbind_child_from_parent(
                childID,
                this->node_pointer_vector,
                this->free_nodeID_queue,
                this->number_of_nodes);
    }

    Graph::Graph()
    {
        // constructor.
        this->number_of_nodes = 0;
    }

    yli::graph::Node* Graph::get_node_pointer(std::size_t childID)
    {
        return this->node_pointer_vector[childID];
    }

    Graph::~Graph()
    {
        // destructor.
        std::cout << "This graph will be destroyed.\n";

        // destroy all nodes of this graph.
        std::cout << "All nodes of this graph will be destroyed.\n";
        yli::hierarchy::delete_children<yli::graph::Node*>(this->node_pointer_vector, this->number_of_nodes);
    }
}
