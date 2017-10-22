#ifndef __NODE_STRUCT_HPP_INCLUDED
#define __NODE_STRUCT_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace graph
{
    class Graph;
}

typedef struct NodeStruct
{
    NodeStruct()
        : nodeID(-1), parent(nullptr)
    {
        // constructor.
    }
    int32_t nodeID;
    graph::Graph* parent;
    std::vector<int32_t> neighbor_nodeIDs;
} NodeStruct;

#endif
