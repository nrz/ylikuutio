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

#ifndef YLIKUUTIO_ONTOLOGY_MESH_MODULE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MESH_MODULE_HPP_INCLUDED

#include "pipeline.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::ontology
{
    class Universe;
    class Ecosystem;
    struct ModelStruct;

    class MeshModule final
    {
        public:
            MeshModule(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ModelStruct& model_struct);

            MeshModule(const MeshModule&) = delete;            // Delete copy constructor.
            MeshModule& operator=(const MeshModule&) = delete; // Delete copy assignment.

            ~MeshModule();

            std::size_t get_number_of_vertices() const;
            const std::vector<glm::vec3>& get_vertices() const;
            const std::vector<glm::vec2>& get_uvs() const;
            const std::vector<glm::vec3>& get_normals() const;
            const std::vector<uint32_t>& get_indices() const;

            std::size_t get_indices_size() const;

            GLint get_vertex_position_modelspace_id() const;
            GLint get_vertex_uv_id() const;
            GLint get_vertex_normal_modelspace_id() const;

            GLuint get_vao() const;
            GLuint get_vertexbuffer() const;
            GLuint get_uvbuffer() const;
            GLuint get_normalbuffer() const;
            GLuint get_elementbuffer() const;

            void set_vertex_position_modelspace_id(const GLint vertex_position_modelspace_id);
            void set_vertex_uv_id(const GLint vertex_uv_id);
            void set_vertex_normal_modelspace_id(const GLint vertex_normal_modelspace_id);

            std::string model_filename;    // Filename of the model file.
            std::string model_file_format; // Type of the model file. supported file formats so far:
            // `"png"`/`"PNG"` - PNG heightmap.
            // `"fbx"`/`"FBX"` - FBX model.
            // `"obj"`/`"OBJ"` - OBJ model.
            // `"srtm"`/`"SRTM"` - SRTM heightmap.
            // `"asc"`/`"ascii_grid"`/`"ASCII_grid"` - ASCII grid.

        private:
            std::string color_channel;    // Color channel to use for altitude data, for PNG model files.

        public:
            float planet_radius { NAN };  // Radius of sea level in kilometers. used only for terrains (planets and moons). `6371.0f` for Earth.

        private:
            float divisor       { 1.0f }; // Value by which SRTM values are divided to convert them to kilometers.
            float latitude      { 0.0f }; // In degrees, for SRTM model files.
            float longitude     { 0.0f }; // In degrees, for SRTM model files.
            uint32_t mesh_i     { 0 };    // For FBX.

        public:
            uint32_t x_step     { 1 };    // Step in x-dimension for input data (set to 1 to load all data points/measurements).
            uint32_t y_step     { 1 };    // Step in z-dimension for input data (set to 1 to load all data points/measurements).

            uint32_t image_width  { 0 };
            uint32_t image_height { 0 };

        private:
            std::vector<glm::vec3> vertices; // Vertices of the `MeshModule`.
            std::vector<glm::vec2> uvs;      // UVs of the `MeshModule`.
            std::vector<glm::vec3> normals;  // Normals of the `MeshModule`.

        public:
            GLint vertex_position_modelspace_id { 0 }; // Dummy value.
            GLint vertex_uv_id                  { 0 }; // Dummy value.
            GLint vertex_normal_modelspace_id   { 0 }; // Dummy value.

        private:
            std::vector<uint32_t> indices;
            std::vector<glm::vec3> indexed_vertices;
            std::vector<glm::vec2> indexed_uvs;
            std::vector<glm::vec3> indexed_normals;

            GLuint vao           { 0 }; // Dummy value.
            GLuint vertexbuffer  { 0 }; // Dummy value.
            GLuint uvbuffer      { 0 }; // Dummy value.
            GLuint normalbuffer  { 0 }; // Dummy value.
            GLuint elementbuffer { 0 }; // Dummy value.

            bool use_real_texture_coordinates { true };
            bool are_opengl_buffers_initialized { false };
    };
}

#endif
