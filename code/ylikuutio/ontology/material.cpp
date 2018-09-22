#include "material.hpp"
#include "shader.hpp"
#include "vector_font.hpp"
#include "species.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/ontology/chunk_master.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void Material::bind_species(yli::ontology::Species* const species)
        {
            // get `childID` from `Material` and set pointer to `species`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Species*>(
                    species,
                    this->species_pointer_vector,
                    this->free_speciesID_queue,
                    this->number_of_species);
        }

        void Material::bind_vector_font(yli::ontology::VectorFont* const vector_font)
        {
            // get `childID` from `Material` and set pointer to `vector_font`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::VectorFont*>(
                    vector_font,
                    this->vector_font_pointer_vector,
                    this->free_vector_fontID_queue,
                    this->number_of_vector_fonts);
        }

        void Material::bind_chunk_master(ontology::ChunkMaster* const chunk_master)
        {
            // get `childID` from `Material` and set pointer to `chunk_master`.
            yli::hierarchy::bind_child_to_parent<ontology::ChunkMaster*>(
                    chunk_master,
                    this->chunk_master_pointer_vector,
                    this->free_chunk_masterID_queue,
                    this->number_of_chunk_masters);
        }

        void Material::unbind_species(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::Species*>(
                    childID,
                    this->species_pointer_vector,
                    this->free_speciesID_queue,
                    this->number_of_species);
        }

        void Material::unbind_vector_font(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::VectorFont*>(
                    childID,
                    this->vector_font_pointer_vector,
                    this->free_vector_fontID_queue,
                    this->number_of_vector_fonts);
        }

        void Material::unbind_chunk_master(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::ChunkMaster*>(
                    childID,
                    this->chunk_master_pointer_vector,
                    this->free_chunk_masterID_queue,
                    this->number_of_chunk_masters);
        }

        void Material::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Shader* const shader = this->parent;

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `Material::bind_to_parent`: `shader` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `Shader` and set pointer to this `Material`.
            shader->bind_material(this);
        }

        Material::~Material()
        {
            if (!this->is_symbiont_material)
            {
                // destructor.
                std::cout << "Material with childID " << std::dec << this->childID << " will be destroyed.\n";

                // destroy all species of this material.
                std::cout << "All species of this material will be destroyed.\n";
                yli::hierarchy::delete_children<yli::ontology::Species*>(this->species_pointer_vector, this->number_of_species);

                // destroy all fonts of this material.
                std::cout << "All fonts of this material will be destroyed.\n";
                yli::hierarchy::delete_children<yli::ontology::VectorFont*>(this->vector_font_pointer_vector, this->number_of_vector_fonts);

                // destroy all chunk masters of this material.
                std::cout << "All chunk masters of this material will be destroyed.\n";
                yli::hierarchy::delete_children<ontology::ChunkMaster*>(this->chunk_master_pointer_vector, this->number_of_chunk_masters);

                glDeleteTextures(1, &this->texture);

                // requirements for further actions:
                // `this->parent` must not be `nullptr`.

                yli::ontology::Shader* const shader = this->parent;

                // set pointer to this `Material` to `nullptr`.
                if (shader == nullptr)
                {
                    std::cerr << "ERROR: `Material::~Material`: `shader` is `nullptr`!\n";
                    return;
                }

                shader->unbind_material(this->childID);
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
            yli::ontology::render_children<ontology::ChunkMaster*>(this->chunk_master_pointer_vector);

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
            return yli::ontology::get_number_of_descendants(this->species_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->vector_font_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->chunk_master_pointer_vector);
        }

        void Material::bind_to_new_parent(yli::ontology::Shader* const new_parent)
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            // `new_parent` must not be `nullptr`.
            yli::ontology::Shader* const shader = this->parent;

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `Material::bind_to_new_parent`: `shader` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `Material::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // unbind from the old parent `Shader`.
            shader->unbind_material(this->childID);

            // get `childID` from `Shader` and set pointer to this `Material`.
            this->parent = new_parent;
            this->parent->bind_material(this);
        }

        void Material::set_terrain_species(yli::ontology::Species* const terrain_species)
        {
            yli::ontology::Shader* const shader_parent = this->parent;

            if (shader_parent != nullptr)
            {
                shader_parent->set_terrain_species(terrain_species);
            }
        }
    }
}
