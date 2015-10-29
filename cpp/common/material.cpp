#include "material.hpp"
#include "texture_loader.hpp"
#include "font.hpp"
#include "species.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace model
{
    void Material::bind_to_parent()
    {
        model::bind_child_to_parent<model::Material*>(this, this->parent_pointer->texture_pointer_vector, this->parent_pointer->free_textureID_queue);
    }

    Material::Material(MaterialStruct material_struct)
    {
        // constructor.
        this->parent_pointer = material_struct.parent_pointer;

        this->texture_file_format = material_struct.texture_file_format;
        this->texture_filename    = material_struct.texture_filename;

        this->char_texture_file_format = this->texture_file_format.c_str();
        this->char_texture_filename    = this->texture_filename.c_str();

        // get childID from the Shader and set pointer to this Material.
        this->bind_to_parent();

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
        this->openGL_textureID = glGetUniformLocation(this->parent_pointer->programID, "myTextureSampler");
    }

    Material::~Material()
    {
        // destructor.
        std::cout << "Material with childID " << this->childID << " will be destroyed.\n";

        // destroy all species of this texture.
        std::cout << "All species of this texture will be destroyed.\n";
        model::delete_children<model::Species*>(this->species_pointer_vector);

        // destroy all fonts of this texture.
        std::cout << "All fonts of this texture will be destroyed.\n";
        model::delete_children<model::Font*>(this->font_pointer_vector);

        glDeleteTextures(1, &this->texture);

        // set pointer to this texture to NULL.
        this->parent_pointer->set_texture_pointer(this->childID, NULL);
    }

    void Material::render()
    {
        // Bind our texture in Material Unit 0.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        // Set our "myTextureSampler" sampler to user Material Unit 0.
        glUniform1i(this->openGL_textureID, 0);

        // render Material by calling `render()` function of each Species and of each Font.
        model::render_children<model::Species*>(this->species_pointer_vector);
        model::render_children<model::Font*>(this->font_pointer_vector);
    }

    void Material::set_species_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->species_pointer_vector, this->free_speciesID_queue);
    }

    void Material::bind_to_new_parent(model::Shader *new_shader_pointer)
    {
        model::bind_child_to_new_parent<model::Material*, model::Shader*>(this, new_shader_pointer, this->parent_pointer->texture_pointer_vector, this->parent_pointer->free_textureID_queue);
    }

    void Material::set_terrain_species_pointer(void* terrain_species_pointer)
    {
        this->terrain_species_pointer = terrain_species_pointer;
        this->parent_pointer->set_terrain_species_pointer(this->terrain_species_pointer);
    }
}
