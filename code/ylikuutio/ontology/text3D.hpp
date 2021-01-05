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

#ifndef __YLIKUUTIO_ONTOLOGY_TEXT3D_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_TEXT3D_HPP_INCLUDED

#include "movable.hpp"
#include "parent_module.hpp"
#include "glyph_object_creation.hpp"
#include "text3D_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli::ontology
{
    class Universe;
    class Object;
    class ParentModule;
    class MasterModule;
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

            Text3D(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::Text3DStruct& text3D_struct,
                    yli::ontology::ParentModule* const parent_module,
                    yli::ontology::MasterModule* const master_module)
                : Movable(
                        universe,
                        text3D_struct,
                        parent_module,
                        master_module),
                parent_of_objects(this)
            {
                // constructor.

                // TODO: `Text3D` constructor also creates each `Object`,
                // and binds each to its corresponding `Glyph` for rendering hierarchy,
                // and also binds each to this `Text3D` for ontological hierarchy.

                this->text_string  = text3D_struct.text_string;

                // Let's create each glyph `Object` in a loop.

                yli::ontology::create_glyph_objects(this->text_string, this);

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Text3D*";
                this->can_be_erased = true;
            }

            Text3D(const Text3D&) = delete;            // Delete copy constructor.
            Text3D& operator=(const Text3D&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Text3D();

            friend class Object;
            friend void create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* text3D);

            yli::ontology::ParentModule parent_of_objects;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            std::string text_string;
    };
}

#endif
