#include "node.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace model
{
    void Node::bind_to_parent()
    {
        model::bind_child_to_parent<model::Node*>(this, this->parent_pointer->node_pointer_vector, this->parent_pointer->free_nodeID_queue);
    }

    Node::Node(NodeStruct node_struct)
    {
        // constructor.
        this->childID = node_struct.nodeID;
        this->coordinate_vector = node_struct.coordinate_vector;
        this->parent_pointer = static_cast<model::Graph*>(node_struct.parent_pointer);

        // set pointer to this node.
        this->parent_pointer->set_node_pointer(this->childID, this);

        // create all bidirectional links between this node and neighbor nodes.
        for (GLuint link_i = 0; link_i < this->neighbor_nodeIDs.size(); link_i++)
        {
            this->create_bidirectional_link(this->neighbor_nodeIDs[link_i]);
        }
    }

    Node::~Node()
    {
        // destructor.
        std::cout << "Node with childID " << this->childID << " will be destroyed.\n";

        // delete all bidirectional links.
        for (GLuint link_i = 0; link_i < this->neighbor_nodeIDs.size(); link_i++)
        {
            this->delete_bidirectional_link(this->neighbor_nodeIDs[link_i]);
        }

        // set pointer to this node to NULL.
        this->parent_pointer->set_node_pointer(this->childID, NULL);
    }

    void Node::create_unidirectional_link(GLuint nodeID)
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

    void Node::create_bidirectional_link(GLuint nodeID)
    {
        // create a link from this node to destination node.
        this->create_unidirectional_link(nodeID);

        // create a link from destination node to this node.
        static_cast<model::Node*>(this->parent_pointer->get_node_pointer(childID))->create_unidirectional_link(this->childID);
    }

    void Node::delete_unidirectional_link(GLuint nodeID)
    {
        // this method deletes an unidirectional link.
        this->neighbor_nodeIDs.erase(std::remove(this->neighbor_nodeIDs.begin(), this->neighbor_nodeIDs.end(), nodeID), this->neighbor_nodeIDs.end());
    }

    void Node::delete_bidirectional_link(GLuint nodeID)
    {
        // this method deletes a bidirectional link.
        this->delete_unidirectional_link(nodeID);

        // delete a link from destination node to this node.
        static_cast<model::Node*>(this->parent_pointer->get_node_pointer(childID))->delete_unidirectional_link(this->childID);
    }

    // Transfering a Node to a new Graph is similar to `bind_to_new_parent`, but there is one important difference:
    // Nodes have references (links) to other nodes, whereas Shaders, Textures, Species, Fonts, Glyphs, and Objects do not.
    // The easiest way would be to request new `childID` for each new node, and this will be probably be implemented first.
    // Another option would be to change only those `childID`'s for which there would be duplicate `childID`'s.
    // However, that may consume huge amounts of memory if a big object (eg. a terrain object) is split into several smaller objects.
    // Therefore a `childID_bias` needs to be defined for each graph, it will be used for reindexing.
    // If `Node::bind_to_parent` would cause overflow (2^32 = 4 294 967 295), it will instead give smallest current `childID` of the graph and
    // decrement `childID_bias` by 1.

    void Node::bind_to_new_parent(model::Graph *new_graph_pointer)
    {
        model::bind_child_to_new_parent<model::Node*, model::Graph*>(this, new_graph_pointer, this->parent_pointer->node_pointer_vector, this->parent_pointer->free_nodeID_queue);
    }
}
