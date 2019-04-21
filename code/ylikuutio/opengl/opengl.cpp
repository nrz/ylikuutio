#include "opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include "SDL.h"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace opengl
    {
        bool init_glew()
        {
            if (glewInit() != GLEW_OK)
            {
                std::cerr << "Failed to initialize GLEW.\n";
                return false;
            }
            return true;
        }

        void enable_depth_test()
        {
            // Enable depth test.
            glEnable(GL_DEPTH_TEST);
        }

        void disable_depth_test()
        {
            // Disable depth test.
            glDisable(GL_DEPTH_TEST);
        }

        void set_depth_func_to_less()
        {
            // Accept a fragment if it closer to the camera than the former one.
            glDepthFunc(GL_LESS);
        }

        void cull_triangles()
        {
            // Cull triangles whose normal is not towards the camera.
            glEnable(GL_CULL_FACE);
        }

        void set_background_color(const float red, const float green, const float blue, const float alpha)
        {
            glClearColor(red, green, blue, alpha);
        }

        void set_filtering_parameters()
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void set_wireframe(const bool wireframe)
        {
            if (wireframe)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT, GL_FILL);
            }
        }

        std::size_t get_n_color_channels(const GLenum format)
        {
            switch (format)
            {
                case GL_COLOR_INDEX:
                    return 1;
                case GL_STENCIL_INDEX:
                    return 1;
                case GL_DEPTH_COMPONENT:
                    return 1;
                case GL_RED:
                    return 1;
                case GL_GREEN:
                    return 1;
                case GL_BLUE:
                    return 1;
                case GL_ALPHA:
                    return 1;
                case GL_RGB:
                    return 3;
                case GL_BGR:
                    return 3;
                case GL_RGBA:
                    return 3;
                case GL_BGRA:
                    return 3;
                case GL_LUMINANCE:
                    return 1;
                case GL_LUMINANCE_ALPHA:
                    return 2;
                default:
                    // Unknown or unsupported format.
                    return 0;
            }
        }

        std::size_t get_size_of_component(const GLenum type)
        {
            // https://www.khronos.org/opengl/wiki/OpenGL_Type

            switch (type)
            {
                case GL_BYTE:
                    return 1;
                case GL_UNSIGNED_BYTE:
                    return 1;
                case GL_SHORT:
                    return 2;
                case GL_UNSIGNED_SHORT:
                    return 2;
                case GL_INT:
                    return 4;
                case GL_UNSIGNED_INT:
                    return 4;
                case GL_FIXED:
                    return 4;
                case GL_HALF_FLOAT:
                    return 2;
                case GL_FLOAT:
                    return 4;
                case GL_DOUBLE:
                    return 8;
                default:
                    // Unknown or unsupported type.
                    return 0;
            }
        }
    }
}
