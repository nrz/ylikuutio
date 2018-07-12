#ifndef __NODE_HPP_INCLUDED
#define __NODE_HPP_INCLUDED

#include "graph.hpp"
#include "node_struct.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <vector>    // std::vector
#include <queue>     // std::queue
#include <algorithm> // std::find

namespace graph
{
    class Node
    {
        public:
            // constructor.
            Node(const NodeStruct& node_struct);

            // destructor.
            ~Node();

            friend class Graph;
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<int32_t>& free_childID_queue, std::size_t* number_of_children);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent, std::vector<T1>& old_child_pointer_vector, std::queue<int32_t>& old_free_childID_queue, std::size_t* old_number_of_children);

        private:
            void bind_to_parent();

            // this method creates a bidirectional link.
            // creating of bidirectional links is not possible before all nodes are created.
            void create_bidirectional_link(int32_t nodeID);

            // this method deletes a bidirectional link.
            // deleting of links is not possible before all nodes are created.
            void delete_bidirectional_link(int32_t nodeID);

            // this method transfers this node to a new graph.
            // links will not be changed.
            // all nodes that are to be transferred must be transferred separately.
            // before transfering any node to a new graph,
            // all links to nodes that do not belong to the new graph of this node must be deleted with separate `delete_bidirectional_link` calls.
            void bind_to_new_parent(graph::Graph *new_graph_pointer);

            int32_t childID;
            graph::Graph* parent;

            // nodes do not keep pointers to neighbor nodes, because all pointer values are not known yet before all nodes are created.
            std::vector<int32_t> neighbor_nodeIDs;

            // this method creates an unidirectional link.
            // in the constructor only unidirectional links can be created.
            void create_unidirectional_link(int32_t nodeID);

            // this method deletes an unidirectional link.
            void delete_unidirectional_link(int32_t nodeID);
    };
}

#endif
