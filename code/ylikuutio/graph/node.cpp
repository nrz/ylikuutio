#include "node.hpp"
#include "node_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace graph
{
    void Node::bind_to_parent()
    {
        yli::hierarchy::bind_child_to_parent<graph::Node*>(this, this->parent->node_pointer_vector, this->parent->free_nodeID_queue, &this->parent->number_of_nodes);
    }

    Node::Node(const NodeStruct& node_struct)
    {
        // constructor.
        this->childID = node_struct.nodeID;
        this->parent = node_struct.parent;

        // set pointer to this node.
        this->parent->set_node_pointer(this->childID, this);

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

        // set pointer to this node to nullptr.
        this->parent->set_node_pointer(this->childID, nullptr);
    }

    void Node::create_unidirectional_link(int32_t nodeID)
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

    void Node::create_bidirectional_link(int32_t nodeID)
    {
        // create a link from this node to destination node.
        this->create_unidirectional_link(nodeID);

        // create a link from destination node to this node.
        static_cast<graph::Node*>(this->parent->get_node_pointer(childID))->create_unidirectional_link(this->childID);
    }

    void Node::delete_unidirectional_link(int32_t nodeID)
    {
        // this method deletes an unidirectional link.
        this->neighbor_nodeIDs.erase(std::remove(this->neighbor_nodeIDs.begin(), this->neighbor_nodeIDs.end(), nodeID), this->neighbor_nodeIDs.end());
    }

    void Node::delete_bidirectional_link(int32_t nodeID)
    {
        // this method deletes a bidirectional link.
        this->delete_unidirectional_link(nodeID);

        // delete a link from destination node to this node.
        static_cast<graph::Node*>(this->parent->get_node_pointer(childID))->delete_unidirectional_link(this->childID);
    }

    // Transfering a `Node` to a new `Graph` is similar to `bind_to_new_parent`, but there is one important difference:
    // `Node`s have references (links) to other `Node`s, whereas `Shader`s, `Material`s, `Species`, `VectorFont`s, `Glyph`s, and `Object`s do not.
    // The easiest way would be to request new `childID` for each new `Node`, and this will be probably be implemented first.
    // Another option would be to change only those `childID`'s for which there would be duplicate `childID`'s.
    // However, that may consume huge amounts of memory if a big object (eg. a terrain object) is split into several smaller objects.
    // Therefore a `childID_bias` needs to be defined for each `Graph`, it will be used for reindexing.
    // If `Node::bind_to_parent` would cause overflow (2^32 = 4 294 967 295), it will instead give smallest current `childID` of the graph and
    // decrement `childID_bias` by 1.

    void Node::bind_to_new_parent(graph::Graph *new_graph_pointer)
    {
        yli::hierarchy::bind_child_to_new_parent<graph::Node*, graph::Graph*>(this, new_graph_pointer, this->parent->node_pointer_vector, this->parent->free_nodeID_queue, &this->parent->number_of_nodes);
    }
}
