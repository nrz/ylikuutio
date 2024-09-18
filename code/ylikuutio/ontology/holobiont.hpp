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

#ifndef YLIKUUTIO_ONTOLOGY_HOLOBIONT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_HOLOBIONT_HPP_INCLUDED

#include "movable.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <string>   // std::string
#include <vector>   // std::vector

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
    class GenericMasterModule;
    class Entity;
    class Universe;
    class Scene;
    class Symbiosis;
    struct HolobiontStruct;

    class Holobiont : public Movable
    {
        protected:
            Holobiont(
                    yli::core::Application& application,
                    Universe& universe,
                    const HolobiontStruct& holobiont_struct,
                    GenericParentModule* const scene_parent_module,
                    GenericMasterModule* const symbiosis_master_module,
                    GenericMasterModule* const brain_master_module);

            virtual ~Holobiont() = default;

        public:
            Holobiont(const Holobiont&) = delete;            // Delete copy constructor.
            Holobiont& operator=(const Holobiont&) = delete; // Delete copy assignment.

            Entity* get_parent() const final;

            void update_x(const float x);
            void update_y(const float y);
            void update_z(const float z);

            // Public callbacks.

            static std::optional<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z(
                    Scene& parent,
                    Symbiosis& symbiosis,
                    const std::string& holobiont_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z);

            static std::optional<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z_yaw_pitch(
                    Scene& parent,
                    Symbiosis& symbiosis,
                    const std::string& holobiont_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z,
                    const std::string& yaw,
                    const std::string& pitch);

            static std::optional<yli::data::AnyValue> create_holobiont_with_parent_name_x_y_z_roll_yaw_pitch(
                    Scene& parent,
                    Symbiosis& symbiosis,
                    const std::string& holobiont_name,
                    const std::string& x,
                    const std::string& y,
                    const std::string& z,
                    const std::string& roll,
                    const std::string& yaw,
                    const std::string& pitch);

            // Public callbacks end here.

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_scene;
            GenericParentModule parent_of_bionts;
            ApprenticeModule apprentice_of_symbiosis;

            Scene* get_scene() const final;

            Symbiosis* get_symbiosis() const;

        private:
            std::size_t get_number_of_children() const final;
            std::size_t get_number_of_descendants() const final;

        public:
            // this method renders this `Holobiont`.
            void render(const Scene* const target_scene);

        private:
            static void create_bionts(Holobiont& holobiont, const std::vector<bool>& should_render_bionts_vector);
    };
}

#endif
