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

        std::vector<int32_t> vertex_indices, uv_indices, normal_indices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_UVs;
        std::vector<glm::vec3> temp_normals;

        std::FILE* file = std::fopen(path, "rb");

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
                unsigned int vertex_index[3], uv_index[3], normal_index[3];
                int matches = fscanf(
                        file,
                        "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                        &vertex_index[0],
                        &uv_index[0],
                        &normal_index[0],
                        &vertex_index[1],
                        &uv_index[1],
                        &normal_index[1],
                        &vertex_index[2],
                        &uv_index[2],
                        &normal_index[2]);
                if (matches != 9)
                {
                    std::printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                    continue;
                }
                vertex_indices.push_back(vertex_index[0]);
                vertex_indices.push_back(vertex_index[1]);
                vertex_indices.push_back(vertex_index[2]);
                uv_indices.push_back(uv_index[0]);
                uv_indices.push_back(uv_index[1]);
                uv_indices.push_back(uv_index[2]);
                normal_indices.push_back(normal_index[0]);
                normal_indices.push_back(normal_index[1]);
                normal_indices.push_back(normal_index[2]);
            }
            else
            {
                // Probably a comment, eat up the rest of the line
                char stupidBuffer[1000];
                fgets(stupidBuffer, 1000, file);
            }
        }

        // For each vertex of each triangle
        for (unsigned int i = 0; i < vertex_indices.size(); i++)
        {
            // Get the indices of its attributes
            unsigned int vertex_index = vertex_indices[i];
            unsigned int uv_index = uv_indices[i];
            unsigned int normal_index = normal_indices[i];

            // Get the attributes thanks to the index
            glm::vec3 vertex = temp_vertices[vertex_index - 1];
            glm::vec2 uv = temp_UVs[uv_index - 1];
            glm::vec3 normal = temp_normals[normal_index - 1];

            // Put the attributes in buffers
            out_vertices.push_back(vertex);
            out_UVs     .push_back(uv);
            out_normals .push_back(normal);
        }

        std::fclose(file);
        return true;
    }
}
