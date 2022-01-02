// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "rigid_body_module.hpp"
#include "universe.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "brain.hpp"
#include "rigid_body_module.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/pi.hpp"
#include "code/ylikuutio/render/render_master.hpp"

// Include Bullet
#include <btBulletDynamicsCommon.h>

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;

    Scene::~Scene()
    {
        // destructor.
        std::cout << "`Scene` with childID " << std::dec << this->childID << " will be destroyed.\n";

        if (this->universe != nullptr && this->universe->get_active_scene() == this)
        {
            // Set active `Scene` to `nullptr`.
            this->universe->set_active_scene(nullptr);
        }
    }

    void Scene::do_physics()
    {
        if (this->universe == nullptr)
        {
            return;
        }

        // TODO: implement physics using Bullet!
    }

    void Scene::act()
    {
        // Intentional actors (AIs and keyboard controlled ones).

        for (std::size_t brain_i = 0; brain_i < this->parent_of_brains.child_pointer_vector.size(); brain_i++)
        {
            yli::ontology::Brain* const brain = static_cast<yli::ontology::Brain*>(this->parent_of_brains.child_pointer_vector[brain_i]);

            if (brain != nullptr)
            {
                brain->act();
            }
        }
    }

    void Scene::activate()
    {
        if (this->universe != nullptr)
        {
            this->universe->set_active_scene(this);
        }
    }

    void Scene::render()
    {
        if (!this->should_be_rendered || this->universe == nullptr)
        {
            return;
        }

        yli::render::RenderMaster* const render_master = this->universe->get_render_master();

        if (render_master == nullptr)
        {
            std::cerr << "ERROR: `Scene::render`: `render_master` is `nullptr`!\n";
            return;
        }

        this->prerender();
        render_master->render_shaders_of_ecosystems(this->universe->get_ecosystem_shaders(), this);
        render_master->render_shaders(this->parent_of_shaders);
        this->postrender();
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
            old_active_camera->set_roll(this->universe->current_camera_roll);
            old_active_camera->set_yaw(this->universe->current_camera_yaw);
            old_active_camera->set_pitch(this->universe->current_camera_pitch);
        }

        // It is OK to disactivate the active camera by setting `active_camera` to `nullptr`.
        this->active_camera = camera;

        // requirements for further actions:
        // `this->universe` must not be `nullptr`.
        // `this->parent` must not be `nullptr`.

        if (this->universe == nullptr)
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
            // and this is the active `Scene` in the active `Universe`.
            // Copy `Camera`'s coordinates and angles to the `Universe`.
            this->universe->current_camera_cartesian_coordinates = camera->get_cartesian_coordinates();
            this->universe->current_camera_roll = camera->get_roll();
            this->universe->current_camera_yaw = camera->get_yaw();
            this->universe->current_camera_pitch = camera->get_pitch();
        }
    }

    yli::ontology::Entity* Scene::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    yli::ontology::Scene* Scene::get_scene() const
    {
        return const_cast<yli::ontology::Scene*>(this);
    }

    std::size_t Scene::get_number_of_children() const
    {
        return this->parent_of_shaders.get_number_of_children() +
            this->parent_of_default_camera.get_number_of_children() +
            this->parent_of_cameras.get_number_of_children() +
            this->parent_of_brains.get_number_of_children() +
            this->parent_of_materials.get_number_of_children() +
            this->parent_of_species.get_number_of_children() +
            this->parent_of_objects.get_number_of_children() +
            this->parent_of_symbioses.get_number_of_children();
    }

    std::size_t Scene::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_shaders.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_default_camera.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_cameras.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_brains.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_materials.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_species.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_objects.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_symbioses.child_pointer_vector);
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

    void Scene::add_rigid_body_module(const yli::ontology::RigidBodyModule& rigid_body_module, yli::ontology::Scene* const scene)
    {
        if (scene == nullptr)
        {
            std::cerr << "ERROR: `Scene::add_rigid_body_module`: `scene` is `nullptr`!\n";
            return;
        }

        if (this->dynamics_world == nullptr)
        {
            std::cerr << "ERROR: `Scene::add_rigid_body_module`: `this->dynamics_world` is `nullptr`!\n";
            return;
        }

        btRigidBody* const bullet_rigid_body = rigid_body_module.get_bullet_rigid_body();

        if (bullet_rigid_body == nullptr)
        {
            std::cerr << "ERROR: `Scene::add_rigid_body_module`: `bullet_rigid_body` is `nullptr`!\n";
            return;
        }

        this->dynamics_world->addRigidBody(bullet_rigid_body);
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
