#ifndef __NODE_HPP_INCLUDED
#define __NODE_HPP_INCLUDED

#include <vector>    // std::vector
#include <queue>     // std::queue
#include <algorithm> // std::find

#include "code/ylikuutio/common/globals.hpp"
#include "graph.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace ontology
{
    class Node
    {
        public:
            // constructor.
            Node(NodeStruct node_struct);

            // destructor.
            ~Node();

            friend class Graph;
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<uint32_t>& free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1>& old_child_pointer_vector, std::queue<uint32_t>& old_free_childID_queue);

        private:
            void bind_to_parent();

            // this method creates a bidirectional link.
            // creating of bidirectional links is not possible before all nodes are created.
            void create_bidirectional_link(uint32_t nodeID);

            // this method deletes a bidirectional link.
            // deleting of links is not possible before all nodes are created.
            void delete_bidirectional_link(uint32_t nodeID);

            // this method transfers this node to a new graph.
            // links will not be changed.
            // all nodes that are to be transferred must be transferred separately.
            // before transfering any node to a new graph,
            // all links to nodes that do not belong to the new graph of this node must be deleted with separate `delete_bidirectional_link` calls.
            void bind_to_new_parent(ontology::Graph *new_graph_pointer);

            uint32_t childID;
            ontology::Graph* parent_pointer;

            // nodes do not keep pointers to neighbor nodes, because all pointer values are not known yet before all nodes are created.
            std::vector<uint32_t> neighbor_nodeIDs;

            // this method creates an unidirectional link.
            // in the constructor only unidirectional links can be created.
            void create_unidirectional_link(uint32_t nodeID);

            // this method deletes an unidirectional link.
            void delete_unidirectional_link(uint32_t nodeID);

            glm::vec3 coordinate_vector;
    };
}

#endif
