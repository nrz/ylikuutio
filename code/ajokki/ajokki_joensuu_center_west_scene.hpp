namespace ontology
{
    class World;
    class Entity;
    class EntityFactory;
}

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    ontology::Entity* create_joensuu_center_west_scene(ontology::EntityFactory* entity_factory, ontology::World* const world);
}
