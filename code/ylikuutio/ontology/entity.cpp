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

#include "entity.hpp"
#include "universe.hpp"
#include "parent_module.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli::ontology
{
    void Entity::bind_to_universe()
    {
        // Requirements:
        // `this->universe` must not be `nullptr`.
        yli::ontology::Universe* const universe = this->universe;

        if (universe == nullptr)
        {
            std::cerr << "ERROR: `Entity::bind_to_universe`: `universe` is `nullptr`!\n";
            return;
        }

        // Get `entityID` from the `Universe` and set pointer to this `Entity`.
        universe->bind_entity(this);
    }

    void Entity::bind_to_new_parent(yli::ontology::Entity* new_entity_parent)
    {
        // Do nothing.
        // `yli::ontology` classes which support binding must `override`
        // this `yli::ontology::Entity` base class implementation.
    }

    Entity::Entity(yli::ontology::Universe* const universe)
        : parent_of_any_struct_entities(this)
    {
        // constructor.
        this->universe = universe;

        // Get `entityID` from `Universe` and set pointer to this `Entity`.
        this->bind_to_universe();

        this->childID = std::numeric_limits<std::size_t>::max(); // `std::numeric_limits<std::size_t>::max()` means that `childID` is not defined.
        this->prerender_callback = nullptr;
        this->postrender_callback = nullptr;
        this->setting_master = std::make_shared<yli::config::SettingMaster>(this);
        this->can_be_erased = false;
        this->should_be_rendered = (this->universe == nullptr ? false : !this->universe->get_is_headless());

        yli::config::SettingStruct should_be_rendered_setting_struct(std::make_shared<yli::common::AnyValue>(this->should_be_rendered));
        should_be_rendered_setting_struct.name = "should_be_rendered";
        should_be_rendered_setting_struct.activate_callback = &yli::config::SettingMaster::activate_should_be_rendered;
        should_be_rendered_setting_struct.read_callback = &yli::config::SettingMaster::read_should_be_rendered;
        should_be_rendered_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(should_be_rendered_setting_struct);` ...\n";
        this->setting_master->create_setting(should_be_rendered_setting_struct);
    }

    Entity::~Entity()
    {
        // destructor.
        std::cout << "`Entity` destructor called.\n";

        if (this->universe == nullptr)
        {
            std::cerr << "ERROR: `Entity::~Entity`: `this->universe` is `nullptr`.\n";
            return;
        }

        this->universe->unbind_entity(this->entityID);

        if (this->name.empty())
        {
            return;
        }

        // OK, this `Entity` had a name, so it's name shall be erased.
        this->universe->erase_entity(this->name);
    }

    void Entity::render()
    {
    }

    std::size_t Entity::get_childID() const
    {
        return this->childID;
    }

    std::string Entity::get_type() const
    {
        return this->type_string;
    }

    bool Entity::get_can_be_erased() const
    {
        return this->can_be_erased;
    }

    yli::ontology::Universe* Entity::get_universe() const
    {
        return this->universe;
    }

    yli::config::SettingMaster* Entity::get_setting_master() const
    {
        if (this->setting_master == nullptr)
        {
            std::cerr << "ERROR: `Entity::get_setting_master`: `this->setting_master` is `nullptr`.\n";
            return nullptr;
        }

        return this->setting_master.get();
    }

    void Entity::prerender() const
    {
        // Requirements:
        // `this->prerender_callback` must not be `nullptr`.
        // `this->universe` must not be `nullptr`.
        // `this->universe->setting_master` must not be `nullptr`.

        if (this->prerender_callback != nullptr &&
                this->universe != nullptr &&
                this->universe->setting_master != nullptr)
        {
            this->prerender_callback(this->universe, this->universe->setting_master.get());
        }
    }

    void Entity::postrender() const
    {
        // Requirements:
        // `this->postrender_callback` must not be `nullptr`.
        // `this->universe` must not be `nullptr`.
        // `this->universe->setting_master` must not be `nullptr`.

        if (this->postrender_callback != nullptr &&
                this->universe != nullptr &&
                this->universe->setting_master != nullptr)
        {
            this->postrender_callback(this->universe, this->universe->setting_master.get());
        }
    }

    std::string Entity::get_name() const
    {
        return this->name;
    }

    void Entity::set_name(const std::string& name)
    {
        // Requirements:
        // `this->universe` must not be `nullptr`.
        // `name` must not be already in use.

        if (this->universe == nullptr)
        {
            return;
        }

        if (this->universe->is_entity(name))
        {
            // The name is already in use.
            return;
        }

        this->name = name;
        this->universe->add_entity(name, this);
    }
}
