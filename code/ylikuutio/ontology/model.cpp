#include "model.hpp"
#include "object.hpp"
#include "family_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

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

        const std::vector<GLuint>& Model::get_indices() const
        {
            return this->indices;
        }

        GLuint Model::get_vertex_position_modelspaceID() const
        {
            return this->vertex_position_modelspaceID;
        }

        GLuint Model::get_vertexUVID() const
        {
            return this->vertexUVID;
        }

        GLuint Model::get_vertex_normal_modelspaceID() const
        {
            return this->vertex_normal_modelspaceID;
        }

        GLuint Model::get_vertexbuffer() const
        {
            return this->vertexbuffer;
        }

        GLuint Model::get_uvbuffer() const
        {
            return this->uvbuffer;
        }

        GLuint Model::get_normalbuffer() const
        {
            return this->normalbuffer;
        }

        GLuint Model::get_elementbuffer() const
        {
            return this->elementbuffer;
        }

        void Model::store_vertex_position_modelspaceID(const GLuint vertex_position_modelspaceID)
        {
            this->vertex_position_modelspaceID = vertex_position_modelspaceID;
        }

        void Model::store_vertexUVID(const GLuint vertexUVID)
        {
            this->vertexUVID = vertexUVID;
        }

        void Model::store_vertex_normal_modelspaceID(const GLuint vertex_normal_modelspaceID)
        {
            this->vertex_normal_modelspaceID = vertex_normal_modelspaceID;
        }
    }
}
