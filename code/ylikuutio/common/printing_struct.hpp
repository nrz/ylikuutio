#ifndef __PRINTING_STRUCT_HPP_INCLUDED
#define __PRINTING_STRUCT_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.

typedef struct PrintingStruct
{
    PrintingStruct()
        : screen_width(-1),
        screen_height(-1),
        x(-1),
        y(-1),
        text_size(-1),
        font_size(-1),
        text_char(nullptr),
        char_font_texture_file_format(nullptr),
        horizontal_alignment(nullptr),
        vertical_alignment(nullptr)
    {
        // constructor.
    }
    int32_t screen_width;
    int32_t screen_height;
    int32_t x;
    int32_t y;
    int32_t text_size;
    int32_t font_size;
    std::string text;
    const char* text_char;
    const char* char_font_texture_file_format;
    const char* horizontal_alignment;
    const char* vertical_alignment;
} PrintingStruct;

#endif
