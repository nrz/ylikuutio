#include "font_loader.hpp"

// Include standard headers
#include <iostream>  // std::cout, std::cin, std::cerr
#include <string>    // std::string
#include <vector>    // std::vector
#include <string.h>

namespace model
{
    bool check_and_report_if_some_string_matches(const char* SVG_base_pointer, char* SVG_data_pointer, std::vector<std::string> identifier_strings_vector)
    {
        for (std::string identifier_string : identifier_strings_vector)
        {
            const char* identifier_string_char = identifier_string.c_str();

            if (strncmp(SVG_data_pointer, identifier_string_char, strlen(identifier_string_char)) == 0)
            {
                const char* identifier_string_char = identifier_string.c_str();
                uint64_t offset = (uint64_t) SVG_data_pointer - (uint64_t) SVG_base_pointer;
                printf("%s found at file offset 0x%lx (memory address 0x%lx). ", identifier_string_char, offset, (uint64_t) SVG_data_pointer);
                return true;
            }
        }
        return false;
    }

    bool check_if_we_are_inside_block(const char* SVG_base_pointer, char*& SVG_data_pointer)
    {
        std::vector<std::string> identifier_strings_vector;

        // All possible block identifier strings.
        identifier_strings_vector = { "<?xml ", "<!DOCTYPE ", "<svg>", "<metadata>", "</metadata>", "<defs>", "<font ", "<font-face", "<missing-glyph" };
        return model::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, identifier_strings_vector);
    }

    void extract_string_with_several_endings(
            char* dest_mem_pointer,
            char*& src_mem_pointer,
            char* char_end_string)
    {
        while (true)
        {
            uint32_t n_of_ending_characters = strlen(char_end_string);
            char* end_char_pointer;
            end_char_pointer = char_end_string;

            // Check if current character is any of the ending characters.
            while (strncmp(end_char_pointer, "\0", sizeof("\0")) != 0)
            {
                if (strncmp(src_mem_pointer, end_char_pointer, 1) == 0)
                {
                    *dest_mem_pointer = '\0';
                    return;
                }
                end_char_pointer += sizeof(*end_char_pointer);
            }

            // OK, current character is not any of the ending characters.
            // Copy it and advance the pointers accordingly.
            strncpy(dest_mem_pointer, src_mem_pointer, 1);
            dest_mem_pointer += sizeof(*src_mem_pointer);
            src_mem_pointer += sizeof(*src_mem_pointer);
        }
    }

    int32_t extract_value_from_string(const char* SVG_base_pointer, char*& vertex_data_pointer, char* char_end_string, const char* description)
    {
        uint64_t offset = (uint64_t) vertex_data_pointer - (uint64_t) SVG_base_pointer;
        printf("%s found at file offset 0x%lx (memory address 0x%lx).\n", description, offset, (uint64_t) vertex_data_pointer);
        vertex_data_pointer += sizeof(*vertex_data_pointer); // Advance to the next character.
        char char_number_buffer[1024];
        char* dest_mem_pointer;
        dest_mem_pointer = char_number_buffer;
        model::extract_string_with_several_endings(dest_mem_pointer, vertex_data_pointer, char_end_string);
        uint32_t value = atoi(dest_mem_pointer); // FIXME: sometimes the value of `dest_mem_pointer` is invalid and causes segmentation fault here.
        printf("%s: %d\n", description, value);
        return value;
    }

    int32_t extract_value_from_string_with_standard_endings(const char* SVG_base_pointer, char*& vertex_data_pointer, const char* description)
    {
        return model::extract_value_from_string(SVG_base_pointer, vertex_data_pointer, (char*) " -Mmhvz\">", description);
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

                if (model::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, std::vector<std::string> { "<glyph" }))
                {
                    return true;
                }
                if (model::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, std::vector<std::string> { "</svg>" }))
                {
                    return false;
                }

                is_inside_block = model::check_if_we_are_inside_block(SVG_base_pointer, SVG_data_pointer);

                SVG_data_pointer += sizeof(*SVG_data_pointer);  // Advance to the next character.
            }
            else
            {
                // OK, we are inside a block.

                SVG_data_pointer = strchr(SVG_data_pointer, '>');
                check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, std::vector<std::string> { '>' });
                is_inside_block = false;
            }
        }
    }

    void extract_string(
            char* dest_mem_pointer,
            char* &src_mem_pointer,
            char* char_end_string)
    {
        while (strncmp(src_mem_pointer, char_end_string, strlen(char_end_string)) != 0)
        {
            strncpy(dest_mem_pointer, src_mem_pointer, 1);
            dest_mem_pointer += sizeof(*src_mem_pointer);
            src_mem_pointer += sizeof(*src_mem_pointer);
        }
        *dest_mem_pointer = '\0';
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
        std::cout << "Reading SVG font file " << font_file_path << " ...\n";

        // TODO: check the size of the font file programmatically!
        uint32_t kongtext_svg_file_size = 22932;

        // TODO: file size of the font file should not be hardcoded!
        char SVG_data[kongtext_svg_file_size];

        // Open the file
        const char* char_font_file_path = font_file_path.c_str();
        FILE* file = fopen(char_font_file_path, "rb");
        if (!file)
        {
            std::cerr << font_file_path << " could not be opened.\n";
            getchar();
            return false;
        }

        // If less than requested number of bytes are read, it's a problem.
        if (fread(SVG_data, 1, kongtext_svg_file_size, file) != kongtext_svg_file_size)
        {
            std::cerr << "not a correct kongtext.svg file.\n";
            return false;
        }

        bool is_first_glyph_found;

        const char* SVG_base_pointer;
        char* SVG_data_pointer;
        SVG_base_pointer = SVG_data;
        SVG_data_pointer = SVG_data;

        // SVG files are XML files, so we just need to read until we find the data we need.
        is_first_glyph_found = model::find_first_glyph_in_SVG(SVG_base_pointer, SVG_data_pointer);

        if (!is_first_glyph_found)
        {
            std::cerr << "no glyphs were found!\n";
            return false;
        }

        uint64_t offset = (uint64_t) SVG_data_pointer - (uint64_t) SVG_base_pointer;
        printf("First glyph found at file offset 0x%lx (memory address 0x%lx).\n", offset, (uint64_t) SVG_data_pointer);

        // Create the vertex data for each glyph in a loop.
        while (true)
        {
            if (strncmp(SVG_data_pointer, "<glyph", strlen("<glyph")) == 0)
            {
                // A glyph was found!
                // printf("<glyph found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                char char_glyph_name[1024];
                char char_unicode[1024];
                std::vector<glm::vec3> current_glyph_vertices; // vertices of the current glyph.
                bool has_glyph_name = false;
                bool has_glyph_unicode = false;
                bool has_glyph_vertices = false;

                while (true)
                {
                    // Keep reading the glyph.
                    if (strncmp(SVG_data_pointer, "glyph-name=", strlen("glyph-name=")) == 0)
                    {
                        // A glyph-name was found.
                        // TODO: If the glyph does not have a glyph name, an empty string will be stored as glyph-name.
                        // printf("glyph-name= found at 0x%lx.\n", (uint64_t) SVG_data_pointer);

                        // Find the memory address of the opening double quote.
                        char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                        if (opening_double_quote_pointer != nullptr)
                        {
                            // printf("opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);

                            opening_double_quote_pointer += sizeof(*opening_double_quote_pointer);

                            // Find the memory address of the closing double quote.
                            char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                            if (closing_double_quote_pointer != nullptr)
                            {
                                // printf("closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);
                                has_glyph_name = true;

                                closing_double_quote_pointer += sizeof(*closing_double_quote_pointer);

                                model::extract_string(char_glyph_name, opening_double_quote_pointer, (char*) "\"");

                                printf("glyph name: %s\n", char_glyph_name);

                                SVG_data_pointer = closing_double_quote_pointer;
                            } // if (closing_double_quote_pointer != nullptr)
                        } // if (opening_double_quote_pointer != nullptr)
                    } // if (strncmp(SVG_data_pointer, "glyph-name=", strlen("glyph-name=")) == 0)
                    else if (strncmp(SVG_data_pointer, "unicode=", strlen("unicode=")) == 0)
                    {
                        // Unicode was found.
                        // TODO: If the glyph does not have unicode, the glyph will be discarded (as there is no way to refer to it).
                        // printf("unicode= found at 0x%lx.\n", (uint64_t) SVG_data_pointer);

                        // Find the memory address of the opening double quote.
                        char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                        if (opening_double_quote_pointer != nullptr)
                        {
                            // printf("opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);

                            opening_double_quote_pointer += sizeof(*opening_double_quote_pointer);

                            // Find the memory address of the closing double quote.
                            char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                            if (closing_double_quote_pointer != nullptr)
                            {
                                // printf("closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);
                                has_glyph_unicode = true;

                                closing_double_quote_pointer += sizeof(*closing_double_quote_pointer);

                                model::extract_string(char_unicode, opening_double_quote_pointer, (char*) "\"");

                                printf("unicode: %s\n", char_unicode);

                                SVG_data_pointer = closing_double_quote_pointer;
                            } // if (closing_double_quote_pointer != nullptr)
                        } // if (opening_double_quote_pointer != nullptr)
                    } // else if (strncmp(SVG_data_pointer, "unicode=", strlen("unicode=")) == 0)
                    else if (strncmp(SVG_data_pointer, "d=", strlen("d=")) == 0)
                    {
                        // d=" was found.
                        // Follow the path and create the vertices accordingly.
                        // TODO: If the glyph does not have path, the vertex data will be empty (space is an example).
                        // printf("d=\" found at 0x%lx.\n", (uint64_t) SVG_data_pointer);

                        // Find the memory address of the opening double quote.
                        char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                        if (opening_double_quote_pointer != nullptr)
                        {
                            // printf("opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);

                            opening_double_quote_pointer += sizeof(*opening_double_quote_pointer);

                            // Find the memory address of the closing double quote.
                            char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                            if (closing_double_quote_pointer != nullptr)
                            {
                                // printf("closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);
                                has_glyph_vertices = true;

                                closing_double_quote_pointer += sizeof(*closing_double_quote_pointer);

                                glm::vec3 current_vertex;
                                current_vertex.z = 0; // z is not defined in the path (originally these are not 3D fonts!).
                                char char_path[1024];

                                model::extract_string(char_path, opening_double_quote_pointer, (char*) "\"");

                                printf("d: %s\n", char_path);

                                // Loop through vertices and push them to `current_glyph_vertices`.
                                char* vertex_data_pointer;
                                vertex_data_pointer = opening_double_quote_pointer;

                                bool keep_reading_path = true;

                                while (keep_reading_path)
                                {
                                    if (strncmp(vertex_data_pointer, "M", strlen("M")) == 0)
                                    {
                                        current_vertex.x = model::extract_value_from_string_with_standard_endings(SVG_base_pointer, vertex_data_pointer,
                                                (const char*) "M (moveto)");

                                        while (true)
                                        {
                                            if (strncmp(vertex_data_pointer, " ", strlen(" ")) == 0)
                                            {
                                                current_vertex.y = model::extract_value_from_string_with_standard_endings(SVG_base_pointer, vertex_data_pointer,
                                                        (const char*) "space (moveto y coordinate)");
                                                current_glyph_vertices.push_back(current_vertex);
                                                break;
                                            } // if (strncmp(vertex_data_pointer, " ", strlen(" ")) == 0)
                                            vertex_data_pointer += sizeof(*vertex_data_pointer); // Advance to the next character.
                                        } // while (true)
                                    } // if (strncmp(vertex_data_pointer, "M", strlen("M")) == 0)
                                    else if (strncmp(vertex_data_pointer, "h", strlen("h")) == 0)
                                    {
                                        // OK, this is horizontal relative lineto.
                                        int32_t horizontal_lineto_value = model::extract_value_from_string_with_standard_endings(SVG_base_pointer, vertex_data_pointer,
                                                (const char*) "h (horizontal relative lineto)");
                                        current_vertex.x += horizontal_lineto_value;
                                        current_glyph_vertices.push_back(current_vertex);
                                    } // else if (strncmp(vertex_data_pointer, "h", strlen("h")) == 0)
                                    else if (strncmp(vertex_data_pointer, "v", strlen("v")) == 0)
                                    {
                                        // OK, this is vertical relative lineto.
                                        int32_t vertical_lineto_value = model::extract_value_from_string_with_standard_endings(SVG_base_pointer, vertex_data_pointer,
                                                (const char*) "v (vertical relative lineto)");
                                        current_vertex.y += vertical_lineto_value;
                                        current_glyph_vertices.push_back(current_vertex);
                                    } // else if (strncmp(vertex_data_pointer, "v", strlen("v")) == 0)
                                    else if (strncmp(vertex_data_pointer, "z", strlen("z")) == 0)
                                    {
                                        uint64_t offset = (uint64_t) vertex_data_pointer - (uint64_t) SVG_base_pointer;
                                        printf("z (closepath) found at file offset 0x%lx (memory address 0x%lx).\n", offset, (uint64_t) vertex_data_pointer);
                                        keep_reading_path = false;
                                        break;
                                    } // else if (strncmp(vertex_data_pointer, "z", strlen("z")) == 0)
                                    else
                                    {
                                        vertex_data_pointer += sizeof(*vertex_data_pointer);
                                    } // else
                                } // while (keep_reading_path)
                                SVG_data_pointer = closing_double_quote_pointer;
                            } // if (closing_double_quote_pointer != nullptr)
                        } // if (opening_double_quote_pointer != nullptr)
                    } // else if (strncmp(SVG_data_pointer, "d=", strlen("d=")) == 0)
                    else if (strncmp(SVG_data_pointer, ">", strlen(">")) == 0)
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
                            //
                            printf("number of vertices: %lu\n", current_glyph_vertices.size());
                            // Store the vertices of the current vector to the glyph vertex vector
                            // which contains the vertices of all the glyphs.
                            out_glyph_vertex_data.push_back(current_glyph_vertices);
                        } // if (has_glyph_unicode)
                        break;
                    } // else if (strncmp(SVG_data_pointer, ">", strlen(">")) == 0)
                    SVG_data_pointer += sizeof(*SVG_data_pointer);  // Advance to the next byte inside the glyph.
                } // while (true)
            } // End of glyph.
            else
            {
                std::vector<std::string> string_vector;
                string_vector = { "</font>", "</defs>", "</svg>" };

                if (model::check_and_report_if_some_string_matches(SVG_base_pointer, SVG_data_pointer, string_vector))
                {
                    break;
                }
            }
            SVG_data_pointer += sizeof(*SVG_data_pointer);  // Advance to the next byte between glyphs.
        } // while (true)
        return true;
    }
}
