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

    int32_t extract_value_from_string(char*& vertex_data_pointer, char* char_end_string, const char* description)
    {
        vertex_data_pointer++;
        char char_number_buffer[1024]; // FIXME: risk of buffer overflow.
        char* dest_mem_pointer;
        dest_mem_pointer = char_number_buffer;
        string::extract_string_with_several_endings(dest_mem_pointer, vertex_data_pointer, char_end_string);
        uint32_t value = std::atoi(dest_mem_pointer);
        std::printf("%s: %d\n", description, value);
        return value;
    }

    int32_t extract_value_from_string_with_standard_endings(char*& vertex_data_pointer, const char* description)
    {
        return model::extract_value_from_string(vertex_data_pointer, (char*) " Mmhvz\">", description);
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
                string::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, std::vector<std::string> { ">" });
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
            strncpy(dest_mem_pointer++, src_mem_pointer++, 1);
        }
        *dest_mem_pointer = '\0';
    }

    bool load_vertex_data(
            const char* SVG_base_pointer,
            char*& SVG_data_pointer,
            std::vector<std::vector<glm::vec3>> &current_glyph_vertices)
    {
        // This function returns a pointer to vertex data of a single glyph and advances `SVG_data_pointer`.

        std::vector<glm::vec3> vertices_of_current_edge_section;    // vertices of the current edge section.
        // d=" was found.
        // Follow the path and create the vertices accordingly.

        // Find the memory address of the opening double quote.
        char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
        if (opening_double_quote_pointer == nullptr)
        {
            std::cerr << "error: no opening double quote found for d=!\n";
            return false;
        }

        // Find the memory address of the closing double quote.
        char* closing_double_quote_pointer = strchr(++opening_double_quote_pointer, '"');
        if (closing_double_quote_pointer == nullptr)
        {
            std::cerr << "error: no closing double quote found for d=!\n";
            return false;
        }

        glm::vec3 current_vertex;
        current_vertex.z = 0; // z is not defined in the path (originally these are not 3D fonts!).
        char char_path[1024];

        // copy from opening double quote to the next `"/"`.
        model::extract_string(char_path, opening_double_quote_pointer, (char*) "/");

        std::printf("d: %s\n", char_path);

        // Loop through vertices and push them to `current_glyph_vertices`.
        char* vertex_data_pointer;
        vertex_data_pointer = char_path;

        while (true)
        {
            if (std::strncmp(vertex_data_pointer, "M", std::strlen("M")) == 0)
            {
                current_vertex.x = model::extract_value_from_string_with_standard_endings(vertex_data_pointer,
                        (const char*) "M (moveto)");

                while (true)
                {
                    if (std::strncmp(vertex_data_pointer, " ", std::strlen(" ")) == 0)
                    {
                        current_vertex.y = model::extract_value_from_string_with_standard_endings(vertex_data_pointer,
                                (const char*) "space (moveto y coordinate)");
                        vertices_of_current_edge_section.push_back(current_vertex);
                        break;
                    } // if (std::strncmp(vertex_data_pointer, " ", std::strlen(" ")) == 0)
                    vertex_data_pointer++;
                } // while (true)
            } // if (std::strncmp(vertex_data_pointer, "M", std::strlen("M")) == 0)
            else if (std::strncmp(vertex_data_pointer, "h", std::strlen("h")) == 0)
            {
                // OK, this is horizontal relative lineto.
                int32_t horizontal_lineto_value = model::extract_value_from_string_with_standard_endings(vertex_data_pointer,
                        (const char*) "h (horizontal relative lineto)");
                current_vertex.x += horizontal_lineto_value;
                vertices_of_current_edge_section.push_back(current_vertex);
            } // else if (std::strncmp(vertex_data_pointer, "h", std::strlen("h")) == 0)
            else if (std::strncmp(vertex_data_pointer, "v", std::strlen("v")) == 0)
            {
                // OK, this is vertical relative lineto.
                int32_t vertical_lineto_value = model::extract_value_from_string_with_standard_endings(vertex_data_pointer,
                        (const char*) "v (vertical relative lineto)");
                current_vertex.y += vertical_lineto_value;
                vertices_of_current_edge_section.push_back(current_vertex);
            } // else if (std::strncmp(vertex_data_pointer, "v", std::strlen("v")) == 0)
            else if (std::strncmp(vertex_data_pointer, "z", std::strlen("z")) == 0)
            {
                std::printf("z (closepath)\n");
                current_glyph_vertices.push_back(vertices_of_current_edge_section); // store the vertices of the current edge section.
                vertices_of_current_edge_section.clear();                           // clear the vector of vertices of the current edge section.
                vertex_data_pointer++;
            } // else if (std::strncmp(vertex_data_pointer, "z", std::strlen("z")) == 0)
            else if (std::strncmp(vertex_data_pointer, "\"", std::strlen("\"")) == 0)
            {
                std::printf("\" (end of vertex data)\n");
                SVG_data_pointer = ++closing_double_quote_pointer;
                return true;
            } // else if (std::strncmp(vertex_data_pointer, "\"", std::strlen("\"")) == 0)
            else
            {
                vertex_data_pointer++;
            }
        } // while (true)
    }

    bool load_SVG_glyph(
            const char* SVG_base_pointer,
            char*& SVG_data_pointer,
            std::vector<std::vector<std::vector<glm::vec3>>> &out_glyph_vertex_data,
            std::vector<std::string> &glyph_names,
            std::vector<std::string> &unicode_strings)
    {
        // This function loads the next SVG glyph.
        // SVG_base_pointer: pointer to the origin of the SVG data.
        // SVG_data_pointer: pointer to the current reading address (must point to a glyph!).
        // out_glyph_vertex_data: vector of 3D objects consisting of 1 or more edge sections consisting of glm::vec3 vectors each of which is a vertex of a glyph.
        // glyph_names: vector of glyph names.
        // unicode_strings: vector of unicode strings.

        // A glyph was found!
        // std::printf("<glyph found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
        char char_glyph_name[1024]; // FIXME: risk of buffer overflow.
        char char_unicode[1024];    // FIXME: risk of buffer overflow.
        std::vector<std::vector<glm::vec3>> current_glyph_vertices; // vertices of the current glyph.
        bool has_glyph_name = false;
        bool has_glyph_unicode = false;

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
                        return false;
                    }
                } // if (opening_double_quote_pointer != nullptr)
                else
                {
                    std::cerr << "error: no opening double quote found for glyph-name=!\n";
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

                        model::extract_string(char_unicode, opening_double_quote_pointer, (char*) "\"");

                        std::printf("unicode: %s\n", char_unicode);

                        SVG_data_pointer = ++closing_double_quote_pointer;
                    } // if (closing_double_quote_pointer != nullptr)
                    else
                    {
                        std::cerr << "error: no closing double quote found for unicode=!\n";
                        return false;
                    }
                } // if (opening_double_quote_pointer != nullptr)
                else
                {
                    std::cerr << "error: no opening double quote found for unicode=!\n";
                    return false;
                }
            } // else if (std::strncmp(SVG_data_pointer, "unicode=", std::strlen("unicode=")) == 0)
            else if (std::strncmp(SVG_data_pointer, "d=", std::strlen("d=")) == 0)
            {
                bool result = model::load_vertex_data(SVG_base_pointer, SVG_data_pointer, current_glyph_vertices);
                if (result == false)
                {
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
        return true;
    }

    bool load_SVG_font(
            std::string font_file_path,
            std::vector<std::vector<std::vector<glm::vec3>>> &out_glyph_vertex_data,
            std::vector<std::string> &glyph_names,
            std::vector<std::string> &unicode_strings)
    {
        std::string file_content = file::slurp(font_file_path);
        const uint32_t file_size = file_content.size();
        char* SVG_data = new char[file_size];
        std::strncpy(SVG_data, file_content.c_str(), file_size);

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
                bool result = model::load_SVG_glyph(
                        SVG_base_pointer,
                        SVG_data_pointer,
                        out_glyph_vertex_data,
                        glyph_names,
                        unicode_strings);
                if (!result)
                {
                    delete SVG_data;
                    return false;
                }
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
