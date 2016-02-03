#ifndef __NODE_HPP_INCLUDED
#define __NODE_HPP_INCLUDED

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

#include <vector>    // std::vector
#include <queue>     // std::queue
#include <algorithm> // std::find

#include "cpp/common/globals.hpp"
#include "graph.hpp"
#include "cpp/common/hierarchy.hpp"
#include "cpp/model/model_templates.hpp"

namespace model
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
                friend void render_children(std::vector<void*> &child_pointer_vector);
            template<class T1>
                friend void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);
            template<class T1, class T2>
                friend void bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<void*> &old_child_pointer_vector, std::queue<GLuint> &old_free_childID_queue);

        private:
            void bind_to_parent();

            // this method creates a bidirectional link.
            // creating of bidirectional links is not possible before all nodes are created.
            void create_bidirectional_link(GLuint nodeID);

            // this method deletes a bidirectional link.
            // deleting of links is not possible before all nodes are created.
            void delete_bidirectional_link(GLuint nodeID);

            // this method transfers this node to a new graph.
            // links will not be changed.
            // all nodes that are to be transferred must be transferred separately.
            // before transfering any node to a new graph,
            // all links to nodes that do not belong to the new graph of this node must be deleted with separate `delete_bidirectional_link` calls.
            void bind_to_new_parent(model::Graph *new_graph_pointer);

            GLuint childID;
            model::Graph *parent_pointer;

            // nodes do not keep pointers to neighbor nodes, because all pointer values are not known yet before all nodes are created.
            std::vector<GLuint> neighbor_nodeIDs;

            // this method creates an unidirectional link.
            // in the constructor only unidirectional links can be created.
            void create_unidirectional_link(GLuint nodeID);

            // this method deletes an unidirectional link.
            void delete_unidirectional_link(GLuint nodeID);

            glm::vec3 coordinate_vector;
    };
}

#endif
