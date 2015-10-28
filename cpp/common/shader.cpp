#include "shader.hpp"
#include "world.hpp"
#include "material.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace model
{
    void Shader::bind_to_parent()
    {
        model::bind_child_to_parent<model::Shader*>(this, this->parent_pointer->shader_pointer_vector, this->parent_pointer->free_shaderID_queue);
    }

    Shader::Shader(ShaderStruct shader_struct)
    {
        // constructor.

        this->vertex_shader        = shader_struct.vertex_shader;
        this->fragment_shader      = shader_struct.fragment_shader;

        this->char_vertex_shader   = this->vertex_shader.c_str();
        this->char_fragment_shader = this->fragment_shader.c_str();
        this->parent_pointer       = shader_struct.parent_pointer;

        // get childID from the World and set pointer to this Shader.
        this->bind_to_parent();

        // Create and compile our GLSL program from the shaders.
        this->programID = LoadShaders(this->char_vertex_shader, this->char_fragment_shader);

        // Get a handle for our "MVP" uniform.
        this->MatrixID = glGetUniformLocation(this->programID, "MVP");
        this->ViewMatrixID = glGetUniformLocation(this->programID, "V");
        this->ModelMatrixID = glGetUniformLocation(this->programID, "M");
    }

    Shader::~Shader()
    {
        // destructor.
        std::cout << "Shader with childID " << this->childID << " will be destroyed.\n";

        // destroy all textures of this shader.
        std::cout << "All textures of this shader will be destroyed.\n";
        model::delete_children<model::Texture*>(this->texture_pointer_vector);

        // set pointer to this shader to NULL.
        this->parent_pointer->set_shader_pointer(this->childID, NULL);

        glDeleteProgram(this->programID);
    }

    void Shader::render()
    {
        // [re]bind `programID` shader.
        glUseProgram(this->programID);

        glUniformMatrix4fv(this->ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]); // This one doesn't change between objects, so this can be done once for all objects that use "programID"

        // render Shader by calling `render()` function of each Texture.
        model::render_children<model::Texture*>(this->texture_pointer_vector);
    }

    void Shader::set_texture_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->texture_pointer_vector, this->free_textureID_queue);
    }

    void Shader::bind_to_new_parent(model::World *new_world_pointer)
    {
        model::bind_child_to_new_parent<model::Shader*, model::World*>(this, new_world_pointer, this->parent_pointer->shader_pointer_vector, this->parent_pointer->free_shaderID_queue);
    }

    void Shader::set_terrain_species_pointer(void* terrain_species_pointer)
    {
        this->terrain_species_pointer = terrain_species_pointer;
        this->parent_pointer->set_terrain_species_pointer(this->terrain_species_pointer);
    }
}
