#include "world.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "code/ylikuutio/config/setting_master.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace ontology
    {
        class SettingMaster;

        void World::bind(yli::ontology::Scene* const scene)
        {
            // get `childID` from `World` and set pointer to `scene`.
            hierarchy::bind_child_to_parent<yli::ontology::Scene*>(
                    scene,
                    this->scene_pointer_vector,
                    this->free_sceneID_queue,
                    &this->number_of_scenes);
        }

        void World::bind_to_parent()
        {
            // get `childID` from `Universe` and set pointer to this `World`.
            this->parent->bind(this);
        }

        World::~World()
        {
            // destructor.
            std::cout << "This world will be destroyed.\n";

            // destroy all scenes of this world.
            std::cout << "All scenes of this world will be destroyed.\n";
            hierarchy::delete_children<yli::ontology::Scene*>(this->scene_pointer_vector, &this->number_of_scenes);
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

        void World::set_active_scene(yli::ontology::Scene* scene)
        {
            this->active_scene = scene;

            if (this->active_scene != nullptr)
            {
                this->parent->turbo_factor = this->active_scene->get_turbo_factor();
                this->parent->twin_turbo_factor = this->active_scene->get_twin_turbo_factor();
            }
        }

        yli::ontology::Scene* World::get_active_scene() const
        {
            return this->active_scene;
        }

        yli::ontology::Entity* World::get_parent() const
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

        void World::set_scene_pointer(const int32_t childID, yli::ontology::Scene* const child_pointer)
        {
            hierarchy::set_child_pointer(childID, child_pointer, this->scene_pointer_vector, this->free_sceneID_queue, &this->number_of_scenes);
        }
    }
}
