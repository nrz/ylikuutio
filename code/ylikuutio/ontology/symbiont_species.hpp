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

#ifndef YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SYMBIONT_SPECIES_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "apprentice_module.hpp"
#include "generic_master_module.hpp"
#include "mesh_module.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

// `SymbiontSpecies` master provides mesh for the `Biont` apprentices.

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
    class GenericMasterModule;
    class Universe;
    class Scene;
    class Pipeline;
    class Biont;
    struct SymbiontSpeciesStruct;

    class SymbiontSpecies final : public Entity
    {
        private:
            SymbiontSpecies(
                    yli::core::Application& application,
                    Universe& universe,
                    const SymbiontSpeciesStruct& symbiont_species_struct,
                    GenericParentModule* const symbiont_material_parent_module);

            ~SymbiontSpecies() = default;

        public:
            SymbiontSpecies(const SymbiontSpecies&) = delete;            // Delete copy constructor.
            SymbiontSpecies& operator=(const SymbiontSpecies&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

            std::size_t get_number_of_apprentices() const;

        private:
            void bind_to_parent() noexcept;

        public:
            GenericMasterModule* get_renderables_container() const;
            Scene* get_scene() const override;

            Pipeline* get_pipeline() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_symbiont_material;
            GenericMasterModule master_of_bionts;
            MeshModule mesh;

        private:
            std::string model_file_format; // Type of the model file, eg. `"png"`.
            std::string model_filename;    // Filename of the model file.
    };

    template<>
        inline GenericMasterModule* SymbiontSpecies::get_generic_master_module<Biont>()
        {
            return &this->master_of_bionts;
        }
}

#endif
