// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_OPENGL_OPENGL_HPP_INCLUDED
#define __YLIKUUTIO_OPENGL_OPENGL_HPP_INCLUDED

#include "code/ylikuutio/memory/memory_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include "SDL.h"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::opengl
{
    bool init_glew();
    void enable_depth_test();
    void disable_depth_test();
    void set_depth_func_to_less();
    void cull_triangles();
    void set_background_color(const float red, const float green, const float blue, const float alpha);
    void set_filtering_parameters();
    void set_nearest_filtering_parameters();
    void set_wireframe(const bool wireframe);
    bool uniform_1i(const GLint location, const GLint v0);
    bool enable_vertex_attrib_array(const GLint attribute);
    bool disable_vertex_attrib_array(const GLint attribute);
    std::size_t get_n_color_channels(const GLenum format);
    std::size_t get_size_of_component(const GLenum type);

    template<class T1>
        std::shared_ptr<std::vector<T1>> copy_data_from_gpu_texture_to_cpu_array(
                const GLenum format,
                const GLenum type,
                const std::size_t texture_width,
                const std::size_t texture_height,
                const std::size_t texture_depth,
                const bool should_ylikuutio_flip_texture)
        {
            // Transfer data from the GPU texture to a CPU array.
            const std::size_t n_color_channels = yli::opengl::get_n_color_channels(format);
            const std::size_t n_texels = texture_width * texture_height * texture_depth;
            const std::size_t size_of_texture = n_color_channels * n_texels;
            T1* const result_array = new T1[size_of_texture];

            glReadBuffer(GL_COLOR_ATTACHMENT0);
            glReadPixels(0, 0, texture_width, texture_height, format, type, result_array);

            if (should_ylikuutio_flip_texture)
            {
                yli::memory::flip_vertically(result_array, n_color_channels * texture_width, texture_height);
            }

            std::shared_ptr<std::vector<T1>> result_vector = std::make_shared<std::vector<T1>>(result_array, result_array + size_of_texture);

            delete[] result_array;

            return result_vector;
        }

        void save_data_from_gpu_texture_into_file(
                const GLenum format,
                const GLenum type,
                const std::size_t texture_width,
                const std::size_t texture_height,
                const std::size_t texture_depth,
                const std::string& filename,
                const bool should_ylikuutio_flip_texture);

        void save_data_from_gpu_texture_into_file(
                const GLenum format,
                const GLenum type,
                const std::size_t texture_width,
                const std::size_t texture_height,
                const std::string& filename,
                const bool should_ylikuutio_flip_texture);

        GLenum get_base_format(const GLenum format);
}

#endif
