#include "gtest/gtest.h"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/string/ylikuutio_string.cpp"

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

TEST(string_matching, some_string_must_match_when_the_only_identifier_string_is_an_empty_string)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, some_string_must_match_when_there_is_only_one_1_character_string_in_the_identifier_string_vector_and_it_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));

    char other_text[] = "ab";
    const char* other_text_base_pointer = other_text;
    char* other_text_data_pointer = other_text;
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(other_text_base_pointer, other_text_data_pointer, sizeof(other_text), identifier_strings_vector));
}

TEST(string_matching, some_string_must_match_when_there_is_only_one_2_character_string_in_the_identifier_string_vector_and_it_matches)
{
    char text[] = "ab";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "ab" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, some_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_it_matches)
{
    char text[] = "abc";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "abc" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, some_string_must_match_when_there_are_two_1_character_strings_in_the_identifier_string_vector_and_the_1st_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, some_string_must_match_when_there_are_two_1_character_strings_in_the_identifier_string_vector_and_the_2nd_matches)
{
    char text[] = "b";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, some_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_the_1st_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b", "c" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, some_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_the_2nd_matches)
{
    char text[] = "b";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b", "c" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, some_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_the_3rd_matches)
{
    char text[] = "c";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b", "c" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_the_identifier_string_vector_is_empty)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = {};
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_the_only_identifier_string_is_longer_than_the_string_to_be_compared_with)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "aa" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_there_is_only_one_1_character_string_in_the_identifier_string_vector_and_it_does_not_match)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "b" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));

    identifier_strings_vector = { "A" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_there_is_only_one_2_character_string_in_the_identifier_string_vector_and_its_1st_character_does_not_match)
{
    char text[] = "ab";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "bb" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));

    identifier_strings_vector = { "Ab" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_there_is_only_one_2_character_string_in_the_identifier_string_vector_and_its_2nd_character_does_not_match)
{
    char text[] = "ab";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "aa" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));

    identifier_strings_vector = { "aB" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_its_1st_character_does_not_match)
{
    char text[] = "abc";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "bbc" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));

    identifier_strings_vector = { "Abc" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_its_2nd_character_does_not_match)
{
    char text[] = "abc";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "aac" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));

    identifier_strings_vector = { "aBc" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_its_3rd_character_does_not_match)
{
    char text[] = "abc";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "abb" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));

    identifier_strings_vector = { "abC" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_there_are_two_1_character_strings_in_the_identifier_string_vector_and_neither_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "A", "b" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(string_matching, no_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_none_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "A", "b", "c" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, sizeof(text), identifier_strings_vector));
}

TEST(unicode_value_from_string, char_only_a)
{
    const char text[] = "a";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
}

TEST(unicode_value_from_string, char_only_abc)
{
    const char text[] = "abc";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'b');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'c');
}

TEST(unicode_value_from_string, unicode_a)
{
    const char text[] = "&#xa;";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0xa);
}

TEST(unicode_value_from_string, unicode_deadbeef)
{
    const char text[] = "&#xdeadbeef;";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0xdeadbeef);
}

TEST(unicode_value_from_string, iloinen_10cc1_01c00_ja_c1e1ece_caace101_kaikkialle)
{
    const char text[] = "iloinen&#x10cc1;&#x01c00;ja&#xc1e1ece;&#xcaace101;kaikkialle";
    const char* text_pointer = text;
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'l');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'o');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'n');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'e');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'n');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0x10cc1);
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0x01c00);
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'j');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0xc1e1ece);
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 0xcaace101);
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'k');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'k');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'k');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'l');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'l');
    ASSERT_EQ(string::extract_unicode_value_from_string(text_pointer), 'e');
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_empty_string)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_1_char)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "a";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_same_chars)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "aa";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_different_chars)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "ab";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, 1_char_must_be_extracted_when_source_string_is_1_char_and_end_string_is_1_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "a";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_from_memory, iloinen_lokki_laulaa_ja_nukkuu)
{
    char text[] = "iloinen lokki laulaa ja nukkuu";
    char* text_pointer = text;

    char end_string[] = "ja";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'i');
    ASSERT_EQ(*dest_array++, 'l');
    ASSERT_EQ(*dest_array++, 'o');
    ASSERT_EQ(*dest_array++, 'i');
    ASSERT_EQ(*dest_array++, 'n');
    ASSERT_EQ(*dest_array++, 'e');
    ASSERT_EQ(*dest_array++, 'n');
    ASSERT_EQ(*dest_array++, ' ');
    ASSERT_EQ(*dest_array++, 'l');
    ASSERT_EQ(*dest_array++, 'o');
    ASSERT_EQ(*dest_array++, 'k');
    ASSERT_EQ(*dest_array++, 'k');
    ASSERT_EQ(*dest_array++, 'i');
    ASSERT_EQ(*dest_array++, ' ');
    ASSERT_EQ(*dest_array++, 'l');
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'u');
    ASSERT_EQ(*dest_array++, 'l');
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, ' ');
    ASSERT_EQ(*dest_array++, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_empty_string)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_1_char)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "a";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_same_chars)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "aa";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_different_chars)
{
    char text[] = "";
    char* text_pointer = text;

    char end_string[] = "ab";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_1_char_and_end_string_is_matching_1_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "a";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_1_char_and_first_char_of_end_string_matches_1st_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "ab";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_1_char_and_second_char_of_end_string_matches_1st_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "ba";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_1_char_and_both_chars_of_end_string_match_1st_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "aa";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_1_char_and_end_string_is_different_1_char)
{
    char text[] = "a";
    char* text_pointer = text;

    char end_string[] = "b";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "a";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_and_2nd_char)
{
    char text[] = "aa";
    char* text_pointer = text;

    char end_string[] = "a";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_2nd_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "b";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_first_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "bc";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_second_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "cb";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_both_chars_of_end_string_are_same_as_2nd_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "bb";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_different_1_char)
{
    char text[] = "ab";
    char* text_pointer = text;

    char end_string[] = "c";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "a";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "b";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "c";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_a_different_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "d";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array++, 'c');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "ad";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "da";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "dea";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defa";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_1st_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defga";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "bd";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "db";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "deb";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defb";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_2nd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defgb";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "cd";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "dc";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "dec";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defc";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_3rd_char)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "defgc";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array, 0);
}

TEST(extract_string_with_several_endings_from_memory, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_an_empty_string)
{
    char text[] = "abc";
    char* text_pointer = text;

    char end_string[] = "";
    char* end_string_pointer = end_string;

    uint32_t array_size = 128;
    char* dest_array = new char[array_size];
    const char* orig_dest_array = dest_array;

    string::extract_string_with_several_endings(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
    ASSERT_EQ(dest_array, orig_dest_array);
    ASSERT_EQ(*dest_array++, 'a');
    ASSERT_EQ(*dest_array++, 'b');
    ASSERT_EQ(*dest_array++, 'c');
    ASSERT_EQ(*dest_array, 0);
}
