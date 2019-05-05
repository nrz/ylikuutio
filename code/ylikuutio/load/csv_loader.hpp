#ifndef __CSV_LOADER_HPP_INCLUDED
#define __CSV_LOADER_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace load
    {
        std::shared_ptr<std::vector<float>> load_CSV_file(
                const std::string& csv_filename,
                std::size_t& data_width,
                std::size_t& data_height,
                std::size_t& data_size);
    }
}

#endif
