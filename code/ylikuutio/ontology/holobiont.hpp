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

#ifndef __YLIKUUTIO_ONTOLOGY_HOLOBIONT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_HOLOBIONT_HPP_INCLUDED

#include "movable.hpp"
#include "parent_module.hpp"
#include "holobiont_struct.hpp"
#include "movable_struct.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp> // glm::quat
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Universe;

    class Holobiont: public yli::ontology::Movable
    {
        public:
            Holobiont(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::HolobiontStruct& holobiont_struct,
                    yli::ontology::ParentModule* const parent_module)
                : Movable(
                        universe,
                        yli::ontology::MovableStruct(
                            holobiont_struct.brain,
                            holobiont_struct.cartesian_coordinates,
                            holobiont_struct.spherical_coordinates,
                            holobiont_struct.yaw,
                            holobiont_struct.vertical_angle),
                        parent_module),
                parent_of_bionts(this)
            {
                // constructor.

                this->original_scale_vector = holobiont_struct.original_scale_vector;
                this->rotate_vector         = holobiont_struct.rotate_vector;
                this->translate_vector      = holobiont_struct.translate_vector;
                this->initial_rotate_vector = holobiont_struct.initial_rotate_vector;

                this->rotate_angle          = holobiont_struct.rotate_angle;
                this->initial_rotate_angle  = holobiont_struct.initial_rotate_angle;

                this->cartesian_coordinates = holobiont_struct.cartesian_coordinates;
                this->spherical_coordinates = holobiont_struct.spherical_coordinates;

                this->create_bionts();

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Holobiont*";
                this->can_be_erased = true;
            }

            Holobiont(const Holobiont&) = delete;            // Delete copy constructor.
            Holobiont &operator=(const Holobiont&) = delete; // Delete copy assignment.

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

            static std::shared_ptr<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z_horizontal_angle_vertical_angle(
                    yli::ontology::Symbiosis* const parent,
                    std::shared_ptr<std::string> holobiont_name,
                    std::shared_ptr<std::string> x,
                    std::shared_ptr<std::string> y,
                    std::shared_ptr<std::string> z,
                    std::shared_ptr<std::string> yaw,
                    std::shared_ptr<std::string> vertical_angle);

            // Public callbacks end here.

            yli::ontology::ParentModule parent_of_bionts;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // this method renders this `Holobiont`.
            void render() override;

            void create_bionts();

            glm::vec3 original_scale_vector;            // original scale vector.
            glm::vec3 rotate_vector;                    // rotate vector.
            glm::vec3 translate_vector;                 // translate vector.
            glm::vec3 initial_rotate_vector;            // initial rotate vector.

            yli::data::SphericalCoordinatesStruct spherical_coordinates;

            float rotate_angle;                         // rotate angle.
            float initial_rotate_angle;                 // initial rotate angle.
    };
}

#endif
