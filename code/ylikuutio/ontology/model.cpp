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

namespace ontology
{
    class Universe;

    Model::~Model()
    {
        // destructor.
    }

    void Model::bind(ontology::Object* object)
    {
        // get `childID` from `Model` and set pointer to `object`.
        hierarchy::bind_child_to_parent<ontology::Object*>(
                object,
                this->object_pointer_vector,
                this->free_objectID_queue,
                &this->number_of_objects);
    }

    void Model::unbind(int32_t childID)
    {
        ontology::Object* dummy_child_pointer = nullptr;
        hierarchy::set_child_pointer(
                childID,
                dummy_child_pointer,
                this->object_pointer_vector,
                this->free_objectID_queue,
                &this->number_of_objects);
    }

    int32_t Model::get_number_of_children() const
    {
        return this->number_of_objects;
    }

    int32_t Model::get_number_of_descendants() const
    {
        return -1;
    }

    std::vector<glm::vec3> Model::get_vertices() const
    {
        return this->vertices;
    }

    std::vector<uint32_t> Model::get_indices() const
    {
        return this->indices;
    }

    GLuint Model::get_vertexPosition_modelspaceID()
    {
        return this->vertexPosition_modelspaceID;
    }

    GLuint Model::get_vertexUVID()
    {
        return this->vertexUVID;
    }

    GLuint Model::get_vertexNormal_modelspaceID()
    {
        return this->vertexNormal_modelspaceID;
    }

    GLuint Model::get_vertexbuffer()
    {
        return this->vertexbuffer;
    }

    GLuint Model::get_uvbuffer()
    {
        return this->uvbuffer;
    }

    GLuint Model::get_normalbuffer()
    {
        return this->normalbuffer;
    }

    GLuint Model::get_elementbuffer()
    {
        return this->elementbuffer;
    }

    void Model::store_vertexPosition_modelspaceID(GLuint vertexPosition_modelspaceID)
    {
        this->vertexPosition_modelspaceID = vertexPosition_modelspaceID;
    }

    void Model::store_vertexUVID(GLuint vertexUVID)
    {
        this->vertexUVID = vertexUVID;
    }

    void Model::store_vertexNormal_modelspaceID(GLuint vertexNormal_modelspaceID)
    {
        this->vertexNormal_modelspaceID = vertexNormal_modelspaceID;
    }
}
