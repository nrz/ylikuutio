#include "object.hpp"

namespace ontology
{
    class Universe;

    class Vehicle: public ontology::Object
    {
        public:
            // constructor.
            Vehicle(ontology::Universe* const universe, ObjectStruct& object_struct)
                : Object(universe, object_struct)
            {
                // constructor.
            }

            // destructor.
            virtual ~Vehicle();
    };
}
