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
    class Object;
    struct SpeciesStruct;

    class Species final : public Entity
    {
        public:
            // Set pointer to `species` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_ecosystem_parent(
                    Species& species,
                    Ecosystem& new_parent);

            // Set pointer to `species` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(
                    Species& species,
                    Scene& new_parent);

            // Set pointer to `species` to `nullptr`, set material according to the input,
            // and request a new apprenticeID from `new_material`.
            static std::optional<yli::data::AnyValue> bind_to_new_material(
                    Species& species,
                    Material& new_material) noexcept;

        private:
            Species(
                    yli::core::Application& application,
                    Universe& universe,
                    const SpeciesStruct& species_struct,
                    GenericParentModule* const ecosystem_or_scene_parent_module,
                    GenericMasterModule* const material_master_module);

            ~Species() = default;

        public:
            Species(const Species&) = delete;            // Delete copy constructor.
            Species& operator=(const Species&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            std::size_t get_number_of_apprentices() const;

            uint32_t get_image_width() const;
            uint32_t get_image_height() const;

            void render(const Scene* const target_scene);

            Scene* get_scene() const override;

            Pipeline* get_pipeline() const;

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_ecosystem_or_scene;

        public:
            GenericMasterModule master_of_objects;
            ApprenticeModule apprentice_of_material;
            MeshModule mesh;
    };

    template<>
        inline GenericMasterModule* Species::get_generic_master_module<Object>()
        {
            return &this->master_of_objects;
        }
}

#endif
