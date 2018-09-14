#ifndef __VEHICLE_HPP_INCLUDED
#define __VEHICLE_HPP_INCLUDED

#include "object.hpp"

namespace yli
{
    namespace ontology
    {
        class Universe;

        class Vehicle: public yli::ontology::Object
        {
            public:
                // constructor.
                Vehicle(yli::ontology::Universe* const universe, const ObjectStruct& object_struct)
                    : Object(universe, object_struct)
                {
                    // constructor.

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Vehicle*";
                }

                // destructor.
                virtual ~Vehicle();
        };
    }
}

#endif
