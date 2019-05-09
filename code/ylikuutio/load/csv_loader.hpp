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

namespace yli
{
    namespace load
    {
        template<class T1>
            std::shared_ptr<std::vector<T1>> load_CSV_file(
                    const std::string& csv_filename,
                    std::size_t& data_width,
                    std::size_t& data_height,
                    std::size_t& data_size)
            {
                // Open the file
                const std::string file_content = yli::file::slurp(csv_filename);

                if (file_content.empty())
                {
                    std::cerr << csv_filename << " could not be opened, or the file is empty.\n";
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

                while (file_content_i < file_content.size())
                {
                    // All possible block identifier strings.
                    const std::vector<std::string> whitespace_strings = { ",", " ", "\n" };

                    while (yli::string::check_and_report_if_some_string_matches(file_content, file_content_i, whitespace_strings))
                    {
                        if (file_content_i < file_content.size() && file_content[file_content_i] == '\n')
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

                    if (file_content_i >= file_content.size())
                    {
                        break;
                    }

                    T1 value = 0;
                    yli::string::extract_value_from_string(file_content, file_content_i, char_end_string, nullptr, value);
                    data_vector->push_back(value);
                    n_elements_in_current_line++;

                    while (file_content_i < file_content.size() && !yli::string::check_and_report_if_some_string_matches(file_content, file_content_i, whitespace_strings))
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
}

#endif
