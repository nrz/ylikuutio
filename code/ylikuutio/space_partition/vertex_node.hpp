#ifndef __VERTEX_NODE_HPP_INCLUDED
#define __VERTEX_NODE_HPP_INCLUDED

#include "code/ylikuutio/graph/node_struct.hpp"
#include "code/ylikuutio/graph/node.hpp"

namespace space_partition
{
    class VertexNode: public graph::Node
    {
        public:
            // constructor.
            VertexNode(glm::vec3 coordinate_vector, const NodeStruct& node_struct)
                : graph::Node(node_struct)
            {
                // constructor.
                this->coordinate_vector = coordinate_vector;
            }

            // destructor.
            ~VertexNode();

        private:
            glm::vec3 coordinate_vector;
    };
}

#endif
