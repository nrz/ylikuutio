#ifndef __AJOKKI_TALLINN_SCENE_HPP_INCLUDED
#define __AJOKKI_TALLINN_SCENE_HPP_INCLUDED

namespace yli
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
    yli::ontology::Entity* create_tallinn_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world);
}

#endif
