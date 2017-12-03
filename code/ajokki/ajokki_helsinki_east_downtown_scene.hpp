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
    ontology::Entity* create_helsinki_east_downtown_scene(ontology::EntityFactory* entity_factory, ontology::World* const world);
}
