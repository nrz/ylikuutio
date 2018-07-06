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
    ylikuutio::ontology::Entity* create_joensuu_center_west_scene(ylikuutio::ontology::EntityFactory* entity_factory, ylikuutio::ontology::World* const world);
}
