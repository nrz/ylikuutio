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

#include "model.hpp"
#include "object.hpp"
#include "family_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;

        Model::~Model()
        {
            // destructor.
        }

        std::size_t Model::get_number_of_children() const
        {
            return this->number_of_objects;
        }

        std::size_t Model::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->object_pointer_vector);
        }

        std::size_t Model::get_number_of_vertices() const
        {
            return this->vertices.size();
        }

        const std::vector<glm::vec3>& Model::get_vertices() const
        {
            return this->vertices;
        }

        const std::vector<glm::vec2>& Model::get_uvs() const
        {
            return this->uvs;
        }

        const std::vector<glm::vec3>& Model::get_normals() const
        {
            return this->normals;
        }

        const std::vector<uint32_t>& Model::get_indices() const
        {
            return this->indices;
        }

        GLint Model::get_vertex_position_modelspaceID() const
        {
            return this->vertex_position_modelspaceID;
        }

        GLint Model::get_vertexUVID() const
        {
            return this->vertexUVID;
        }

        GLint Model::get_vertex_normal_modelspaceID() const
        {
            return this->vertex_normal_modelspaceID;
        }

        uint32_t Model::get_vertexbuffer() const
        {
            return this->vertexbuffer;
        }

        uint32_t Model::get_uvbuffer() const
        {
            return this->uvbuffer;
        }

        uint32_t Model::get_normalbuffer() const
        {
            return this->normalbuffer;
        }

        uint32_t Model::get_elementbuffer() const
        {
            return this->elementbuffer;
        }

        void Model::store_vertex_position_modelspaceID(const GLint vertex_position_modelspaceID)
        {
            this->vertex_position_modelspaceID = vertex_position_modelspaceID;
        }

        void Model::store_vertexUVID(const GLint vertexUVID)
        {
            this->vertexUVID = vertexUVID;
        }

        void Model::store_vertex_normal_modelspaceID(const GLint vertex_normal_modelspaceID)
        {
            this->vertex_normal_modelspaceID = vertex_normal_modelspaceID;
        }
    }
}
