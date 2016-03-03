#include "gtest/gtest.h"
#include "cpp/ylikuutio/file/file_loader.hpp"

// Include standard headers
#include <cstdio>  // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring> // std::memcmp, std::strcmp, std::strlen, std::strncmp

TEST(file_must_be_slurped_appropriately, kongtext_svg)
{
    std::string file_contents = file::slurp("kongtext.svg");
    const char* file_contents_char = file_contents.c_str();
    const char* first_line_of_kongtext_svg = "<?xml version=\"1.0\" standalone=\"no\"?>";
    std::printf("%.*s\n", std::strlen(first_line_of_kongtext_svg), file_contents_char);
    ASSERT_EQ(std::strncmp(file_contents_char, first_line_of_kongtext_svg, std::strlen(first_line_of_kongtext_svg)), 0);

    int offset_of_first_character_of_tenth_line = 0x126;
    const char* tenth_line_of_kongtext_svg = "<font id=\"KongtextRegular\" horiz-adv-x=\"1024\" >";
    std::printf("%.*s\n", std::strlen(tenth_line_of_kongtext_svg), file_contents_char + offset_of_first_character_of_tenth_line);
    ASSERT_EQ(std::strncmp(file_contents_char + offset_of_first_character_of_tenth_line, tenth_line_of_kongtext_svg, std::strlen(tenth_line_of_kongtext_svg)), 0);
}
