#include "entity.hpp"
#include "universe.hpp"

// Include standard headers
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace ontology
{
    Entity::Entity()
    {
        // constructor.
        this->prerender_callback = nullptr;
        this->postrender_callback = nullptr;
    }

    Entity::~Entity()
    {
        // destructor.

        if (!this->name.empty() && this->universe_pointer != nullptr)
        {
            // OK, this `Entity` had a name, so it's name shall be erased.
            if (this->universe_pointer->entity_anyvalue_map.count(this->name) != 0)
            {
                // OK, `Universe` knows the name of this `Entity`.
                delete this->universe_pointer->entity_anyvalue_map[this->name];
                this->universe_pointer->entity_anyvalue_map.erase(this->name);
            }
        }
    }

    void Entity::prerender()
    {
        if (this->prerender_callback != nullptr &&
                this->universe_pointer != nullptr &&
                this->universe_pointer->setting_master_pointer != nullptr)
        {
            this->prerender_callback(this->universe_pointer, this->universe_pointer->setting_master_pointer);
        }
    }

    void Entity::postrender()
    {
        if (this->postrender_callback != nullptr &&
                this->universe_pointer != nullptr &&
                this->universe_pointer->setting_master_pointer != nullptr)
        {
            this->postrender_callback(this->universe_pointer, this->universe_pointer->setting_master_pointer);
        }
    }
}
