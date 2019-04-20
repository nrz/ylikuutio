#ifndef __GPGPU_TEST_SCENE_HPP_INCLUDED
#define __GPGPU_TEST_SCENE_HPP_INCLUDED

namespace yli
{
    namespace ontology
    {
        class World;
        class Entity;
        class EntityFactory;
    }
}

namespace gpgpu_test
{
    yli::ontology::Entity* create_gpgpu_test_scene(yli::ontology::EntityFactory* entity_factory, yli::ontology::World* const world);
}

#endif
