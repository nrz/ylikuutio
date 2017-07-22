#ifndef __ENTITY_HPP_INCLUDED
#define __ENTITY_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace ontology
{
    class Universe;

    class Entity
    {
        public:
            // constructor.
            Entity();

            // destructor.
            ~Entity();

            virtual int32_t get_number_of_children() = 0;
            virtual int32_t get_number_of_descendants() = 0;

        protected:
            ontology::Universe* universe_pointer;            // pointer to the `Universe`.
            std::vector<void*> child_vector_pointers_vector;
    };
}
#endif
