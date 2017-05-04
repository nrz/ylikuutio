#include "entity.hpp"

// Include standard headers
#include <string>   // std::string

namespace ontology
{
    Entity::Entity()
    {
    }

    Entity::~Entity()
    {
    }

    // set name of this entity.
    void Entity::set_name(std::string name)
    {
        this->name = name;
    }
}
