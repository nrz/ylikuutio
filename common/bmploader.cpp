// Include standard headers
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <glm/glm.hpp>

#include "bmploader.hpp"

// #define USE_HEIGHT_AS_TEXTURE_COORDINATE
#define USE_REAL_TEXTURE_COORDINATES

int32_t get_y(
        int32_t *vertex_data,
        int32_t x,
        int32_t z,
        int32_t image_width)
{
    int32_t *vertex_pointer;
    vertex_pointer = vertex_data + z * image_width + x;
    return *vertex_pointer;
}

bool triangulate_quads(
        int32_t *input_vertex_pointer,
        uint32_t image_width,
        uint32_t image_height,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals,
        std::string triangulation_type)

{
#define SOUTHWEST (current_vertex_i - image_width - 1)
#define SOUTHEAST (current_vertex_i - image_width)
#define NORTHWEST (current_vertex_i - 1)
#define NORTHEAST (current_vertex_i)

    std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    uint32_t texture_x = 0;
    uint32_t texture_y = 0;

    // First, define the temporary vertices in a double loop.
    for (int32_t z = 0; z < image_height; z++)
    {
        for (int32_t x = 0; x < image_width; x++)
        {
            int32_t y;       // Y (altitude).

            // current x,z coordinates).
            y = get_y(input_vertex_pointer, x, z, image_width);

            // This corresponds to "v": specify one vertex.
            glm::vec3 vertex;
            vertex.x = x;
            vertex.y = y;
            vertex.z = z;
            temp_vertices.push_back(vertex);

            // This corresponds to "vt": specify texture coordinates of one vertex.
            glm::vec2 uv;
            uv.x = round((float) texture_x);
            uv.y = round((float) texture_y);
            temp_uvs.push_back(uv);

            // This corresponds to "vn": specify normal of one vertex.
            glm::vec3 normal;
            normal.x = 0; // TODO: define a proper normal!
            normal.y = 1; // TODO: define a proper normal!
            normal.z = 0; // TODO: define a proper normal!
            temp_normals.push_back(normal);

            texture_x ^= 1;
        }
        texture_y ^= 1;
    }

    uint32_t vertexIndex[3], uvIndex[3], normalIndex[3];

    bool is_4_triangles_in_use = false;
    bool is_southwest_northeast_in_use = false;
    bool is_southeast_northwest_in_use = false;
    bool is_triangulation_type_valid = false;

    const char *char_triangulation_type = triangulation_type.c_str();

    if (strcmp(char_triangulation_type, "4_triangles") == 0)
    {
        is_4_triangles_in_use = true;
        is_triangulation_type_valid = true;
    }
    else if ((strcmp(char_triangulation_type, "southwest_northeast") == 0) || (strcmp(char_triangulation_type, "northeast_southwest") == 0))
    {
        is_southwest_northeast_in_use = true;
        is_triangulation_type_valid = true;
    }
    else if ((strcmp(char_triangulation_type, "southeast_northwest") == 0) || (strcmp(char_triangulation_type, "northwest_southeast") == 0))
    {
        is_southeast_northwest_in_use = true;
        is_triangulation_type_valid = true;
    }

    std::cout << "triangulation type in use: " << triangulation_type << "\n";
    std::cout << "is triangulation type valid: " << is_triangulation_type_valid << "\n";

    uint32_t triangle_i = 0;

    if (is_4_triangles_in_use)
    {
        std::cerr << "quad triangulation type " << triangulation_type << " not yet implemented!\n";
        return false;
    }
    else if (is_southwest_northeast_in_use)
    {
        std::cout << "image width: " << image_width << " pixels.\n";
        std::cout << "image height: " << image_height << " pixels.\n";

        // Then, define the faces in a double loop.
        // Begin from index 1.
        for (int32_t z = 1; z < image_height; z++)
        {
            // Begin from index 1.
            for (int32_t x = 1; x < image_width; x++)
            {
                // This corresponds to "f": specify a face (but here we specify 2 faces instead!).
                std::cout << "Handling coordinate (" << x << ", " << z << ").\n";

                uint32_t current_vertex_i = image_width * z + x;

                if (is_southwest_northeast_in_use)
                {
                    // First triangle: 1, 4, 2 (southwest, northeast, southeast).
                    // Second triangle: 1, 3, 4 (southwest, northwest, northeast).
                    // 1, 4, 2 are relative vertex indices (base 1).
                    // 1, 3, 4 are relative vertex indices (base 1).

                    // Define the first triangle: 1, 4, 2 (southwest, northeast, southeast).
                    // southwest: down and left from current coordinate.
                    // southeast: down from current coordinate.
                    // northeast: current coordinate.

                    vertexIndex[0] = SOUTHWEST;
                    vertexIndex[1] = NORTHEAST;
                    vertexIndex[2] = SOUTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = get_y(input_vertex_pointer, x - 1, z - 1, image_width); // altitude of southwest vertex.
                    uvIndex[1] = get_y(input_vertex_pointer, x, z, image_width);         // altitude of northeast (current) vertex.
                    uvIndex[2] = get_y(input_vertex_pointer, x, z - 1, image_width);     // altitude of southeast vertex.
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = image_width * (z - 1) + (x - 1); // southwest vertex.
                    uvIndex[1] = image_width * z + x;             // northeast (current) vertex.
                    uvIndex[2] = image_width * (z - 1) + x;       // southeast vertex.
#endif
                }
                normalIndex[0] = 0; // TODO: add proper normal index.
                normalIndex[1] = 0; // TODO: add proper normal index.
                normalIndex[2] = 0; // TODO: add proper normal index.

                glm::vec3 vertex;
                glm::vec2 uv;
                glm::vec3 normal;

                vertex = temp_vertices[vertexIndex[0]];
                out_vertices.push_back(vertex);
                uv = temp_uvs[uvIndex[0]];
                out_uvs.push_back(uv);
                normal = temp_normals[normalIndex[0]];
                out_normals.push_back(normal);

                // std::cout << "triangle " << triangle_i << ", vertex 0: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ").\n";

                vertex = temp_vertices[vertexIndex[1]];
                out_vertices.push_back(vertex);
                uv = temp_uvs[uvIndex[1]];
                out_uvs.push_back(uv);
                normal = temp_normals[normalIndex[1]];
                out_normals.push_back(normal);

                // std::cout << "triangle " << triangle_i << ", vertex 1: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ").\n";

                vertex = temp_vertices[vertexIndex[2]];
                out_vertices.push_back(vertex);
                uv = temp_uvs[uvIndex[2]];
                out_uvs.push_back(uv);
                normal = temp_normals[normalIndex[2]];
                out_normals.push_back(normal);

                // std::cout << "triangle " << triangle_i << ", vertex 2: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ").\n\n";
                triangle_i++;

                if (is_southwest_northeast_in_use)
                {
                    // Define the second triangle: 1, 3, 4 (southwest, northwest, northeast).
                    // southwest: down and left from current coordinate.
                    // northwest: left from current coordinate.
                    // northeast: current coordinate.

                    vertexIndex[0] = SOUTHWEST;
                    vertexIndex[1] = NORTHWEST;
                    vertexIndex[2] = NORTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = get_y(input_vertex_pointer, x - 1, z - 1, image_width); // altitude of southwest vertex.
                    uvIndex[1] = get_y(input_vertex_pointer, x - 1, z, image_width);     // altitude of northwest vertex.
                    uvIndex[2] = get_y(input_vertex_pointer, x, z, image_width);         // altitude of northeast (current) vertex.
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = image_width * (z - 1) + (x - 1); // southwest vertex.
                    uvIndex[1] = image_width * z + (x - 1);       // northwest vertex.
                    uvIndex[2] = image_width * z + x;             // northeast (current) vertex.
#endif
                }

                normalIndex[0] = 0; // TODO: add proper normal index.
                normalIndex[1] = 0; // TODO: add proper normal index.
                normalIndex[2] = 0; // TODO: add proper normal index.

                vertex = temp_vertices[vertexIndex[0]];
                out_vertices.push_back(vertex);
                uv = temp_uvs[uvIndex[0]];
                out_uvs.push_back(uv);
                normal = temp_normals[normalIndex[0]];
                out_normals.push_back(normal);

                // std::cout << "triangle " << triangle_i << ", vertex 0: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ").\n";

                vertex = temp_vertices[vertexIndex[1]];
                out_vertices.push_back(vertex);
                uv = temp_uvs[uvIndex[1]];
                out_uvs.push_back(uv);
                normal = temp_normals[normalIndex[1]];
                out_normals.push_back(normal);

                // std::cout << "triangle " << triangle_i << ", vertex 1: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ").\n";

                vertex = temp_vertices[vertexIndex[2]];
                out_vertices.push_back(vertex);
                uv = temp_uvs[uvIndex[2]];
                out_uvs.push_back(uv);
                normal = temp_normals[normalIndex[2]];
                out_normals.push_back(normal);

                // std::cout << "triangle " << triangle_i << ", vertex 2: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ").\n";
                triangle_i++;
            }
        }
        return true;
    }
    else if (is_southeast_northwest_in_use)
    {
        std::cerr << "quad triangulation type " << triangulation_type << " not yet implemented!\n";
        return false;
    }
    else
    {
        std::cerr << "quad triangulation type " << triangulation_type << " not yet implemented!\n";
        return false;
    }
    return true;
}

bool load_BMP_world(
        const char *image_path,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals,
        std::string color_channel)
{
    std::cout << "Loading BMP file " << image_path << " ...\n";

    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    uint32_t image_width, image_height;
    // Actual RGB image data.
    uint8_t *image_data;

    // Open the file
    FILE *file = fopen(image_path,"rb");
    if (!file)
    {
        std::cerr << image_path << " could not be opened.\n";
        getchar();
        return 0;
    }

    // Read the header, i.e. the 54 first bytes

    // If less than 54 bytes are read, it's a problem.
    if (fread(header, 1, 54, file) != 54)
    {
        std::cerr << "not a correct BMP file.\n";
        return 0;
    }

    // A BMP files always begins with "BM"
    if ((header[0] != 'B') || (header[1] != 'M'))
    {
        std::cerr << "not a correct BMP file.\n";
        return 0;
    }

    // Make sure this is a 24bpp file
    if (*(int*) & (header[0x1E]) != 0)
    {
        std::cerr << "not a correct BMP file.\n";
        return 0;
    }

    if (*(int*) & (header[0x1C]) != 24)
    {
        std::cerr << "not a correct BMP file.\n";
        return 0;
    }

    // Read the information about the image
    dataPos      = *(int*) & (header[0x0A]);
    imageSize    = *(int*) & (header[0x22]);
    image_width  = *(int*) & (header[0x12]);
    image_height = *(int*) & (header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)
    {
        imageSize = image_width * image_height * 3; // 3 : one byte for each Red, Green and Blue component
    }

    if (dataPos == 0)
    {
        dataPos = 54; // The BMP header is done that way
    }

    // Create a buffer.
    image_data = new uint8_t [imageSize];

    // Read the actual image data from the file into the buffer.
    fread(image_data, 1, imageSize, file);

    // Everything is in memory now, the file can be closed
    fclose(file);

    int32_t *vertex_data;
    vertex_data = new int32_t [imageSize];

    uint8_t *image_pointer;
    image_pointer = image_data;

    int32_t *vertex_pointer;
    vertex_pointer = vertex_data;

    // start processing image_data.
    for (int32_t z = 0; z < image_height; z++)
    {
        for (int32_t x = 0; x < image_width; x++)
        {
            const char *char_color_channel = color_channel.c_str();
            int32_t y;

            if (strcmp(char_color_channel, "red") == 0)
            {
                y = (int32_t) *image_pointer;       // y-coordinate is the red (R) value.
            }
            else if (strcmp(char_color_channel, "green") == 0)
            {
                y = (int32_t) *(image_pointer + 1); // y-coordinate is the green (G) value.
            }
            else if (strcmp(char_color_channel, "green") == 0)
            {
                y = (int32_t) *(image_pointer + 2); // y-coordinate is the blue (B) value.
            }
            // y-coordinate is the mean of R, G, & B.
            else if ((strcmp(char_color_channel, "mean") == 0) || (strcmp(char_color_channel, "all") == 0))
            {
                y = (((int32_t) *image_pointer) + ((int32_t) *(image_pointer + 1)) + ((int32_t) *(image_pointer + 2))) / 3;
            }
            else
            {
                std::cerr << "invalid color channel!";
            }

            // std::cout << color_channel << " color channel value at (" << x << ", " << z << "): " << y << ".\n";
            *vertex_pointer++ = y;
            image_pointer += 3; // R, G, & B.
        }
    }
    std::cout << "color channel in use: " << color_channel << "\n";

    // std::string triangulation_type = "4_triangles";
    // std::string triangulation_type = "southeast_northwest"; // "northwest_southeast" is equivalent.
    std::string triangulation_type = "southwest_northeast"; // "northeast_southwest" is equivalent.

    bool triangulation_result = triangulate_quads(vertex_data, image_width, image_height, out_vertices, out_uvs, out_normals, triangulation_type);
    return true;
}
