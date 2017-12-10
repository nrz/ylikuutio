#include "object.hpp"

// Every intentional entity is a `Creature`.
// Every player-controlled character is a `Creature`.
// Every AI-controlled character is a `Creature`.
// If any intentional motion is wanted for an entity (eg. ship, spaceship, vehicle), then it should be a `Creature`.
// Available input methods may be different for player-controlled and AI-controlled characters.
// AI-controlled creatures may have limitations in their options, if so desired.
// For example, it may be useful to disable exit game and enter console functions from AI characters.

namespace ontology
{
    class Universe;

    class Creature: public ontology::Object
    {
        public:
            // constructor.
            Creature(ontology::Universe* const universe, const ObjectStruct& object_struct)
                : Object(universe, object_struct)
            {
                // constructor.
            }

            // destructor.
            virtual ~Creature();
    };
}
