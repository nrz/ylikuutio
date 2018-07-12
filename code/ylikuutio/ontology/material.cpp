#include "material.hpp"
#include "vector_font.hpp"
#include "species.hpp"
#include "render_templates.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/space_partition/chunk_master.hpp"
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
#include <cstddef>  // std::size_t
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace ontology
    {
        void Material::bind_species(yli::ontology::Species* const species)
        {
            // get `childID` from `Material` and set pointer to `species`.
            hierarchy::bind_child_to_parent<yli::ontology::Species*>(
                    species,
                    this->species_pointer_vector,
                    this->free_speciesID_queue,
                    &this->number_of_species);
        }

        void Material::bind_vector_font(yli::ontology::VectorFont* const vector_font)
        {
            // get `childID` from `Material` and set pointer to `vector_font`.
            hierarchy::bind_child_to_parent<yli::ontology::VectorFont*>(
                    vector_font,
                    this->vector_font_pointer_vector,
                    this->free_vector_fontID_queue,
                    &this->number_of_vector_fonts);
        }

        void Material::bind_chunk_master(space_partition::ChunkMaster* const chunk_master)
        {
            // get `childID` from `Material` and set pointer to `chunk_master`.
            hierarchy::bind_child_to_parent<space_partition::ChunkMaster*>(
                    chunk_master,
                    this->chunk_master_pointer_vector,
                    this->free_chunk_masterID_queue,
                    &this->number_of_chunk_masters);
        }

        void Material::unbind_species(const int32_t childID)
        {
            yli::ontology::Species* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(
                    childID,
                    dummy_child_pointer,
                    this->species_pointer_vector,
                    this->free_speciesID_queue,
                    &this->number_of_species);
        }

        void Material::unbind_vector_font(const int32_t childID)
        {
            yli::ontology::VectorFont* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(
                    childID,
                    dummy_child_pointer,
                    this->vector_font_pointer_vector,
                    this->free_vector_fontID_queue,
                    &this->number_of_vector_fonts);
        }

        void Material::unbind_chunk_master(const int32_t childID)
        {
            space_partition::ChunkMaster* dummy_child_pointer = nullptr;
            hierarchy::set_child_pointer(
                    childID,
                    dummy_child_pointer,
                    this->chunk_master_pointer_vector,
                    this->free_chunk_masterID_queue,
                    &this->number_of_chunk_masters);
        }

        void Material::bind_to_parent()
        {
            // get `childID` from `Shader` and set pointer to this `Material`.
            this->parent->bind_material(this);
        }

        Material::~Material()
        {
            if (!this->is_symbiont_material)
            {
                // destructor.
                std::cout << "Material with childID " << std::dec << this->childID << " will be destroyed.\n";

                // destroy all species of this material.
                std::cout << "All species of this material will be destroyed.\n";
                hierarchy::delete_children<yli::ontology::Species*>(this->species_pointer_vector, &this->number_of_species);

                // destroy all fonts of this material.
                std::cout << "All fonts of this material will be destroyed.\n";
                hierarchy::delete_children<yli::ontology::VectorFont*>(this->vector_font_pointer_vector, &this->number_of_vector_fonts);

                // destroy all chunk masters of this material.
                std::cout << "All chunk masters of this material will be destroyed.\n";
                hierarchy::delete_children<space_partition::ChunkMaster*>(this->chunk_master_pointer_vector, &this->number_of_chunk_masters);

                glDeleteTextures(1, &this->texture);

                // set pointer to this material to nullptr.
                this->parent->set_material_pointer(this->childID, nullptr);
            }
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
            yli::ontology::render_children<yli::ontology::Species*>(this->species_pointer_vector);
            yli::ontology::render_children<yli::ontology::VectorFont*>(this->vector_font_pointer_vector);
            yli::ontology::render_children<space_partition::ChunkMaster*>(this->chunk_master_pointer_vector);

            this->postrender();
        }

        yli::ontology::Entity* Material::get_parent() const
        {
            return this->parent;
        }

        std::size_t Material::get_number_of_children() const
        {
            return this->number_of_species + this->number_of_vector_fonts + this->number_of_chunk_masters;
        }

        std::size_t Material::get_number_of_descendants() const
        {
            return 0; // TODO; write the code!
        }

        void Material::set_species_pointer(const int32_t childID, yli::ontology::Species* const child_pointer)
        {
            hierarchy::set_child_pointer(childID, child_pointer, this->species_pointer_vector, this->free_speciesID_queue, &this->number_of_species);
        }

        void Material::set_vector_font_pointer(const int32_t childID, yli::ontology::VectorFont* const child_pointer)
        {
            hierarchy::set_child_pointer(childID, child_pointer, this->vector_font_pointer_vector, this->free_vector_fontID_queue, &this->number_of_vector_fonts);
        }

        void Material::set_chunk_master_pointer(const int32_t childID, space_partition::ChunkMaster* const child_pointer)
        {
            hierarchy::set_child_pointer(childID, child_pointer, this->chunk_master_pointer_vector, this->free_chunk_masterID_queue, &this->number_of_chunk_masters);
        }

        void Material::bind_to_new_parent(yli::ontology::Shader* const new_shader_pointer)
        {
            // unbind from the old parent `Shader`.
            this->parent->unbind_material(this->childID);

            // get `childID` from `Shader` and set pointer to this `Material`.
            this->parent = new_shader_pointer;
            this->parent->bind_material(this);
        }

        void Material::set_terrain_species(yli::ontology::Species* const terrain_species)
        {
            this->terrain_species = terrain_species;
            this->parent->set_terrain_species(this->terrain_species);
        }
    }
}
