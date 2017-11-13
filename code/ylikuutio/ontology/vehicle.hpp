#include "object.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ontology
{
    class Universe;

    class Vehicle: public ontology::Object
    {
        public:
            // constructor.
            Vehicle(ontology::Universe* const universe, const ObjectStruct& object_struct)
                : Object(universe, object_struct)
            {
                // constructor.
            }

            // destructor.
            virtual ~Vehicle();
    };
}
