#include "species.hpp"
#include "objloader.hpp"
#include "heightmap_loader.hpp"
#include "vboindexer.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "object.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace ontology
{
    void Species::bind_to_parent()
    {
        hierarchy::bind_child_to_parent<ontology::Species*>(this, this->parent_pointer->species_pointer_vector, this->parent_pointer->free_speciesID_queue);
    }

    Species::Species(SpeciesStruct species_struct)
    {
        // constructor.
        this->is_world          = species_struct.is_world;
        this->model_file_format = species_struct.model_file_format;
        this->model_filename    = species_struct.model_filename;
        this->color_channel     = species_struct.color_channel;
        this->light_position    = species_struct.light_position;
        this->parent_pointer    = species_struct.parent_pointer;
        this->triangulation_type = species_struct.triangulation_type;

        this->char_model_file_format = this->model_file_format.c_str();
        this->char_model_filename    = this->model_filename.c_str();

        // get `childID` from the `Material` and set pointer to this `Species`.
        this->bind_to_parent();

        // Get a handle for our buffers.
        this->vertexPosition_modelspaceID = glGetAttribLocation(this->parent_pointer->parent_pointer->programID, "vertexPosition_modelspace");
        this->vertexUVID = glGetAttribLocation(this->parent_pointer->parent_pointer->programID, "vertexUV");
        this->vertexNormal_modelspaceID = glGetAttribLocation(this->parent_pointer->parent_pointer->programID, "vertexNormal_modelspace");

        bool model_loading_result;

        if ((std::strcmp(this->char_model_file_format, "obj") == 0) || (std::strcmp(this->char_model_file_format, "OBJ") == 0))
        {
            model_loading_result = ontology::load_OBJ(this->char_model_filename, this->vertices, this->UVs, this->normals);
        }
        else if (std::strcmp(this->char_model_file_format, "SRTM") == 0)
        {
            double current_latitude_in_degrees;
            double current_longitude_in_degrees;
            current_latitude_in_degrees = -16.50f;
            current_longitude_in_degrees = -68.15f;

            model_loading_result = ontology::load_SRTM_world(
                    this->model_filename,
                    current_latitude_in_degrees,
                    current_longitude_in_degrees,
                    this->vertices,
                    this->UVs,
                    this->normals,
                    this->triangulation_type);
        }
        else if ((std::strcmp(this->char_model_file_format, "bmp") == 0) || (std::strcmp(this->char_model_file_format, "BMP") == 0))
        {
            model_loading_result = ontology::load_BMP_world(
                    this->model_filename,
                    this->vertices,
                    this->UVs,
                    this->normals,
                    this->image_width,
                    this->image_height,
                    this->color_channel,
                    this->triangulation_type);
        }
        else
        {
            std::cerr << "no model was loaded!\n";
            std::cerr << "model file format: " << this->model_file_format << "\n";
        }

        // Fill the index buffer.
        ontology::indexVBO(this->vertices, this->UVs, this->normals, this->indices, this->indexed_vertices, this->indexed_UVs, this->indexed_normals);

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
        glUseProgram(this->parent_pointer->parent_pointer->programID);
        this->lightID = glGetUniformLocation(this->parent_pointer->parent_pointer->programID, "LightPosition_worldspace");

        if (this->is_world)
        {
            // set world species pointer so that it points to this species.
            // currently there can be only one world species (used in collision detection).
            this->parent_pointer->parent_pointer->parent_pointer->parent_pointer->set_terrain_species_pointer(this);
        }

        // TODO: Compute the graph of this object type to enable object vertex modification!
    }

    Species::~Species()
    {
        // destructor.
        std::cout << "Species with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all objects of this species.
        std::cout << "All objects of this species will be destroyed.\n";
        hierarchy::delete_children<ontology::Object*>(this->object_pointer_vector);

        // Cleanup VBO, shader and texture.
        glDeleteBuffers(1, &this->vertexbuffer);
        glDeleteBuffers(1, &this->uvbuffer);
        glDeleteBuffers(1, &this->normalbuffer);
        glDeleteBuffers(1, &this->elementbuffer);

        // set pointer to this species to nullptr.
        this->parent_pointer->set_species_pointer(this->childID, nullptr);
    }

    void Species::render()
    {
        ontology::render_species_or_glyph<ontology::Species*>(this);
    }

    void Species::set_object_pointer(uint32_t childID, ontology::Object* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->object_pointer_vector, this->free_objectID_queue);
    }

    void Species::bind_to_new_parent(ontology::Material* new_material_pointer)
    {
        hierarchy::bind_child_to_new_parent<ontology::Species*, ontology::Material*>(this, new_material_pointer, this->parent_pointer->species_pointer_vector, this->parent_pointer->free_speciesID_queue);
    }
}
