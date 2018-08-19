#include "graph.hpp"
#include "node.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli
{
    namespace graph
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

        std::size_t Graph::get_nodeID()
        {
            return yli::hierarchy::request_childID(this->node_pointer_vector, this->free_nodeID_queue);
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
}
