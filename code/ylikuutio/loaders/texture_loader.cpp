#include "texture_loader.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <stdlib.h> // free, malloc

namespace loaders
{
    GLuint load_BMP_texture(const char* imagepath)
    {
        // TODO: change imagepath to std::string
        std::printf("Reading image %s\n", imagepath);

        // Data read from the header of the BMP file
        uint8_t header[54];
        uint32_t dataPos;
        uint32_t imageSize;
        uint32_t width, height;
        // Actual RGB data
        uint8_t* data;

        // Open the file
        std::FILE* file = std::fopen(imagepath,"rb");
        if (!file)
        {
            // TODO: change std::printf to std::cerr (after changing imagepath to std::string).
            std::printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
            return 0;
        }

        // Read the header, i.e. the 54 first bytes

        // If less than 54 bytes are read, problem
        // TODO: move hardcoded value 54 to variable.
        if (std::fread(header, 1, 54, file) != 54)
        {
            std::printf("Not a correct BMP file\n");
            return 0;
        }

        // A BMP files always begins with "BM"
        if ((header[0] != 'B') || (header[1] != 'M'))
        {
            std::printf("Not a correct BMP file\n");
            return 0;
        }

        // Make sure this is a 24bpp file
        if (*(int*) &header[0x1e] != 0)
        {
            std::printf("Not a correct BMP file\n");
            return 0;
        }

        if (*(int*) &header[0x1c] != 24)
        {
            std::printf("Not a correct BMP file\n");
            return 0;
        }

        // Read the information about the image
        dataPos    = *(int*) &header[0x0a];
        imageSize  = *(int*) &header[0x22];
        width      = *(int*) &header[0x12];
        height     = *(int*) &header[0x16];

        // Some BMP files are misformatted, guess missing information
        if (imageSize == 0)
        {
            imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
        }

        if (dataPos == 0)
        {
            dataPos = 54; // The BMP header is done that way
        }

        // Create a buffer
        data = new uint8_t [imageSize];

        if (data == nullptr)
        {
            std::cerr << "Reserving memory for texture data failed.\n";
            std::fclose(file);
            return 0;
        }

        // Read the actual data from the file into the buffer
        // TODO: add check for file reading!
        // TODO: rename imageSize to image_size
        std::fread(data, 1, imageSize, file);

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        // Create one OpenGL texture
        GLuint textureID;
        glGenTextures(1, &textureID);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Give the image to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

        // OpenGL has now copied the data. Free our own version
        delete[] data;

        // Poor filtering, or ...
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

#define CLAMP_TEXTURES
        // #define REPEAT_TEXTURES

#ifdef CLAMP_TEXTURES
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

#ifdef REPEAT_TEXTURES
        // ... nice trilinear filtering.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
#endif

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Return the ID of the texture we just created
        return textureID;
    }

    // Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library,
    // or do it yourself (just like load_BMP_texture and load_DDS_texture)
    //GLuint loadTGA_glfw(const char*  imagepath){
    //
    //    // Create one OpenGL texture
    //    GLuint textureID;
    //    glGenTextures(1, &textureID);
    //
    //    // "Bind" the newly created texture : all future texture functions will modify this texture
    //    glBindTexture(GL_TEXTURE_2D, textureID);
    //
    //    // Read the file, call glTexImage2D with the right parameters
    //    glfwLoadTexture2D(imagepath, 0);
    //
    //    // Nice trilinear filtering.
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //
    //    // Return the ID of the texture we just created
    //    return textureID;
    //}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

    GLuint load_DDS_texture(const char* imagepath)
    {
        uint8_t header[124];
        std::FILE* fp;

        /* try to open the file */
        fp = std::fopen(imagepath, "rb");
        if (fp == nullptr)
        {
            std::printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
            return 0;
        }

        /* verify the type of file */
        char filecode[4];
        // TODO: add check for file reading!
        // TODO: store hardcoded value 4 into a variable.
        std::fread(filecode, 1, 4, fp);
        if (std::strncmp(filecode, "DDS ", 4) != 0)
        {
            std::fclose(fp);
            return 0;
        }

        /* get the surface desc */
        // TODO: add check for file reading!
        // TODO: store hardcoded value 4 into a variable.
        std::fread(&header, 124, 1, fp);

        uint32_t height      = *(uint32_t*) &header[8];
        uint32_t width       = *(uint32_t*) &header[12];
        uint32_t linearSize  = *(uint32_t*) &header[16];
        uint32_t mipMapCount = *(uint32_t*) &header[24];
        uint32_t fourCC      = *(uint32_t*) &header[80];

        uint8_t* buffer;
        uint32_t bufsize;
        /* how big is it going to be including all mipmaps? */
        bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
        buffer = (uint8_t*) malloc(bufsize * sizeof(uint8_t));

        // TODO: add check for file reading!
        // TODO: store hardcoded value 4 into a variable.
        std::fread(buffer, 1, bufsize, fp);
        /* close the file pointer */
        std::fclose(fp);

        uint32_t components = (fourCC == FOURCC_DXT1) ? 3 : 4;
        uint32_t format;
        switch(fourCC)
        {
            case FOURCC_DXT1:
                format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                break;
            case FOURCC_DXT3:
                format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                break;
            case FOURCC_DXT5:
                format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                break;
            default:
                free(buffer);
                return 0;
        }

        // Create one OpenGL texture
        GLuint textureID;
        glGenTextures(1, &textureID);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        uint32_t blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
        uint32_t offset = 0;

        /* load the mipmaps */
        for (uint32_t level = 0; level < mipMapCount && (width || height); ++level)
        {
            uint32_t size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
            glCompressedTexImage2D(
                    GL_TEXTURE_2D,
                    level,
                    format,
                    width,
                    height,
                    0,
                    size,
                    buffer + offset);

            offset += size;
            width  /= 2;
            height /= 2;

            // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
            if (width < 1)
            {
                width = 1;
            }
            if (height < 1)
            {
                height = 1;
            }
        }
        free(buffer);

        return textureID;
    }
}
