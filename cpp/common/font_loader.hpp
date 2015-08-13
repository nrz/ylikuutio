#ifndef __FONT_LOADER_HPP_INCLUDED
#define __FONT_LOADER_HPP_INCLUDED

// Include standard headers
#include <string>
#include <vector>   // std::vector

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

namespace model
{
    bool load_SVG_font(std::string font_file_path,
            std::vector<std::vector<glm::vec3>> &out_glyph_vertex_data,
            std::vector<std::vector<glm::vec2>> &out_glyph_UV_data,
            std::vector<std::vector<glm::vec3>> &out_glyph_normal_data,
            std::vector<std::string> &glyph_names,
            std::vector<std::string> &unicode_strings,
            GLfloat vertex_scaling_factor);
}

#endif
