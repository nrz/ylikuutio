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

#include "entity.hpp"
#include "child_module.hpp"
#include "parent_module.hpp"
#include "apprentice_module.hpp"
#include "master_module.hpp"
#include "shader.hpp"
#include "material_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include <ofbx.h>

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;
    class SymbiontSpecies;

    class SymbiontMaterial: public yli::ontology::Entity
    {
        public:
            SymbiontMaterial(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::MaterialStruct& material_struct,
                    yli::ontology::ParentModule* const symbiosis_parent_module) // Parent is a `Symbiosis`.
                : Entity(universe, material_struct),
                child_of_symbiosis(symbiosis_parent_module, this),
                parent_of_symbiont_species(this, &this->registry, "symbiont_species")
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

            yli::ontology::Scene* get_scene() const override;
            yli::ontology::Entity* get_parent() const override;

            uint32_t get_texture() const;
            GLint get_openGL_textureID() const;

            yli::ontology::ChildModule child_of_symbiosis;
            yli::ontology::ParentModule parent_of_symbiont_species;

        protected:
            uint32_t image_width  { 0 };
            uint32_t image_height { 0 };
            uint32_t image_size   { 0 };

            GLuint texture           { 0 }; // Texture of this `SymbiontMaterial`, returned by `load_common_texture` (used for `glGenTextures` etc.). Dummy value.
            GLuint opengl_texture_id { 0 }; // Texture ID, returned by `glGetUniformLocation(program_id, "texture_sampler")`. Dummy value.

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
