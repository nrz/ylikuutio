#ifndef __GRAPH_HPP_INCLUDED
#define __GRAPH_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector
#include <queue>    // std::queue

namespace graph
{
    class Node;

    class Graph
    {
        public:
            // constructor.
            Graph();

            // destructor.
            ~Graph();

            friend class Node;

        private:
            // this method sets a node pointer.
            void set_node_pointer(uint32_t nodeID, graph::Node* child_pointer);

            // this method gets a node pointer.
            graph::Node* get_node_pointer(uint32_t nodeID);

            // this method gets a node ID and removes it from the `free_nodeID_queue` if it was popped from the queue.
            uint32_t get_nodeID();

            std::vector<graph::Node*> node_pointer_vector;
            std::queue<uint32_t> free_nodeID_queue;
            int32_t number_of_nodes;
    };
}

#endif
