// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "file_loader.hpp"

// Include standard headers
#include <fstream>  // std::ifstream
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <iterator> // std::istream_iterator
#include <memory>   // std::make_shared, std::shared_ptr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace file
    {
        std::shared_ptr<std::string> slurp(const std::string& file_path)
        {
            // inspired by http://stackoverflow.com/questions/116038/what-is-the-best-way-to-slurp-a-file-into-a-stdstring-in-c/116220#116220
            std::cout << "Loading file " << file_path << " into memory.\n";

            std::ifstream input_stream(file_path.c_str());

            if (input_stream.fail())
            {
                return nullptr;
            }

            std::stringstream file_buffer;
            file_buffer << input_stream.rdbuf();
            std::shared_ptr<std::string> file_contents = std::make_shared<std::string>(file_buffer.str());
            return file_contents;
        }

        std::shared_ptr<std::vector<uint8_t>> binary_slurp(const std::string& file_path)
        {
            std::cout << "Loading binary file " << file_path << " into memory.\n";

            std::ifstream file(file_path.c_str(), std::fstream::binary);

            if (file.fail())
            {
                return nullptr;
            }

            file.unsetf(std::ios::skipws);           // do not skip whitespace.
            file.seekg(0, std::ios::end);
            std::streampos file_size = file.tellg();
            file.seekg(0, std::ios::beg);
            std::shared_ptr<std::vector<uint8_t>> data_vector = std::make_shared<std::vector<uint8_t>>();
            data_vector->reserve(file_size);
            data_vector->insert(
                    data_vector->begin(),
                    std::istream_iterator<uint8_t>(file),
                    std::istream_iterator<uint8_t>());
            return data_vector;
        }
    }
}
