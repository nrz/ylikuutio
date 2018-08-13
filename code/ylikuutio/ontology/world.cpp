#include "world.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/config/setting_master.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        class SettingMaster;

        void World::bind_scene(yli::ontology::Scene* const scene)
        {
            // get `childID` from `World` and set pointer to `scene`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Scene*>(
                    scene,
                    this->scene_pointer_vector,
                    this->free_sceneID_queue,
                    this->number_of_scenes);
        }

        void World::unbind_scene(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->scene_pointer_vector,
                    this->free_sceneID_queue,
                    this->number_of_scenes);
        }

        void World::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Universe* const universe = this->parent;

            if (universe == nullptr)
            {
                std::cerr << "ERROR: `World::bind_to_parent`: `universe` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `Universe` and set pointer to this `World`.
            universe->bind_world(this);
        }

        World::~World()
        {
            // destructor.
            std::cout << "This world will be destroyed.\n";

            // destroy all scenes of this world.
            std::cout << "All scenes of this world will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Scene*>(this->scene_pointer_vector, this->number_of_scenes);
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
            // requirements:
            // `this->parent` must not be `nullptr`.
            // `scene` must not be `nullptr`.

            yli::ontology::Universe* const universe = this->parent;

            if (universe == nullptr)
            {
                std::cerr << "ERROR: `World::set_active_scene`: `universe` is `nullptr`!\n";
                return;
            }

            if (scene == nullptr)
            {
                std::cerr << "ERROR: `World::set_active_scene`: `scene` is `nullptr`!\n";
                return;
            }

            this->active_scene = scene;
            universe->turbo_factor = this->active_scene->get_turbo_factor();
            universe->twin_turbo_factor = this->active_scene->get_twin_turbo_factor();
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

        std::size_t World::get_number_of_children() const
        {
            return this->number_of_scenes;
        }

        std::size_t World::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->scene_pointer_vector);
        }
    }
}
