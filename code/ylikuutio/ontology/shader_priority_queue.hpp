#ifndef __SHADER_PRIORITY_QUEUE_HPP_INCLUDED
#define __SHADER_PRIORITY_QUEUE_HPP_INCLUDED

#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/shader_compare.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::priority_queue, std::queue

namespace yli
{
    namespace ontology
    {
        // Inspired by https://stackoverflow.com/questions/19467485/how-to-remove-element-not-at-top-from-priority-queue/36711682#36711682
        //
        // Heap-based priority queue.
        // Random access read: O(1)
        // Insert:             O(log(n))
        // Delete:             O(log(n))

        class ShaderPriorityQueue: public std::priority_queue<yli::ontology::Shader*, std::vector<yli::ontology::Shader*>>
        {
            public:
                bool remove(const std::size_t childID);
        };
    }
}

#endif
