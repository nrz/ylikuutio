// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "gtest/gtest.h"
#include "code/ylikuutio/load/font_loader.hpp"
#include "code/ylikuutio/file/file_loader.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

TEST(glyphs_must_be_found_appropriately, kongtext_svg)
{
    const std::string font_filename = "kongtext.svg";

    std::optional<std::string> file_content = yli::file::slurp(font_filename);
    const uint64_t file_size = file_content->size();

    const char* const svg_base_pointer { &(*file_content)[0] };
    const char* svg_data_pointer       { &(*file_content)[0] };

    // SVG files are XML files, so we just need to read until we find the data we need.
    const bool is_first_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_first_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x2e0);
    svg_data_pointer++;

    const bool is_second_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_second_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x320);
    svg_data_pointer++;

    const bool is_third_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_third_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x353);
    svg_data_pointer++;

    const bool is_fourth_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_fourth_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x386);
    svg_data_pointer++;

    const bool is_fifth_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_fifth_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x3b4);
    svg_data_pointer++;

    const bool is_sixth_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_sixth_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x3f2);
    svg_data_pointer++;

    const bool is_seventh_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_seventh_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x421);
    svg_data_pointer++;

    const bool is_eigth_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_eigth_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x48b);
    svg_data_pointer++;

    const bool is_ninth_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_ninth_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x4fc);
    svg_data_pointer++;

    const bool is_tenth_glyph_found = yli::load::find_first_glyph_in_svg(svg_base_pointer, svg_data_pointer, file_size);
    ASSERT_TRUE(is_tenth_glyph_found);
    ASSERT_EQ(svg_data_pointer, svg_base_pointer + 0x5d6);
}

TEST(font_must_be_loaded_appropriately, kongtext_svg)
{
    const std::string font_filename = "kongtext.svg";

    std::vector<std::vector<std::vector<glm::vec2>>> glyph_vertex_data;
    std::vector<std::string> glyph_names;
    std::vector<std::string> unicode_strings;

    const bool is_debug_mode = false; // Travis fails for too much output.

    ASSERT_TRUE(yli::load::load_svg_font(
                font_filename,
                glyph_vertex_data,
                glyph_names,
                unicode_strings,
                is_debug_mode));

    ASSERT_EQ(glyph_names.size(), 217);
    ASSERT_EQ(glyph_vertex_data.size(), 217);
    ASSERT_EQ(unicode_strings.size(), 217);

    ASSERT_EQ(std::strcmp(glyph_names.at(0).c_str(), "nonmarkingreturn"), 0);
    ASSERT_EQ(glyph_vertex_data.at(0).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(1).c_str(), "space"), 0);
    ASSERT_EQ(glyph_vertex_data.at(1).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(3).c_str(), "quotedbl"), 0);
    ASSERT_EQ(glyph_vertex_data.at(3).size(), 2);        // 2 edge sections. d="M256 768h128v-384h-128v384zM640 768h128v-384h-128v384z"
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).size(), 5);  // d="M256 768h128v-384h-128v384z
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(0).x, 256);
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(0).y, 768);
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(1).x, 384); // h128
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(1).y, 768);
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(2).x, 384);
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(2).y, 384); // v-384
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(3).x, 256); // h-128
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(3).y, 384);
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(4).x, 256);
    ASSERT_EQ(glyph_vertex_data.at(3).at(0).at(4).y, 768); // v384
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).size(), 5);  // M640 768h128v-384h-128v384z"
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(0).x, 640);
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(0).y, 768);
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(1).x, 768); // h128
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(1).y, 768);
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(2).x, 768);
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(2).y, 384); // v-384
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(3).x, 640); // h-128
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(3).y, 384);
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(4).x, 640);
    ASSERT_EQ(glyph_vertex_data.at(3).at(1).at(4).y, 768); // v384

    ASSERT_EQ(std::strcmp(glyph_names.at(4).c_str(), "numbersign"), 0);
    ASSERT_EQ(glyph_vertex_data.at(4).size(), 2);        // 2 edge sections. d="M256 768h128v-128h256v128h128v-128h128v-128h-128v-128h128v-128h-128v-128h-128v128h-256v-128h-128v128h-128v128h128v128h-128v128h128v128zM384 512v-128h256v128h-256z"
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).size(), 29); // d="M256 768h128v-128h256v128h128v-128h128v-128h-128v-128h128v-128h-128v-128h-128v128h-256v-128h-128v128h-128v128h128v128h-128v128h128v128z
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(0).x, 256);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(0).y, 768);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(1).x, 384); // h128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(1).y, 768);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(2).x, 384);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(2).y, 640); // v-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(3).x, 640); // h256
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(3).y, 640);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(4).x, 640);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(4).y, 768); // v128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(5).x, 768); // h128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(5).y, 768);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(6).x, 768);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(6).y, 640); // v-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(7).x, 896); // h128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(7).y, 640);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(8).x, 896);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(8).y, 512); // v-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(9).x, 768); // h-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(9).y, 512);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(10).x, 768);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(10).y, 384); // v-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(11).x, 896); // h128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(11).y, 384);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(12).x, 896);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(12).y, 256); // v-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(13).x, 768); // h-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(13).y, 256);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(14).x, 768);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(14).y, 128); // v-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(15).x, 640); // h-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(15).y, 128);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(16).x, 640);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(16).y, 256); // v128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(17).x, 384); // h-256
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(17).y, 256);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(18).x, 384);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(18).y, 128); // v-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(19).x, 256); // h-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(19).y, 128);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(20).x, 256);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(20).y, 256); // v128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(21).x, 128); // h-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(21).y, 256);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(22).x, 128);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(22).y, 384); // v128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(23).x, 256); // h128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(23).y, 384);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(24).x, 256);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(24).y, 512); // v128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(25).x, 128); // h-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(25).y, 512);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(26).x, 128);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(26).y, 640); // v128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(27).x, 256); // h128
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(27).y, 640);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(28).x, 256);
    ASSERT_EQ(glyph_vertex_data.at(4).at(0).at(28).y, 768); // v128
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).size(), 5);  // M384 512v-128h256v128h-256z"
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(0).x, 384);
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(0).y, 512);
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(1).x, 384);
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(1).y, 384); // v-128
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(2).x, 640); // h256
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(2).y, 384);
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(3).x, 640);
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(3).y, 512); // v128
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(4).x, 384); // h-256
    ASSERT_EQ(glyph_vertex_data.at(4).at(1).at(4).y, 512);

    ASSERT_EQ(std::strcmp(glyph_names.at(5).c_str(), "dollar"), 0);
    ASSERT_EQ(glyph_vertex_data.at(5).size(), 1);        // complex polygon!
    ASSERT_EQ(glyph_vertex_data.at(5).at(0).size(), 29); // complex polygon!

    ASSERT_EQ(std::strcmp(glyph_names.at(6).c_str(), "percent"), 0);
    ASSERT_EQ(glyph_vertex_data.at(6).size(), 3);        // 3 edge sections. d="M128 896h256v-256h-256v256zM768 896h128v-256h-128v-128h-128v-128h-128v-128h-128v-128h-128v-128h-256v128h128v128h128v128h128v128h128v128h128v128h128v128zM640 256h256v-256h-256v256z"
    ASSERT_EQ(glyph_vertex_data.at(6).at(0).size(), 5);  // d="M128 896h256v-256h-256v256z
    ASSERT_EQ(glyph_vertex_data.at(6).at(1).size(), 27); // M768 896h128v-256h-128v-128h-128v-128h-128v-128h-128v-128h-128v-128h-256v128h128v128h128v128h128v128h128v128h128v128h128v128z
    ASSERT_EQ(glyph_vertex_data.at(6).at(2).size(), 5);  // M640 256h256v-256h-256v256z"

    ASSERT_EQ(std::strcmp(glyph_names.at(7).c_str(), "ampersand"), 0);
    ASSERT_EQ(glyph_vertex_data.at(7).size(), 4); // 3 edge sections. d="M256 768h384v-128h128v-128h256v-128h-128v-256h128v-128h-256v128h-128v-128h-512v128h-128v128h128v128h128v128h-128v128h128v128zM384 640v-128h128v128h-128zM640 512v-128h128v128h-128zM384 384v-128h-128v-128h384v128h-128v128h-128z"
    ASSERT_EQ(glyph_vertex_data.at(7).at(0).size(), 27); // d="M256 768h384v-128h128v-128h256v-128h-128v-256h128v-128h-256v128h-128v-128h-512v128h-128v128h128v128h128v128h-128v128h128v128z
    ASSERT_EQ(glyph_vertex_data.at(7).at(1).size(), 5);  // M384 640v-128h128v128h-128z
    ASSERT_EQ(glyph_vertex_data.at(7).at(2).size(), 5);  // M640 512v-128h128v128h-128z
    ASSERT_EQ(glyph_vertex_data.at(7).at(3).size(), 9);  // M384 384v-128h-128v-128h384v128h-128v128h-128z"

    ASSERT_EQ(std::strcmp(glyph_names.at(8).c_str(), "quotesingle"), 0);
    ASSERT_EQ(glyph_vertex_data.at(8).size(), 1);
    ASSERT_EQ(glyph_vertex_data.at(8).at(0).size(), 9);

    ASSERT_EQ(std::strcmp(glyph_names.at(9).c_str(), "parenleft"), 0);
    ASSERT_EQ(glyph_vertex_data.at(9).size(), 1);
    ASSERT_EQ(glyph_vertex_data.at(9).at(0).size(), 13);

    ASSERT_EQ(std::strcmp(glyph_names.at(207).c_str(), "quotedblbase"), 0);
    ASSERT_EQ(glyph_vertex_data.at(207).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(208).c_str(), "dagger"), 0);
    ASSERT_EQ(glyph_vertex_data.at(208).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(209).c_str(), "daggerdbl"), 0);
    ASSERT_EQ(glyph_vertex_data.at(209).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(210).c_str(), "bullet"), 0);
    ASSERT_EQ(glyph_vertex_data.at(210).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(211).c_str(), "ellipsis"), 0);
    ASSERT_EQ(glyph_vertex_data.at(211).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(212).c_str(), "perthousand"), 0);
    ASSERT_EQ(glyph_vertex_data.at(212).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(213).c_str(), "guilsinglleft"), 0);
    ASSERT_EQ(glyph_vertex_data.at(213).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(214).c_str(), "guilsinglright"), 0);
    ASSERT_EQ(glyph_vertex_data.at(214).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(215).c_str(), "Euro"), 0);
    ASSERT_EQ(glyph_vertex_data.at(215).size(), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(216).c_str(), "trademark"), 0);
    ASSERT_EQ(glyph_vertex_data.at(216).size(), 2);        // 2 edge sections. d="M0 896h384v-128h-128v-256h-128v256h-128v128zM384 640h640v-384h-128v256h-128v-128h-128v128h-128v-256h-128v384z"
    ASSERT_EQ(glyph_vertex_data.at(216).at(0).size(), 9);  // d="M0 896h384v-128h-128v-256h-128v256h-128v128z
    ASSERT_EQ(glyph_vertex_data.at(216).at(1).size(), 13); // M384 640h640v-384h-128v256h-128v-128h-128v128h-128v-256h-128v384z"
}
