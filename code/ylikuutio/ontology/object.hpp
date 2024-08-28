// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_OBJECT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_OBJECT_HPP_INCLUDED

#include "movable.hpp"
#include "child_module.hpp"
#include "apprentice_module.hpp"
#include "object_type.hpp"
#include "object_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <string>   // std::string

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;
    class Pipeline;
    class Species;
    class ShapeshifterSequence;
    class Text3D;
    class GenericParentModule;
    class GenericMasterModule;

    class Object : public yli::ontology::Movable
    {
        public:
            // Set pointer to `object` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(
                    yli::ontology::Object& object,
                    yli::ontology::Scene& new_parent);

            // Set pointer to `object` to `nullptr`, set mesh according to the input,
            // and request a new apprenticeID from `new_species`.
            static std::optional<yli::data::AnyValue> bind_to_new_species_master(
                    yli::ontology::Object& object,
                    yli::ontology::Species& new_species) noexcept;

            // Set pointer to `object` to `nullptr`, set mesh according to the input,
            // and request a new apprenticeID from `new_shapeshifter_sequence`.
            static std::optional<yli::data::AnyValue> bind_to_new_shapeshifter_sequence_master(
                    yli::ontology::Object& object,
                    yli::ontology::ShapeshifterSequence& new_shapeshifter_sequence) noexcept;

            // Set pointer to `object` to `nullptr`, set mesh according to the input,
            // and request a new apprenticeID from `new_text_3d`.
            static std::optional<yli::data::AnyValue> bind_to_new_text_3d_master(
                    yli::ontology::Object& object,
                    yli::ontology::Text3D& new_text_3d) noexcept;

        protected:
            Object(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::ObjectStruct& object_struct,
                    yli::ontology::GenericParentModule* const scene_parent_module,
                    yli::ontology::GenericMasterModule* const mesh_master_module,
                    yli::ontology::GenericMasterModule* const brain_master_module);

            virtual ~Object() = default;

        public:
            Object(const Object&) = delete;            // Delete copy constructor.
            Object& operator=(const Object&) = delete; // Delete copy assignment.

            yli::ontology::Entity* get_parent() const final;

            // Public callbacks.

            static std::optional<yli::data::AnyValue> with_parent_name_x_y_z(
                    yli::ontology::Scene& parent,
                    yli::ontology::Species& species,
                    const std::string& object_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z);

            static std::optional<yli::data::AnyValue> with_parent_name_x_y_z_yaw_pitch(
                    yli::ontology::Scene& parent,
                    yli::ontology::Species& species,
                    const std::string& object_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z,
                    const std::string& yaw,
                    const std::string& pitch);

            static std::optional<yli::data::AnyValue> with_parent_name_x_y_z_roll_yaw_pitch(
                    yli::ontology::Scene& parent,
                    yli::ontology::Species& species,
                    const std::string& object_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z,
                    const std::string& roll,
                    const std::string& yaw,
                    const std::string& pitch);

            // Public callbacks end here.

            yli::ontology::Scene* get_scene() const final;

            yli::ontology::Pipeline* get_pipeline() const;

        private:
            std::size_t get_number_of_children() const final;
            std::size_t get_number_of_descendants() const final;

        public:
            // this method renders this `Object`.
            void render(const yli::ontology::Scene* const target_scene);

        private:
            void render_this_object(yli::ontology::Pipeline* const pipeline);

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

        public:
            yli::ontology::ChildModule child_of_scene;
            yli::ontology::ApprenticeModule apprentice_of_mesh;

        private:
            yli::ontology::ObjectType object_type { yli::ontology::ObjectType::REGULAR };
    };
}

#endif
