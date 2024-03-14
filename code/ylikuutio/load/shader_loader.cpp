// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_LOAD_SHADER_LOADER_CPP_INCLUDED
#define __YLIKUUTIO_LOAD_SHADER_LOADER_CPP_INCLUDED

#include "shader_loader.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::load
{
    GLuint load_shaders(const char* const vertex_shader_filename, const char* const fragment_shader_filename)
    {
        // Read the vertex shader code from the file.
        const std::optional<std::string> vertex_shader_code = yli::file::slurp(vertex_shader_filename);

        if (!vertex_shader_code)
        {
            std::cerr << "ERROR: `yli::load::load_shaders`: vertex shader file " << vertex_shader_filename << " not loaded successfully!\n";
            return false;
        }

        if (vertex_shader_code->empty())
        {
            std::cerr << "ERROR: `yli::load::load_shaders`: vertex shader file " << vertex_shader_filename << " is empty!\n";
            return false;
        }

        // Read the fragment shader code from the file.
        const std::optional<std::string> fragment_shader_code = yli::file::slurp(fragment_shader_filename);

        if (!fragment_shader_code)
        {
            std::cerr << "ERROR: `yli::load::load_shaders`: fragment shader file " << fragment_shader_filename << " not loaded successfully!\n";
            return false;
        }

        if (fragment_shader_code->empty())
        {
            std::cerr << "ERROR: `yli::load::load_shaders`: fragment shader file " << fragment_shader_filename << " is empty!\n";
            return false;
        }

        // Create the shaders.
        const uint32_t vertex_shaderID = glCreateShader(GL_VERTEX_SHADER);
        const uint32_t fragment_shaderID = glCreateShader(GL_FRAGMENT_SHADER);

        GLint result = GL_FALSE;
        int info_log_length;

        // Compile vertex shader.
        std::cout << "Compiling vertex shader: " << vertex_shader_filename << "\n";
        const char* const vertex_source_pointer = vertex_shader_code->c_str();
        glShaderSource(vertex_shaderID, 1, &vertex_source_pointer, nullptr);
        glCompileShader(vertex_shaderID);

        // Check vertex shader.
        glGetShaderiv(vertex_shaderID, GL_COMPILE_STATUS, &result);
        glGetShaderiv(vertex_shaderID, GL_INFO_LOG_LENGTH, &info_log_length);

        if (info_log_length > 0)
        {
            std::vector<char> vertex_shader_error_message(info_log_length + 1);
            glGetShaderInfoLog(vertex_shaderID, info_log_length, nullptr, &vertex_shader_error_message[0]);
            const std::string error_string(vertex_shader_error_message.begin(), vertex_shader_error_message.end());
            std::cerr << error_string << "\n";
        }

        // Compile fragment shader.
        std::cout << "Compiling fragment shader: " << fragment_shader_filename << "\n";
        const char* const fragment_source_pointer = fragment_shader_code->c_str();
        glShaderSource(fragment_shaderID, 1, &fragment_source_pointer, nullptr);
        glCompileShader(fragment_shaderID);

        // Check fragment shader.
        glGetShaderiv(fragment_shaderID, GL_COMPILE_STATUS, &result);
        glGetShaderiv(fragment_shaderID, GL_INFO_LOG_LENGTH, &info_log_length);

        if (info_log_length > 0)
        {
            std::vector<char> fragment_shader_error_message(info_log_length + 1);
            glGetShaderInfoLog(fragment_shaderID, info_log_length, nullptr, &fragment_shader_error_message[0]);
            const std::string error_string(fragment_shader_error_message.begin(), fragment_shader_error_message.end());
            std::cerr << error_string << "\n";
        }

        // Link the program.
        std::cout << "Linking program\n";
        const GLuint program_id = glCreateProgram();
        glAttachShader(program_id, vertex_shaderID);
        glAttachShader(program_id, fragment_shaderID);
        glLinkProgram(program_id);

        // Check the program.
        glGetProgramiv(program_id, GL_LINK_STATUS, &result);
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

        if (info_log_length > 0)
        {
            std::vector<char> program_error_message(info_log_length + 1);
            glGetProgramInfoLog(program_id, info_log_length, nullptr, &program_error_message[0]);
            const std::string error_string(program_error_message.begin(), program_error_message.end());
            std::cerr << error_string << "\n";
        }

        glDeleteShader(vertex_shaderID);
        glDeleteShader(fragment_shaderID);

        return program_id;
    }
}
#endif
