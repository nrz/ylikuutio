#include "shader_priority_queue.hpp"
#include "shader.hpp"
#include "shader_compare.hpp"

// Include standard headers
#include <algorithm> // std::make_heap etc.
#include <cstddef>   // std::size_t
#include <queue>     // std::priority_queue, std::queue

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

        bool ShaderPriorityQueue::remove(const std::size_t childID)
        {
            for (auto it = this->c.begin(); it != this->c.end(); it++)
            {
                if ((*it)->get_childID() == childID)
                {
                    this->c.erase(it);
                    std::make_heap(this->c.begin(), this->c.end(), yli::ontology::ShaderCompare());
                    return true;
                }
            }

            return false;
        }
    }
}

