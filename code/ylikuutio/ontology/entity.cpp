#include "entity.hpp"
#include "universe.hpp"
#include "code/ylikuutio/config/setting_master.hpp"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli
{
    namespace ontology
    {
        Entity::Entity(yli::ontology::Universe* const universe)
        {
            // constructor.
            this->childID = std::numeric_limits<std::size_t>::max();
            this->universe = universe;
            this->prerender_callback = nullptr;
            this->postrender_callback = nullptr;
            this->setting_master = std::make_shared<yli::config::SettingMaster>(this);
            this->can_be_erased = false;
        }

        Entity::~Entity()
        {
            // destructor.
            std::cout << "Entity destructor called.\n";

            if (this->name.empty())
            {
                std::cerr << "ERROR: `Entity::~Entity`: `this->name` is empty.\n";
                return;
            }

            if (this->universe == nullptr)
            {
                std::cerr << "ERROR: `Entity::~Entity`: `this->universe` is `nullptr`.\n";
                return;
            }

            // OK, this `Entity` had a name, so it's name shall be erased.
            this->universe->erase_entity(this->name);
        }

        std::size_t Entity::get_childID() const
        {
            return this->childID;
        }

        std::string Entity::get_type() const
        {
            return this->type;
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
            // requirements:
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
            // requirements:
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

        void Entity::set_name(const std::string& name)
        {
            // requirements:
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
}
