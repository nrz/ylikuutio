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

#ifndef __ENTITY_HPP_INCLUDED
#define __ENTITY_HPP_INCLUDED

#include "parent_module.hpp"
#include "pre_render_callback.hpp"
#include "post_render_callback.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli::config
{
    class SettingMaster;
}

namespace yli::ontology
{
    class Universe;

    class Entity
    {
        public:
            // Each class that supports binding to a new parent needs to `override` this function.
            virtual void bind_to_new_parent(yli::ontology::Entity* const new_entity_parent);

            // constructor.
            Entity(yli::ontology::Universe* const universe);

            Entity(const Entity&) = delete;            // Delete copy constructor.
            Entity &operator=(const Entity&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Entity();

            virtual void render();

            std::size_t get_childID() const;
            std::string get_type() const;

            bool get_can_be_erased() const;

            yli::ontology::Universe* get_universe() const;
            yli::config::SettingMaster* get_setting_master() const;
            void set_setting_master(yli::config::SettingMaster* const setting_master);

            virtual yli::ontology::Entity* get_parent() const = 0;
            virtual std::size_t get_number_of_children() const = 0;
            virtual std::size_t get_number_of_descendants() const = 0;

            void set_name(const std::string& name);

            bool should_be_rendered;

            friend yli::ontology::Universe;

            std::size_t childID; // TODO: add checks for `std::numeric_limits<std::size_t>::max();` (invalid value).

        protected:
            void prerender() const;
            void postrender() const;

            yli::ontology::Universe* universe;                          // pointer to the `Universe`.
            std::shared_ptr<yli::config::SettingMaster> setting_master; // pointer to the `SettingMaster`.
            std::size_t entityID;

            std::string type_string;

            std::string name;    // name of this `Entity`.

            bool can_be_erased;

            PreRenderCallback prerender_callback;
            PostRenderCallback postrender_callback;

            yli::ontology::ParentModule parent_of_any_struct_entities;

        private:
            void bind_to_Universe();
    };
}

#endif
