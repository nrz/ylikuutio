// Include standard headers
#include <iostream>
#include <string>
#include <string.h>

#include "font_loader.hpp"

namespace model
{
    bool find_first_glyph_in_SVG(char*& SVG_data_pointer)
    {
        bool is_inside_block = false;

        // Read bytes of SVG data until `"<glyph "` is encountered!
        while (true)
        {
            if (!is_inside_block)
            {
                // OK, were are not inside a block.

                if (strncmp(SVG_data_pointer, "<?xml ", strlen("<?xml ")) == 0)
                {
                    printf("<?xml found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    is_inside_block = true;
                }
                else if (strncmp(SVG_data_pointer, "<!DOCTYPE ", strlen("<!DOCTYPE ")) == 0)
                {
                    printf("<!DOCTYPE found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    is_inside_block = true;
                }
                else if (strncmp(SVG_data_pointer, "<svg>", strlen("<svg>")) == 0)
                {
                    printf("<svg> found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    is_inside_block = true;
                }
                else if (strncmp(SVG_data_pointer, "<metadata>", strlen("<metadata>")) == 0)
                {
                    printf("<metadata> found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    is_inside_block = true;
                }
                else if (strncmp(SVG_data_pointer, "</metadata>", strlen("</metadata>")) == 0)
                {
                    printf("</metadata> found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    is_inside_block = true;
                }
                else if (strncmp(SVG_data_pointer, "<defs>", strlen("<defs>")) == 0)
                {
                    printf("<defs> found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    is_inside_block = true;
                }
                else if (strncmp(SVG_data_pointer, "<font ", strlen("<font ")) == 0)
                {
                    printf("<font found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    is_inside_block = true;
                }
                else if (strncmp(SVG_data_pointer, "<font-face", strlen("<font-face")) == 0)
                {
                    printf("<font-face found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    is_inside_block = true;
                }
                else if (strncmp(SVG_data_pointer, "<missing-glyph", strlen("<missing-glyph")) == 0)
                {
                    printf("<missing-glyph found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    is_inside_block = true;
                }
                else if (strncmp(SVG_data_pointer, "<glyph", strlen("<glyph")) == 0)
                {
                    // A glyph was found!
                    printf("<glyph found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                    return true;
                }
                else if (strncmp(SVG_data_pointer, "</svg>", strlen("</svg>")) == 0)
                {
                    // No glyphs were found!
                    printf("No glyphs were found! </svg> found at 0x%lx. ", (uint64_t) SVG_data_pointer);
                    break;
                }
                SVG_data_pointer += sizeof(*SVG_data_pointer);  // Advance to the next character.
            }
            else
            {
                // OK, we are inside a block.

                SVG_data_pointer = strchr(SVG_data_pointer, '>');
                if (SVG_data_pointer != NULL)
                {
                    printf("> found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                }
                is_inside_block = false;
            }
        }
        return false;
    }

    bool extract_string(
            char* dest_mem_pointer,
            char* src_mem_pointer,
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
            std::vector<std::vector<glm::vec3>> &out_glyph_vertex_data)
    {
        std::cout << "Reading SVG font file " << font_file_path << " ...\n";

        // TODO: check the size of the font file programmatically!
        uint32_t kongtext_svg_file_size = 22932;

        // TODO: file size of the font file should not be hardcoded!
        char SVG_data[kongtext_svg_file_size];

        // Open the file
        const char *char_font_file_path = font_file_path.c_str();
        FILE *file = fopen(char_font_file_path, "rb");
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

        char *SVG_data_pointer;
        SVG_data_pointer = SVG_data;

        // SVG files are XML files, so we just need to read until we find the data we need.
        is_first_glyph_found = model::find_first_glyph_in_SVG(SVG_data_pointer);

        if (!is_first_glyph_found)
        {
            std::cerr << "no glyphs were found!\n";
            return false;
        }
        printf("First glyph found at 0x%lx.\n", (uint64_t) SVG_data_pointer);

        // Create the vertex data for each glyph in a loop.
        while (true)
        {
            if (strncmp(SVG_data_pointer, "<glyph", strlen("<glyph")) == 0)
            {
                // A glyph was found!
                // printf("<glyph found at 0x%lx.\n", (uint64_t) SVG_data_pointer);

                while (true)
                {
                    // Keep reading the glyph.
                    if (strncmp(SVG_data_pointer, "glyph-name=", strlen("glyph-name=")) == 0)
                    {
                        // A glyph-name was found.
                        // TODO: If the glyph does not have a glyph name, an empty string will be stored as glyph-name.
                        // printf("glyph-name= found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                        {
                            // Find the memory address of the opening double quote.
                            char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                            if (opening_double_quote_pointer != NULL)
                            {
                                // printf("opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);

                                opening_double_quote_pointer += sizeof(*opening_double_quote_pointer);

                                // Find the memory address of the closing double quote.
                                char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                                if (closing_double_quote_pointer != NULL)
                                {
                                    // printf("closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);

                                    closing_double_quote_pointer += sizeof(*closing_double_quote_pointer);

                                    char char_glyph_name[1024];
                                    char* src_mem_pointer;
                                    char* dest_mem_pointer;
                                    src_mem_pointer = opening_double_quote_pointer;
                                    dest_mem_pointer = char_glyph_name;
                                    extract_string(dest_mem_pointer, src_mem_pointer, (char*) "\"");

                                    printf("glyph name: %s\n", char_glyph_name);

                                    SVG_data_pointer = closing_double_quote_pointer;
                                }
                            }
                        }
                    }
                    else if (strncmp(SVG_data_pointer, "unicode=", strlen("unicode=")) == 0)
                    {
                        // Unicode was found.
                        // TODO: If the glyph does not have unicode, the glyph will be discarded (as there is no way to refer to it).
                        // printf("unicode= found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                        {
                            // Find the memory address of the opening double quote.
                            char* opening_double_quote_pointer = strchr(SVG_data_pointer, '"');
                            if (opening_double_quote_pointer != NULL)
                            {
                                // printf("opening \" found at 0x%lx.\n", (uint64_t) opening_double_quote_pointer);

                                opening_double_quote_pointer += sizeof(*opening_double_quote_pointer);

                                // Find the memory address of the closing double quote.
                                char* closing_double_quote_pointer = strchr(opening_double_quote_pointer, '"');
                                if (closing_double_quote_pointer != NULL)
                                {
                                    // printf("closing \" found at 0x%lx.\n", (uint64_t) closing_double_quote_pointer);

                                    closing_double_quote_pointer += sizeof(*closing_double_quote_pointer);

                                    char char_unicode[1024];
                                    char* src_mem_pointer;
                                    char* dest_mem_pointer;
                                    src_mem_pointer = opening_double_quote_pointer;
                                    dest_mem_pointer = char_unicode;
                                    extract_string(dest_mem_pointer, src_mem_pointer, (char*) "\"");

                                    printf("unicode: %s\n", char_unicode);

                                    SVG_data_pointer = closing_double_quote_pointer;
                                }
                            }
                        }
                    }
                    else if (strncmp(SVG_data_pointer, "d=\"", strlen("d=\"")) == 0)
                    {
                        // d=" was found.
                        // Follow the path and create the vertices accordingly.
                        // TODO: If the glyph does not have path, the vertex data will be empty (space is an example).
                        // printf("d=\" found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                        {
                            SVG_data_pointer += strlen("d=\"");
                        }
                    }
                    else if (strncmp(SVG_data_pointer, ">", strlen(">")) == 0)
                    {
                        // OK, this is the end of this glyph.
                        break;
                    }
                    SVG_data_pointer += sizeof(*SVG_data_pointer);  // Advance to the next byte inside the glyph.
                }
            } // End of glyph.
            else if (strncmp(SVG_data_pointer, "</font>", strlen("</font>")) == 0)
            {
                printf("</font> found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                break;
            }
            else if (strncmp(SVG_data_pointer, "</defs>", strlen("</defs>")) == 0)
            {
                printf("</defs> found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                break;
            }
            else if (strncmp(SVG_data_pointer, "</svg>", strlen("</svg>")) == 0)
            {
                printf("</svg> found at 0x%lx.\n", (uint64_t) SVG_data_pointer);
                break;
            }
            SVG_data_pointer += sizeof(*SVG_data_pointer);  // Advance to the next byte between glyphs.
        }
        return true;
    }
}
