#include "world.hpp"
#include "universe.hpp"
#include "scene.hpp"

namespace ontology
{
    void World::bind_to_parent()
    {
        // get `childID` from `Universe` and set pointer to this `World`.
        hierarchy::bind_child_to_parent<ontology::World*>(this, this->parent->world_pointer_vector, this->parent->free_worldID_queue, &this->parent->number_of_worlds);
    }

    World::~World()
    {
        // destructor.
        std::cout << "This world will be destroyed.\n";

        // destroy all scenes of this world.
        std::cout << "All scenes of this world will be destroyed.\n";
        hierarchy::delete_children<ontology::Scene*>(this->scene_pointer_vector, &this->number_of_scenes);

        std::cout << "The setting master of this world will be destroyed.\n";
        delete this->setting_master;
    }

    void World::render()
    {
        if (this->active_scene != nullptr)
        {
            this->prerender();

            // render this `World` by calling `render()` function of the active `Scene`.
            this->active_scene->render();

            this->postrender();
        }
    }

    void World::set_active_scene(ontology::Scene* scene)
    {
        this->active_scene = scene;

        if (this->active_scene != nullptr)
        {
            this->parent->turbo_factor = this->active_scene->turbo_factor;
            this->parent->twin_turbo_factor = this->active_scene->twin_turbo_factor;
        }
    }

    ontology::Scene* World::get_active_scene()
    {
        return this->active_scene;
    }

    ontology::Entity* World::get_parent() const
    {
        // `World` has no parent.
        return nullptr;
    }

    int32_t World::get_number_of_children() const
    {
        return this->number_of_scenes;
    }

    int32_t World::get_number_of_descendants() const
    {
        return -1;
    }

    void World::set_scene_pointer(int32_t childID, ontology::Scene* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->scene_pointer_vector, this->free_sceneID_queue, &this->number_of_scenes);
    }
}
