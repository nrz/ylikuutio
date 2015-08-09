#include "texture.hpp"
#include "texture_loader.hpp"
#include "font.hpp"
#include "species.hpp"

namespace model
{
    void Texture::bind_to_parent()
    {
        model::bind_child_to_parent<model::Texture*>(this, this->parent_pointer->texture_pointer_vector, this->parent_pointer->free_textureID_queue);
    }

    Texture::Texture(TextureStruct texture_struct)
    {
        // constructor.
        this->parent_pointer = static_cast<model::Shader*>(texture_struct.parent_pointer);

        this->texture_file_format = texture_struct.texture_file_format;
        this->texture_filename    = texture_struct.texture_filename;

        this->char_texture_file_format = this->texture_file_format.c_str();
        this->char_texture_filename    = this->texture_filename.c_str();

        // get childID from the Shader and set pointer to this texture.
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

    Texture::~Texture()
    {
        // destructor.
        std::cout << "Texture with childID " << this->childID << " will be destroyed.\n";

        // destroy all species of this texture.
        std::cout << "All species of this texture will be destroyed.\n";
        model::delete_children<model::Species*>(this->species_pointer_vector);

        // destroy all fonts of this texture.
        std::cout << "All fonts of this texture will be destroyed.\n";
        model::delete_children<model::Font*>(this->species_pointer_vector);

        glDeleteTextures(1, &this->texture);

        // set pointer to this texture to NULL.
        this->parent_pointer->set_texture_pointer(this->childID, NULL);
    }

    void Texture::render()
    {
        // Bind our texture in Texture Unit 0.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        // Set our "myTextureSampler" sampler to user Texture Unit 0.
        glUniform1i(this->openGL_textureID, 0);

        // render Texture by calling `render()` function of each Species and of each Font.
        model::render_children<model::Species*>(this->species_pointer_vector);
        model::render_children<model::Font*>(this->font_pointer_vector);
    }

    void Texture::set_species_pointer(GLuint childID, void* parent_pointer)
    {
        set_child_pointer(childID, parent_pointer, this->species_pointer_vector, this->free_speciesID_queue);
    }

    void Texture::bind_to_new_parent(model::Shader *new_shader_pointer)
    {
        model::bind_child_to_new_parent<model::Texture*, model::Shader*>(this, new_shader_pointer, this->parent_pointer->texture_pointer_vector, this->parent_pointer->free_textureID_queue);
    }

    void Texture::set_world_species_pointer(void* world_species_pointer)
    {
        this->world_species_pointer = world_species_pointer;
        this->parent_pointer->set_world_species_pointer(this->world_species_pointer);
    }
}
