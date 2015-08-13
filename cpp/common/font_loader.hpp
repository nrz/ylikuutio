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
            std::vector<std::vector<glm::vec3>> &out_glyph_vertex_data);
}

#endif
