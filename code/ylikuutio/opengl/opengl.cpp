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

#include "opengl.hpp"
#include "code/ylikuutio/file/file_writer.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include "SDL.h"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

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

        void set_nearest_filtering_parameters()
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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

        bool uniform_1i(const GLint location, const GLint v0)
        {
            if (location == -1)
            {
                return false;
            }

            glUniform1i(location, v0);

            return true;
        }

        bool enable_vertex_attrib_array(const GLint attribute)
        {
            if (attribute == -1)
            {
                return false;
            }

            glEnableVertexAttribArray(attribute);

            return true;
        }

        bool disable_vertex_attrib_array(const GLint attribute)
        {
            if (attribute == -1)
            {
                return false;
            }

            glDisableVertexAttribArray(attribute);

            return true;
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
                case GL_DEPTH_STENCIL:
                    return 2;
                case GL_RED:
                    return 1;
                case GL_RED_INTEGER:
                    return 1;
                case GL_GREEN:
                    return 1;
                case GL_BLUE:
                    return 1;
                case GL_RG:
                    return 2;
                case GL_RG_INTEGER:
                    return 2;
                case GL_ALPHA:
                    return 1;
                case GL_RGB:
                    return 3;
                case GL_RGB_INTEGER:
                    return 3;
                case GL_BGR:
                    return 3;
                case GL_BGR_INTEGER:
                    return 3;
                case GL_RGBA:
                    return 4;
                case GL_RGBA_INTEGER:
                    return 4;
                case GL_BGRA:
                    return 4;
                case GL_BGRA_INTEGER:
                    return 4;
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

        void save_data_from_gpu_texture_into_file(
                const GLenum format,
                const GLenum type,
                const std::size_t texture_width,
                const std::size_t texture_height,
                const std::size_t texture_depth,
                const std::string& filename,
                const bool should_ylikuutio_flip_texture)
        {
            if (filename.empty())
            {
                return;
            }

            if (type == GL_BYTE)
            {
                std::shared_ptr<std::vector<int8_t>> data_vector_shared_ptr = yli::opengl::copy_data_from_gpu_texture_to_cpu_array<int8_t>(
                        yli::opengl::get_base_format(format),
                        type,
                        texture_width,
                        texture_height,
                        texture_depth,
                        should_ylikuutio_flip_texture);
                yli::file::binary_write(*data_vector_shared_ptr, filename);
            }
            else if (type == GL_UNSIGNED_BYTE)
            {
                std::shared_ptr<std::vector<uint8_t>> data_vector_shared_ptr = yli::opengl::copy_data_from_gpu_texture_to_cpu_array<uint8_t>(
                        yli::opengl::get_base_format(format),
                        type,
                        texture_width,
                        texture_height,
                        texture_depth,
                        should_ylikuutio_flip_texture);
                yli::file::binary_write(*data_vector_shared_ptr, filename);
            }
            else if (type == GL_SHORT)
            {
                std::shared_ptr<std::vector<int16_t>> data_vector_shared_ptr = yli::opengl::copy_data_from_gpu_texture_to_cpu_array<int16_t>(
                        yli::opengl::get_base_format(format),
                        type,
                        texture_width,
                        texture_height,
                        texture_depth,
                        should_ylikuutio_flip_texture);
                yli::file::binary_write(*data_vector_shared_ptr, filename);
            }
            else if (type == GL_UNSIGNED_SHORT)
            {
                std::shared_ptr<std::vector<uint16_t>> data_vector_shared_ptr = yli::opengl::copy_data_from_gpu_texture_to_cpu_array<uint16_t>(
                        yli::opengl::get_base_format(format),
                        type,
                        texture_width,
                        texture_height,
                        texture_depth,
                        should_ylikuutio_flip_texture);
                yli::file::binary_write(*data_vector_shared_ptr, filename);
            }
            else if (type == GL_INT)
            {
                std::shared_ptr<std::vector<int32_t>> data_vector_shared_ptr = yli::opengl::copy_data_from_gpu_texture_to_cpu_array<int32_t>(
                        yli::opengl::get_base_format(format),
                        type,
                        texture_width,
                        texture_height,
                        texture_depth,
                        should_ylikuutio_flip_texture);
                yli::file::binary_write(*data_vector_shared_ptr, filename);
            }
            else if (type == GL_UNSIGNED_INT)
            {
                std::shared_ptr<std::vector<uint32_t>> data_vector_shared_ptr = yli::opengl::copy_data_from_gpu_texture_to_cpu_array<uint32_t>(
                        yli::opengl::get_base_format(format),
                        type,
                        texture_width,
                        texture_height,
                        texture_depth,
                        should_ylikuutio_flip_texture);
                yli::file::binary_write(*data_vector_shared_ptr, filename);
            }
            else if (type == GL_FIXED)
            {
                // TODO: add support for `GL_FIXED`!
                std::cerr << "ERROR: `yli::opengl::save_data_from_gpu_texture_into_file`: type `GL_FIXED` is not supported yet!\n";
            }
            else if (type == GL_HALF_FLOAT)
            {
                // TODO: add support for `GL_HALF_FLOAT`!
                std::cerr << "ERROR: `yli::opengl::save_data_from_gpu_texture_into_file`: type `GL_HALF_FLOAT` is not supported yet!\n";
            }
            else if (type == GL_FLOAT)
            {
                std::shared_ptr<std::vector<float>> data_vector_shared_ptr = yli::opengl::copy_data_from_gpu_texture_to_cpu_array<float>(
                        yli::opengl::get_base_format(format),
                        type,
                        texture_width,
                        texture_height,
                        texture_depth,
                        should_ylikuutio_flip_texture);
                yli::file::binary_write(*data_vector_shared_ptr, filename);
            }
            else if (type == GL_DOUBLE)
            {
                std::shared_ptr<std::vector<double>> data_vector_shared_ptr = yli::opengl::copy_data_from_gpu_texture_to_cpu_array<double>(
                        yli::opengl::get_base_format(format),
                        type,
                        texture_width,
                        texture_height,
                        texture_depth,
                        should_ylikuutio_flip_texture);
                yli::file::binary_write(*data_vector_shared_ptr, filename);
            }
            else
            {
                std::cerr << "ERROR: `yli::opengl::save_data_from_gpu_texture_into_file`: unknown or unsupported type: " << type << "\n";
            }

            // Unknown or unsupported type.
            return;
        }

        void save_data_from_gpu_texture_into_file(
                const GLenum format,
                const GLenum type,
                const std::size_t texture_width,
                const std::size_t texture_height,
                const std::string& filename,
                const bool should_ylikuutio_flip_texture)
        {
            const std::size_t texture_depth = 1;
            yli::opengl::save_data_from_gpu_texture_into_file(
                format,
                type,
                texture_width,
                texture_height,
                texture_depth,
                filename,
                should_ylikuutio_flip_texture);
        }

        GLenum get_base_format(const GLenum format)
        {
            switch (format)
            {
                case GL_RED_INTEGER:
                    return GL_RED;
                case GL_RG_INTEGER:
                    return GL_RG;
                case GL_RGB_INTEGER:
                    return GL_RGB;
                case GL_BGR_INTEGER:
                    return GL_BGR;
                case GL_RGBA_INTEGER:
                    return GL_RGBA;
                case GL_BGRA_INTEGER:
                    return GL_BGRA;
                default:
                    return format;
            }
        }
    }
}
