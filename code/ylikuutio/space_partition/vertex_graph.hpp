#ifndef __VERTEX_GRAPH_HPP_INCLUDED
#define __VERTEX_GRAPH_HPP_INCLUDED

#include "code/ylikuutio/graph/graph.hpp"

namespace space_partition
{
    class VertexGraph : public graph::Graph
    {
        public:
            // constructor.

            // This constructor creates a graph from vertex data produced eg. by `bool triangulate_quads`.
            VertexGraph(std::vector<glm::vec3>& in_vertices, uint32_t image_width, uint32_t image_height, std::string triangulation_type)
                : graph::Graph()
            {
                // constructor.
            }

            // destructor.
            ~VertexGraph();
    };
}

#endif
