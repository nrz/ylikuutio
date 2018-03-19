#include "vehicle.hpp"
#include "object_struct.hpp"

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

    class RailVehicle: public ontology::Vehicle
    {
        public:
            // constructor.
            RailVehicle(ontology::Universe* const universe, ObjectStruct& object_struct)
                : Vehicle(universe, object_struct)
            {
                // constructor.
            }

            // destructor.
            virtual ~RailVehicle();
    };
}
