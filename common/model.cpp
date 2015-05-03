#include <string>

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

#include "model.hpp"
#include "globals.hpp"
#include "texture.hpp"
#include "bmploader.hpp"
#include "objloader.hpp"
#include "vboindexer.hpp"
#include "controls.hpp"

namespace model
{
    Species::Species(SpeciesStruct species_struct)
    {
        // constructor.
        this->model_file_format   = species_struct.model_file_format;
        this->model_filename      = species_struct.model_filename;
        this->texture_file_format = species_struct.texture_file_format;
        this->texture_filename    = species_struct.texture_filename;
        this->color_channel       = species_struct.color_channel;
        this->vertex_shader       = species_struct.vertex_shader;
        this->fragment_shader     = species_struct.fragment_shader;
        this->lightPos            = species_struct.lightPos;

        this->char_model_file_format   = this->model_file_format.c_str();
        this->char_model_filename      = this->model_filename.c_str();
        this->char_texture_file_format = this->texture_file_format.c_str();
        this->char_texture_filename    = this->texture_filename.c_str();
        this->char_color_channel       = this->color_channel.c_str();

        this->char_vertex_shader       = this->vertex_shader.c_str();
        this->char_fragment_shader     = this->fragment_shader.c_str();

        // Create and compile our GLSL program from the shaders.
        this->programID = LoadShaders(this->char_vertex_shader, this->char_fragment_shader);

        // Get a handle for our "MVP" uniform.
        this->MatrixID = glGetUniformLocation(this->programID, "MVP");
        this->ViewMatrixID = glGetUniformLocation(this->programID, "V");
        this->ModelMatrixID = glGetUniformLocation(this->programID, "M");

        // Get a handle for our buffers.
        this->vertexPosition_modelspaceID = glGetAttribLocation(this->programID, "vertexPosition_modelspace");
        this->vertexUVID = glGetAttribLocation(this->programID, "vertexUV");
        this->vertexNormal_modelspaceID = glGetAttribLocation(this->programID, "vertexNormal_modelspace");

        // Load the texture.
        if ((strcmp(this->char_texture_file_format, "bmp") == 0) || (strcmp(this->char_texture_file_format, "BMP") == 0))
        {
            this->texture = texture::loadBMP_custom(this->char_texture_filename);
        }
        else if ((strcmp(this->char_texture_file_format, "dds") == 0) || (strcmp(this->char_texture_file_format, "DDS") == 0))
        {
            this->texture = texture::loadDDS(this->char_texture_filename);
        }
        else
        {
            std::cerr << "no texture was loaded!\n";
            std::cerr << "texture file format: " << this->texture_file_format << "\n";
        }

        // Get a handle for our "myTextureSampler" uniform.
        this->textureID = glGetUniformLocation(programID, "myTextureSampler");

        bool model_loading_result;

        if ((strcmp(this->char_model_file_format, "obj") == 0) || (strcmp(this->char_model_file_format, "OBJ") == 0))
        {
            model_loading_result = model::load_OBJ(this->char_model_filename, this->vertices, this->UVs, this->normals);
        }
        else if ((strcmp(this->char_model_file_format, "bmp") == 0) || (strcmp(this->char_model_file_format, "BMP") == 0))
        {
            model_loading_result = model::load_BMP_world(this->char_model_filename, this->vertices, this->UVs, this->normals, this->color_channel);
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
        glUseProgram(this->programID);
        this->lightID = glGetUniformLocation(this->programID, "LightPosition_worldspace");
    }

    void Species::render()
    {
        // Compute the MVP matrix from keyboard and mouse input.
        controls::computeMatricesFromInputs();
        this->ProjectionMatrix = controls::getProjectionMatrix();
        this->ViewMatrix = controls::getViewMatrix();

        // [re]bind `programID` shader.
        glUseProgram(this->programID);

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
    }

    Object::Object(ObjectStruct object_struct)
    {
        // constructor.
        this->model_matrix     = object_struct.model_matrix;
        this->translate_vector = object_struct.translate_vector;
        this->species_ptr      = static_cast<model::Species*>(object_struct.species_ptr);

        bool model_loading_result = false;
    }

    void Object::render()
    {
        this->model_matrix = glm::translate(this->model_matrix, this->translate_vector);
        this->MVP_matrix = this->species_ptr->ProjectionMatrix * this->species_ptr->ViewMatrix * this->model_matrix;

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform.
        glUniformMatrix4fv(this->species_ptr->MatrixID, 1, GL_FALSE, &this->MVP_matrix[0][0]);
        glUniformMatrix4fv(this->species_ptr->ModelMatrixID, 1, GL_FALSE, &this->model_matrix[0][0]);

        // 1st attribute buffer : vertices.
        glBindBuffer(GL_ARRAY_BUFFER, this->species_ptr->vertexbuffer);
        glVertexAttribPointer(
                this->species_ptr->vertexPosition_modelspaceID, // The attribute we want to configure
                3,                                              // size
                GL_FLOAT,                                       // type
                GL_FALSE,                                       // normalized?
                0,                                              // stride
                (void*) 0                                       // array buffer offset
                );

        // 2nd attribute buffer : UVs.
        glBindBuffer(GL_ARRAY_BUFFER, this->species_ptr->uvbuffer);
        glVertexAttribPointer(
                this->species_ptr->vertexUVID, // The attribute we want to configure
                2,                             // size : U+V => 2
                GL_FLOAT,                      // type
                GL_FALSE,                      // normalized?
                0,                             // stride
                (void*) 0                      // array buffer offset
                );

        // 3rd attribute buffer : normals.
        glBindBuffer(GL_ARRAY_BUFFER, this->species_ptr->normalbuffer);
        glVertexAttribPointer(
                this->species_ptr->vertexNormal_modelspaceID, // The attribute we want to configure
                3,                                            // size
                GL_FLOAT,                                     // type
                GL_FALSE,                                     // normalized?
                0,                                            // stride
                (void*) 0                                     // array buffer offset
                );

        // Index buffer.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->species_ptr->elementbuffer);

        // Draw the triangles!
        glDrawElements(
                GL_TRIANGLES,                      // mode
                this->species_ptr->indices.size(), // count
                GL_UNSIGNED_INT,                   // type
                (void*) 0                          // element array buffer offset
                );
    }
}
