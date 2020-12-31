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
#include "parent_module.hpp"
#include "holobiont_struct.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Symbiosis;

    class Holobiont: public yli::ontology::Movable
    {
        public:
            Holobiont(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::HolobiontStruct& holobiont_struct,
                    yli::ontology::ParentModule* const parent_module)
                : Movable(
                        universe,
                        holobiont_struct,
                        parent_module),
                parent_of_bionts(this)
            {
                // constructor.

                this->create_bionts(holobiont_struct.should_render_bionts_vector);

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Holobiont*";
                this->can_be_erased = true;
            }

            Holobiont(const Holobiont&) = delete;            // Delete copy constructor.
            Holobiont& operator=(const Holobiont&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Holobiont();

            void update_x(float x);
            void update_y(float y);
            void update_z(float z);

            // Public callbacks.

            static std::shared_ptr<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z(
                    yli::ontology::Symbiosis* const parent,
                    std::shared_ptr<std::string> holobiont_name,
                    std::shared_ptr<std::string> x,
                    std::shared_ptr<std::string> y,
                    std::shared_ptr<std::string> z);

            static std::shared_ptr<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z_yaw_pitch(
                    yli::ontology::Symbiosis* const parent,
                    std::shared_ptr<std::string> holobiont_name,
                    std::shared_ptr<std::string> x,
                    std::shared_ptr<std::string> y,
                    std::shared_ptr<std::string> z,
                    std::shared_ptr<std::string> yaw,
                    std::shared_ptr<std::string> pitch);

            // Public callbacks end here.

            template<class T1, class T2>
                friend void yli::render::render_children(const std::vector<T1>& child_pointer_vector);

            yli::ontology::ParentModule parent_of_bionts;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // this method renders this `Holobiont`.
            void render();

            void create_bionts(const std::vector<bool>& should_render_bionts_vector);
    };
}

#endif
