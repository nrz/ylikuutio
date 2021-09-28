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

#ifndef __YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_master_module.hpp"
#include "model_module.hpp"
#include "model_struct.hpp"
#include "code/ylikuutio/opengl/vboindexer.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

// `SymbiontSpecies` is not the ontological parent of `Biont`,
// as `Holobiont` is the ontological parent of `Biont`.
// The relationship between `SymbiontSpecies` and `Biont`
// is purely only for rendering.
//
// To avoid potential problems in the future, follow this order:
// 1. bind `Biont` to its `Holobiont` parent.
// 2. bind `Biont` to its corresponding `SymbiontSpecies`.
// 3. do stuff
// 4. unbind `Biont` from its `SymbiontSpecies`.
// 5. unbind `Biont` from its `Holobiont` parent.

namespace yli::ontology
{
    class ParentModule;
    class Universe;
    class Scene;
    class Shader;

    class SymbiontSpecies: public yli::ontology::Entity
    {
        public:
            SymbiontSpecies(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::ParentModule* const symbiont_material_parent_module)
                : Entity(universe, model_struct),
                child_of_symbiont_material(symbiont_material_parent_module, this),
                master_of_bionts(this, &this->registry, "bionts"),
                model(universe, model_struct)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::SymbiontSpecies*";
            }

            SymbiontSpecies(const SymbiontSpecies&) = delete;            // Delete copy constructor.
            SymbiontSpecies& operator=(const SymbiontSpecies&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~SymbiontSpecies();

            yli::ontology::Entity* get_parent() const override;

            std::size_t get_number_of_apprentices() const;

            GLint get_light_id() const;

        private:
            void bind_to_parent();

        public:
            // this method renders all `Object`s of this `SymbiontSpecies`.
            void render();

            yli::ontology::GenericMasterModule* get_renderables_container() const;

        private:
            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            yli::ontology::ChildModule child_of_symbiont_material;
            yli::ontology::GenericMasterModule master_of_bionts;
            yli::ontology::ModelModule model;

        private:
            yli::ontology::Shader* shader; // Pointer to `Shader` (not a parent!).

            std::string model_file_format; // Type of the model file, eg. `"png"`.
            std::string model_filename;    // Filename of the model file.
    };
}

#endif
