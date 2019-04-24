#ifndef __OPENGL_HPP_INCLUDED
#define __OPENGL_HPP_INCLUDED

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include "SDL.h"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
    namespace opengl
    {
        bool init_glew();
        void enable_depth_test();
        void disable_depth_test();
        void set_depth_func_to_less();
        void cull_triangles();
        void set_background_color(const float red, const float green, const float blue, const float alpha);
        void set_filtering_parameters();
        void set_wireframe(const bool wireframe);
        std::size_t get_n_color_channels(const GLenum format);
        std::size_t get_size_of_component(const GLenum type);

        std::shared_ptr<std::vector<uint8_t>> copy_data_from_gpu_texture_to_cpu_array(
                GLenum format,
                GLenum type,
                std::size_t texture_width,
                std::size_t texture_height);
    }
}

#endif
