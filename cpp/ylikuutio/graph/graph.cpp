#include "graph.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "node.hpp"

namespace model
{
    Graph::Graph()
    {
        // constructor.
    }

    void Graph::set_node_pointer(uint32_t childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->node_pointer_vector, this->free_nodeID_queue);
    }

    void* Graph::get_node_pointer(uint32_t childID)
    {
        return this->node_pointer_vector[childID];
    }

    uint32_t Graph::get_nodeID()
    {
        return get_childID(node_pointer_vector, free_nodeID_queue);
    }

    Graph::~Graph()
    {
        // destructor.
        std::cout << "This graph will be destroyed.\n";

        // destroy all nodes of this graph.
        std::cout << "All nodes of this graph will be destroyed.\n";
        model::delete_children<model::Node*>(this->node_pointer_vector);
    }
}
