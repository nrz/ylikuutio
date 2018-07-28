#ifndef __VERTEX_GRAPH_HPP_INCLUDED
#define __VERTEX_GRAPH_HPP_INCLUDED

#include "code/ylikuutio/graph/graph.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class VertexGraph: public yli::graph::Graph
        {
            public:
                // This constructor creates a graph from vertex data produced eg. by `bool triangulate_quads`.
                VertexGraph(std::vector<glm::vec3>& in_vertices, uint32_t image_width, uint32_t image_height, std::string triangulation_type)
                    : yli::graph::Graph()
                {
                    // constructor.
                }

                // destructor.
                ~VertexGraph();
        };
    }
}

#endif
