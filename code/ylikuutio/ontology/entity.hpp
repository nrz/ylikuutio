#ifndef __ENTITY_HPP_INCLUDED
#define __ENTITY_HPP_INCLUDED

#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
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
            virtual ~Entity();

            std::string get_type();

            virtual int32_t get_number_of_children() = 0;
            virtual int32_t get_number_of_descendants() = 0;

        protected:
            void prerender();
            void postrender();

            ontology::Universe* universe_pointer;            // pointer to the `Universe`.
            std::vector<void*> child_vector_pointers_vector;
            int32_t childID;

            std::string type;

            std::string name; // name of this entity.

            PreRenderCallback prerender_callback;
            PostRenderCallback postrender_callback;
    };
}
#endif
