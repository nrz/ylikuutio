#ifndef __VERTEX_GRAPH_HPP_INCLUDED
#define __VERTEX_GRAPH_HPP_INCLUDED

#include "code/ylikuutio/graph/graph.hpp"

namespace graph
{
    class Graph;
}

namespace space_partition
{
    class VertexGraph : public graph::Graph
    {
        public:
            // constructor.
            VertexGraph()
                : graph::Graph()
            {
                // constructor.
            }

            // destructor.
            ~VertexGraph();
    };
}

#endif
