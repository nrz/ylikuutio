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

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
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

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
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

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
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

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
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

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
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

    string::extract_string(text, text_pointer, sizeof(text), dest_array, dest_array, array_size, end_string);
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
