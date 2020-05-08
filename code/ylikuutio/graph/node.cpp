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

#include "node.hpp"
#include "graph.hpp"
#include "node_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <algorithm> // std::find etc.
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::graph
{
    void Node::bind_to_parent()
    {
        // requirements:
        // `this->parent` must not be `nullptr`.

        yli::graph::Graph* const graph = this->parent;

        if (graph == nullptr)
        {
            std::cerr << "ERROR: `Node::bind_to_parent`: `graph` is `nullptr`!\n";
            return;
        }

        graph->bind_node(this);
    }

    Node::Node(const yli::graph::NodeStruct& node_struct)
    {
        // constructor.
        this->childID = node_struct.nodeID;
        this->parent = node_struct.parent;

        // requirements for further actions:
        // `this->parent` must not be `nullptr`.

        yli::graph::Graph* const graph = this->parent;

        if (graph == nullptr)
        {
            std::cerr << "ERROR: `Node::Node`: `graph` is `nullptr`!\n";
            return;
        }

        // set pointer to this `Node`.
        graph->bind_node(this);

        // create all bidirectional links between this node and neighbor nodes.
        for (std::size_t link_i = 0; link_i < this->neighbor_nodeIDs.size(); link_i++)
        {
            this->create_bidirectional_link(this->neighbor_nodeIDs[link_i]);
        }
    }

    Node::~Node()
    {
        // destructor.
        std::cout << "Node with childID " << this->childID << " will be destroyed.\n";

        // delete all bidirectional links.
        for (std::size_t link_i = 0; link_i < this->neighbor_nodeIDs.size(); link_i++)
        {
            this->delete_bidirectional_link(this->neighbor_nodeIDs[link_i]);
        }

        // requirements for further actions:
        // `this->parent` must not be `nullptr`.

        yli::graph::Graph* const graph = this->parent;

        if (graph == nullptr)
        {
            std::cerr << "ERROR: `Node::~Node`: `graph` is `nullptr`!\n";
            return;
        }

        // set pointer to this `Node` to `nullptr`.
        graph->unbind_node(this->childID);
    }

    void Node::create_unidirectional_link(std::size_t nodeID)
    {
        // this method creates an unidirectional link.

        // check that a link not exist already.
        if (std::find(this->neighbor_nodeIDs.begin(), this->neighbor_nodeIDs.end(), nodeID) == this->neighbor_nodeIDs.end())
        {
            // OK, it does not exist yet,
            // so create a link from this node to destination node.
            this->neighbor_nodeIDs.push_back(nodeID);
        }

        // an alternative: create a link from this node to destination node without checking its prior existence.
        // this->neighbor_nodeIDs.push_back(nodeID);
    }

    void Node::create_bidirectional_link(std::size_t nodeID)
    {
        // requirements:
        // `this->parent` must not be `nullptr`.

        yli::graph::Graph* const graph = this->parent;

        if (graph == nullptr)
        {
            std::cerr << "ERROR: `Node::create_bidirectional_link`: `graph` is `nullptr`!\n";
            return;
        }

        // create a link from this node to destination node.
        this->create_unidirectional_link(nodeID);

        // create a link from destination node to this node.
        static_cast<yli::graph::Node*>(graph->get_node_pointer(childID))->create_unidirectional_link(this->childID);
    }

    void Node::delete_unidirectional_link(std::size_t nodeID)
    {
        // this method deletes an unidirectional link.
        this->neighbor_nodeIDs.erase(std::remove(this->neighbor_nodeIDs.begin(), this->neighbor_nodeIDs.end(), nodeID), this->neighbor_nodeIDs.end());
    }

    void Node::delete_bidirectional_link(std::size_t nodeID)
    {
        // requirements:
        // `this->parent` must not be `nullptr`.

        yli::graph::Graph* const graph = this->parent;

        if (graph == nullptr)
        {
            std::cerr << "ERROR: `Node::delete_bidirectional_link`: `graph` is `nullptr`!\n";
            return;
        }

        // this method deletes a bidirectional link.
        this->delete_unidirectional_link(nodeID);

        // delete a link from destination node to this node.
        static_cast<yli::graph::Node*>(graph->get_node_pointer(childID))->delete_unidirectional_link(this->childID);
    }

    // Transfering a `Node` to a new `Graph` is similar to `bind_to_new_parent`, but there is one important difference:
    // `Node`s have references (links) to other `Node`s, whereas `Shader`s, `Material`s, `Species`, `VectorFont`s, `Glyph`s, and `Object`s do not.
    // The easiest way would be to request new `childID` for each new `Node`, and this will be probably be implemented first.
    // Another option would be to change only those `childID`'s for which there would be duplicate `childID`'s.
    // However, that may consume huge amounts of memory if a big object (eg. a terrain object) is split into several smaller objects.
    // Therefore a `childID_bias` needs to be defined for each `Graph`, it will be used for reindexing.
    // If `Node::bind_to_parent` would cause overflow (2^32 = 4 294 967 295), it will instead give smallest current `childID` of the graph and
    // decrement `childID_bias` by 1.

    void Node::bind_to_new_parent(yli::graph::Graph* const new_parent)
    {
        // this method sets pointer to this `Node` to `nullptr`, sets `parent` according to the input,
        // and requests a new `childID` from the new `Graph`.
        //
        // requirements:
        // `this->parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::graph::Graph* const graph = this->parent;

        if (graph == nullptr)
        {
            std::cerr << "ERROR: `Node::bind_to_new_parent`: `graph` is `nullptr`!\n";
            return;
        }

        if (new_parent == nullptr)
        {
            std::cerr << "ERROR: `Node::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
            return;
        }

        // unbind from the old parent `Graph`.
        graph->unbind_node(this->childID);

        // get `childID` from `Graph` and set pointer to this `Node`.
        this->parent = new_parent;
        this->parent->bind_node(this);
    }
}
