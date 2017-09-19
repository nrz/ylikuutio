#ifndef __TEXTURE_LOADER_HPP_INCLUDED
#define __TEXTURE_LOADER_HPP_INCLUDED

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <string>   // std::string

namespace loaders
{
    // Load a .BMP file using our custom loader
    GLuint load_BMP_texture(const std::string& filename);

    //// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
    //// or do it yourself (just like load_BMP_texture and load_DDS_texture)
    //// Load a .TGA file using GLFW's own loader
    //GLuint loadTGA_glfw(const char*  imagepath);

    // Load a .DDS file using GLFW's own loader
    GLuint load_DDS_texture(const std::string& filename);
}

#endif
