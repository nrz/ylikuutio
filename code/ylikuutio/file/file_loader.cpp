// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
#include <ios>      // std::ios
#include <iostream> // std::cout, std::cerr
#include <iterator> // std::istream_iterator
#include <optional> // std::optional
#include <sstream>  // std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::file
{
    std::optional<std::string> slurp(const std::string& file_path)
    {
        // Inspired by http://stackoverflow.com/questions/116038/what-is-the-best-way-to-slurp-a-file-into-a-stdstring-in-c/116220#116220
        std::cout << "Loading file " << file_path << " into memory.\n";

        std::ifstream file_stream(file_path.c_str());

        if (file_stream.fail())
        {
            return std::nullopt;
        }

        std::stringstream file_buffer;
        file_buffer << file_stream.rdbuf();
        return file_buffer.str();
    }

    std::optional<std::vector<uint8_t>> binary_slurp(const std::string& file_path)
    {
        std::cout << "Loading binary file " << file_path << " into memory.\n";

        std::ifstream file_stream(file_path.c_str(), std::ios::binary);

        if (file_stream.fail())
        {
            return std::nullopt;
        }

        file_stream.unsetf(std::ios::skipws);           // Do not skip whitespace.
        file_stream.seekg(0, std::ios::end);
        std::streampos file_size = file_stream.tellg();
        file_stream.seekg(0, std::ios::beg);
        std::vector<uint8_t> data_vector;
        data_vector.reserve(file_size);
        data_vector.insert(
                data_vector.begin(),
                std::istream_iterator<uint8_t>(file_stream),
                std::istream_iterator<uint8_t>());
        return data_vector;
    }
}
