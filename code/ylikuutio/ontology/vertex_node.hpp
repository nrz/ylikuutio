#ifndef __VERTEX_NODE_HPP_INCLUDED
#define __VERTEX_NODE_HPP_INCLUDED

#include "code/ylikuutio/graph/node_struct.hpp"
#include "code/ylikuutio/graph/node.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli
{
    namespace ontology
    {
        class VertexNode: public yli::graph::Node
        {
            public:
                // constructor.
                VertexNode(glm::vec3 coordinate_vector, const NodeStruct& node_struct)
                    : yli::graph::Node(node_struct)
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
}

#endif
