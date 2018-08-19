#ifndef __SHADER_LOADER_HPP_INCLUDED
#define __SHADER_LOADER_HPP_INCLUDED

#include "shader_loader.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <algorithm> // std::find
#include <cstdio>    // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <fstream>   // std::ifstream
#include <ios>       // std::ios
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli
{
    namespace load
    {
        GLuint load_shaders(const char* const vertex_file_path, const char* const fragment_file_path)
        {
            // Create the shaders
            GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

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
                std::printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
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
            std::printf("Compiling shader : %s\n", vertex_file_path);
            char const *VertexSourcePointer = VertexShaderCode.c_str();
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
            std::printf("Compiling shader : %s\n", fragment_file_path);
            char const *FragmentSourcePointer = FragmentShaderCode.c_str();
            glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
            glCompileShader(FragmentShaderID);

            // Check Fragment Shader
            glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
            glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if (InfoLogLength > 0)
            {
                std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
                glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
                std::printf("%s\n", &FragmentShaderErrorMessage[0]);
            }

            // Link the program
            std::printf("Linking program\n");
            GLuint ProgramID = glCreateProgram();
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
                std::printf("%s\n", &ProgramErrorMessage[0]);
            }

            glDeleteShader(VertexShaderID);
            glDeleteShader(FragmentShaderID);

            return ProgramID;
        }
    }
}
#endif
