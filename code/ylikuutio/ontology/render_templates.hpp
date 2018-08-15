#ifndef __RENDER_TEMPLATES_HPP_INCLUDED
#define __RENDER_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        template<class T1>
            void render_children(const std::vector<T1>& child_pointer_vector)
            {
                for (std::size_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
                {
                    T1 child_pointer = static_cast<T1>(child_pointer_vector[child_i]);

                    if (child_pointer != nullptr)
                    {
                        child_pointer->render();
                    }
                }
            }
    }
}

#endif
