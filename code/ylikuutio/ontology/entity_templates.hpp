#ifndef __ENTITY_TEMPLATES_HPP_INCLUDED
#define __ENTITY_TEMPLATES_HPP_INCLUDED

#include "universe.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace ontology
{
    template<class T1>
        void set_name(std::string name, T1 entity)
        {
            ontology::Universe* universe = entity->universe_pointer;

            if (universe == nullptr)
            {
                return;
            }

            datatypes::AnyValue* entity_any_value = new datatypes::AnyValue(entity);

            if (entity_any_value == nullptr)
            {
                return;
            }

            if (universe->entity_anyvalue_map[name] != nullptr)
            {
                return;
            }

            entity->name = name;
            universe->entity_anyvalue_map[name] = entity_any_value;
        }
}

#endif
