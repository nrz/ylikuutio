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

#ifndef __YLIKUUTIO_ONTOLOGY_OBJECT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_OBJECT_HPP_INCLUDED

#include "movable.hpp"
#include "object_type.hpp"
#include "object_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Shader;
    class Species;
    class ShapeshifterSequence;
    class Text3D;
    class Glyph;
    class ParentModule;

    class Object: public yli::ontology::Movable
    {
        public:
            // this method sets pointer to this `Object` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Species` or from the new `Text3D`.
            void bind_to_new_parent(yli::ontology::Species* const new_parent);
            void bind_to_new_parent(yli::ontology::ShapeshifterSequence* const new_parent);
            void bind_to_new_parent(yli::ontology::Text3D* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            Object(yli::ontology::Universe* const universe, const yli::ontology::ObjectStruct& object_struct, yli::ontology::ParentModule* const parent_module)
                : Movable(
                        universe,
                        object_struct,
                        parent_module)
            {
                // constructor.

                this->object_type = object_struct.object_type;

                if (this->object_type == yli::ontology::ObjectType::CHARACTER)
                {
                    this->glyph = object_struct.glyph;
                }
                else
                {
                    this->glyph = nullptr;
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Object*";
                this->can_be_erased = true;
            }

            Object(const Object&) = delete;            // Delete copy constructor.
            yli::ontology::Object& operator=(const Object&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Object();

            yli::ontology::Glyph* get_glyph() const;

            // Public callbacks.

            static std::shared_ptr<yli::data::AnyValue> create_object_with_parent_name_x_y_z(
                    yli::ontology::Species* const parent,
                    std::shared_ptr<std::string> object_name,
                    std::shared_ptr<std::string> x,
                    std::shared_ptr<std::string> y,
                    std::shared_ptr<std::string> z);

            static std::shared_ptr<yli::data::AnyValue> create_object_with_parent_name_x_y_z_yaw_pitch(
                    yli::ontology::Species* const parent,
                    std::shared_ptr<std::string> object_name,
                    std::shared_ptr<std::string> x,
                    std::shared_ptr<std::string> y,
                    std::shared_ptr<std::string> z,
                    std::shared_ptr<std::string> yaw,
                    std::shared_ptr<std::string> pitch);

            // Public callbacks end here.

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // this method renders this `Object`.
            void render() override;
            void render_this_object(yli::ontology::Shader* const shader_pointer);

            yli::ontology::Glyph* glyph { nullptr }; // pointer to the `Glyph` (not a parent!).

            yli::ontology::ObjectType object_type { yli::ontology::ObjectType::REGULAR };
    };
}

#endif
