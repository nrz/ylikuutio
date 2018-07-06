#include "object.hpp"

namespace ylikuutio
{
    namespace ontology
    {
        class Universe;

        class Vehicle: public ylikuutio::ontology::Object
        {
            public:
                // constructor.
                Vehicle(ylikuutio::ontology::Universe* const universe, ObjectStruct& object_struct)
                    : Object(universe, object_struct)
                {
                    // constructor.
                }

                // destructor.
                virtual ~Vehicle();
        };
    }
}
