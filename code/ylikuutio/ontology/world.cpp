// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "world.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "camera.hpp"
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

        void World::bind_Scene(yli::ontology::Scene* const scene)
        {
            // get `childID` from `World` and set pointer to `scene`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Scene*>(
                    scene,
                    this->scene_pointer_vector,
                    this->free_sceneID_queue,
                    this->number_of_scenes);
        }

        void World::unbind_Scene(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->scene_pointer_vector,
                    this->free_sceneID_queue,
                    this->number_of_scenes);
        }

        void World::bind_to_parent()
        {
            // Requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::Universe* const universe = this->parent;

            if (universe == nullptr)
            {
                std::cerr << "ERROR: `World::bind_to_parent`: `universe` is `nullptr`!\n";
                return;
            }

            // Get `childID` from the `Universe` and set pointer to this `World`.
            universe->bind_World(this);
        }

        World::~World()
        {
            // destructor.
            std::cout << "This world will be destroyed.\n";

            // Destroy all `Scene`s of this `World`.
            std::cout << "All scenes of this world will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Scene*>(this->scene_pointer_vector, this->number_of_scenes);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Universe* const universe = this->parent;

            if (universe == nullptr)
            {
                std::cerr << "ERROR: `World::~World`: `universe` is `nullptr`!\n";
                return;
            }

            // set pointer to this `World` to `nullptr`.
            universe->unbind_World(this->childID);
        }

        void World::do_physics()
        {
            if (this->active_scene != nullptr)
            {
                this->active_scene->do_physics();
            }
        }

        void World::act()
        {
            if (this->active_scene != nullptr)
            {
                this->active_scene->act();
            }
        }

        void World::render()
        {
            if (this->should_be_rendered && this->active_scene != nullptr)
            {
                this->prerender();

                // Render this `World` by calling `render()` function of the active `Scene`.
                this->active_scene->render();

                this->postrender();
            }
        }

        void World::set_active_scene(yli::ontology::Scene* const scene)
        {
            // Requirements:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Scene* const old_active_scene = this->active_scene;

            if (this->universe != nullptr && old_active_scene != nullptr)
            {
                yli::ontology::Camera* const old_active_camera = old_active_scene->get_active_camera();

                if (old_active_camera != nullptr && !old_active_camera->get_is_static_view())
                {
                    // OK, there is an old active `Camera`, and it is not a static view `Camera`.
                    // Copy the coordinates and angles from the `Universe` to the old active `Camera`.
                    old_active_camera->set_cartesian_coordinates(this->universe->current_camera_cartesian_coordinates);
                    old_active_camera->set_horizontal_angle(this->universe->current_camera_horizontal_angle);
                    old_active_camera->set_vertical_angle(this->universe->current_camera_vertical_angle);
                }
            }

            this->active_scene = scene;

            if (scene == nullptr || this->universe == nullptr)
            {
                // No active `Scene` at the moment,
                // or `this->universe` is `nullptr`.
                return;
            }

            this->universe->turbo_factor = scene->get_turbo_factor();
            this->universe->twin_turbo_factor = scene->get_twin_turbo_factor();

            yli::ontology::Camera* const camera = scene->get_active_camera();

            if (camera != nullptr)
            {
                // OK, the newly activated `Scene` has an active `Camera`.
                // Copy `Camera`'s coordinates and angles to the `Universe`.
                this->universe->current_camera_cartesian_coordinates = camera->get_cartesian_coordinates();
                this->universe->current_camera_horizontal_angle = camera->get_horizontal_angle();
                this->universe->current_camera_vertical_angle = camera->get_vertical_angle();
            }
        }

        yli::ontology::Scene* World::get_active_scene() const
        {
            return this->active_scene;
        }

        yli::ontology::Entity* World::get_parent() const
        {
            return this->parent;
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
