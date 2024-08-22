// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_SPECIES_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SPECIES_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_master_module.hpp"
#include "apprentice_module.hpp"
#include "mesh_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Ecosystem;
    class Scene;
    class Pipeline;
    class Material;
    struct SpeciesStruct;

    class Species final : public yli::ontology::Entity
    {
        public:
            // Set pointer to `species` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_ecosystem_parent(
                    yli::ontology::Species& species,
                    yli::ontology::Ecosystem& new_parent);

            // Set pointer to `species` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(
                    yli::ontology::Species& species,
                    yli::ontology::Scene& new_parent);

            // Set pointer to `species` to `nullptr`, set material according to the input,
            // and request a new apprenticeID from `new_material`.
            static std::optional<yli::data::AnyValue> bind_to_new_material(
                    yli::ontology::Species& species,
                    yli::ontology::Material& new_material) noexcept;

        private:
            Species(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::SpeciesStruct& species_struct,
                    yli::ontology::GenericParentModule* const ecosystem_or_scene_parent_module,
                    yli::ontology::GenericMasterModule* const material_master_module);

            ~Species() = default;

        public:
            Species(const Species&) = delete;            // Delete copy constructor.
            Species& operator=(const Species&) = delete; // Delete copy assignment.

            yli::ontology::Entity* get_parent() const override;

            std::size_t get_number_of_apprentices() const;

            uint32_t get_image_width() const;
            uint32_t get_image_height() const;

            void render(const yli::ontology::Scene* const target_scene);

            yli::ontology::Scene* get_scene() const override;

            yli::ontology::Pipeline* get_pipeline() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            yli::ontology::ChildModule child_of_ecosystem_or_scene;

        public:
            yli::ontology::GenericMasterModule master_of_objects;
            yli::ontology::ApprenticeModule apprentice_of_material;
            yli::ontology::MeshModule mesh;
    };
}

#endif
