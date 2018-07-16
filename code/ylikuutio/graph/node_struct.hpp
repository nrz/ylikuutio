#ifndef __NODE_STRUCT_HPP_INCLUDED
#define __NODE_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <vector>   // std::vector

namespace graph
{
    class Graph;
}

typedef struct NodeStruct
{
    NodeStruct()
        : nodeID(std::numeric_limits<std::size_t>::max()), parent(nullptr)
    {
        // constructor.
    }
    std::size_t nodeID;
    graph::Graph* parent;
    std::vector<std::size_t> neighbor_nodeIDs;
} NodeStruct;

#endif
