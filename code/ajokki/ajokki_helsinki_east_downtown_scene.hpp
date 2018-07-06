namespace ylikuutio
{
    namespace ontology
    {
        class World;
        class Entity;
        class EntityFactory;
    }
}

namespace ajokki
{
    ylikuutio::ontology::Entity* create_helsinki_east_downtown_scene(ylikuutio::ontology::EntityFactory* entity_factory, ylikuutio::ontology::World* const world);
}
