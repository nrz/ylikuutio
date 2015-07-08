#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include <string>
#include <algorithm> // std::find

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

// Include matrix_transform.hpp .
#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

// Include gtc/quaternion.hpp .
#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp>
#endif

// Include gtx/quaternion.hpp .
#ifndef __GLM_GTX_QUATERNION_HPP_INCLUDED
#define __GLM_GTX_QUATERNION_HPP_INCLUDED
#include <glm/gtx/quaternion.hpp>
#endif

#include "model.hpp"
#include "globals.hpp"
#include "texture.hpp"
#include "heightmap_loader.hpp"
#include "objloader.hpp"
#include "vboindexer.hpp"
#include "controls.hpp"

namespace model
{
    // `World`, `Shader`, `Species`, `Object`.
    // `World` must be created before any `Shader`. `world_pointer` must be given to each `Shader`.
    // `Shader` must be created before any `Species`. `shader_pointer` must be given to each `Species`.
    // `Species` must be create before any `Object` of that `Species`. `species_pointer` must be given to each `Object` of the `Species`.
    //
    // Deleting a `World` also deletes all shaders, species and objects that belong the same world.
    // Deleting a `Shader` also deletes all species and objects that belong the same world.
    // Deleting a `Species` also deletes all objects that belong the same world.
    // Deleting an `Object` only deletes the object.

    // Characteristics of object type graphs:
    // 1. Each object must be an undirected graph.
    // 2. Each edge must be a link in the graph.
    // 3. The faces of each object must form a closed surface. The only exception is the terrain object, which may have borders.
    //
    // Modifying object type graphs:
    // 1. Translation of vertex does not require changes in any other nodes of the graph.
    // 2. Adding a vertex always requires changes in some other nodes of the graph.
    // 3. Deleting a vertex always requires deletion of edges from some other nodes of the graph.
    // 4. Deleting a vertex or vertices usually also requires appropriate vertex additions. These changes are called 'complex modifications'.
    //
    // Adding a vertex or several vertices:
    // 1. The new edges must be connected to the existing graph with appropriate links.
    // 2. Each new face must be a triangle.
    //
    // Deleting a vertex or several vertices:
    // 1. When a vertex or several vertices are deleted, their links must be deleted too (`Node` destructor handles this).
    // 2. If the vertex to be deleted is on the border of a [terrain] object, it can be deleted.
    // 3. If the vertices that are neighbors to the vertex to be deleted form only triangeles, the vertex can be deleted without vertex additions.
    // 4. Otherwise the vertex cannot be deleted without appropriate vertex and edge additions.
    //
    // Complex modifications:
    // 1. In complex modifications one or more vertices and edges are deleted and one or more vertices and edges are added.
    // 2. Complex modifications may also change the topology of the object (tunnels, arcs, etc.).
    // 3. If a complex modification causes splitting the object in two or more pieces, each piece becomes a separate object.
    // 4. If the splitted object is a terrain object, then the lowest vertex (any vertex with smallest y-coordinate) of each piece is searched and the
    //    y-coordinates of these are compared. The piece with the smallest y-coordinate (lowest altitude) remains terrain, other pieces become
    //    regular objects. The pieces that become regular objects will be subject to gravity the same way as any regular object.

    World::World()
    {
        // constructor.
    }

    World::~World()
    {
        // destructor.
        std::cout << "This world will be destroyed.\n";

        // destroy all shaders of this world.
        for (GLuint shader_i = 0; shader_i < this->shader_pointer_vector.size(); shader_i++)
        {
            model::Shader *shader_pointer;
            shader_pointer = static_cast<model::Shader*>(this->shader_pointer_vector[shader_i]);

            if (shader_pointer != NULL)
            {
                // call destructor of each shader.
                delete shader_pointer;
            }
        }
    }

    void World::render()
    {
        // this method renders the world by calling `render()` methods of each shader.
        for (GLuint shader_i = 0; shader_i < this->shader_pointer_vector.size(); shader_i++)
        {
            model::Shader *shader_pointer;
            shader_pointer = static_cast<model::Shader*>(this->shader_pointer_vector[shader_i]);

            if (shader_pointer != NULL)
            {
                shader_pointer->render();
            }
        }
    }

    void World::set_pointer(GLuint shaderID, void* shader_pointer)
    {
        this->shader_pointer_vector[shaderID] = shader_pointer;

        if (shader_pointer == NULL)
        {
            // OK, the pointer to be stored was NULL, then that shaderID is released to be used again.
            this->free_shaderID_queue.push(shaderID);

            if (shaderID == this->shader_pointer_vector.size() - 1)
            {
                // OK, this is the biggest shaderID of all shaderID's of this world.
                // We can reduce the size of the shader pointer vector at least by 1.
                while ((!shader_pointer_vector.empty()) && (shader_pointer_vector.back() == NULL))
                {
                    // Reduce the size of shader pointer vector by 1.
                    shader_pointer_vector.pop_back();
                }
            }
        }
    }

    void* World::get_pointer(GLuint shaderID)
    {
        return this->shader_pointer_vector[shaderID];
    }

    GLuint World::get_shaderID()
    {
        GLuint shaderID;

        while (!this->free_shaderID_queue.empty())
        {
            // return the first (oldest) free shaderID.
            shaderID = this->free_shaderID_queue.front();
            this->free_shaderID_queue.pop();

            // check that the shader index does not exceed current shader pointer vector.
            if (shaderID < this->shader_pointer_vector.size())
            {
                // OK, it does not exceed current shader pointer vector.
                return shaderID;
            }
        }

        // OK, the queue is empty.
        // A new shader index must be created.
        shaderID = this->shader_pointer_vector.size();

        // shader pointer vector must also be extended with an appropriate NULL pointer.
        this->shader_pointer_vector.push_back(NULL);

        return shaderID;
    }

    Shader::Shader(ShaderStruct shader_struct)
    {
        // constructor.

        this->vertex_shader        = shader_struct.vertex_shader;
        this->fragment_shader      = shader_struct.fragment_shader;

        this->char_vertex_shader   = this->vertex_shader.c_str();
        this->char_fragment_shader = this->fragment_shader.c_str();
        this->world_pointer        = static_cast<model::World*>(shader_struct.world_pointer);

        // get shaderID from the World.
        this->shaderID = this->world_pointer->get_shaderID();

        // set pointer to this shader.
        this->world_pointer->set_pointer(this->shaderID, this);

        // Create and compile our GLSL program from the shaders.
        this->programID = LoadShaders(this->char_vertex_shader, this->char_fragment_shader);
    }

    Shader::~Shader()
    {
        // destructor.
        std::cout << "Shader with shaderID " << this->shaderID << " will be destroyed.\n";

        // destroy all species of this shader.
        for (GLuint species_i = 0; species_i < this->species_pointer_vector.size(); species_i++)
        {
            model::Species *species_pointer;
            species_pointer = static_cast<model::Species*>(this->species_pointer_vector[species_i]);

            if (species_pointer != NULL)
            {
                // call destructor of each species.
                delete species_pointer;
            }
        }
        glDeleteProgram(this->programID);
    }

    void Shader::render()
    {
        // this method renders the shader by calling `render()` methods of each species.
        for (GLuint species_i = 0; species_i < this->species_pointer_vector.size(); species_i++)
        {
            model::Species *species_pointer;
            species_pointer = static_cast<model::Species*>(this->species_pointer_vector[species_i]);

            if (species_pointer != NULL)
            {
                species_pointer->render();
            }
        }
    }

    void Shader::set_pointer(GLuint speciesID, void* species_pointer)
    {
        this->species_pointer_vector[speciesID] = species_pointer;

        if (species_pointer == NULL)
        {
            // OK, the pointer to be stored was NULL, then that speciesID is released to be used again.
            this->free_speciesID_queue.push(speciesID);

            if (speciesID == this->species_pointer_vector.size() - 1)
            {
                // OK, this is the biggest speciesID of all speciesID's of this shader.
                // We can reduce the size of the species pointer vector at least by 1.
                while ((!species_pointer_vector.empty()) && (species_pointer_vector.back() == NULL))
                {
                    // Reduce the size of species pointer vector by 1.
                    species_pointer_vector.pop_back();
                }
            }
        }
    }

    void* Shader::get_pointer(GLuint speciesID)
    {
        return this->species_pointer_vector[speciesID];
    }

    GLuint Shader::get_speciesID()
    {
        GLuint speciesID;

        while (!this->free_speciesID_queue.empty())
        {
            // return the first (oldest) free speciesID.
            speciesID = this->free_speciesID_queue.front();
            this->free_speciesID_queue.pop();

            // check that the species index does not exceed current species pointer vector.
            if (speciesID < this->species_pointer_vector.size())
            {
                // OK, it does not exceed current species pointer vector.
                return speciesID;
            }
        }

        // OK, the queue is empty.
        // A new species index must be created.
        speciesID = this->species_pointer_vector.size();

        // species pointer vector must also be extended with an appropriate NULL pointer.
        this->species_pointer_vector.push_back(NULL);

        return speciesID;
    }

    void Shader::switch_to_new_world(model::World *new_world_pointer)
    {
        // set pointer to this shader to NULL.
        this->world_pointer->set_pointer(this->shaderID, NULL);

        this->world_pointer = new_world_pointer;

        // get shaderID from the World.
        this->shaderID = this->world_pointer->get_shaderID();
    }

    Graph::Graph()
    {
        // constructor.
    }

    void Graph::set_pointer(GLuint nodeID, void* node_pointer)
    {
        this->node_pointer_vector[nodeID] = node_pointer;

        if (node_pointer == NULL)
        {
            // OK, the pointer to be stored was NULL, then that nodeID is released to be used again.
            this->free_nodeID_queue.push(nodeID);

            if (nodeID == this->node_pointer_vector.size() - 1)
            {
                // OK, this is the biggest nodeID of all nodeID's of this graph.
                // We can reduce the size of the node pointer vector at least by 1.
                while ((!node_pointer_vector.empty()) && (node_pointer_vector.back() == NULL))
                {
                    // Reduce the size of node pointer vector by 1.
                    node_pointer_vector.pop_back();
                }
            }
        }
    }

    void* Graph::get_pointer(GLuint nodeID)
    {
        return this->node_pointer_vector[nodeID];
    }

    GLuint Graph::get_nodeID()
    {
        GLuint nodeID;

        while (!this->free_nodeID_queue.empty())
        {
            // return the first (oldest) free nodeID.
            nodeID = this->free_nodeID_queue.front();
            this->free_nodeID_queue.pop();

            // check that the node index does not exceed current node pointer vector.
            if (nodeID < this->node_pointer_vector.size())
            {
                // OK, it does not exceed current node pointer vector.
                return nodeID;
            }
        }

        // OK, the queue is empty.
        // A new node index must be created.
        nodeID = this->node_pointer_vector.size();

        // node pointer vector must also be extended with an appropriate NULL pointer.
        this->node_pointer_vector.push_back(NULL);

        return nodeID;
    }

    Graph::~Graph()
    {
        // destructor.

        // destroy all nodes of this graph.
        for (GLuint node_i = 0; node_i < this->node_pointer_vector.size(); node_i++)
        {
            model::Node *node_pointer;
            node_pointer = static_cast<model::Node*>(this->node_pointer_vector[node_i]);

            if (node_pointer != NULL)
            {
                // call destructor of each node.
                delete node_pointer;
            }
        }
    }

    Node::Node(NodeStruct node_struct)
    {
        // constructor.
        this->nodeID = node_struct.nodeID;
        this->coordinate_vector = node_struct.coordinate_vector;
        this->graph_pointer = static_cast<model::Graph*>(node_struct.graph_pointer);

        // set pointer to this node.
        this->graph_pointer->set_pointer(this->nodeID, this);

        // create all unidirectional links from this node to neighbor nodes.
        for (GLuint link_i = 0; link_i < this->neighbor_nodeIDs.size(); link_i++)
        {
            this->create_unidirectional_link(this->neighbor_nodeIDs[link_i]);
        }
    }

    Node::~Node()
    {
        // destructor.

        // delete all bidirectional links.
        for (GLuint link_i = 0; link_i < this->neighbor_nodeIDs.size(); link_i++)
        {
            this->delete_bidirectional_link(this->neighbor_nodeIDs[link_i]);
        }

        // set pointer to this node to NULL.
        this->graph_pointer->set_pointer(this->nodeID, NULL);
    }

    void Node::create_unidirectional_link(GLuint nodeID)
    {
        // this method creates an unidirectional link.

        // check that a link not exist already.
        if (std::find(this->neighbor_nodeIDs.begin(), this->neighbor_nodeIDs.end(), nodeID) == this->neighbor_nodeIDs.end())
        {
            // OK, it does not exist yet,
            // so create a link from this node to destination node.
            this->neighbor_nodeIDs.push_back(nodeID);
        }
        // an alternative: create a link from this node to destination node without checking its prior existence.
        // this->neighbor_nodeIDs.push_back(nodeID);
    }

    void Node::create_bidirectional_link(GLuint nodeID)
    {
        // create a link from this node to destination node.
        this->create_unidirectional_link(nodeID);

        // create a link from destination node to this node.
        static_cast<model::Node*>(this->graph_pointer->get_pointer(nodeID))->create_unidirectional_link(this->nodeID);
    }

    void Node::delete_unidirectional_link(GLuint nodeID)
    {
        // this method deletes an unidirectional link.
        this->neighbor_nodeIDs.erase(std::remove(this->neighbor_nodeIDs.begin(), this->neighbor_nodeIDs.end(), nodeID), this->neighbor_nodeIDs.end());
    }

    void Node::delete_bidirectional_link(GLuint nodeID)
    {
        // this method deletes a bidirectional link.
        this->delete_unidirectional_link(nodeID);

        // delete a link from destination node to this node.
        static_cast<model::Node*>(this->graph_pointer->get_pointer(nodeID))->delete_unidirectional_link(this->nodeID);
    }

    // Transfering node to a new graph is similar to `switch_to_new_world`, `switch_to_new_shader`, `switch_to_new_species`,
    // but there is one important difference:
    // nodes have references (links) to other nodes, whereas shaders, species, and objects do not.
    // The easiest way would be to request new `nodeID` for each new node, and this will be probably be implemented first.
    // Another option would be to change only those `nodeID`'s for which there would be duplicate `nodeID`'s.
    // However, that may consume huge amounts of memory if a big object (eg. a terrain object) is split into several smaller objects.
    // Therefore a `nodeID_bias` needs to be defined for each graph, it will be used for reindexing.
    // If `Graph::get_nodeID` would cause overflow (2^32 = 4 294 967 295), it will instead give smallest current `nodeID` of the graph and decrement `nodeID_bias` by 1.

    void Node::transfer_to_new_graph(model::Graph *new_graph_pointer)
    {
        // set pointer to this node to NULL.
        this->graph_pointer->set_pointer(this->nodeID, NULL);

        // set new graph pointer.
        this->graph_pointer = new_graph_pointer;

        // request a new nodeID.
        this->nodeID = this->graph_pointer->get_nodeID();

        // set pointer to this node.
        this->graph_pointer->set_pointer(this->nodeID, this);
    }

    Species::Species(SpeciesStruct species_struct)
    {
        // constructor.
        this->model_file_format   = species_struct.model_file_format;
        this->model_filename      = species_struct.model_filename;
        this->texture_file_format = species_struct.texture_file_format;
        this->texture_filename    = species_struct.texture_filename;
        this->color_channel       = species_struct.color_channel;
        this->lightPos            = species_struct.lightPos;
        this->shader_pointer      = static_cast<model::Shader*>(species_struct.shader_pointer);

        this->char_model_file_format   = this->model_file_format.c_str();
        this->char_model_filename      = this->model_filename.c_str();
        this->char_texture_file_format = this->texture_file_format.c_str();
        this->char_texture_filename    = this->texture_filename.c_str();
        this->char_color_channel       = this->color_channel.c_str();

        // get speciesID from the Shader.
        this->speciesID = this->shader_pointer->get_speciesID();

        // set pointer to this species.
        this->shader_pointer->set_pointer(this->speciesID, this);

        // Get a handle for our "MVP" uniform.
        this->MatrixID = glGetUniformLocation(this->shader_pointer->programID, "MVP");
        this->ViewMatrixID = glGetUniformLocation(this->shader_pointer->programID, "V");
        this->ModelMatrixID = glGetUniformLocation(this->shader_pointer->programID, "M");

        // Get a handle for our buffers.
        this->vertexPosition_modelspaceID = glGetAttribLocation(this->shader_pointer->programID, "vertexPosition_modelspace");
        this->vertexUVID = glGetAttribLocation(this->shader_pointer->programID, "vertexUV");
        this->vertexNormal_modelspaceID = glGetAttribLocation(this->shader_pointer->programID, "vertexNormal_modelspace");

        // Load the texture.
        if ((strcmp(this->char_texture_file_format, "bmp") == 0) || (strcmp(this->char_texture_file_format, "BMP") == 0))
        {
            this->texture = texture::load_BMP_texture(this->char_texture_filename);
        }
        else if ((strcmp(this->char_texture_file_format, "dds") == 0) || (strcmp(this->char_texture_file_format, "DDS") == 0))
        {
            this->texture = texture::load_DDS_texture(this->char_texture_filename);
        }
        else
        {
            std::cerr << "no texture was loaded!\n";
            std::cerr << "texture file format: " << this->texture_file_format << "\n";
        }

        // Get a handle for our "myTextureSampler" uniform.
        this->textureID = glGetUniformLocation(this->shader_pointer->programID, "myTextureSampler");

        bool model_loading_result;

        if ((strcmp(this->char_model_file_format, "obj") == 0) || (strcmp(this->char_model_file_format, "OBJ") == 0))
        {
            model_loading_result = model::load_OBJ(this->char_model_filename, this->vertices, this->UVs, this->normals);
        }
        else if (strcmp(this->char_model_file_format, "SRTM") == 0)
        {
            double current_latitude_in_degrees;
            double current_longitude_in_degrees;
            current_latitude_in_degrees = -16.50f;
            current_longitude_in_degrees = -68.15f;

            model_loading_result = model::load_SRTM_world(
                    this->model_filename,
                    current_latitude_in_degrees,
                    current_longitude_in_degrees,
                    this->vertices,
                    this->UVs,
                    this->normals);
        }
        else if ((strcmp(this->char_model_file_format, "bmp") == 0) || (strcmp(this->char_model_file_format, "BMP") == 0))
        {
            model_loading_result = model::load_BMP_world(this->model_filename, this->vertices, this->UVs, this->normals, this->color_channel);
        }
        else
        {
            std::cerr << "no model was loaded!\n";
            std::cerr << "model file format: " << this->model_file_format << "\n";
        }

        model::indexVBO(this->vertices, this->UVs, this->normals, this->indices, this->indexed_vertices, this->indexed_UVs, this->indexed_normals);

        // Load it into a VBO.
        glGenBuffers(1, &this->vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, this->indexed_vertices.size() * sizeof(glm::vec3), &this->indexed_vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, this->indexed_UVs.size() * sizeof(glm::vec2), &this->indexed_UVs[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->normalbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->normalbuffer);
        glBufferData(GL_ARRAY_BUFFER, this->indexed_normals.size() * sizeof(glm::vec3), &this->indexed_normals[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0] , GL_STATIC_DRAW);

        // Get a handle for our "LightPosition" uniform.
        glUseProgram(this->shader_pointer->programID);
        this->lightID = glGetUniformLocation(this->shader_pointer->programID, "LightPosition_worldspace");

        // Compute the graph of this object type.
    }

    Species::~Species()
    {
        // destructor.
        std::cout << "Species with speciesID " << this->speciesID << " will be destroyed.\n";

        // destroy all objects of this species.
        for (GLuint object_i = 0; object_i < this->object_pointer_vector.size(); object_i++)
        {
            model::Object *object_pointer;
            object_pointer = static_cast<model::Object*>(this->object_pointer_vector[object_i]);

            if (object_pointer != NULL)
            {
                // call destructor of each object.
                delete object_pointer;
            }
        }

        // Cleanup VBO, shader and texture.
        glDeleteBuffers(1, &this->vertexbuffer);
        glDeleteBuffers(1, &this->uvbuffer);
        glDeleteBuffers(1, &this->normalbuffer);
        glDeleteBuffers(1, &this->elementbuffer);
        glDeleteTextures(1, &this->texture);

        // set pointer to this species to NULL.
        this->shader_pointer->set_pointer(this->speciesID, NULL);
    }

    void Species::render()
    {
        // Compute the MVP matrix from keyboard and mouse input.
        controls::computeMatricesFromInputs();
        this->ProjectionMatrix = controls::getProjectionMatrix();
        this->ViewMatrix = controls::getViewMatrix();

        // [re]bind `programID` shader.
        glUseProgram(this->shader_pointer->programID);

        glUniform3f(this->lightID, this->lightPos.x, this->lightPos.y, this->lightPos.z);
        glUniformMatrix4fv(this->ViewMatrixID, 1, GL_FALSE, &this->ViewMatrix[0][0]); // This one doesn't change between objects, so this can be done once for all objects that use "programID"

        // Bind our texture in Texture Unit 0.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        // Set our "myTextureSampler" sampler to user Texture Unit 0.
        glUniform1i(this->textureID, 0);

        // 1st attribute buffer : vertices.
        glEnableVertexAttribArray(this->vertexPosition_modelspaceID);

        // 2nd attribute buffer : UVs.
        glEnableVertexAttribArray(this->vertexUVID);

        // 3rd attribute buffer : normals.
        glEnableVertexAttribArray(this->vertexNormal_modelspaceID);

        // this method renders the species by calling `render()` methods of each object.
        for (GLuint object_i = 0; object_i < this->object_pointer_vector.size(); object_i++)
        {
            model::Object *object_pointer;
            object_pointer = static_cast<model::Object*>(this->object_pointer_vector[object_i]);

            if (object_pointer != NULL)
            {
                object_pointer->render();
            }
        }
    }

    void Species::set_pointer(GLuint objectID, void* object_pointer)
    {
        this->object_pointer_vector[objectID] = object_pointer;

        if (object_pointer == NULL)
        {
            // OK, the pointer to be stored was NULL, then that objectID is released to be used again.
            this->free_objectID_queue.push(objectID);

            if (objectID == this->object_pointer_vector.size() - 1)
            {
                // OK, this is the biggest objectID of all objectID's of this species.
                // We can reduce the size of the object pointer vector at least by 1.
                while ((!object_pointer_vector.empty()) && (object_pointer_vector.back() == NULL))
                {
                    // Reduce the size of object pointer vector by 1.
                    object_pointer_vector.pop_back();
                }
            }
        }
    }

    void* Species::get_pointer(GLuint objectID)
    {
        return this->object_pointer_vector[objectID];
    }

    GLuint Species::get_objectID()
    {
        GLuint objectID;

        while (!this->free_objectID_queue.empty())
        {
            // return the first (oldest) free objectID.
            objectID = this->free_objectID_queue.front();
            this->free_objectID_queue.pop();

            // check that the object index does not exceed current object pointer vector.
            if (objectID < this->object_pointer_vector.size())
            {
                // OK, it does not exceed current object pointer vector.
                return objectID;
            }
        }

        // OK, the queue is empty.
        // A new object index must be created.
        objectID = this->object_pointer_vector.size();

        // object pointer vector must also be extended with an appropriate NULL pointer.
        this->object_pointer_vector.push_back(NULL);

        return objectID;
    }

    void Species::switch_to_new_shader(model::Shader *new_shader_pointer)
    {
        // set pointer to this species to NULL.
        this->shader_pointer->set_pointer(this->speciesID, NULL);

        this->shader_pointer = new_shader_pointer;

        // get speciesID from the Shader.
        this->speciesID = this->shader_pointer->get_speciesID();
    }

    Object::Object(ObjectStruct object_struct)
    {
        // constructor.
        this->coordinate_vector = object_struct.coordinate_vector;
        this->rotate_angle      = object_struct.rotate_angle;
        this->rotate_vector     = object_struct.rotate_vector;
        this->translate_vector  = object_struct.translate_vector;
        this->has_entered       = false;
        this->species_pointer   = static_cast<model::Species*>(object_struct.species_pointer);

        // get objectID from the Species.
        this->objectID = this->species_pointer->get_objectID();

        // set pointer to this object.
        this->species_pointer->set_pointer(this->objectID, this);

        bool model_loading_result = false;
    }

    Object::~Object()
    {
        // destructor.
        std::cout << "Object with objectID " << this->objectID << " will be destroyed.\n";

        // set pointer to this object to NULL.
        this->species_pointer->set_pointer(this->objectID, NULL);
    }

    void Object::render()
    {
        if (!this->has_entered)
        {
            this->model_matrix = glm::translate(glm::mat4(1.0f), this->coordinate_vector);

            // store the new coordinates to be used in the next update.
            this->coordinate_vector = glm::vec3(model_matrix[0][0], model_matrix[1][1], model_matrix[2][2]);
            this->has_entered = true;
        }
        else
        {
            // create `rotation_matrix` using quaternions.
            glm::quat my_quaternion;
            my_quaternion = glm::quat(DEGREES_TO_RADIANS(this->rotate_vector));
            glm::mat4 rotation_matrix = glm::toMat4(my_quaternion);

            // rotate.
            // this->model_matrix = rotation_matrix * this->model_matrix;
            if (this->rotate_vector != glm::vec3(0.0f, 0.0f, 0.0f))
            {
                this->model_matrix = glm::rotate(this->model_matrix, this->rotate_angle, this->rotate_vector);
            }

            this->model_matrix = glm::translate(this->model_matrix, this->translate_vector);
            this->coordinate_vector = glm::vec3(model_matrix[0][0], model_matrix[1][1], model_matrix[2][2]);
        }

        this->MVP_matrix = this->species_pointer->ProjectionMatrix * this->species_pointer->ViewMatrix * this->model_matrix;

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform.
        glUniformMatrix4fv(this->species_pointer->MatrixID, 1, GL_FALSE, &this->MVP_matrix[0][0]);
        glUniformMatrix4fv(this->species_pointer->ModelMatrixID, 1, GL_FALSE, &this->model_matrix[0][0]);

        // 1st attribute buffer : vertices.
        glBindBuffer(GL_ARRAY_BUFFER, this->species_pointer->vertexbuffer);
        glVertexAttribPointer(
                this->species_pointer->vertexPosition_modelspaceID, // The attribute we want to configure
                3,                                                  // size
                GL_FLOAT,                                           // type
                GL_FALSE,                                           // normalized?
                0,                                                  // stride
                (void*) 0                                           // array buffer offset
                );

        // 2nd attribute buffer : UVs.
        glBindBuffer(GL_ARRAY_BUFFER, this->species_pointer->uvbuffer);
        glVertexAttribPointer(
                this->species_pointer->vertexUVID, // The attribute we want to configure
                2,                                 // size : U+V => 2
                GL_FLOAT,                          // type
                GL_FALSE,                          // normalized?
                0,                                 // stride
                (void*) 0                          // array buffer offset
                );

        // 3rd attribute buffer : normals.
        glBindBuffer(GL_ARRAY_BUFFER, this->species_pointer->normalbuffer);
        glVertexAttribPointer(
                this->species_pointer->vertexNormal_modelspaceID, // The attribute we want to configure
                3,                                                // size
                GL_FLOAT,                                         // type
                GL_FALSE,                                         // normalized?
                0,                                                // stride
                (void*) 0                                         // array buffer offset
                );

        // Index buffer.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->species_pointer->elementbuffer);

        // Draw the triangles!
        glDrawElements(
                GL_TRIANGLES,                          // mode
                this->species_pointer->indices.size(), // count
                GL_UNSIGNED_INT,                       // type
                (void*) 0                              // element array buffer offset
                );
    }

    void Object::switch_to_new_species(model::Species *new_species_pointer)
    {
        // set pointer to this object to NULL.
        this->species_pointer->set_pointer(this->objectID, NULL);

        this->species_pointer = new_species_pointer;

        // get objectID from the Species.
        this->objectID = this->species_pointer->get_objectID();
    }
}
