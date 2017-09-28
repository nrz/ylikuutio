#include "gtest/gtest.h"
#include "code/ylikuutio/file/file_loader.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

TEST(file_must_be_slurped_appropriately, kongtext_svg)
{
    std::string file_contents = file::slurp("kongtext.svg");
    std::string first_line_of_kongtext_svg = "<?xml version=\"1.0\" standalone=\"no\"?>";
    uint32_t length_of_first_line_of_kongtext_svg = first_line_of_kongtext_svg.size();
    ASSERT_EQ(file_contents.compare(0, length_of_first_line_of_kongtext_svg, first_line_of_kongtext_svg), 0);

    uint32_t offset_of_first_character_of_tenth_line = 0x126;
    std::string tenth_line_of_kongtext_svg = "<font id=\"KongtextRegular\" horiz-adv-x=\"1024\" >";
    uint32_t length_of_tenth_line_of_kongtext_svg = tenth_line_of_kongtext_svg.size();
    ASSERT_EQ(file_contents.compare(offset_of_first_character_of_tenth_line, length_of_tenth_line_of_kongtext_svg, tenth_line_of_kongtext_svg), 0);
}
