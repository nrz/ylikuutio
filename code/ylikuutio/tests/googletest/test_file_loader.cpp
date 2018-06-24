#include "gtest/gtest.h"
#include "code/ylikuutio/file/file_loader.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

TEST(file_must_be_slurped_appropriately, kongtext_svg)
{
    const std::string file_content = file::slurp("kongtext.svg");
    const std::string first_line_of_kongtext_svg = "<?xml version=\"1.0\" standalone=\"no\"?>";
    const uint32_t length_of_first_line_of_kongtext_svg = first_line_of_kongtext_svg.size();
    ASSERT_EQ(file_content.compare(0, length_of_first_line_of_kongtext_svg, first_line_of_kongtext_svg), 0);

    const uint32_t offset_of_first_character_of_tenth_line = 0x126;
    const std::string tenth_line_of_kongtext_svg = "<font id=\"KongtextRegular\" horiz-adv-x=\"1024\" >";
    const uint32_t length_of_tenth_line_of_kongtext_svg = tenth_line_of_kongtext_svg.size();
    ASSERT_EQ(file_content.compare(offset_of_first_character_of_tenth_line, length_of_tenth_line_of_kongtext_svg, tenth_line_of_kongtext_svg), 0);
}
