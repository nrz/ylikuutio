#ifndef __FAMILY_TEMPLATES_HPP_INCLUDED
#define __FAMILY_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        template<class T1>
            std::size_t get_number_of_descendants(const std::vector<T1>& child_pointer_vector)
            {
                std::size_t number_of_descendants = 0;

                for (std::size_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
                {
                    T1 child_pointer = static_cast<T1>(child_pointer_vector[child_i]);

                    if (child_pointer != nullptr)
                    {
                        number_of_descendants += child_pointer->get_number_of_descendants() + 1; // +1 for the child itself.
                    }
                }

                return number_of_descendants;
            }
    }
}

#endif
