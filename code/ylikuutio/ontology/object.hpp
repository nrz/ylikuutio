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

#ifndef __YLIKUUTIO_ONTOLOGY_OBJECT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_OBJECT_HPP_INCLUDED

#include "movable.hpp"
#include "child_module.hpp"
#include "object_type.hpp"
#include "object_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <string>   // std::string
#include <variant>  // std::holds_alternative, std::variant
#include <vector>   // std::vector

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;
    class Shader;
    class Species;
    class ShapeshifterSequence;
    class Text3D;
    class Glyph;
    class ParentModule;
    class GenericMasterModule;

    class Object: public yli::ontology::Movable
    {
        public:
            // this method sets pointer to this `Object` to `nullptr`, sets `parent` according to the input,
            // and requests a new `childID` from the new `Species` or from the new `Text3D`.
            void bind_to_new_species_parent(yli::ontology::Species* const new_parent);
            void bind_to_new_shapeshifter_sequence_parent(yli::ontology::ShapeshifterSequence* const new_parent);
            void bind_to_new_text_3d_parent(yli::ontology::Text3D* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            Object(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::ObjectStruct& object_struct,
                    yli::ontology::ParentModule* const mesh_parent_module,
                    yli::ontology::GenericMasterModule* const brain_master)
                : Movable(
                        universe,
                        object_struct,
                        brain_master),
                child(mesh_parent_module, this)
            {
                // constructor.

                if (std::holds_alternative<yli::ontology::Species*>(object_struct.parent))
                {
                    this->object_type = yli::ontology::ObjectType::REGULAR;
                }
                else if (std::holds_alternative<yli::ontology::ShapeshifterSequence*>(object_struct.parent))
                {
                    this->object_type = yli::ontology::ObjectType::SHAPESHIFTER;
                }
                else if (std::holds_alternative<yli::ontology::Text3D*>(object_struct.parent))
                {
                    this->object_type = yli::ontology::ObjectType::CHARACTER;
                    this->glyph = object_struct.glyph;
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Object*";
                this->can_be_erased = true;
            }

            Object(const Object&) = delete;            // Delete copy constructor.
            Object& operator=(const Object&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Object();

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::Glyph* get_glyph() const;

            // Public callbacks.

            static std::optional<yli::data::AnyValue> create_object_with_parent_name_x_y_z(
                    yli::ontology::Species& parent,
                    const std::string& object_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z);

            static std::optional<yli::data::AnyValue> create_object_with_parent_name_x_y_z_yaw_pitch(
                    yli::ontology::Species& parent,
                    const std::string& object_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z,
                    const std::string& yaw,
                    const std::string& pitch);

            static std::optional<yli::data::AnyValue> create_object_with_parent_name_x_y_z_roll_yaw_pitch(
                    yli::ontology::Species& parent,
                    const std::string& object_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z,
                    const std::string& roll,
                    const std::string& yaw,
                    const std::string& pitch);

            // Public callbacks end here.

            yli::ontology::Scene* get_scene() const override;

            yli::ontology::Shader* get_shader() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            // this method renders this `Object`.
            void render();

        private:
            void render_this_object(yli::ontology::Shader* const shader);

        public:
            yli::ontology::ChildModule child;

        private:
            yli::ontology::Glyph* glyph { nullptr }; // pointer to the `Glyph` (not a parent!).

            yli::ontology::ObjectType object_type { yli::ontology::ObjectType::REGULAR };
    };
}

#endif
