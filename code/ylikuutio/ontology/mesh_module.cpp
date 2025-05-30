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

#include "mesh_module.hpp"
#include "universe.hpp"
#include "pipeline.hpp"
#include "request.hpp"
#include "mesh_provider_struct.hpp"
#include "code/ylikuutio/load/model_loader.hpp"
#include "code/ylikuutio/load/model_loader_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cerr
#include <stdint.h> // uint32_t etc.
#include <variant>  // std::holds_alternative
#include <vector>   // std::vector

namespace yli::ontology
{
    class Scene;

    MeshModule::MeshModule(
            Universe& universe,
            const MeshProviderStruct& mesh_provider_struct,
            Pipeline* const pipeline)
    {
        // If software rendering is in use, the vertices, UVs, and normals can not be loaded into GPU memory,
        // but they can still be loaded into CPU memory to be used by the software rendering.
        const bool should_load_vertices_uvs_and_normals =
            universe.get_is_opengl_in_use() ||
            universe.get_is_vulkan_in_use() ||
            universe.get_is_software_rendering_in_use();

        if (should_load_vertices_uvs_and_normals &&
                universe.get_is_opengl_in_use() &&
                pipeline != nullptr)
        {
            // VAO.
            glGenVertexArrays(1, &this->vao);

            // Get a handle for our buffers.
            this->vertex_position_modelspace_id = glGetAttribLocation(pipeline->get_program_id(), "vertex_position_modelspace");
            this->vertex_uv_id = glGetAttribLocation(pipeline->get_program_id(), "vertex_uv");
            this->vertex_normal_modelspace_id = glGetAttribLocation(pipeline->get_program_id(), "vertex_normal_modelspace");

            yli::load::ModelLoaderStruct model_loader_struct = mesh_provider_struct.model_loader_struct;
            model_loader_struct.image_width_pointer           = &this->image_width;
            model_loader_struct.image_height_pointer          = &this->image_height;

            const bool is_debug_mode = true;

            yli::load::load_model(
                    model_loader_struct,
                    this->vertices,
                    this->uvs,
                    this->normals,
                    this->indices,
                    this->indexed_vertices,
                    this->indexed_uvs,
                    this->indexed_normals,
                    this->vao,
                    this->vertexbuffer,
                    this->uvbuffer,
                    this->normalbuffer,
                    this->elementbuffer,
                    universe.get_graphics_api_backend(),
                    is_debug_mode);

            this->are_opengl_buffers_initialized = true;
        }
    }

    MeshModule::~MeshModule()
    {
        if (this->are_opengl_buffers_initialized)
        {
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);
            glDeleteBuffers(1, &this->normalbuffer);
            glDeleteBuffers(1, &this->elementbuffer);
        }
    }

    std::size_t MeshModule::get_number_of_vertices() const
    {
        return this->vertices.size();
    }

    const std::vector<glm::vec3>& MeshModule::get_vertices() const
    {
        return this->vertices;
    }

    const std::vector<glm::vec2>& MeshModule::get_uvs() const
    {
        return this->uvs;
    }

    const std::vector<glm::vec3>& MeshModule::get_normals() const
    {
        return this->normals;
    }

    const std::vector<uint32_t>& MeshModule::get_indices() const
    {
        return this->indices;
    }

    std::size_t MeshModule::get_indices_size() const
    {
        return this->indices.size();
    }

    GLint MeshModule::get_vertex_position_modelspace_id() const
    {
        return this->vertex_position_modelspace_id;
    }

    GLint MeshModule::get_vertex_uv_id() const
    {
        return this->vertex_uv_id;
    }

    GLint MeshModule::get_vertex_normal_modelspace_id() const
    {
        return this->vertex_normal_modelspace_id;
    }

    GLuint MeshModule::get_vao() const
    {
        return this->vao;
    }

    GLuint MeshModule::get_vertexbuffer() const
    {
        return this->vertexbuffer;
    }

    GLuint MeshModule::get_uvbuffer() const
    {
        return this->uvbuffer;
    }

    GLuint MeshModule::get_normalbuffer() const
    {
        return this->normalbuffer;
    }

    GLuint MeshModule::get_elementbuffer() const
    {
        return this->elementbuffer;
    }

    void MeshModule::set_vertex_position_modelspace_id(const GLint vertex_position_modelspace_id)
    {
        this->vertex_position_modelspace_id = vertex_position_modelspace_id;
    }

    void MeshModule::set_vertex_uv_id(const GLint vertex_uv_id)
    {
        this->vertex_uv_id = vertex_uv_id;
    }

    void MeshModule::set_vertex_normal_modelspace_id(const GLint vertex_normal_modelspace_id)
    {
        this->vertex_normal_modelspace_id = vertex_normal_modelspace_id;
    }
}
