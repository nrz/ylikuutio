#ifndef __ENTITY_HPP_INCLUDED
#define __ENTITY_HPP_INCLUDED

// Include standard headers
#include <vector>   // std::vector

namespace ontology
{
    class Entity
    {
        public:
            // constructor.
            Entity();

            // destructor.
            ~Entity();

        protected:
            std::vector<void*> child_vector_pointers_vector;
    };
}
#endif
