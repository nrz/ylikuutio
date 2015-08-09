#ifndef __GRAPH_HPP_INCLUDED
#define __GRAPH_HPP_INCLUDED

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h>
#endif

#include <iostream>
#include <vector>    // std::vector
#include <queue>     // std::queue

namespace model
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
            void set_node_pointer(GLuint nodeID, void* node_pointer);

            // this method gets a node pointer.
            void* get_node_pointer(GLuint nodeID);

            // this method gets a node ID and removes it from the `free_nodeID_queue` if it was popped from the queue.
            GLuint get_nodeID();

            std::vector<void*> node_pointer_vector;
            std::queue<GLuint> free_nodeID_queue;
    };
}

#endif
