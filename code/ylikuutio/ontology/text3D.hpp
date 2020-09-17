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

#ifndef __YLIKUUTIO_ONTOLOGY_TEXT3D_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_TEXT3D_HPP_INCLUDED

#include "movable.hpp"
#include "parent_module.hpp"
#include "glyph_object_creation.hpp"
#include "text3D_struct.hpp"
#include "object_struct.hpp"
#include "movable_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Object;
    class ParentModule;
    class VectorFont;

    class Text3D: public yli::ontology::Movable
    {
        public:
            // this method deletes all glyph Objects of this `Text3D`,
            // sets pointer to this `Text3D` to `nullptr`,
            // sets `parent` according to the input (the new `VectorFont`),
            // requests a new `childID` from the new `VectorFont`,
            // and creates all glyph Objects of this `Text3D` with the font data.
            // Note: different fonts may provide glyphs for different Unicodes!
            void bind_to_new_parent(yli::ontology::VectorFont* const new_vector_font_pointer);

            Text3D(yli::ontology::Universe* const universe, const yli::ontology::Text3DStruct& text3D_struct, yli::ontology::ParentModule* const parent_module)
                : Movable(
                        universe,
                        yli::ontology::MovableStruct(
                            text3D_struct.brain,
                            text3D_struct.cartesian_coordinates,
                            text3D_struct.spherical_coordinates,
                            text3D_struct.yaw,
                            text3D_struct.pitch),
                        parent_module),
                parent_of_objects(this)
            {
                // constructor.

                // TODO: `Text3D` constructor also creates each `Object`,
                // and binds each to its corresponding `Glyph` for rendering hierarchy,
                // and also binds each to this `Text3D` for ontological hierarchy.

                this->rotate_angle = NAN;
                this->text_string  = text3D_struct.text_string;

                std::cout << "Creating the glyph Objects for the string \"" << this->text_string << "\"\n";

                // Let's create each glyph `Object` in a loop.

                yli::ontology::create_glyph_objects(this->text_string, this);

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Text3D*";
                this->can_be_erased = true;
            }

            Text3D(const Text3D&) = delete;            // Delete copy constructor.
            Text3D &operator=(const Text3D&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Text3D();

            friend class Object;
            friend void create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* text3D);

            yli::ontology::ParentModule parent_of_objects;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            std::string text_string;

            glm::vec3 original_scale_vector; // original scale vector.
            float rotate_angle;              // rotate angle.
            glm::vec3 rotate_vector;         // rotate vector.
    };
}

#endif
