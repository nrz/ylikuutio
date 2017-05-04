#ifndef _ENTITY_HPP_INCLUDED
#define _ENTITY_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace ontology
{
    class Entity
    {
        public:
            // constructor.
            Entity();

            // destructor.
            ~Entity();

            // set name of this entity.
            void set_name(std::string name);

        private:
            std::string name;
    };
}

#endif
