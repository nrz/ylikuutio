// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "scene.hpp"
#include "universe.hpp"
#include "world.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "species.hpp"
#include "camera.hpp"
#include "brain.hpp"
#include "ground_level.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli
{
    namespace ontology
    {
        class Species;

        void Scene::bind_Shader(yli::ontology::Shader* const shader)
        {
            // get `childID` from `Scene` and set pointer to `shader`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Shader*>(
                    shader,
                    this->shader_pointer_vector,
                    this->free_shaderID_queue,
                    this->number_of_shaders);

            // `shader` needs to be added to the priority queue as well.
            this->shader_priority_queue.push(shader);
        }

        void Scene::bind_Camera(yli::ontology::Camera* const camera)
        {
            // get `childID` from `Scene` and set pointer to `camera`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Camera*>(
                    camera,
                    this->camera_pointer_vector,
                    this->free_cameraID_queue,
                    this->number_of_cameras);
        }

        void Scene::bind_Brain(yli::ontology::Brain* const brain)
        {
            // get `childID` from `Scene` and set pointer to `ai`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Brain*>(
                    brain,
                    this->brain_pointer_vector,
                    this->free_brainID_queue,
                    this->number_of_brains);
        }

        void Scene::unbind_Shader(const std::size_t childID)
        {
            // `shader` needs to be removed from the priority queue as well.
            this->shader_priority_queue.remove(childID);

            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->shader_pointer_vector,
                    this->free_shaderID_queue,
                    this->number_of_shaders);
        }

        void Scene::unbind_Camera(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->camera_pointer_vector,
                    this->free_cameraID_queue,
                    this->number_of_cameras);
        }

        void Scene::unbind_Brain(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->brain_pointer_vector,
                    this->free_brainID_queue,
                    this->number_of_brains);
        }

        void Scene::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::World* const world = this->parent;

            if (world == nullptr)
            {
                std::cerr << "ERROR: `Scene::bind_to_parent`: `world` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `World` and set pointer to this `Scene`.
            world->bind_Scene(this);
        }

        Scene::~Scene()
        {
            // destructor.
            std::cout << "Scene with childID " << std::dec << this->childID << " will be destroyed.\n";

            // destroy all `Shader`s of this `Scene`.
            std::cout << "All shaders of this scene will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Shader*>(this->shader_pointer_vector, this->number_of_shaders);

            // destroy all `Camera`s of this `Scene`.
            std::cout << "All cameras of this scene will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Camera*>(this->camera_pointer_vector, this->number_of_cameras);

            // destroy all `Brain`s of this `Scene`.
            std::cout << "All brains of this scene will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Brain*>(this->brain_pointer_vector, this->number_of_brains);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::World* const world = this->parent;

            if (world == nullptr)
            {
                std::cerr << "ERROR: `Scene::~Scene`: `world` is `nullptr`!\n";
                return;
            }

            // set pointer to this `Scene` to `nullptr`.
            world->unbind_Scene(this->childID);
        }

        void Scene::do_physics()
        {
            // Coordinates are stored in `Universe`,
            // but gravity and fall speed are stored in `Scene`.
            // Therefore, coordinates exist even in a void without any `Scene`.

            if (this->universe == nullptr)
            {
                return;
            }

            if (!this->is_flight_mode_in_use)
            {
                // Accelerate and fall.

                this->fall_speed += this->gravity;
                this->universe->current_camera_cartesian_coordinates.y -= this->fall_speed;

                // Adjust position according to the ground.

                if (this->terrain_species != nullptr)
                {
                    float ground_y = yli::ontology::get_floor_level(
                            this->terrain_species,
                            this->universe->current_camera_cartesian_coordinates);

                    if (!std::isnan(ground_y) && this->universe->current_camera_cartesian_coordinates.y < ground_y)
                    {
                        this->universe->current_camera_cartesian_coordinates.y = ground_y;
                        this->fall_speed = 0.0f;
                    }
                }
            }
        }

        void Scene::act()
        {
            // Intentional actors (AIs and keyboard controlled ones).

            for (std::size_t brain_i = 0; brain_i < this->brain_pointer_vector.size(); brain_i++)
            {
                yli::ontology::Brain* const brain = this->brain_pointer_vector[brain_i];

                if (brain != nullptr)
                {
                    brain->act();
                }
            }
        }

        void Scene::render()
        {
            if (this->should_be_rendered)
            {
                this->prerender();

                // render this `Scene` by calling `render()` function of each `Shader`.
                yli::ontology::render_children<yli::ontology::Shader*>(this->shader_pointer_vector);

                this->postrender();
            }
        }

        yli::ontology::Camera* Scene::get_active_camera() const
        {
            return this->active_camera;
        }

        void Scene::set_active_camera(yli::ontology::Camera* camera)
        {
            if (camera != nullptr && camera->get_parent() != this)
            {
                // `Camera`s of other `Scene`s can not be set
                // as the active `Camera` for this `Scene`.
                return;
            }

            yli::ontology::Camera* const old_active_camera = this->active_camera;

            if (this->universe != nullptr &&
                    old_active_camera != nullptr &&
                    !old_active_camera->get_is_static_view())
            {
                // OK, there is an old active `Camera`, and it is not a static view `Camera`.
                // Copy the coordinates and angles from the `Universe` to the old active `Camera`.
                old_active_camera->set_cartesian_coordinates(this->universe->current_camera_cartesian_coordinates);
                old_active_camera->set_horizontal_angle(this->universe->current_camera_horizontal_angle);
                old_active_camera->set_vertical_angle(this->universe->current_camera_vertical_angle);
            }

            // It is OK to disactivate the active camera by setting `active_camera` to `nullptr`.
            this->active_camera = camera;

            // requirements for further actions:
            // `this->universe` must not be `nullptr`.
            // `this->parent` must not be `nullptr`.

            if (this->universe == nullptr || this->parent == nullptr)
            {
                return;
            }

            yli::ontology::Scene* const active_scene = this->universe->get_active_scene();

            if (active_scene == nullptr)
            {
                return;
            }

            if (active_scene == this && camera != nullptr)
            {
                // OK, the newly activated `Camera` is not `nullptr`,
                // and this is the active `Scene` in the active `World`.
                // Copy `Camera`'s coordinates and angles to the `Universe`.
                this->universe->current_camera_cartesian_coordinates = camera->get_cartesian_coordinates();
                this->universe->current_camera_horizontal_angle = camera->get_horizontal_angle();
                this->universe->current_camera_vertical_angle = camera->get_vertical_angle();
            }
        }

        yli::ontology::Entity* Scene::get_parent() const
        {
            return this->parent;
        }

        std::size_t Scene::get_number_of_children() const
        {
            return this->number_of_shaders + this->number_of_cameras + this->number_of_brains;
        }

        std::size_t Scene::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->shader_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->camera_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->brain_pointer_vector);
        }

        // this method returns a pointer to an `Entity` using the name as key.
        yli::ontology::Entity* Scene::get_entity(const std::string& name) const
        {
            if (this->name_map.count(name) != 1)
            {
                return nullptr;
            }

            return this->name_map.at(name);
        }

        float Scene::get_turbo_factor() const
        {
            if (this->universe != nullptr &&
                    this == this->universe->get_active_scene())
            {
                return this->universe->turbo_factor;
            }

            return NAN;
        }

        void Scene::set_turbo_factor(const float turbo_factor)
        {
            this->turbo_factor = turbo_factor;

            if (this->universe != nullptr &&
                    this == this->universe->get_active_scene())
            {
                this->universe->turbo_factor = this->turbo_factor;
            }
        }

        float Scene::get_twin_turbo_factor() const
        {
            if (this->universe != nullptr &&
                    this == this->universe->get_active_scene())
            {
                return this->universe->twin_turbo_factor;
            }

            return NAN;
        }

        void Scene::set_twin_turbo_factor(const float twin_turbo_factor)
        {
            this->twin_turbo_factor = twin_turbo_factor;

            if (this->universe != nullptr &&
                    this == this->universe->get_active_scene())
            {
                this->universe->twin_turbo_factor = this->twin_turbo_factor;
            }
        }

        float Scene::get_gravity() const
        {
            return this->gravity;
        }

        void Scene::set_gravity(const float gravity)
        {
            this->gravity = gravity;
        }

        float Scene::get_fall_speed() const
        {
            return this->fall_speed;
        }

        void Scene::set_fall_speed(const float fall_speed)
        {
            this->fall_speed = fall_speed;
        }

        yli::ontology::Species* Scene::get_terrain_species() const
        {
            if (this->universe != nullptr &&
                    this == this->universe->get_active_scene())
            {
                return this->terrain_species;
            }

            return nullptr;
        }

        void Scene::set_terrain_species(yli::ontology::Species* const terrain_species)
        {
            yli::ontology::Material* const material = static_cast<yli::ontology::Material*>(terrain_species->get_parent());

            if (material == nullptr)
            {
                return;
            }

            yli::ontology::Shader* const shader = static_cast<yli::ontology::Shader*>(material->get_parent());

            if (shader == nullptr)
            {
                return;
            }

            if (shader->get_parent() == this)
            {
                this->terrain_species = terrain_species;
            }
        }

        yli::ontology::World* Scene::get_world_parent() const
        {
            return this->parent;
        }

        float Scene::get_water_level() const
        {
            return this->water_level;
        }

        bool Scene::get_is_flight_mode_in_use() const
        {
            return this->is_flight_mode_in_use;
        }

        void Scene::set_is_flight_mode_in_use(const bool is_flight_mode_in_use)
        {
            this->is_flight_mode_in_use = is_flight_mode_in_use;
        }
    }
}
