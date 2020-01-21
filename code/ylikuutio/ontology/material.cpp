// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "material.hpp"
#include "entity.hpp"
#include "shader.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/ontology/chunk_master.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class Species;

        void Material::bind_ChunkMaster(ontology::ChunkMaster* const chunk_master)
        {
            // Get `childID` from `Material` and set pointer to `chunk_master`.
            yli::hierarchy::bind_child_to_parent<ontology::ChunkMaster*>(
                    chunk_master,
                    this->chunk_master_pointer_vector,
                    this->free_chunk_masterID_queue,
                    this->number_of_chunk_masters);
        }

        void Material::unbind_ChunkMaster(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::ChunkMaster*>(
                    childID,
                    this->chunk_master_pointer_vector,
                    this->free_chunk_masterID_queue,
                    this->number_of_chunk_masters);
        }

        void Material::bind_to_parent()
        {
            // Requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Shader* const shader = this->parent;

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `Material::bind_to_parent`: `shader` is `nullptr`!\n";
                return;
            }

            // Get `childID` from the `Shader` and set pointer to this `Material`.
            shader->parent_of_materials.bind_child(this);
        }

        Material::~Material()
        {
            if (!this->is_symbiont_material)
            {
                // destructor.
                std::cout << "`Material` with childID " << std::dec << this->childID << " will be destroyed.\n";

                // Destroy all `ChunkMaster`s of this `Material`.
                std::cout << "All `ChunkMaster`s of this `Material` will be destroyed.\n";
                yli::hierarchy::delete_children<ontology::ChunkMaster*>(this->chunk_master_pointer_vector, this->number_of_chunk_masters);

                glDeleteTextures(1, &this->texture);

                // Requirements for further actions:
                // `this->parent` must not be `nullptr`.

                yli::ontology::Shader* const shader = this->parent;

                // Set pointer to this `Material` to `nullptr`.
                if (shader == nullptr)
                {
                    std::cerr << "ERROR: `Material::~Material`: `shader` is `nullptr`!\n";
                    return;
                }

                shader->parent_of_materials.unbind_child(this->childID);
            }
        }

        void Material::render()
        {
            if (!this->should_be_rendered)
            {
                return;
            }

            this->prerender();

            // Bind our texture in Texture Unit 0.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->texture);

            // Set our "texture_sampler" sampler to use Texture Unit 0.
            yli::opengl::uniform_1i(this->openGL_textureID, 0);

            // Render this `Material` by calling `render()` function of each `Species`, each `VectorFont`, and each `ChunkMaster`.
            yli::ontology::render_children<yli::ontology::Entity*>(this->parent_of_species.child_pointer_vector);
            yli::ontology::render_children<yli::ontology::Entity*>(this->parent_of_vector_fonts.child_pointer_vector);
            yli::ontology::render_children<ontology::ChunkMaster*>(this->chunk_master_pointer_vector);

            this->postrender();
        }

        yli::ontology::Entity* Material::get_parent() const
        {
            return this->parent;
        }

        std::size_t Material::get_number_of_children() const
        {
            return this->parent_of_species.number_of_children + this->parent_of_shapeshifter_transformations.number_of_children + this->parent_of_vector_fonts.number_of_children + this->number_of_chunk_masters;
        }

        std::size_t Material::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->parent_of_species.child_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->parent_of_shapeshifter_transformations.child_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->parent_of_vector_fonts.child_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->chunk_master_pointer_vector);
        }

        void Material::bind_to_new_parent(yli::ontology::Shader* const new_parent)
        {
            // Requirements:
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

            // Unbind from the old parent `Shader`.
            shader->parent_of_materials.unbind_child(this->childID);

            // Get `childID` from `Shader` and set pointer to this `Material`.
            this->parent = new_parent;
            this->parent->parent_of_materials.bind_child(this);
        }

        void Material::set_terrain_species(yli::ontology::Species* const terrain_species)
        {
            yli::ontology::Shader* const shader_parent = this->parent;

            if (shader_parent != nullptr)
            {
                shader_parent->set_terrain_species(terrain_species);
            }
        }

        const std::string& Material::get_texture_file_format() const
        {
            return this->texture_file_format;
        }

        const std::string& Material::get_texture_filename() const
        {
            return this->texture_filename;
        }

        std::size_t Material::get_image_width() const
        {
            return this->image_width;
        }

        std::size_t Material::get_image_height() const
        {
            return this->image_height;
        }

        std::size_t Material::get_image_size() const
        {
            return this->image_size;
        }
    }
}
