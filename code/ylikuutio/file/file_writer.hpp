// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_FILE_FILE_WRITER_HPP_INCLUDED
#define YLIKUUTIO_FILE_FILE_WRITER_HPP_INCLUDED

// Include standard headers
#include <fstream>  // std::ifstream
#include <ios>      // std::ios
#include <iostream> // std::cout, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::file
{
    template<typename T1>
        void binary_write(const std::vector<T1>& data, const std::string& file_path)
        {
            std::cout << "Writing binary file " << file_path << "\n";

            std::ofstream file_stream(file_path, std::ios::out | std::ios::binary);
            file_stream.write((char*) &data[0], data.size() * sizeof(T1));
            file_stream.close();
        }
}

#endif
