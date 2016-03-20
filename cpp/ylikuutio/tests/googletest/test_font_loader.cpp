#include "gtest/gtest.h"
#include "cpp/ylikuutio/model/font_loader.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstring> // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <string>  // std::string
#include <vector>  // std::vector

TEST(font_must_be_loaded_appropriately, kongtext_svg)
{
    std::string font_filename = "kongtext.svg";

    std::vector<std::vector<glm::vec3>> glyph_vertex_data;
    std::vector<std::vector<glm::vec2>> glyph_UV_data;
    std::vector<std::vector<glm::vec3>> glyph_normal_data;
    std::vector<std::string> glyph_names;
    std::vector<std::string> unicode_strings;
    GLfloat vertex_scaling_factor = 1.0f;

    bool font_loading_result = model::load_SVG_font(
            font_filename,
            glyph_vertex_data,
            glyph_UV_data,
            glyph_normal_data,
            glyph_names,
            unicode_strings,
            vertex_scaling_factor);
    ASSERT_EQ(glyph_names.size(), 217);
    ASSERT_EQ(glyph_vertex_data.size(), 217);
    ASSERT_EQ(std::strcmp(glyph_names.at(0).c_str(), "nonmarkingreturn"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(1).c_str(), "space"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(2).c_str(), "exclam"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(3).c_str(), "quotedbl"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(4).c_str(), "numbersign"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(5).c_str(), "dollar"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(6).c_str(), "percent"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(7).c_str(), "ampersand"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(8).c_str(), "quotesingle"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(9).c_str(), "parenleft"), 0);

    ASSERT_EQ(std::strcmp(glyph_names.at(207).c_str(), "quotedblbase"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(208).c_str(), "dagger"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(209).c_str(), "daggerdbl"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(210).c_str(), "bullet"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(211).c_str(), "ellipsis"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(212).c_str(), "perthousand"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(213).c_str(), "guilsinglleft"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(214).c_str(), "guilsinglright"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(215).c_str(), "Euro"), 0);
    ASSERT_EQ(std::strcmp(glyph_names.at(216).c_str(), "trademark"), 0);
}
