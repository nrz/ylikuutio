#ifndef __GRAPH_HPP_INCLUDED
#define __GRAPH_HPP_INCLUDED

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <vector>   // std::vector
#include <queue>    // std::queue

namespace ontology
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
            void set_node_pointer(uint32_t nodeID, ontology::Node* child_pointer);

            // this method gets a node pointer.
            void* get_node_pointer(uint32_t nodeID);

            // this method gets a node ID and removes it from the `free_nodeID_queue` if it was popped from the queue.
            uint32_t get_nodeID();

            std::vector<ontology::Node*> node_pointer_vector;
            std::queue<uint32_t> free_nodeID_queue;
    };
}

#endif
