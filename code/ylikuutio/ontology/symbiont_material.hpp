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

#ifndef __SYMBIONT_MATERIAL_HPP_INCLUDED
#define __SYMBIONT_MATERIAL_HPP_INCLUDED

#include "material.hpp"
#include "symbiosis.hpp"
#include "material_struct.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/texture_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include <ofbx.h>

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Entity;
        class SymbiontSpecies;

        class SymbiontMaterial: public yli::ontology::Material
        {
            public:
                void bind_SymbiontSpecies(yli::ontology::SymbiontSpecies* const symbiont_species);
                void unbind_SymbiontSpecies(const std::size_t childID);

                // constructor.
                SymbiontMaterial(yli::ontology::Universe* const universe, const yli::ontology::MaterialStruct& material_struct)
                    : Material(universe, material_struct)
                {
                    // constructor.
                    this->parent                     = material_struct.symbiosis;
                    this->ofbx_texture               = material_struct.ofbx_texture;
                    this->number_of_symbiont_species = 0;

                    // get `childID` from the `Symbiosis` and set pointer to this `SymbiontMaterial`.
                    this->bind_to_parent();

                    this->load_texture();

                    // `yli::ontology::Entity` member variables begin here.
                    this->child_vector_pointers_vector.push_back(&this->symbiont_species_pointer_vector);
                    this->type_string = "yli::ontology::SymbiontMaterial*";
                }

                SymbiontMaterial(const SymbiontMaterial&) = delete;            // Delete copy constructor.
                SymbiontMaterial &operator=(const SymbiontMaterial&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~SymbiontMaterial();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                uint32_t get_texture() const;
                GLint get_openGL_textureID() const;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                void load_texture();

                // this method renders all `SymbiontSpecies` using this `SymbiontMaterial`.
                void render();

                yli::ontology::Symbiosis* parent;  // pointer to the `Symbiosis`.

                const ofbx::Texture* ofbx_texture;

                uint32_t texture;                  // texture of this `SymbiontMaterial`.
                GLint openGL_textureID;            // texture ID, returned by `glGetUniformLocation(programID, "texture_sampler")`.

                std::vector<yli::ontology::SymbiontSpecies*> symbiont_species_pointer_vector;
                std::queue<std::size_t> free_symbiont_speciesID_queue;
                std::size_t number_of_symbiont_species;
        };
    }
}

#endif
