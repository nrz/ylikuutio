#ifndef __VERTEX_NODE_HPP_INCLUDED
#define __VERTEX_NODE_HPP_INCLUDED

#include "code/ylikuutio/graph/node.hpp"

namespace graph
{
    class Node;
}

namespace space_partition
{
    class VertexNode : public graph::Node
    {
        public:
            // constructor.
            VertexNode(glm::vec3 vertex, std::vector<VertexNode*>& neighbor_node_pointers)
                : graph::Node()
            {
                // constructor.
                this->vertex = vertex;
                this->neighbor_node_pointers = neighbor_node_pointers;
            }

        private:
            glm::vec3 vertex;
            std::vector<space_partition::VertexNode*> neighbor_node_pointers;
    };
}

#endif
