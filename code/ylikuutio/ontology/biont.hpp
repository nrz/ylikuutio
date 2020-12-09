// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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
#include "biont_struct.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Shader;
    class SymbiontSpecies;
    class ParentModule;

    class Biont: public yli::ontology::Movable
    {
        public:
            Biont(yli::ontology::Universe* const universe, yli::ontology::BiontStruct& biont_struct, yli::ontology::ParentModule* const parent_module)
                : Movable(
                        universe,
                        biont_struct,
                        parent_module)
            {
                // constructor.
                this->symbiont_species = biont_struct.symbiont_species;

                this->biontID          = biont_struct.biontID;

                this->should_render    = biont_struct.should_render;

                // Get `childID` from `SymbiontSpecies` (not a parent!) and set pointer to this `Biont`.
                this->bind_to_symbiont_species();

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Biont*";
            }

            Biont(const Biont&) = delete;            // Delete copy constructor.
            yli::ontology::Biont& operator=(const Biont&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Biont();

            template<class T1, class T2>
                friend void yli::render::render_children(const std::vector<T1>& child_pointer_vector);

        protected:
            void bind_to_symbiont_species();

            // This method renders this `Biont`.
            void render();
            void render_this_biont(const yli::ontology::Shader* const shader);

            yli::ontology::SymbiontSpecies* symbiont_species; // pointer to the `SymbiontSpecies` (not a parent!).

            std::size_t biontID { std::numeric_limits<std::size_t>::max() };

            bool should_render;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
