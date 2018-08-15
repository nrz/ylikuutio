#ifndef __GRAPH_HPP_INCLUDED
#define __GRAPH_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <vector>   // std::vector

namespace yli
{
    namespace graph
    {
        class Node;

        class Graph
        {
            public:
                void bind_node(yli::graph::Node* const node);
                void unbind_node(const std::size_t childID);

                // constructor.
                Graph();

                // destructor.
                ~Graph();

                friend class Node;

            private:
                // this method gets a node pointer.
                yli::graph::Node* get_node_pointer(std::size_t nodeID);

                // this method gets a node ID and removes it from the `free_nodeID_queue` if it was popped from the queue.
                std::size_t get_nodeID();

                std::vector<yli::graph::Node*> node_pointer_vector;
                std::queue<std::size_t> free_nodeID_queue;
                std::size_t number_of_nodes;
        };
    }
}

#endif
