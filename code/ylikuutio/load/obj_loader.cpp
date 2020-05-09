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

#include "obj_loader.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

// Include standard headers
#include <algorithm> // std::replace
#include <cstddef>   // std::size_t
#include <cstring>   // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream>  // std::cout, std::cin, std::cerr
#include <memory>    // std::make_shared, std::shared_ptr
#include <sstream>   // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::load
{
    bool load_OBJ(
            const std::string& filename,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals)
    {
        std::cout << "Loading OBJ file " << filename << " ...\n";

        // Open the file
        const std::shared_ptr<std::string> file_content = yli::file::slurp(filename);

        if (file_content->empty())
        {
            std::cerr << filename << " could not be opened, or the file is empty.\n";
            return false;
        }

        std::vector<int32_t> vertex_indices, uv_indices, normal_indices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_UVs;
        std::vector<glm::vec3> temp_normals;

        std::size_t file_content_i = 0;

        while (true)
        {
            // Assume we are at the beginning of a line now.
            const std::vector<std::string> whitespace_vector = { " ", "\t" };

            // Read until any non-whitespace character.
            while (true)
            {
                if (!yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, whitespace_vector))
                {
                    // Not whitespace.
                    break;
                }

                file_content_i++;
            }

            if (file_content_i >= file_content->size())
            {
                std::cout << filename << " ends in a line consisting only of whitespace.\n";
                break;
            }

            // OK, non-whitespace found.
            std::string current_line_string;
            const char* newline_char_end_string = "\n";
            yli::string::extract_string_with_several_endings(*file_content, file_content_i, current_line_string, newline_char_end_string);

            // Replace slashes `'/'` with space `' '`, to make string processing easier.
            std::replace(current_line_string.begin(), current_line_string.end(), '/', ' ');

            // Note: `"vt"` and `"vn"` needs to be checked for before `"v"`!

            std::stringstream current_line_stringstream = std::stringstream(current_line_string);
            std::string prefix;

            if (current_line_string.compare(0, std::strlen("#"), "#") == 0)
            {
                // `#`
                // This line is a comment.
            }
            else if (current_line_string.compare(0, std::strlen("vt"), "vt") == 0)
            {
                // `vt`
                // This line specifies texture coordinate of one vertex.
                // Example:
                // vt 0.748573 0.750412
                glm::vec2 uv;
                current_line_stringstream >> prefix >> uv.x >> uv.y;
                temp_UVs.push_back(uv);
            }
            else if (current_line_string.compare(0, std::strlen("vn"), "vn") == 0)
            {
                // `vn`
                // This line specifies the normal of one vertex.
                // Example:
                // vn 0.000000 0.000000 -1.000000
                glm::vec3 normal;
                current_line_stringstream >> prefix >> normal.x >> normal.y >> normal.z;
                temp_normals.push_back(normal);
            }
            else if (current_line_string.compare(0, std::strlen("v"), "v") == 0)
            {
                // `v`
                // This line specifies a vertex.
                // Example:
                // v 1.000000 -1.000000 -1.000000
                glm::vec3 vertex;
                current_line_stringstream >> prefix >> vertex.x >> vertex.y >> vertex.z;
                temp_vertices.push_back(vertex);
            }
            else if (current_line_string.compare(0, std::strlen("f"), "f") == 0)
            {
                // `f`
                // This line specifies a face.
                // Example:
                // f 5/1/1 1/2/1 4/3/1
                int32_t vertex_i1;
                int32_t vertex_i2;
                int32_t vertex_i3;
                int32_t uv_i1;
                int32_t uv_i2;
                int32_t uv_i3;
                int32_t normal_i1;
                int32_t normal_i2;
                int32_t normal_i3;
                current_line_stringstream >> prefix >> vertex_i1 >> uv_i1 >> normal_i1 >> vertex_i2 >> uv_i2 >> normal_i2 >> vertex_i3 >> uv_i3 >> normal_i3;
                vertex_indices.push_back(vertex_i1);
                vertex_indices.push_back(vertex_i2);
                vertex_indices.push_back(vertex_i3);
                uv_indices.push_back(uv_i1);
                uv_indices.push_back(uv_i2);
                uv_indices.push_back(uv_i3);
                normal_indices.push_back(normal_i1);
                normal_indices.push_back(normal_i2);
                normal_indices.push_back(normal_i3);
            }
            else if (current_line_string.compare(0, std::strlen("l"), "l") == 0)
            {
                // `l`
                // TODO: implement `l`.
            }
            else if (current_line_string.compare(0, std::strlen("o"), "o") == 0)
            {
                // `o`
                // TODO: implement `o`.
                // Currently, terminate processing when `o` is encountered.
                break;
            }
            else if (current_line_string.compare(0, std::strlen("s"), "s") == 0)
            {
                // `s`
                // TODO: implement `s`.
            }
            else if (current_line_string.compare(0, std::strlen("mtllib"), "mtllib") == 0)
            {
                // `mtllib`
                // TODO: implement `mtllib`.
            }
            else if (current_line_string.compare(0, std::strlen("usemtl"), "usemtl") == 0)
            {
                // `usemtl`
                // TODO: implement `usemtl`.
            }

            const std::vector<std::string> endline_vector = { "\n", "\r" };

            // Read until any non-whitespace character.
            while (yli::string::check_and_report_if_some_string_matches(*file_content, ++file_content_i, endline_vector));
        }

        // For each vertex of each triangle
        for (std::size_t i = 0; i < vertex_indices.size(); i++)
        {
            // Get the indices of its attributes
            int32_t vertex_index = vertex_indices[i];
            int32_t uv_index = uv_indices[i];
            int32_t normal_index = normal_indices[i];

            // Get the attributes thanks to the index
            glm::vec3 vertex = temp_vertices[vertex_index - 1];
            glm::vec2 uv = temp_UVs[uv_index - 1];
            glm::vec3 normal = temp_normals[normal_index - 1];

            // Put the attributes in buffers
            out_vertices.push_back(vertex);
            out_uvs.push_back(uv);
            out_normals.push_back(normal);
        }

        return true;
    }
}
