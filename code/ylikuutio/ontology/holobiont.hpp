// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class GenericMasterModule;
    class Entity;
    class Universe;
    class Scene;
    class Symbiosis;
    struct HolobiontStruct;

    class Holobiont final : public yli::ontology::Movable
    {
        public:
            Holobiont(
                    yli::ontology::Universe& universe,
                    const yli::ontology::HolobiontStruct& holobiont_struct,
                    yli::ontology::GenericParentModule* const scene_parent,
                    yli::ontology::GenericMasterModule* const symbiosis_master,
                    yli::ontology::GenericMasterModule* const brain_master);

            Holobiont(const Holobiont&) = delete;            // Delete copy constructor.
            Holobiont& operator=(const Holobiont&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Holobiont() = default;

            yli::ontology::Entity* get_parent() const override;

            void update_x(const float x);
            void update_y(const float y);
            void update_z(const float z);

            // Public callbacks.

            static std::optional<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z(
                    yli::ontology::Scene& parent,
                    yli::ontology::Symbiosis& symbiosis,
                    const std::string& holobiont_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z);

            static std::optional<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z_yaw_pitch(
                    yli::ontology::Scene& parent,
                    yli::ontology::Symbiosis& symbiosis,
                    const std::string& holobiont_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z,
                    const std::string& yaw,
                    const std::string& pitch);

            static std::optional<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z_roll_yaw_pitch(
                    yli::ontology::Scene& parent,
                    yli::ontology::Symbiosis& symbiosis,
                    const std::string& holobiont_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z,
                    const std::string& roll,
                    const std::string& yaw,
                    const std::string& pitch);

            // Public callbacks end here.

            yli::ontology::ChildModule child_of_scene;
            yli::ontology::GenericParentModule parent_of_bionts;
            yli::ontology::ApprenticeModule apprentice_of_symbiosis;

            yli::ontology::Scene* get_scene() const override;

            yli::ontology::Symbiosis* get_symbiosis() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            // this method renders this `Holobiont`.
            void render(const yli::ontology::Scene* const target_scene);

        private:
            void create_bionts(const std::vector<bool>& should_render_bionts_vector);
    };
}

#endif
