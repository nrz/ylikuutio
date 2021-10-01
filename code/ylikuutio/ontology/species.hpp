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

#ifndef __YLIKUUTIO_ONTOLOGY_SPECIES_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SPECIES_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "parent_module.hpp"
#include "mesh_module.hpp"
#include "model_struct.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Material;

    class Species: public yli::ontology::Entity
    {
        public:
            // this method sets pointer to this `Species` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Material`.
            void bind_to_new_material_parent(yli::ontology::Material* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            Species(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::ParentModule* const material_parent_module)
                : Entity(universe, model_struct),
                child_of_material(material_parent_module, this),
                parent_of_objects(this, &this->registry, "objects"),
                mesh(universe, model_struct)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Species*";
                this->can_be_erased = true;
            }

            Species(const Species&) = delete;            // Delete copy constructor.
            Species& operator=(const Species&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Species();

            yli::ontology::Entity* get_parent() const override;

            uint32_t get_x_step() const;
            uint32_t get_z_step() const;
            uint32_t get_image_width() const;
            uint32_t get_image_height() const;

            const std::string& get_model_file_format() const;

            // this method renders all `Object`s of this `Species`.
            void render();

            yli::ontology::ParentModule* get_renderables_container();

            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            yli::ontology::ChildModule child_of_material;

        public:
            yli::ontology::ParentModule parent_of_objects;
            yli::ontology::MeshModule mesh;
    };
}

#endif
