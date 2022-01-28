// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#include "model_loader.hpp"
#include "model_loader_struct.hpp"
#include "obj_loader.hpp"
#include "fbx_model_loader.hpp"
#include "ascii_grid_heightmap_loader.hpp"
#include "png_heightmap_loader.hpp"
#include "srtm_heightmap_loader.hpp"
#include "heightmap_loader_struct.hpp"
#include "code/ylikuutio/load/model_loader_struct.hpp"
#include "code/ylikuutio/opengl/vboindexer.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::load
{
    bool load_model(
            const yli::load::ModelLoaderStruct& model_loader_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals,
            std::vector<uint32_t>& indices,
            std::vector<glm::vec3>& indexed_vertices,
            std::vector<glm::vec2>& indexed_uvs,
            std::vector<glm::vec3>& indexed_normals,
            GLuint& vertexbuffer,
            GLuint& uvbuffer,
            GLuint& normalbuffer,
            GLuint& elementbuffer,
            const yli::render::GraphicsApiBackend graphics_api_backend,
            const bool is_debug_mode)
    {
        bool model_loading_result = false;

        if (model_loader_struct.model_struct.model_file_format == "obj" || model_loader_struct.model_struct.model_file_format == "OBJ")
        {
            model_loading_result = yli::load::load_obj(
                    model_loader_struct.model_struct.model_filename,
                    out_vertices,
                    out_uvs,
                    out_normals);
        }
        else if (model_loader_struct.model_struct.model_file_format == "fbx" || model_loader_struct.model_struct.model_file_format == "FBX")
        {
            model_loading_result = yli::load::load_fbx(
                    model_loader_struct.model_struct.model_filename,
                    model_loader_struct.model_struct.mesh_i,
                    out_vertices,
                    out_uvs,
                    out_normals,
                    is_debug_mode);

            std::cout << model_loader_struct.model_struct.model_filename << " loaded successfully.\n";
        }
        else if (model_loader_struct.model_struct.model_file_format == "srtm" || model_loader_struct.model_struct.model_file_format == "SRTM" ||
                model_loader_struct.model_struct.model_file_format == "png" || model_loader_struct.model_struct.model_file_format == "PNG" ||
                model_loader_struct.model_struct.model_file_format == "asc" ||
                model_loader_struct.model_struct.model_file_format == "ascii_grid" ||
                model_loader_struct.model_struct.model_file_format == "ASCII_grid")
        {
            if (model_loader_struct.image_width_pointer == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_model`: !\n";
                std::cerr << "`model_loader_struct.image_width_pointer` is `nullptr`!\n";
                return false;
            }

            if (model_loader_struct.image_height_pointer == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_model`: !\n";
                std::cerr << "`model_loader_struct.image_height_pointer` is `nullptr`!\n";
                return false;
            }

            yli::load::HeightmapLoaderStruct heightmap_loader_struct;
            heightmap_loader_struct.filename                     = model_loader_struct.model_struct.model_filename;
            heightmap_loader_struct.file_format                  = model_loader_struct.model_struct.model_file_format;
            heightmap_loader_struct.latitude                     = model_loader_struct.model_struct.latitude;
            heightmap_loader_struct.longitude                    = model_loader_struct.model_struct.longitude;
            heightmap_loader_struct.planet_radius                = model_loader_struct.model_struct.planet_radius;
            heightmap_loader_struct.divisor                      = model_loader_struct.model_struct.divisor;
            heightmap_loader_struct.x_step                       = model_loader_struct.model_struct.x_step;
            heightmap_loader_struct.z_step                       = model_loader_struct.model_struct.z_step;
            heightmap_loader_struct.triangulation_type           = model_loader_struct.model_struct.triangulation_type;
            heightmap_loader_struct.use_real_texture_coordinates = model_loader_struct.model_struct.use_real_texture_coordinates;

            if (model_loader_struct.model_struct.model_file_format == "srtm" || model_loader_struct.model_struct.model_file_format == "SRTM")
            {
                model_loading_result = yli::load::load_srtm_terrain(
                        heightmap_loader_struct,
                        model_loader_struct.model_struct.model_filename,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        *model_loader_struct.image_width_pointer,
                        *model_loader_struct.image_height_pointer);
            }
            else if (model_loader_struct.model_struct.model_file_format == "png" || model_loader_struct.model_struct.model_file_format == "PNG")
            {
                model_loading_result = yli::load::load_png_terrain(
                        heightmap_loader_struct,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        *model_loader_struct.image_width_pointer,
                        *model_loader_struct.image_height_pointer,
                        model_loader_struct.model_struct.color_channel);
            }
            else if (model_loader_struct.model_struct.model_file_format == "asc" ||
                    model_loader_struct.model_struct.model_file_format == "ascii_grid" ||
                    model_loader_struct.model_struct.model_file_format == "ASCII_grid")
            {
                model_loading_result = yli::load::load_ascii_grid_terrain(
                        heightmap_loader_struct,
                        out_vertices,
                        out_uvs,
                        out_normals,
                        *model_loader_struct.image_width_pointer,
                        *model_loader_struct.image_height_pointer);
            }

        }
        else
        {
            std::cerr << "ERROR: `yli::load::load_model`: no model was loaded!\n";
            std::cerr << "Model file format: " << model_loader_struct.model_struct.model_file_format << "\n";
            return false;
        }

        std::cout << "Indexing...\n";

        // Fill the index buffer.
        yli::opengl::indexVBO(
                out_vertices,
                out_uvs,
                out_normals,
                indices,
                indexed_vertices,
                indexed_uvs,
                indexed_normals);

        std::cout << "Indexing completed successfully.\n";

        if (graphics_api_backend == yli::render::GraphicsApiBackend::OPENGL)
        {
            // Load it into a VBO.
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

            glGenBuffers(1, &uvbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

            glGenBuffers(1, &normalbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
            glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

            glGenBuffers(1, &elementbuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);
        }

        // TODO: Compute the graph of the mesh of this `Species` to enable object vertex modification!
        return model_loading_result;
    }
}
