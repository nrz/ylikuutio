#ifndef __VECTOR_FUNCTIONS_HPP_INCLUDED
#define __VECTOR_FUNCTIONS_HPP_INCLUDED

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
#include <vector> // std::vector

namespace yli
{
    namespace linear_algebra
    {
        template<class T1>
            std::shared_ptr<std::vector<T1>> insert_elements(
                    const std::vector<T1>& data_vector,
                    const std::vector<T1>& left_filler_vector,
                    const std::vector<T1>& right_filler_vector)
            {
                std::shared_ptr<std::vector<T1>> output_vector = std::make_shared<std::vector<T1>>();

                for (const T1& data : data_vector)
                {
                    for (const T1& left_value : left_filler_vector)
                    {
                        output_vector->push_back(left_value);
                    }

                    output_vector->push_back(data);

                    for (const T1& right_value : right_filler_vector)
                    {
                        output_vector->push_back(right_value);
                    }
                }

                return output_vector;
            }
    }
}

#endif
