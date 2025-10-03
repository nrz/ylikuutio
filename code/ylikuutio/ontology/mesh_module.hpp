// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::ontology
{
    class Universe;
    class Ecosystem;
    class Pipeline;
    struct MeshProviderStruct;

    class MeshModule final
    {
        public:
            MeshModule(
                    Universe& universe,
                    const MeshProviderStruct& mesh_provider_struct,
                    yli::ontology::Pipeline* const pipeline);

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
            GLuint get_vertex_buffer() const;
            GLuint get_uv_buffer() const;
            GLuint get_normal_buffer() const;
            GLuint get_element_buffer() const;

            void set_vertex_position_modelspace_id(const GLint vertex_position_modelspace_id);
            void set_vertex_uv_id(const GLint vertex_uv_id);
            void set_vertex_normal_modelspace_id(const GLint vertex_normal_modelspace_id);

        public:
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
            GLuint vertex_buffer { 0 }; // Dummy value.
            GLuint uv_buffer     { 0 }; // Dummy value.
            GLuint normal_buffer { 0 }; // Dummy value.
            GLuint element_buffer { 0 }; // Dummy value.

            bool use_real_texture_coordinates   { true };
            bool are_opengl_buffers_initialized { false };
    };
}

#endif
