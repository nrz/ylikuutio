#include "graph.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "node.hpp"

namespace ontology
{
    Graph::Graph()
    {
        // constructor.
    }

    void Graph::set_node_pointer(uint32_t childID, ontology::Node* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->node_pointer_vector, this->free_nodeID_queue);
    }

    ontology::Node* Graph::get_node_pointer(uint32_t childID)
    {
        return this->node_pointer_vector[childID];
    }

    uint32_t Graph::get_nodeID()
    {
        return hierarchy::get_childID(this->node_pointer_vector, this->free_nodeID_queue);
    }

    Graph::~Graph()
    {
        // destructor.
        std::cout << "This graph will be destroyed.\n";

        // destroy all nodes of this graph.
        std::cout << "All nodes of this graph will be destroyed.\n";
        hierarchy::delete_children<ontology::Node*>(this->node_pointer_vector);
    }
}
