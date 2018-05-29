#include "entity.hpp"
#include "universe.hpp"
#include "code/ylikuutio/config/setting_master.hpp"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace ontology
{
    Entity::Entity(ontology::Universe* const universe)
    {
        // constructor.
        this->childID = -1;
        this->universe = universe;
        this->prerender_callback = nullptr;
        this->postrender_callback = nullptr;
        this->setting_master = new config::SettingMaster(this);
        this->can_be_erased = false;
    }

    Entity::~Entity()
    {
        // destructor.
        std::cout << "Entity destructor called.\n";

        std::cout << "The setting master of this entity will be destroyed.\n";
        delete this->setting_master;

        if (this->name.empty())
        {
            std::cerr << "Entity destructor: error: name is empty.\n";
            return;
        }

        if (this->universe == nullptr)
        {
            std::cerr << "Entity destructor: error: `universe` is `nullptr`.\n";
            return;
        }

        // OK, this `Entity` had a name, so it's name shall be erased.
        this->universe->erase_entity(this->name);
    }

    std::string Entity::get_type() const
    {
        return this->type;
    }

    bool Entity::get_can_be_erased() const
    {
        return this->can_be_erased;
    }

    ontology::Universe* Entity::get_universe() const
    {
        return this->universe;
    }

    config::SettingMaster* Entity::get_setting_master() const
    {
        return this->setting_master;
    }

    void Entity::set_setting_master(config::SettingMaster* const setting_master)
    {
        this->setting_master = setting_master;
    }

    void Entity::prerender() const
    {
        if (this->prerender_callback != nullptr &&
                this->universe != nullptr &&
                this->universe->setting_master != nullptr)
        {
            this->prerender_callback(this->universe, this->universe->setting_master);
        }
    }

    void Entity::postrender() const
    {
        if (this->postrender_callback != nullptr &&
                this->universe != nullptr &&
                this->universe->setting_master != nullptr)
        {
            this->postrender_callback(this->universe, this->universe->setting_master);
        }
    }

    void Entity::set_name(const std::string& name)
    {
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
