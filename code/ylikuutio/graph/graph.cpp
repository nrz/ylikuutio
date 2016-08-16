#include "graph.hpp"
#include "node.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace ontology
{
    Graph::Graph(std::vector<glm::vec3>& in_vertices, uint32_t image_width, uint32_t image_height, std::string triangulation_type)
    {
        // constructor.

        // This constructor creates a graph from vertex data produced eg. by `bool triangulate_quads`.
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
