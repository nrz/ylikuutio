#include "font_loader.hpp"
#include "cpp/ylikuutio/file/file_loader.hpp"
#include "cpp/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace model
{
    bool check_if_we_are_inside_block(const char* SVG_base_pointer, char*& SVG_data_pointer)
    {
        // This function returns `true` if we are inside block, `false` otherwise.

        std::vector<std::string> identifier_strings_vector;

        // All possible block identifier strings.
        identifier_strings_vector = { "<?xml ", "<!DOCTYPE ", "<svg>", "<metadata>", "</metadata>", "<defs>", "<font ", "<font-face", "<missing-glyph" };
        return string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, identifier_strings_vector);
    }

    void extract_string_with_several_endings(
            char* dest_mem_pointer,
            char*& src_mem_pointer,
            char* char_end_string)
    {
        // This function copies characters from `src_mem_pointer` until a character matches.

        while (true)
        {
            uint32_t n_of_ending_characters = std::strlen(char_end_string);
            char* end_char_pointer;
            end_char_pointer = char_end_string;

            // Check if current character is any of the ending characters.
            while (*end_char_pointer != '\0')
            {
                if (std::strncmp(src_mem_pointer, end_char_pointer, 1) == 0)
                {
                    *dest_mem_pointer = '\0';
                    return;
                }
                end_char_pointer++;
            }

            // OK, current character is not any of the ending characters.
            // Copy it and advance the pointers accordingly.
            strncpy(dest_mem_pointer, src_mem_pointer, 1);
            dest_mem_pointer++;
            src_mem_pointer++;
        }
    }

    int32_t extract_value_from_string(const char* SVG_base_pointer, char*& vertex_data_pointer, char* char_end_string, const char* description)
    {
        uint64_t offset = (uint64_t) vertex_data_pointer - (uint64_t) SVG_base_pointer;
        std::printf("%s found at file offset 0x%lx (memory address 0x%lx).\n", description, offset, (uint64_t) vertex_data_pointer);
        vertex_data_pointer++;
        char char_number_buffer[1024];
        char* dest_mem_pointer;
        dest_mem_pointer = char_number_buffer;
        model::extract_string_with_several_endings(dest_mem_pointer, vertex_data_pointer, char_end_string);
        uint32_t value = std::atoi(dest_mem_pointer); // FIXME: sometimes the value of `dest_mem_pointer` is invalid and causes segmentation fault here.
        std::printf("%s: %d\n", description, value);
        return value;
    }

    int32_t extract_value_from_string_with_standard_endings(const char* SVG_base_pointer, char*& vertex_data_pointer, const char* description)
    {
        return model::extract_value_from_string(SVG_base_pointer, vertex_data_pointer, (char*) " Mmhvz\">", description);
    }

    bool find_first_glyph_in_SVG(const char* SVG_base_pointer, char*& SVG_data_pointer)
    {
        // This function advances `SVG_data_pointer` to the start of the first glyph.
        // Returns true if a glyph was found.
        // Returns false if no glyph was found.

        bool is_inside_block = false;

        // Read bytes of SVG data until `"<glyph "` is encountered!
        while (true)
        {
            if (!is_inside_block)
            {
                // OK, were are not inside a block.
                if (SVG_data_pointer == nullptr)
                {
                    return false;
                }

                if (string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, std::vector<std::string> { "<glyph" }))
                {
                    return true;
                }
                if (string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, std::vector<std::string> { "</svg>" }))
                {
                    return false;
                }

                is_inside_block = model::check_if_we_are_inside_block(SVG_base_pointer, SVG_data_pointer);
                SVG_data_pointer++;
            }
            else
            {
                // OK, we are inside a block.
                SVG_data_pointer = std::strchr(SVG_data_pointer, '>');
                string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, std::vector<std::string> { '>' });
                is_inside_block = false;
            }
        }
    }

    void extract_string(
            char* dest_mem_pointer,
            char* &src_mem_pointer,
            char* char_end_string)
    {
        while (std::strncmp(src_mem_pointer, char_end_string, std::strlen(char_end_string)) != 0)
        {
            strncpy(dest_mem_pointer, src_mem_pointer, 1);
            dest_mem_pointer++;
            src_mem_pointer++;
        }
        *dest_mem_pointer = '\0';
    }

    void load_SVG_glyph(
            const char* SVG_base_pointer,
            char*& SVG_data_pointer,
            std::vector<std::vector<glm::vec3>> &out_glyph_vertex_data,
            std::vector<std::vector<glm::vec2>> &out_glyph_UV_data,
            std::vector<std::vector<glm::vec3>> &out_glyph_normal_data,
            std::vector<std::string> &glyph_names,
            std::vector<std::string> &unicode_strings,
            float vertex_scaling_factor)
    {
        // This function loads the next SVG glyph.
        // SVG_base_pointer: pointer to the origin of the SVG data.
        // SVG_data_pointer: pointer to the current reading address (must point to a glyph!).
        // out_glyph_vertex_data: vector of 3D objects (glm::vec3 vectors each of which is a vertex of a glyph).
        // out_glyph_vertex_data: vector of glm::vec2 vectors of UVs.
        // out_glyph_normal_data: vector of glm::vec3 vectors of normals
        // glyph_names: vector of glyph names.
        // unicode_strings: vector of unicode strings.
        // vertex_scaling_factor: scaling factor by which the vertex coordinates are multiplied.
    }

    bool load_SVG_font(
            std::string font_file_path,
            std::vector<std::vector<glm::vec3>> &out_glyph_vertex_data,
            std::vector<std::vector<glm::vec2>> &out_glyph_UV_data,
            std::vector<std::vector<glm::vec3>> &out_glyph_normal_data,
            std::vector<std::string> &glyph_names,
            std::vector<std::string> &unicode_strings,
            float vertex_scaling_factor)
    {
        std::string kongtext_svg_string = file::slurp(font_file_path);
        const uint32_t kongtext_svg_size = kongtext_svg_string.size();
        char* SVG_data = new char[kongtext_svg_size];
        std::strncpy(SVG_data, kongtext_svg_string.c_str(), kongtext_svg_size);

        bool is_first_glyph_found;

        const char* SVG_base_pointer;
        char* SVG_data_pointer;
        SVG_base_pointer = SVG_data;
        SVG_data_pointer = SVG_data;

        // SVG files are XML files, so we just need to read until we find the data we need.
        is_first_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);

        if (!is_first_glyph_found || SVG_data_pointer == nullptr)
        {
            std::cerr << "no glyphs were found!\n";
            delete SVG_data;
            return false;
        }

        uint64_t offset = (uint64_t) SVG_data_pointer - (uint64_t) SVG_base_pointer;
        std::printf("First glyph found at file offset 0x%lx (memory address 0x%lx).\n", offset, (uint64_t) SVG_data_pointer);

        // Create the vertex data for each glyph in a loop.
        while (true)
        {
            if (std::strncmp(SVG_data_pointer, "<glyph", std::strlen("<glyph")) == 0)
            {
                // A glyph was found!
                // std::printf("<glyph found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                char char_glyph_name[1024];
                char char_unicode[1024];
                std::vector<glm::vec3> current_glyph_vertices; // vertices of the current glyph.
                bool has_glyph_name = false;
                bool has_glyph_unicode = false;
                bool has_glyph_vertices = false;

                while (true)
                {
                    // Keep reading the glyph.
                    if (std::strncmp(SVG_data_pointer, "glyph-name=", std::strlen("glyph-name=")) == 0)
                    {
                        // A glyph-name was found.
                        // TODO: If the glyph does not have a glyph name, an empty string will be stored as glyph-name.
                        // std::printf("glyph-name= found at 0x%lx.\n", (uint64_t) SVG_data_pointer);

                        // Find the memory address of the opening double quote.
                        char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                        if (opening_double_quote_pointer != nullptr)
                        {
                            // std::printf("opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);

                            opening_double_quote_pointer++;

                            // Find the memory address of the closing double quote.
                            char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                            if (closing_double_quote_pointer != nullptr)
                            {
                                // std::printf("closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);
                                has_glyph_name = true;

                                closing_double_quote_pointer++;

                                model::extract_string(char_glyph_name, opening_double_quote_pointer, (char*) "\"");

                                std::printf("glyph name: %s\n", char_glyph_name);

                                SVG_data_pointer = ++closing_double_quote_pointer;
                            } // if (closing_double_quote_pointer != nullptr)
                            else
                            {
                                std::cerr << "error: no closing double quote found for glyph-name=!\n";
                                delete SVG_data;
                                return false;
                            }
                        } // if (opening_double_quote_pointer != nullptr)
                        else
                        {
                            std::cerr << "error: no opening double quote found for glyph-name=!\n";
                            delete SVG_data;
                            return false;
                        }
                    } // if (std::strncmp(SVG_data_pointer, "glyph-name=", std::strlen("glyph-name=")) == 0)
                    else if (std::strncmp(SVG_data_pointer, "unicode=", std::strlen("unicode=")) == 0)
                    {
                        // Unicode was found.
                        // TODO: If the glyph does not have unicode, the glyph will be discarded (as there is no way to refer to it).
                        // std::printf("unicode= found at 0x%lx.\n", (uint64_t) SVG_data_pointer);

                        // Find the memory address of the opening double quote.
                        char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                        if (opening_double_quote_pointer != nullptr)
                        {
                            // std::printf("opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);

                            opening_double_quote_pointer++;

                            // Find the memory address of the closing double quote.
                            char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                            if (closing_double_quote_pointer != nullptr)
                            {
                                // std::printf("closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);
                                has_glyph_unicode = true;

                                closing_double_quote_pointer++;

                                model::extract_string(char_unicode, opening_double_quote_pointer, (char*) "\"");

                                std::printf("unicode: %s\n", char_unicode);

                                SVG_data_pointer = ++closing_double_quote_pointer;
                            } // if (closing_double_quote_pointer != nullptr)
                            else
                            {
                                std::cerr << "error: no closing double quote found for unicode=!\n";
                                delete SVG_data;
                                return false;
                            }
                        } // if (opening_double_quote_pointer != nullptr)
                        else
                        {
                            std::cerr << "error: no opening double quote found for unicode=!\n";
                            delete SVG_data;
                            return false;
                        }
                    } // else if (std::strncmp(SVG_data_pointer, "unicode=", std::strlen("unicode=")) == 0)
                    else if (std::strncmp(SVG_data_pointer, "d=", std::strlen("d=")) == 0)
                    {
                        // d=" was found.
                        // Follow the path and create the vertices accordingly.
                        // TODO: If the glyph does not have path, the vertex data will be empty (space is an example).
                        // std::printf("d=\" found at 0x%lx.\n", (uint64_t) SVG_data_pointer);

                        // Find the memory address of the opening double quote.
                        char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                        if (opening_double_quote_pointer != nullptr)
                        {
                            // std::printf("opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);

                            opening_double_quote_pointer++;

                            // Find the memory address of the closing double quote.
                            char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                            if (closing_double_quote_pointer != nullptr)
                            {
                                // std::printf("closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);
                                has_glyph_vertices = true;

                                closing_double_quote_pointer++;

                                glm::vec3 current_vertex;
                                current_vertex.z = 0; // z is not defined in the path (originally these are not 3D fonts!).
                                char char_path[1024];

                                model::extract_string(char_path, opening_double_quote_pointer, (char*) "\"");

                                std::printf("d: %s\n", char_path);

                                // Loop through vertices and push them to `current_glyph_vertices`.
                                char* vertex_data_pointer;
                                vertex_data_pointer = char_path;

                                bool keep_reading_path = true;

                                while (keep_reading_path)
                                {
                                    if (std::strncmp(vertex_data_pointer, "M", std::strlen("M")) == 0)
                                    {
                                        current_vertex.x = model::extract_value_from_string_with_standard_endings(SVG_base_pointer, vertex_data_pointer,
                                                (const char*) "M (moveto)");

                                        while (true)
                                        {
                                            if (std::strncmp(vertex_data_pointer, " ", std::strlen(" ")) == 0)
                                            {
                                                current_vertex.y = model::extract_value_from_string_with_standard_endings(SVG_base_pointer, vertex_data_pointer,
                                                        (const char*) "space (moveto y coordinate)");
                                                current_glyph_vertices.push_back(current_vertex);
                                                break;
                                            } // if (std::strncmp(vertex_data_pointer, " ", std::strlen(" ")) == 0)
                                            vertex_data_pointer++;
                                        } // while (true)
                                    } // if (std::strncmp(vertex_data_pointer, "M", std::strlen("M")) == 0)
                                    else if (std::strncmp(vertex_data_pointer, "h", std::strlen("h")) == 0)
                                    {
                                        // OK, this is horizontal relative lineto.
                                        int32_t horizontal_lineto_value = model::extract_value_from_string_with_standard_endings(SVG_base_pointer, vertex_data_pointer,
                                                (const char*) "h (horizontal relative lineto)");
                                        current_vertex.x += horizontal_lineto_value;
                                        current_glyph_vertices.push_back(current_vertex);
                                    } // else if (std::strncmp(vertex_data_pointer, "h", std::strlen("h")) == 0)
                                    else if (std::strncmp(vertex_data_pointer, "v", std::strlen("v")) == 0)
                                    {
                                        // OK, this is vertical relative lineto.
                                        int32_t vertical_lineto_value = model::extract_value_from_string_with_standard_endings(SVG_base_pointer, vertex_data_pointer,
                                                (const char*) "v (vertical relative lineto)");
                                        current_vertex.y += vertical_lineto_value;
                                        current_glyph_vertices.push_back(current_vertex);
                                    } // else if (std::strncmp(vertex_data_pointer, "v", std::strlen("v")) == 0)
                                    else if (std::strncmp(vertex_data_pointer, "z", std::strlen("z")) == 0)
                                    {
                                        uint64_t offset = (uint64_t) vertex_data_pointer - (uint64_t) SVG_base_pointer;
                                        std::printf("z (closepath) found at file offset 0x%lx (memory address 0x%lx).\n", offset, (uint64_t) vertex_data_pointer);
                                        keep_reading_path = false;
                                        break;
                                    } // else if (std::strncmp(vertex_data_pointer, "z", std::strlen("z")) == 0)
                                    else
                                    {
                                        vertex_data_pointer++;
                                    }
                                } // while (keep_reading_path)
                                SVG_data_pointer = ++closing_double_quote_pointer;
                            } // if (closing_double_quote_pointer != nullptr)
                            else
                            {
                                std::cerr << "error: no closing double quote found for d=!\n";
                                delete SVG_data;
                                return false;
                            }
                        } // if (opening_double_quote_pointer != nullptr)
                        else
                        {
                            std::cerr << "error: no opening double quote found for d=!\n";
                            delete SVG_data;
                            return false;
                        }
                    } // else if (std::strncmp(SVG_data_pointer, "d=", std::strlen("d=")) == 0)
                    else if (std::strncmp(SVG_data_pointer, "/>", std::strlen("/>")) == 0)
                    {
                        // OK, this is the end of this glyph.
                        if (has_glyph_unicode)
                        {
                            // OK, this glyph has an unicode, so it can be stored.
                            std::string glyph_unicode_string;
                            glyph_unicode_string = char_unicode;
                            unicode_strings.push_back(glyph_unicode_string);

                            std::string glyph_name_string;

                            if (!has_glyph_name)
                            {
                                glyph_name_string = "";
                            }
                            else
                            {
                                glyph_name_string = char_glyph_name;
                            }
                            glyph_names.push_back(glyph_name_string);

                            // TODO: Create default vertex vector (no vertices), if needed.
                            std::printf("number of vertices: %lu\n", current_glyph_vertices.size());
                            // Store the vertices of the current vector to the glyph vertex vector
                            // which contains the vertices of all the glyphs.
                            out_glyph_vertex_data.push_back(current_glyph_vertices);
                        } // if (has_glyph_unicode)
                        SVG_data_pointer += std::strlen("/>");
                        break;
                    } // else if (std::strncmp(SVG_data_pointer, ">", std::strlen(">")) == 0)
                    else
                    {
                        SVG_data_pointer++; // Advance to the next byte inside the glyph.
                    }
                } // while (true)
            } // End of glyph.
            else
            {
                std::vector<std::string> string_vector;
                string_vector = { "</font>", "</defs>", "</svg>" };

                if (string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, string_vector))
                {
                    delete SVG_data;
                    return true;
                }
                SVG_data_pointer++;
            }
        } // while (true)
    }
}
