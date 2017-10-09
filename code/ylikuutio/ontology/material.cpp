#include "material.hpp"
#include "vector_font.hpp"
#include "species.hpp"
#include "render_templates.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/space_partition/chunk_master.hpp"
#include "code/ylikuutio/loaders/texture_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Include standard headers
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace ontology
{
    void Material::bind_to_parent()
    {
        // get `childID` from `Shader` and set pointer to this `Material`.
        hierarchy::bind_child_to_parent<ontology::Material*>(this, this->parent_pointer->material_pointer_vector, this->parent_pointer->free_materialID_queue, &this->parent_pointer->number_of_materials);
    }

    Material::Material(const MaterialStruct material_struct)
    {
        // constructor.
        this->parent_pointer = material_struct.parent_pointer;
        this->universe_pointer = this->parent_pointer->universe_pointer;

        this->terrain_species_pointer = nullptr;

        this->texture_file_format = material_struct.texture_file_format;
        this->texture_filename    = material_struct.texture_filename;

        this->char_texture_file_format = this->texture_file_format.c_str();
        this->char_texture_filename    = this->texture_filename.c_str();

        this->number_of_species = 0;
        this->number_of_vector_fonts = 0;
        this->number_of_chunk_masters = 0;

        // get `childID` from the `Shader` and set pointer to this `Material`.
        this->bind_to_parent();

        // Load the texture.
        if ((std::strcmp(this->char_texture_file_format, "bmp") == 0) || (std::strcmp(this->char_texture_file_format, "BMP") == 0))
        {
            this->texture = loaders::load_BMP_texture(this->texture_filename);
        }
        else if ((std::strcmp(this->char_texture_file_format, "dds") == 0) || (std::strcmp(this->char_texture_file_format, "DDS") == 0))
        {
            this->texture = loaders::load_DDS_texture(this->texture_filename);
        }
        else
        {
            std::cerr << "no texture was loaded!\n";
            std::cerr << "texture file format: " << this->texture_file_format << "\n";
            this->texture = 0; // some dummy value.
        }

        // Get a handle for our "myTextureSampler" uniform.
        this->openGL_textureID = glGetUniformLocation(this->parent_pointer->programID, "myTextureSampler");

        this->child_vector_pointers_vector.push_back(&this->species_pointer_vector);
        this->child_vector_pointers_vector.push_back(&this->vector_font_pointer_vector);
        this->child_vector_pointers_vector.push_back(&this->chunk_master_pointer_vector);
        this->type = "ontology::Material*";
    }

    Material::~Material()
    {
        // destructor.
        std::cout << "Material with childID " << std::dec << this->childID << " will be destroyed.\n";

        // destroy all species of this material.
        std::cout << "All species of this material will be destroyed.\n";
        hierarchy::delete_children<ontology::Species*>(this->species_pointer_vector, &this->number_of_species);

        // destroy all fonts of this material.
        std::cout << "All fonts of this material will be destroyed.\n";
        hierarchy::delete_children<ontology::VectorFont*>(this->vector_font_pointer_vector, &this->number_of_vector_fonts);

        // destroy all chunk masters of this material.
        std::cout << "All chunk masters of this material will be destroyed.\n";
        hierarchy::delete_children<space_partition::ChunkMaster*>(this->chunk_master_pointer_vector, &this->number_of_chunk_masters);

        glDeleteTextures(1, &this->texture);

        // set pointer to this material to nullptr.
        this->parent_pointer->set_material_pointer(this->childID, nullptr);
    }

    void Material::render()
    {
        this->prerender();

        // Bind our texture in Texture Unit 0.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        // Set our "myTextureSampler" sampler to user Texture Unit 0.
        glUniform1i(this->openGL_textureID, 0);

        // render this `Material` by calling `render()` function of each `Species`, each `VectorFont`, and each `ChunkMaster`.
        ontology::render_children<ontology::Species*>(this->species_pointer_vector);
        ontology::render_children<ontology::VectorFont*>(this->vector_font_pointer_vector);
        ontology::render_children<space_partition::ChunkMaster*>(this->chunk_master_pointer_vector);

        this->postrender();
    }

    ontology::Entity* Material::get_parent()
    {
        return this->parent_pointer;
    }

    int32_t Material::get_number_of_children()
    {
        return this->number_of_species + this->number_of_vector_fonts + this->number_of_chunk_masters;
    }

    int32_t Material::get_number_of_descendants()
    {
        return -1;
    }

    void Material::set_species_pointer(const int32_t childID, ontology::Species* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->species_pointer_vector, this->free_speciesID_queue, &this->number_of_species);
    }

    void Material::set_vector_font_pointer(const int32_t childID, ontology::VectorFont* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->vector_font_pointer_vector, this->free_vector_fontID_queue, &this->number_of_vector_fonts);
    }

    void Material::set_chunk_master_pointer(const int32_t childID, space_partition::ChunkMaster* const child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->chunk_master_pointer_vector, this->free_chunk_masterID_queue, &this->number_of_chunk_masters);
    }

    void Material::bind_to_new_parent(ontology::Shader* const new_shader_pointer)
    {
        // this method sets pointer to this `Material` to nullptr, sets `parent_pointer` according to the input, and requests a new `childID` from the new `Shader`.
        hierarchy::bind_child_to_new_parent<ontology::Material*, ontology::Shader*>(this, new_shader_pointer, this->parent_pointer->material_pointer_vector, this->parent_pointer->free_materialID_queue, &this->parent_pointer->number_of_materials);
    }

    void Material::set_name(const std::string& name)
    {
        ontology::set_name(name, this);
    }

    void Material::set_terrain_species_pointer(ontology::Species* const terrain_species_pointer)
    {
        this->terrain_species_pointer = terrain_species_pointer;
        this->parent_pointer->set_terrain_species_pointer(this->terrain_species_pointer);
    }
}
