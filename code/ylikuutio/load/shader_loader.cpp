// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __SHADER_LOADER_HPP_INCLUDED
#define __SHADER_LOADER_HPP_INCLUDED

#include "shader_loader.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <algorithm> // std::find
#include <fstream>   // std::ifstream
#include <ios>       // std::ios
#include <iostream>  // std::cout, std::cin, std::cerr
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli
{
    namespace load
    {
        uint32_t load_shaders(const char* const vertex_file_path, const char* const fragment_file_path)
        {
            // Create the shaders
            const uint32_t VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            const uint32_t FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

            // Read the Vertex Shader code from the file
            std::string VertexShaderCode;
            std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
            if (VertexShaderStream.is_open())
            {
                std::string Line = "";
                while (getline(VertexShaderStream, Line))
                {
                    VertexShaderCode += "\n" + Line;
                }
                VertexShaderStream.close();
            }
            else
            {
                std::cerr << "ERROR: `yli::load::load_shaders`: opening file " << vertex_file_path << " failed.\n";
                return 0;
            }

            // Read the Fragment Shader code from the file
            std::string FragmentShaderCode;
            std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
            if (FragmentShaderStream.is_open())
            {
                std::string Line = "";
                while(getline(FragmentShaderStream, Line))
                {
                    FragmentShaderCode += "\n" + Line;
                }
                FragmentShaderStream.close();
            }

            GLint Result = GL_FALSE;
            int InfoLogLength;

            // Compile Vertex Shader
            std::cout << "Compling vertex shader: " << vertex_file_path << "\n";
            const char* const VertexSourcePointer = VertexShaderCode.c_str();
            glShaderSource(VertexShaderID, 1, &VertexSourcePointer , nullptr);
            glCompileShader(VertexShaderID);

            // Check Vertex Shader
            glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
            glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0)
            {
                std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
                glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
                std::printf("%s\n", &VertexShaderErrorMessage[0]);
            }

            // Compile Fragment Shader
            std::cout << "Compling fragment shader: " << fragment_file_path << "\n";
            const char* const FragmentSourcePointer = FragmentShaderCode.c_str();
            glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
            glCompileShader(FragmentShaderID);

            // Check Fragment Shader
            glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
            glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0)
            {
                std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
                glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
                std::string error_string(FragmentShaderErrorMessage.begin(), FragmentShaderErrorMessage.end());
                std::cerr << error_string << "\n";
            }

            // Link the program
            std::cout << "Linking program\n";
            const uint32_t ProgramID = glCreateProgram();
            glAttachShader(ProgramID, VertexShaderID);
            glAttachShader(ProgramID, FragmentShaderID);
            glLinkProgram(ProgramID);

            // Check the program
            glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
            glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0)
            {
                std::vector<char> ProgramErrorMessage(InfoLogLength+1);
                glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
                std::string error_string(ProgramErrorMessage.begin(), ProgramErrorMessage.end());
                std::cerr << error_string << "\n";
            }

            glDeleteShader(VertexShaderID);
            glDeleteShader(FragmentShaderID);

            return ProgramID;
        }
    }
}
#endif
