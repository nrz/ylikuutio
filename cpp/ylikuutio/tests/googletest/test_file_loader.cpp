#include "gtest/gtest.h"
#include "cpp/ylikuutio/file/file_loader.hpp"

// Include standard headers
#include <stdio.h>  // FILE, fclose, fopen, fread, getchar, printf etc.

TEST(file_must_be_slurped_appropriately, kongtext_svg)
{
    std::string file_contents = file::slurp("kongtext.svg");
    const char* file_contents_char = file_contents.c_str();
    const char* first_line_of_kongtext_svg = "<?xml version=\"1.0\" standalone=\"no\"?>";
    printf("%.*s\n", strlen(first_line_of_kongtext_svg), file_contents_char);
    ASSERT_EQ(strncmp(file_contents_char, first_line_of_kongtext_svg, strlen(first_line_of_kongtext_svg)), 0);

    int offset_of_first_character_of_tenth_line = 0x126;
    const char* tenth_line_of_kongtext_svg = "<font id=\"KongtextRegular\" horiz-adv-x=\"1024\" >";
    printf("%.*s\n", strlen(tenth_line_of_kongtext_svg), file_contents_char + offset_of_first_character_of_tenth_line);
    ASSERT_EQ(strncmp(file_contents_char + offset_of_first_character_of_tenth_line, tenth_line_of_kongtext_svg, strlen(tenth_line_of_kongtext_svg)), 0);
}
