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

#ifndef __YLIKUUTIO_ONTOLOGY_TEXT_3D_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_TEXT_3D_HPP_INCLUDED

#include "movable.hpp"
#include "child_module.hpp"
#include "parent_module.hpp"
#include "glyph_object_creation.hpp"
#include "text_3d_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;
    class Shader;
    class Object;
    class ParentModule;
    class GenericMasterModule;
    class VectorFont;

    class Text3D: public yli::ontology::Movable
    {
        public:
            // This method disables all character `Object`s of this `Text3D`,
            // sets `parent` according to the input, requests a new `childID`
            // from the new `VectorFont`, and creates and enables the needed
            // character `Object`s of this `Text3D`.
            // Note: different fonts may provide glyphs for different Unicode code points!
            void bind_to_new_vector_font_parent(yli::ontology::VectorFont* const new_vector_font_pointer);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            Text3D(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::Text3DStruct& text_3d_struct,
                    yli::ontology::ParentModule* const parent_module,
                    yli::ontology::GenericMasterModule* const generic_master_module)
                : Movable(
                        universe,
                        text_3d_struct,
                        parent_module,
                        generic_master_module),
                child_of_vector_font(parent_module, this),
                parent_of_objects(this, &this->registry, "objects")
            {
                // constructor.

                // TODO: `Text3D` constructor also creates each `Object`,
                // and binds each to its corresponding `Glyph` for rendering hierarchy,
                // and also binds each to this `Text3D` for ontological hierarchy.

                this->text_string = text_3d_struct.text_string;

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

            friend class yli::ontology::Object;
            friend void yli::ontology::create_glyph_objects(const std::string& text_string, yli::ontology::Text3D* text_3d);

            yli::ontology::ChildModule child_of_vector_font;
            yli::ontology::ParentModule parent_of_objects;

        private:
            yli::ontology::Scene* get_scene() const override;

        public:
            yli::ontology::Shader* get_shader() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            std::string text_string;
    };
}

#endif
