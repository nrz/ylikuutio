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
                SVG_data_pointer++; // Advance to the next byte.
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

    // bool load_SVG_font(std::string font_file_path)
    bool load_SVG_font(
            std::string font_file_path,
            std::vector<std::vector<glm::vec3>> &out_glyph_vertex_data)
    {
        std::cout << "Loading SVG font file " << font_file_path << " ...\n";

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

        // TODO: implement the creation of the glyph objects.
        return true;
    }
}
