#include "model.hpp"
#include "object.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;

        void Model::bind(yli::ontology::Object* const object)
        {
            // get `childID` from `Model` and set pointer to `object`.
            hierarchy::bind_child_to_parent<yli::ontology::Object*>(
                    object,
                    this->object_pointer_vector,
                    this->free_objectID_queue,
                    &this->number_of_objects);
        }

        void Model::unbind(const int32_t childID)
        {
            yli::ontology::Object* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(
                    childID,
                    dummy_child_pointer,
                    this->object_pointer_vector,
                    this->free_objectID_queue,
                    &this->number_of_objects);
        }

        Model::~Model()
        {
            // destructor.
        }

        int32_t Model::get_number_of_children() const
        {
            return this->number_of_objects;
        }

        int32_t Model::get_number_of_descendants() const
        {
            return -1;
        }

        const std::vector<glm::vec3>& Model::get_vertices() const
        {
            return this->vertices;
        }

        const std::vector<uint32_t>& Model::get_indices() const
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
