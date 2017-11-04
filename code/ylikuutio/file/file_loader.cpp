#include "file_loader.hpp"

// Include standard headers
#include <fstream>  // std::ifstream
#include <iostream> // std::cout, std::cin, std::cerr
#include <iterator> // std::istream_iterator
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace file
{
    std::string slurp(const std::string& file_path)
    {
        // inspired by http://stackoverflow.com/questions/116038/what-is-the-best-way-to-slurp-a-file-into-a-stdstring-in-c/116220#116220
        std::cout << "Loading file " << file_path << " into memory.\n";

        std::ifstream input_stream(file_path.c_str());
        std::stringstream file_buffer;
        file_buffer << input_stream.rdbuf();
        std::string file_contents_string = file_buffer.str();
        return file_contents_string;
    }

    std::vector<uint8_t> binary_slurp(const std::string& file_path)
    {
        std::ifstream file(file_path.c_str(), std::fstream::binary);
        file.unsetf(std::ios::skipws);           // do not skip whitespace.
        file.seekg(0, std::ios::end);
        std::streampos file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<uint8_t> data_vector;
        data_vector.reserve(file_size);
        data_vector.insert(
                data_vector.begin(),
                std::istream_iterator<uint8_t>(file),
                std::istream_iterator<uint8_t>());
        return data_vector;
    }
}
