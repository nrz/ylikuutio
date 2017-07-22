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
}
