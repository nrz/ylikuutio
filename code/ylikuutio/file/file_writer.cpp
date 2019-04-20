#include "file_writer.hpp"

// Include standard headers
#include <fstream>  // std::fstream
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace file
    {
        bool binary_write(const std::vector<uint8_t>& data, const std::string& file_path)
        {
            std::cout << "Writing binary file " << file_path << "\n";

            std::ofstream file_stream(file_path, std::ios::out | std::ios::binary);
            file_stream.write((char*) &data[0], data.size() * sizeof(uint8_t));
            file_stream.close();

            return false;
        }
    }
}
