#ifndef __ENTITY_TEMPLATES_HPP_INCLUDED
#define __ENTITY_TEMPLATES_HPP_INCLUDED

#include "universe.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace ontology
{
    template<class T1>
        void set_name(std::string name, T1* entity)
        {
            datatypes::AnyValue* entity_any_value = new datatypes::AnyValue(entity);
            ontology::Universe* universe = entity->universe_pointer;
            universe->entity_anyvalue_map[name] = entity_any_value;
        }
}

#endif
