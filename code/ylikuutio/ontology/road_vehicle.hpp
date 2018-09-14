#ifndef __ROAD_VEHICLE_HPP_INCLUDED
#define __ROAD_VEHICLE_HPP_INCLUDED

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

        class RoadVehicle: public yli::ontology::Vehicle
        {
            public:
                // constructor.
                RoadVehicle(yli::ontology::Universe* const universe, const ObjectStruct& object_struct)
                    : Vehicle(universe, object_struct)
                {
                    // constructor.

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::RoadVehicle*";
                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~RoadVehicle();
        };
    }
}

#endif
