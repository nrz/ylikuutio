#ifndef __RAIL_VEHICLE_HPP_INCLUDED
#define __RAIL_VEHICLE_HPP_INCLUDED

#include "vehicle.hpp"
#include "object_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace yli
{
    namespace ontology
    {
        class Universe;

        class RailVehicle: public yli::ontology::Vehicle
        {
            public:
                // constructor.
                RailVehicle(yli::ontology::Universe* const universe, const ObjectStruct& object_struct)
                    : Vehicle(universe, object_struct)
                {
                    // constructor.

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::RailVehicle*";
                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~RailVehicle();
        };
    }
}

#endif
