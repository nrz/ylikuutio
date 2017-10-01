#define LINE_HEADER_SIZE 4096

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

#include "obj_loader.hpp"

// Include standard headers
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

void read_until_newline(std::FILE* file)
{
    while (getc(file) != '\n');
}

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide :
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

namespace loaders
{
    bool load_OBJ(
            const char* path,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals)
    {
        std::cout << "Loading OBJ file " << path << " ...\n";

        std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_UVs;
        std::vector<glm::vec3> temp_normals;

        std::FILE* file = std::fopen(path, "r");

        if (file == nullptr)
        {
            std::printf("Opening file %s failed!\n", path);
            return false;
        }

        while (true)
        {
            char lineHeader[LINE_HEADER_SIZE];
            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
            {
                break; // EOF = End Of File. Quit the loop.
            }

            // else : parse lineHeader

            if (std::strcmp(lineHeader, "#") == 0)
            {
                read_until_newline(file);
            }
            else if (std::strcmp(lineHeader, "l") == 0)
            {
                read_until_newline(file);
            }
            else if (std::strcmp(lineHeader, "mtllib") == 0)
            {
                // TODO: Add support for `mtllib`!
                read_until_newline(file);
            }
            else if (std::strcmp(lineHeader, "o") == 0)
            {
                read_until_newline(file);
            }
            else if (std::strcmp(lineHeader, "s") == 0)
            {
                read_until_newline(file);
            }
            else if (std::strcmp(lineHeader, "usemtl") == 0)
            {
                // TODO: Add support for `usemtl`!
                read_until_newline(file);
            }
            else if (std::strcmp(lineHeader, "v") == 0)
            {
                // This line specifies a vertex.
                // Example:
                // v 1.000000 -1.000000 -1.000000
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_vertices.push_back(vertex);
            }
            else if (std::strcmp(lineHeader, "vt") == 0)
            {
                // This line specifies texture coordinate of one vertex.
                // Example:
                // vt 0.748573 0.750412
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                // uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
                temp_UVs.push_back(uv);
            }
            else if (std::strcmp(lineHeader, "vn") == 0)
            {
                // This line specifies the normal of one vertex.
                // Example:
                // vn 0.000000 0.000000 -1.000000
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                temp_normals.push_back(normal);
            }
            else if (std::strcmp(lineHeader, "f") == 0)
            {
                // This line specifies a face.
                // Example:
                // f 5/1/1 1/2/1 4/3/1
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(
                        file,
                        "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                        &vertexIndex[0],
                        &uvIndex[0],
                        &normalIndex[0],
                        &vertexIndex[1],
                        &uvIndex[1],
                        &normalIndex[1],
                        &vertexIndex[2],
                        &uvIndex[2],
                        &normalIndex[2]);
                if (matches != 9)
                {
                    std::printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                    continue;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
            else
            {
                // Probably a comment, eat up the rest of the line
                char stupidBuffer[1000];
                fgets(stupidBuffer, 1000, file);
            }
        }

        // For each vertex of each triangle
        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            // Get the indices of its attributes
            unsigned int vertexIndex = vertexIndices[i];
            unsigned int uvIndex = uvIndices[i];
            unsigned int normalIndex = normalIndices[i];

            // Get the attributes thanks to the index
            glm::vec3 vertex = temp_vertices[vertexIndex - 1];
            glm::vec2 uv = temp_UVs[uvIndex - 1];
            glm::vec3 normal = temp_normals[normalIndex - 1];

            // Put the attributes in buffers
            out_vertices.push_back(vertex);
            out_UVs     .push_back(uv);
            out_normals .push_back(normal);
        }

        std::fclose(file);
        return true;
    }
}
