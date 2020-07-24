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

#ifndef __CSV_LOADER_HPP_INCLUDED
#define __CSV_LOADER_HPP_INCLUDED

#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::load
{
    template<class T1>
        std::shared_ptr<std::vector<T1>> load_csv_file(
                const std::string& filename,
                std::size_t& data_width,
                std::size_t& data_height,
                std::size_t& data_size)
        {
            // Open the file
            const std::shared_ptr<std::string> file_content = yli::file::slurp(filename);

            if (file_content == nullptr || file_content->empty())
            {
                std::cerr << filename << " could not be opened, or the file is empty.\n";
                return nullptr;
            }

            // Assume that all lines have equal number of elements.
            // If any lines has number of elements different than the first line with elements,
            // that is an error and `nullptr` will be returned and `data_width`, `data_height`,
            // and `data_size` are set to 0.
            // However, lines with 0 elements are allowed at any time.

            // Initialize output values to 0 in case that loading fails due to an error.
            data_width = 0;
            data_height = 0;
            data_size = 0;

            std::size_t file_content_i = 0;
            std::size_t n_lines = 0;
            std::size_t n_elements_in_first_line = 0;
            std::size_t n_elements_in_current_line = 0;
            const char* const char_end_string = ", \n";

            std::shared_ptr<std::vector<T1>> data_vector = std::make_shared<std::vector<T1>>();

            while (file_content_i < file_content->size())
            {
                // All possible block identifier strings.
                const std::vector<std::string> whitespace_strings = { ",", " ", "\n" };

                while (yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, whitespace_strings))
                {
                    if (file_content_i < file_content->size() && (*file_content)[file_content_i] == '\n')
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
                                return nullptr;
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

                T1 value = 0;
                yli::string::extract_value_from_string(*file_content, file_content_i, char_end_string, nullptr, value);
                data_vector->emplace_back(value);
                n_elements_in_current_line++;

                while (file_content_i < file_content->size() && !yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, whitespace_strings))
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
                    return nullptr;
                }
            }

            data_width = n_elements_in_first_line;
            data_height = n_lines;
            data_size = n_lines * n_elements_in_first_line;
            data_size = data_vector->size();
            return data_vector;
        }
}

#endif
