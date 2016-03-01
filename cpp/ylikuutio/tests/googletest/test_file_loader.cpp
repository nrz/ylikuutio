#include "gtest/gtest.h"
#include "cpp/ylikuutio/file/file_loader.hpp"

// Include standard headers
TEST(file_must_be_slurped_appropriately, kongtext_svg)
{
    std::string file_contents = file::slurp("kongtext.svg");
    const char* file_contents_char = file_contents.c_str();
    const char* first_line_of_kongtext_svg = "<?xml version=\"1.0\" standalone=\"no\"?>";
    std::cout << "Length of first_line_of_kongtext_svg: " << strlen(first_line_of_kongtext_svg) << "\n";
    printf("%.*s\n", strlen(first_line_of_kongtext_svg), file_contents_char);
    ASSERT_EQ(strncmp(file_contents_char, first_line_of_kongtext_svg, strlen(first_line_of_kongtext_svg)), 0);
}
