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

uint32_t get_y(
        uint32_t *vertex_data,
        uint32_t x,
        uint32_t z,
        uint32_t image_width)
{
    uint32_t *vertex_pointer;
    vertex_pointer = vertex_data + z * image_width + x;
    return *vertex_pointer;
}

uint32_t output_triangle_vertices(
        std::vector<glm::vec3> &temp_vertices,
        std::vector<glm::vec2> &temp_uvs,
        std::vector<glm::vec3> &temp_normals,
        uint32_t vertexIndex[3],
        uint32_t uvIndex[3],
        uint32_t normalIndex[3],
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals,
        uint32_t triangle_i)
{
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
}

bool triangulate_quads(
        uint32_t *input_vertex_pointer,
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
#define CENTER (current_interpolated_vertex_i)

#define SOUTHWEST_Y (get_y(input_vertex_pointer, x - 1, z - 1, image_width))
#define SOUTHEAST_Y (get_y(input_vertex_pointer, x, z, image_width))
#define NORTHWEST_Y (get_y(input_vertex_pointer, x - 1, z, image_width))
#define NORTHEAST_Y (get_y(input_vertex_pointer, x, z, image_width))
#define CENTER_Y ((SOUTHWEST_Y + SOUTHEAST_Y + NORTHWEST_Y + NORTHEAST_Y) / 4)

    std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    uint32_t texture_x = 0;
    uint32_t texture_y = 0;

    // First, define the temporary vertices in a double loop.
    for (uint32_t z = 0; z < image_height; z++)
    {
        for (uint32_t x = 0; x < image_width; x++)
        {
            // current x,z coordinates).
            float y = (float) get_y(input_vertex_pointer, x, z, image_width);

            // This corresponds to "v": specify one vertex.
            glm::vec3 vertex;
            vertex.x = (float) x;
            vertex.y = y;
            vertex.z = (float) z;
            temp_vertices.push_back(vertex);

            // This corresponds to "vt": specify texture coordinates of one vertex.
            glm::vec2 uv;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
            uv.x = y / 256;
            uv.y = 0.0f;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
            uv.x = round((float) texture_x);
            uv.y = round((float) texture_y);
#endif

            temp_uvs.push_back(uv);

            // This corresponds to "vn": specify normal of one vertex.
            glm::vec3 normal;
            normal.x = 0.0f; // TODO: define a proper normal!
            normal.y = 1.0f; // TODO: define a proper normal!
            normal.z = 0.0f; // TODO: define a proper normal!
            temp_normals.push_back(normal);

            texture_x ^= 1;
        }
        texture_y ^= 1;
    }

    uint32_t vertexIndex[3], uvIndex[3], normalIndex[3];

    bool is_bilinear_interpolation_in_use = false;
    bool is_southwest_northeast_in_use = false;
    bool is_southeast_northwest_in_use = false;
    bool is_triangulation_type_valid = false;

    const char *char_triangulation_type = triangulation_type.c_str();

    if (strcmp(char_triangulation_type, "bilinear_interpolation") == 0)
    {
        is_bilinear_interpolation_in_use = true;
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

    if (is_bilinear_interpolation_in_use)
    {
        std::cout << "image width: " << image_width << " pixels.\n";
        std::cout << "image height: " << image_height << " pixels.\n";

        uint32_t current_interpolated_vertex_i = image_width * image_height;

        // Then, define the faces in a double loop.
        // Begin from index 1.
        for (uint32_t z = 1; z < image_height; z++)
        {
            // Begin from index 1.
            for (uint32_t x = 1; x < image_width; x++)
            {
                // This corresponds to "f": specify a face (but here we specify 2 faces instead!).
                // std::cout << "Processing coordinate (" << x << ", " << z << ").\n";

                uint32_t current_vertex_i = image_width * z + x;

                // Interpolate y coordinate (altitude).
                float y = ((float) SOUTHWEST_Y + SOUTHEAST_Y + NORTHWEST_Y + NORTHEAST_Y) / 4;

                // Create a new vertex using bilinear interpolation.
                // This corresponds to "v": specify one vertex.
                glm::vec3 vertex;
                vertex.x = (float) x - 0.5f;
                vertex.y = y;
                vertex.z = (float) z - 0.5f;
                temp_vertices.push_back(vertex);

                // This corresponds to "vt": specify texture coordinates of one vertex.
                glm::vec2 uv;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                uv.x = y / 256;
                uv.y = 0.0f;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                uv.x = 0.5f;
                uv.y = 0.5f;
#endif

                temp_uvs.push_back(uv);

                // This corresponds to "vn": specify normal of one vertex.
                glm::vec3 normal;
                normal.x = 0.0f; // TODO: define a proper normal!
                normal.y = 1.0f; // TODO: define a proper normal!
                normal.z = 0.0f; // TODO: define a proper normal!
                temp_normals.push_back(normal);

                // Then, define the triangles (4 faces).
                // Triangle order: S - W - N - E.
                //
                // First triangle: center, southeast, southwest.
                // Second triangle: center, southwest, northwest.
                // Third triangle: center, northwest, northeast.
                // Fourth triangle: center, northeast, southeast.

                // Define the first triangle, S: center, southeast, southwest.
                vertexIndex[0] = CENTER;
                vertexIndex[1] = SOUTHEAST;
                vertexIndex[2] = SOUTHWEST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                uvIndex[0] = CENTER_Y;
                uvIndex[1] = SOUTHEAST_y;
                uvIndex[2] = SOUTHWEST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                uvIndex[0] = CENTER;
                uvIndex[1] = SOUTHEAST;
                uvIndex[2] = SOUTHWEST;
#endif

                normalIndex[0] = 0; // TODO: add proper normal index.
                normalIndex[1] = 0; // TODO: add proper normal index.
                normalIndex[2] = 0; // TODO: add proper normal index.

                triangle_i = output_triangle_vertices(
                        temp_vertices,
                        temp_uvs,
                        temp_normals,
                        vertexIndex,
                        uvIndex,
                        normalIndex,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        triangle_i);

                // Define the second triangle, W: center, southwest, northwest.
                vertexIndex[0] = CENTER;
                vertexIndex[1] = SOUTHWEST;
                vertexIndex[2] = NORTHWEST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                uvIndex[0] = CENTER_Y;
                uvIndex[1] = SOUTHWEST_Y;
                uvIndex[2] = NORTHWEST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                uvIndex[0] = CENTER;
                uvIndex[1] = SOUTHWEST;
                uvIndex[2] = NORTHWEST;
#endif

                normalIndex[0] = 0; // TODO: add proper normal index.
                normalIndex[1] = 0; // TODO: add proper normal index.
                normalIndex[2] = 0; // TODO: add proper normal index.

                triangle_i = output_triangle_vertices(
                        temp_vertices,
                        temp_uvs,
                        temp_normals,
                        vertexIndex,
                        uvIndex,
                        normalIndex,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        triangle_i);

                // Define the third triangle, N: center, northwest, northeast.
                vertexIndex[0] = CENTER;
                vertexIndex[1] = NORTHWEST;
                vertexIndex[2] = NORTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                uvIndex[0] = CENTER_Y;
                uvIndex[1] = NORTHWEST_y;
                uvIndex[2] = NORTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                uvIndex[0] = CENTER;
                uvIndex[1] = NORTHWEST;
                uvIndex[2] = NORTHEAST;
#endif

                normalIndex[0] = 0; // TODO: add proper normal index.
                normalIndex[1] = 0; // TODO: add proper normal index.
                normalIndex[2] = 0; // TODO: add proper normal index.

                triangle_i = output_triangle_vertices(
                        temp_vertices,
                        temp_uvs,
                        temp_normals,
                        vertexIndex,
                        uvIndex,
                        normalIndex,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        triangle_i);

                // Define the fourth triangle, E: center, northeast, southeast.
                vertexIndex[0] = CENTER;
                vertexIndex[1] = NORTHEAST;
                vertexIndex[2] = SOUTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                uvIndex[0] = CENTER_Y;
                uvIndex[1] = NORTHEAST_y;
                uvIndex[2] = SOUTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                uvIndex[0] = CENTER;
                uvIndex[1] = NORTHEAST;
                uvIndex[2] = SOUTHEAST;
#endif

                normalIndex[0] = 0; // TODO: add proper normal index.
                normalIndex[1] = 0; // TODO: add proper normal index.
                normalIndex[2] = 0; // TODO: add proper normal index.

                triangle_i = output_triangle_vertices(
                        temp_vertices,
                        temp_uvs,
                        temp_normals,
                        vertexIndex,
                        uvIndex,
                        normalIndex,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        triangle_i);

                current_interpolated_vertex_i++;
            }
        }
        return true;
    }
    else if (is_southwest_northeast_in_use || is_southeast_northwest_in_use)
    {
        std::cout << "image width: " << image_width << " pixels.\n";
        std::cout << "image height: " << image_height << " pixels.\n";

        // Then, define the faces in a double loop.
        // Begin from index 1.
        for (uint32_t z = 1; z < image_height; z++)
        {
            // Begin from index 1.
            for (uint32_t x = 1; x < image_width; x++)
            {
                // This corresponds to "f": specify a face (but here we specify 2 faces instead!).
                // std::cout << "Processing coordinate (" << x << ", " << z << ").\n";

                uint32_t current_vertex_i = image_width * z + x;

                if (is_southwest_northeast_in_use)
                {
                    // Define the triangles (2 faces).
                    // Triangle order: SE - NW.
                    //
                    // First triangle: 1, 4, 2 (southwest, northeast, southeast).
                    // Second triangle: 1, 3, 4 (southwest, northwest, northeast).
                    // 1, 4, 2 are relative vertex indices (base 1).
                    // 1, 3, 4 are relative vertex indices (base 1).

                    // Define the first triangle, SE: 1, 4, 2 (southwest, northeast, southeast).
                    // southwest: down and left from current coordinate.
                    // southeast: down from current coordinate.
                    // northeast: current coordinate.

                    vertexIndex[0] = SOUTHWEST;
                    vertexIndex[1] = NORTHEAST;
                    vertexIndex[2] = SOUTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = SOUTHWEST_Y;
                    uvIndex[1] = NORTHEAST_Y;
                    uvIndex[2] = SOUTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = SOUTHWEST;
                    uvIndex[1] = NORTHEAST;
                    uvIndex[2] = SOUTHEAST;
#endif
                }
                else if (is_southeast_northwest_in_use)
                {
                    // Define the triangles (2 faces).
                    // Triangle order: SW - NE.
                    //
                    // First triangle: 2, 1, 3 (southeast, southwest, northwest).
                    // Second triangle: 2, 3, 4 (southeast, northwest, northeast).
                    // 2, 1, 3 are relative vertex indices (base 1).
                    // 2, 3, 4 are relative vertex indices (base 1).

                    // Define the first triangle, SW: 2, 1, 3 (southeast, southwest, northwest).
                    // southeast: down from current coordinate.
                    // southwest: down and left from current coordinate.
                    // northwest: left from current coordinate.

                    vertexIndex[0] = SOUTHEAST;
                    vertexIndex[1] = SOUTHWEST;
                    vertexIndex[2] = NORTHWEST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = SOUTHEAST_Y;
                    uvIndex[1] = SOUTHWEST_Y;
                    uvIndex[2] = NORTHWEST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = SOUTHEAST;
                    uvIndex[1] = SOUTHWEST;
                    uvIndex[2] = NORTHWEST;
#endif
                }

                normalIndex[0] = 0; // TODO: add proper normal index.
                normalIndex[1] = 0; // TODO: add proper normal index.
                normalIndex[2] = 0; // TODO: add proper normal index.

                triangle_i = output_triangle_vertices(
                        temp_vertices,
                        temp_uvs,
                        temp_normals,
                        vertexIndex,
                        uvIndex,
                        normalIndex,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        triangle_i);

                if (is_southwest_northeast_in_use)
                {
                    // Define the second triangle, NW: 1, 3, 4 (southwest, northwest, northeast).
                    // southwest: down and left from current coordinate.
                    // northwest: left from current coordinate.
                    // northeast: current coordinate.

                    vertexIndex[0] = SOUTHWEST;
                    vertexIndex[1] = NORTHWEST;
                    vertexIndex[2] = NORTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = SOUTHWEST_Y;
                    uvIndex[1] = NORTHWEST_Y;
                    uvIndex[2] = NORTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = SOUTHWEST;
                    uvIndex[1] = NORTHWEST;
                    uvIndex[2] = NORTHEAST;
#endif
                }
                else if (is_southeast_northwest_in_use)
                {
                    // Define the second triangle, NE: 2, 3, 4 (southeast, northwest, northeast).
                    // southeast: down from current coordinate.
                    // northwest: left from current coordinate.
                    // northeast: current coordinate.

                    vertexIndex[0] = SOUTHEAST;
                    vertexIndex[1] = NORTHWEST;
                    vertexIndex[2] = NORTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = SOUTHEAST_Y;
                    uvIndex[1] = NORTHWEST_Y;
                    uvIndex[2] = NORTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = SOUTHEAST;
                    uvIndex[1] = NORTHWEST;
                    uvIndex[2] = NORTHEAST;
#endif
                }

                normalIndex[0] = 0; // TODO: add proper normal index.
                normalIndex[1] = 0; // TODO: add proper normal index.
                normalIndex[2] = 0; // TODO: add proper normal index.

                triangle_i = output_triangle_vertices(
                        temp_vertices,
                        temp_uvs,
                        temp_normals,
                        vertexIndex,
                        uvIndex,
                        normalIndex,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        triangle_i);
            }
        }
        return true;
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

    uint32_t *vertex_data;
    vertex_data = new uint32_t [imageSize];

    uint8_t *image_pointer;
    image_pointer = image_data;

    uint32_t *vertex_pointer;
    vertex_pointer = vertex_data;

    // start processing image_data.
    for (uint32_t z = 0; z < image_height; z++)
    {
        for (uint32_t x = 0; x < image_width; x++)
        {
            const char *char_color_channel = color_channel.c_str();
            uint32_t y;

            if (strcmp(char_color_channel, "red") == 0)
            {
                y = (uint32_t) *image_pointer;       // y-coordinate is the red (R) value.
            }
            else if (strcmp(char_color_channel, "green") == 0)
            {
                y = (uint32_t) *(image_pointer + 1); // y-coordinate is the green (G) value.
            }
            else if (strcmp(char_color_channel, "green") == 0)
            {
                y = (uint32_t) *(image_pointer + 2); // y-coordinate is the blue (B) value.
            }
            // y-coordinate is the mean of R, G, & B.
            else if ((strcmp(char_color_channel, "mean") == 0) || (strcmp(char_color_channel, "all") == 0))
            {
                y = (((uint32_t) *image_pointer) + ((uint32_t) *(image_pointer + 1)) + ((uint32_t) *(image_pointer + 2))) / 3;
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

    std::string triangulation_type = "bilinear_interpolation";
    // std::string triangulation_type = "southeast_northwest"; // "northwest_southeast" is equivalent.
    // std::string triangulation_type = "southwest_northeast"; // "northeast_southwest" is equivalent.

    bool triangulation_result = triangulate_quads(vertex_data, image_width, image_height, out_vertices, out_uvs, out_normals, triangulation_type);
    return true;
}
