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
#include <string>   // std::string
#include <vector>   // std::vector

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
}
