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

#ifndef __YLIKUUTIO_ONTOLOGY_HOLOBIONT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_HOLOBIONT_HPP_INCLUDED

#include "movable.hpp"
#include "holobiont_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class ParentModule;
    class GenericMasterModule;
    class Entity;
    class Universe;
    class Scene;
    class Symbiosis;

    class Holobiont: public yli::ontology::Movable
    {
        public:
            Holobiont(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::HolobiontStruct& holobiont_struct,
                    yli::ontology::ParentModule* const symbiosis_parent_module,
                    yli::ontology::GenericMasterModule* const generic_master_module)
                : Movable(
                        universe,
                        holobiont_struct,
                        symbiosis_parent_module,
                        generic_master_module),
                parent_of_bionts(this, &this->registry, "bionts")
            {
                // constructor.

                this->create_bionts(holobiont_struct.scene, holobiont_struct.should_render_bionts_vector);

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Holobiont*";
                this->can_be_erased = true;
            }

            Holobiont(const Holobiont&) = delete;            // Delete copy constructor.
            Holobiont& operator=(const Holobiont&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Holobiont();

            void update_x(const float x);
            void update_y(const float y);
            void update_z(const float z);

            // Public callbacks.

            static std::optional<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z(
                    yli::ontology::Symbiosis* const parent,
                    const std::string& holobiont_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z);

            static std::optional<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z_yaw_pitch(
                    yli::ontology::Symbiosis* const parent,
                    const std::string& holobiont_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z,
                    const std::string& yaw,
                    const std::string& pitch);

            // Public callbacks end here.

            yli::ontology::ParentModule parent_of_bionts;

            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            // this method renders this `Holobiont`.
            void render();

        private:
            void create_bionts(yli::ontology::Scene* const scene, const std::vector<bool>& should_render_bionts_vector);
    };
}

#endif
