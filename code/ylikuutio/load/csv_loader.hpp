// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_LOAD_CSV_LOADER_HPP_INCLUDED
#define YLIKUUTIO_LOAD_CSV_LOADER_HPP_INCLUDED

#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>     // std::size_t
#include <iostream>    // std::cout, std::cerr
#include <optional>    // std::optional
#include <stdint.h>    // uint32_t etc.
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector

namespace yli::load
{
    template<typename T1>
        std::optional<std::vector<T1>> load_csv_file(
                const std::string& filename,
                uint32_t& data_width,
                uint32_t& data_height,
                uint32_t& data_size)
        {
            // Open the file
            const std::optional<std::string> file_content = yli::file::slurp(filename);

            if (!file_content)
            {
                std::cerr << "ERROR: `yli::load::load_csv_file`: CSV file " << filename << " not loaded successfully!\n";
                return std::nullopt;
            }

            if (file_content->empty())
            {
                std::cerr << "ERROR: `yli::load::load_csv_file`: CSV file " << filename << " is empty!\n";
                return std::nullopt;
            }

            // Assume that all lines have equal number of elements.
            // If any lines has number of elements different than the first line with elements,
            // that is an error and `std::nullopt` will be returned and `data_width`, `data_height`,
            // and `data_size` are set to 0.
            // However, lines with 0 elements are allowed at any time.

            // Initialize output values to 0 in case that loading fails due to an error.
            data_width = 0;
            data_height = 0;
            data_size = 0;

            std::size_t file_content_i = 0;
            uint32_t n_lines = 0;
            uint32_t n_elements_in_first_line = 0;
            uint32_t n_elements_in_current_line = 0;
            const char* const char_end_string = ", \n";

            std::vector<T1> data_vector;

            while (file_content_i < file_content->size())
            {
                // All possible block identifier strings.
                const std::vector<std::string> whitespace_strings = { ",", " ", "\n" };

                while (yli::string::check_and_report_if_some_string_matches<char>(*file_content, file_content_i, whitespace_strings))
                {
                    if (file_content_i < file_content->size() && file_content->at(file_content_i) == '\n')
                    {
                        // Newline was found.
                        if (n_elements_in_current_line > 0)
                        {
                            // This line was not empty.
                            n_lines++;

                            if (n_elements_in_first_line == 0)
                            {
                                // This was the first non-empty line.
                                n_elements_in_first_line = n_elements_in_current_line;
                            }
                            else if (n_elements_in_current_line != n_elements_in_first_line)
                            {
                                // This line has a different number of elements than the first line.
                                // All non-empty lines are expected to have the same number of elements,
                                // so that the data can be entered in a matrix.
                                return std::nullopt;
                            }
                        }

                        // Next line begins now.
                        n_elements_in_current_line = 0;
                    }

                    file_content_i++;
                }

                if (file_content_i >= file_content->size())
                {
                    break;
                }

                std::optional<T1> value = yli::string::extract_value_from_string<char, T1>(*file_content, file_content_i, char_end_string, std::string_view(""));

                if (!value)
                {
                    std::cerr << "ERROR: `yli::load::load_csv_file`: extracting value from string failed!\n";
                    return std::nullopt;
                }

                data_vector.emplace_back(*value);
                n_elements_in_current_line++;

                while (file_content_i < file_content->size() && !yli::string::check_and_report_if_some_string_matches<char>(*file_content, file_content_i, whitespace_strings))
                {
                    file_content_i++;
                }
            }

            if (n_elements_in_current_line > 0)
            {
                // This last line was not an empty line.
                n_lines++;

                if (n_elements_in_current_line != n_elements_in_first_line)
                {
                    // This line has a different number of elements than the first line.
                    // All non-empty lines are expected to have the same number of elements,
                    // so that the data can be entered in a matrix.
                    std::cout << "n_elements_in_current_line = " << n_elements_in_current_line << "\n";
                    std::cout << "n_elements_in_first_line = " << n_elements_in_first_line << "\n";
                    return std::nullopt;
                }
            }

            data_width = n_elements_in_first_line;
            data_height = n_lines;
            data_size = n_lines * n_elements_in_first_line;
            data_size = data_vector.size();
            return data_vector;
        }
}

#endif
