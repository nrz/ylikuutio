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

#include "symbiont_material.hpp"
#include "symbiont_species.hpp"
#include "symbiosis.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/load/fbx_texture_loader.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include <ofbx.h>

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace ontology
    {
        class Entity;

        void SymbiontMaterial::bind_SymbiontSpecies(yli::ontology::SymbiontSpecies* const symbiont_species)
        {
            // get `childID` from `SymbiontMaterial` and set pointer to `symbiont_species`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::SymbiontSpecies*>(
                    symbiont_species,
                    this->symbiont_species_pointer_vector,
                    this->free_symbiont_speciesID_queue,
                    this->number_of_symbiont_species);
        }

        void SymbiontMaterial::unbind_SymbiontSpecies(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::SymbiontSpecies*>(
                    childID,
                    this->symbiont_species_pointer_vector,
                    this->free_symbiont_speciesID_queue,
                    this->number_of_symbiont_species);
        }

        void SymbiontMaterial::bind_to_parent()
        {
            // requirements:
            // `this->symbiosis_parent` must not be `nullptr`.
            yli::ontology::Symbiosis* const symbiosis = this->parent;

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `SymbiontMaterial::bind_to_parent`: `symbiosis` is `nullptr`!\n";
                return;
            }

            // get `childID` from `Symbiosis` and set pointer to this `SymbiontMaterial`.
            symbiosis->bind_SymbiontMaterial(this);
        }

        SymbiontMaterial::~SymbiontMaterial()
        {
            // destructor.
            std::cout << "SymbiontMaterial with childID " << std::dec << this->childID << " will be destroyed.\n";

            // destroy all symbiont species of this symbiont material.
            std::cout << "All symbiont species of this symbiont material will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::SymbiontSpecies*>(this->symbiont_species_pointer_vector, this->number_of_symbiont_species);

            glDeleteTextures(1, &this->texture);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Symbiosis* const symbiosis = this->parent;

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `SymbiontMaterial::~SymbiontMaterial`: `symbiosis` is `nullptr`!\n";
                return;
            }

            // set pointer to this symbiont_material to `nullptr`.
            symbiosis->unbind_SymbiontMaterial(this->childID);
        }

        void SymbiontMaterial::render()
        {
            this->prerender();

            // Bind our texture in Texture Unit 0.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->texture);
            // Set our "texture_sampler" sampler to user Texture Unit 0.
            yli::opengl::uniform_1i(this->openGL_textureID, 0);

            // render this `SymbiontMaterial` by calling `render()` function of each `SymbiontSpecies`.
            yli::ontology::render_children<yli::ontology::SymbiontSpecies*>(this->symbiont_species_pointer_vector);

            this->postrender();
        }

        yli::ontology::Entity* SymbiontMaterial::get_parent() const
        {
            return this->parent;
        }

        std::size_t SymbiontMaterial::get_number_of_children() const
        {
            return this->number_of_symbiont_species;
        }

        std::size_t SymbiontMaterial::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->symbiont_species_pointer_vector);
        }

        void SymbiontMaterial::load_texture()
        {
            // requirements:
            // `this->ofbx_texture` must not be `nullptr`.
            // `this->parent` must not be `nullptr`.
            // `this->parent->get_parent()` must not be `nullptr`.

            const ofbx::Texture* const texture = this->ofbx_texture;

            if (texture == nullptr)
            {
                std::cerr << "ERROR: `SymbiontMaterial::load_texture`: `texture` is `nullptr`!\n";
                return;
            }

            const yli::ontology::Symbiosis* const symbiosis = static_cast<yli::ontology::Symbiosis*>(this->parent);

            if (symbiosis == nullptr)
            {
                std::cerr << "ERROR: `SymbiontMaterial::load_texture`: `symbiosis` is `nullptr`!\n";
                return;
            }

            const yli::ontology::Shader* const shader = static_cast<yli::ontology::Shader*>(symbiosis->get_parent());

            if (shader == nullptr)
            {
                std::cerr << "ERROR: `SymbiontMaterial::load_texture`: `shader` is `nullptr`!\n";
                return;
            }

            if (!yli::load::load_FBX_texture(texture, this->image_width, this->image_height, this->image_size, this->texture))
            {
                std::cerr << "ERROR: loading FBX texture failed!\n";
            }

            // Get a handle for our "texture_sampler" uniform.
            this->openGL_textureID = glGetUniformLocation(shader->get_programID(), "texture_sampler");
        }

        uint32_t SymbiontMaterial::get_texture() const
        {
            return this->texture;
        }

        GLint SymbiontMaterial::get_openGL_textureID() const
        {
            return this->openGL_textureID;
        }
    }
}
