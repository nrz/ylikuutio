namespace ontology
{
    class Entity;
    class EntityFactory;
}

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    ontology::Entity* create_helsinki_east_downtown_scene(std::shared_ptr<ontology::EntityFactory> entity_factory);
}
