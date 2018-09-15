#ifndef __AJOKKI_JOENSUU_CENTER_WEST_SCENE_HPP_INCLUDED
#define __AJOKKI_JOENSUU_CENTER_WEST_SCENE_HPP_INCLUDED

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
    yli::ontology::Entity* create_joensuu_center_west_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world);
}

#endif
