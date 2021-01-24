// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_SYMBIONT_MATERIAL_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SYMBIONT_MATERIAL_HPP_INCLUDED

#include "material.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include <ofbx.h>

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Universe;
    class SymbiontSpecies;
    class ParentModule;

    class SymbiontMaterial: public yli::ontology::Material
    {
        public:
            SymbiontMaterial(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::MaterialStruct& material_struct,
                    yli::ontology::ParentModule* const parent_module)
                : Material(universe, material_struct, parent_module)
            {
                // constructor.
                this->ofbx_texture = material_struct.ofbx_texture;
                this->load_texture();

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::SymbiontMaterial*";
            }

            SymbiontMaterial(const SymbiontMaterial&) = delete;            // Delete copy constructor.
            SymbiontMaterial& operator=(const SymbiontMaterial&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~SymbiontMaterial();

            uint32_t get_texture() const;
            GLint get_openGL_textureID() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            void load_texture();

            // this method renders all `SymbiontSpecies` using this `SymbiontMaterial`.
            void render();

            const ofbx::Texture* ofbx_texture;
    };
}

#endif
