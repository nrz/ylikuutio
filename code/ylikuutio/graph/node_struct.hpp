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
        : parent_pointer(nullptr)
    {
        // constructor.
    }
    uint32_t nodeID;
    graph::Graph* parent_pointer;
    std::vector<uint32_t> neighbor_nodeIDs;
} NodeStruct;

#endif
