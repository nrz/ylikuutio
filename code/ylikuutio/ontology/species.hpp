// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "generic_master_module.hpp"
#include "apprentice_module.hpp"
#include "mesh_module.hpp"

// Include standard headers
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    class Shader;
    class Material;
    struct ModelStruct;

    class Species: public yli::ontology::Entity
    {
        public:
            // Set pointer to `species` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(yli::ontology::Species& species, yli::ontology::Scene& new_parent);

            // Set pointer to `species` to `nullptr`, set material according to the input,
            // and request a new apprenticeID from `new_material`.
            static std::optional<yli::data::AnyValue> bind_to_new_material(yli::ontology::Species& species, yli::ontology::Material& new_material);

            Species(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::GenericParentModule* const scene_parent_module,
                    yli::ontology::GenericMasterModule* const material_master);

            Species(const Species&) = delete;            // Delete copy constructor.
            Species& operator=(const Species&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Species();

            yli::ontology::Entity* get_parent() const override;

            std::size_t get_number_of_apprentices() const;

            uint32_t get_x_step() const;
            uint32_t get_z_step() const;
            uint32_t get_image_width() const;
            uint32_t get_image_height() const;

            const std::string& get_model_file_format() const;

            // this method renders all `Object`s of this `Species`.
            void render();

            yli::ontology::Scene* get_scene() const override;

            yli::ontology::Shader* get_shader() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            yli::ontology::ChildModule child_of_scene;

        public:
            yli::ontology::GenericMasterModule master_of_objects;
            yli::ontology::ApprenticeModule apprentice_of_material;
            yli::ontology::MeshModule mesh;
    };
}

#endif
