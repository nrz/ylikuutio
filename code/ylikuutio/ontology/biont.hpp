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

#ifndef __YLIKUUTIO_ONTOLOGY_BIONT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_BIONT_HPP_INCLUDED

#include "movable.hpp"
#include "child_module.hpp"
#include "apprentice_module.hpp"
#include "biont_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;
    class Shader;
    class GenericParentModule;
    class GenericMasterModule;

    class Biont: public yli::ontology::Movable
    {
        public:
            Biont(
                    yli::ontology::Universe& universe,
                    yli::ontology::BiontStruct& biont_struct,
                    yli::ontology::GenericParentModule* const holobiont_parent_module,
                    yli::ontology::GenericMasterModule* const symbiont_species_generic_master_module)
                : Movable(
                        universe,
                        biont_struct,
                        nullptr),
                child_of_holobiont(holobiont_parent_module, this),
                apprentice_of_symbiont_species(symbiont_species_generic_master_module, this)
            {
                // constructor.

                this->biontID       = biont_struct.biontID;
                this->should_render = biont_struct.should_render;

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Biont*";
            }

            Biont(const Biont&) = delete;            // Delete copy constructor.
            Biont& operator=(const Biont&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Biont();

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::ChildModule child_of_holobiont;
            yli::ontology::ApprenticeModule apprentice_of_symbiont_species;

            // This method renders this `Biont`.
            void render();

        protected:
            void render_this_biont(const yli::ontology::Shader* const shader);

            std::size_t biontID { std::numeric_limits<std::size_t>::max() };

            bool should_render;

        private:
            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
