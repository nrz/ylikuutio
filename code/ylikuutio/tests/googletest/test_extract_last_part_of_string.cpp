#include "gtest/gtest.h"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string
#include <vector>   // std::vector

TEST(extract_last_part_of_string, nothing_must_be_extracted_when_source_string_is_empty_string)
{
    char text[] = "";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'a';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, nothing_must_be_extracted_when_source_string_is_1_char_and_has_no_separator)
{
    char text[] = "a";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'b';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, nothing_must_be_extracted_when_source_string_is_2_same_chars_and_has_no_separator)
{
    char text[] = "aa";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'b';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, nothing_must_be_extracted_when_source_string_is_2_different_chars_and_has_no_separator)
{
    char text[] = "ab";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'c';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, nothing_must_be_extracted_when_source_string_is_3_different_chars_and_has_no_separator)
{
    char text[] = "abc";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'd';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, nothing_must_be_extracted_when_source_string_is_2_same_chars_and_separator_is_the_last_char)
{
    char text[] = "ab";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'b';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, nothing_must_be_extracted_when_source_string_is_2_same_chars_and_separator_is_the_same_char)
{
    char text[] = "aa";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'a';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, nothing_must_be_extracted_when_source_string_is_3_same_chars_and_separator_is_the_same_char)
{
    char text[] = "aaa";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'a';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, 1_char_must_be_extracted_when_source_string_is_2_different_chars_and_separator_is_the_first_char)
{
    char text[] = "ab";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'a';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, nothing_must_be_extracted_when_source_string_is_3_different_chars_and_separator_is_the_last_char)
{
    char text[] = "abc";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'c';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, 1_char_must_be_extracted_when_source_string_is_3_different_chars_and_separator_is_the_second_char)
{
    char text[] = "abc";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'b';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'c');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_last_part_of_string, 2_chars_must_be_extracted_when_source_string_is_3_different_chars_and_separator_is_the_first_char)
{
    char text[] = "abc";

    const std::size_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;
    const char separator = 'a';

    yli::string::extract_last_part_of_string(text, sizeof(text), dest_array, array_size, separator);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array++, 'c');
    ASSERT_EQ(*dest_array, 0);
}
