// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_BIONT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_BIONT_HPP_INCLUDED

#include "movable.hpp"
#include "child_module.hpp"
#include "apprentice_module.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits

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
    class Entity;
    class Universe;
    class Scene;
    class GenericParentModule;
    class GenericMasterModule;
    struct BiontStruct;

    class Biont final : public Movable
    {
        private:
            Biont(
                    yli::core::Application& application,
                    Universe& universe,
                    const BiontStruct& biont_struct,
                    GenericParentModule* const holobiont_parent_module,
                    GenericMasterModule* const symbiont_species_master_module);

            ~Biont() = default;

        public:
            Biont(const Biont&) = delete;            // Delete copy constructor.
            Biont& operator=(const Biont&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_holobiont;
            ApprenticeModule apprentice_of_symbiont_species;

            // This method renders this `Biont`.
            void render();

        protected:
            void render_this_biont();

            std::size_t biontID { std::numeric_limits<std::size_t>::max() };

        private:
            Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
