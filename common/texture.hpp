#ifndef TEXTURE_HPP
#define TEXTURE_HPP

namespace texture
{
    // Load a .BMP file using our custom loader
    GLuint load_BMP_texture(const char * imagepath);

    //// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
    //// or do it yourself (just like load_BMP_texture and loadDDS)
    //// Load a .TGA file using GLFW's own loader
    //GLuint loadTGA_glfw(const char * imagepath);

    // Load a .DDS file using GLFW's own loader
    GLuint loadDDS(const char * imagepath);
}

#endif
