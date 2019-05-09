#ifndef __FILE_WRITER_HPP_INCLUDED
#define __FILE_WRITER_HPP_INCLUDED

// Include standard headers
#include <fstream>  // std::ifstream
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace file
    {
        template<class T1>
            void binary_write(const std::vector<T1>& data, const std::string& file_path)
            {
                std::cout << "Writing binary file " << file_path << "\n";

                std::ofstream file_stream(file_path, std::ios::out | std::ios::binary);
                file_stream.write((char*) &data[0], data.size() * sizeof(T1));
                file_stream.close();
            }
    }
}

#endif
