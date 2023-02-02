// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_master_module.hpp"
#include "mesh_module.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
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
    class GenericParentModule;
    class Universe;
    class Scene;
    class Pipeline;
    struct ModelStruct;

    class SymbiontSpecies final : public yli::ontology::Entity
    {
        public:
            SymbiontSpecies(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::GenericParentModule* const symbiont_material_parent_module);

            SymbiontSpecies(const SymbiontSpecies&) = delete;            // Delete copy constructor.
            SymbiontSpecies& operator=(const SymbiontSpecies&) = delete; // Delete copy assignment.

            // destructor.
            ~SymbiontSpecies() = default;

            yli::ontology::Entity* get_parent() const override;

            std::size_t get_number_of_apprentices() const;

        private:
            void bind_to_parent() noexcept;

        public:
            yli::ontology::GenericMasterModule* get_renderables_container() const;
            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            yli::ontology::ChildModule child_of_symbiont_material;
            yli::ontology::GenericMasterModule master_of_bionts;
            yli::ontology::MeshModule mesh;

        private:
            yli::ontology::Pipeline* pipeline; // Pointer to `Pipeline` (not a parent!).

            std::string model_file_format; // Type of the model file, eg. `"png"`.
            std::string model_filename;    // Filename of the model file.
    };
}

#endif
