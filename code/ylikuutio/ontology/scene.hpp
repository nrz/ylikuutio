// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_SCENE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SCENE_HPP_INCLUDED

#include "entity.hpp"
#include "universe.hpp"
#include "camera.hpp"
#include "child_module.hpp"
#include "parent_module.hpp"
#include "shader_priority_queue.hpp"
#include "scene_struct.hpp"
#include "camera_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include Bullet
#include <btBulletDynamicsCommon.h>

// Include standard headers
#include <cmath>   // NAN, std::isnan, std::pow
#include <cstddef> // std::size_t
#include <memory>  // std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr
#include <queue>   // std::priority_queue, std::queue
#include <string>  // std::string
#include <vector>  // std::vector

// How `yli::ontology::Scene` class works:
//
// By default no `Scene` is activated.
// The `Universe` knows the active `Scene`.
//
// When the description below does not specifically say otherwise:
// * "active `Scene`" refers to the active `Scene`.
// * "active `Camera`" refers to the active `Camera` of the active `Scene`.
//
// When a `Scene` is activated:
// 1. If there is an active `Camera` in the current `Scene` and the `Camera`
//    is not static view `Camera`, then the coordinates and angles are
//    copied from the `Universe` to the `Camera`.
// 2. The `Scene` is marked as the active `Scene`.
// 3. If the newly activated `Scene` has an activated `Camera`, then
//    the coordinates and angles of that `Camera` are copied to the `Universe`.
//
// When a `Scene` is deleted:
// 1. Every child of `Scene` gets deleted as usual, including the `Camera`s.

namespace yli::data
{
    struct SphericalCoordinatesStruct;
}

namespace yli::ontology
{
    class Universe;
    class World;
    class Shader;
    class Species;
    class Symbiosis;
    class RigidBody;

    class Scene: public yli::ontology::Entity
    {
        public:
            void bind_shader(yli::ontology::Shader* const shader);

            void unbind_shader(const std::size_t childID, const std::string& local_name);

            // This method sets pointer to this `Scene` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `World`.
            void bind_to_new_world_parent(yli::ontology::World* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            Scene(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::SceneStruct& scene_struct,
                    yli::ontology::ParentModule* const parent_module)
                : Entity(universe, scene_struct),
                child_of_world(parent_module, this),
                parent_of_default_camera(this, &this->registry, "default_camera"),
                parent_of_cameras(this, &this->registry, "cameras"),
                parent_of_brains(this, &this->registry, "brains"),
                parent_of_rigid_bodies(this, &this->registry, "rigid_bodies")
            {
                // constructor.
                this->gravity     = scene_struct.gravity;
                this->fall_speed  = scene_struct.gravity;
                this->water_level = scene_struct.water_level;

                this->is_flight_mode_in_use = scene_struct.is_flight_mode_in_use;

                // create the default `Camera`.
                yli::ontology::CameraStruct camera_struct = scene_struct.default_camera_struct;
                camera_struct.parent = this;
                new yli::ontology::Camera(this->universe, camera_struct, &this->parent_of_default_camera, nullptr); // create the default camera.

                // Bullet variables.
                if (this->universe != nullptr)
                {
                    yli::ontology::Universe* const universe = this->universe;

                    this->dynamics_world = std::make_unique<btDiscreteDynamicsWorld>(
                            universe->get_dispatcher(),
                            universe->get_overlapping_pair_cache(),
                            universe->get_solver(),
                            universe->get_collision_configuration());

                    // Gravity is stored as a non-negative value, make it negative for Bullet.
                    this->dynamics_world->setGravity(btVector3(0.0f, -this->gravity, 0.0f));

                    // Bullet is now initialized for this `Scene`.
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Scene*";
                this->can_be_erased = true;
            }

            Scene(const Scene&) = delete;            // Delete copy constructor.
            Scene& operator=(const Scene&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Scene();

            yli::ontology::Entity* get_parent() const override;

            // this method processes the physics.
            void do_physics();

            // Intentional actors (AIs and keyboard controlled ones).
            void act();

            void activate() override;

            // this method renders all `Shader`s of this `Scene`.
            void render();

            yli::ontology::Camera* get_active_camera() const;
            void set_active_camera(yli::ontology::Camera* camera);

            // this method returns a pointer to `yli::data::AnyValue` corresponding to the given `key`.
            std::shared_ptr<yli::data::AnyValue> get_variable(const std::string& key) const;
            float get_turbo_factor() const;
            void set_turbo_factor(const float turbo_factor);
            float get_twin_turbo_factor() const;
            void set_twin_turbo_factor(const float turbo_factor);

            float get_gravity() const;
            void set_gravity(const float gravity);
            float get_fall_speed() const;
            void set_fall_speed(const float fall_speed);

            void add_rigid_body(yli::ontology::RigidBody* const rigid_body);

            yli::ontology::Species* get_terrain_species() const;

            // set terrain `Species` pointers in `Scene` and `Universe` so that they point to the chosen terrain `Species`.
            // currently there can be only one terrain `Species` in each `Scene` (used in collision detection).
            void set_terrain_species(yli::ontology::Species* const terrain_species);

            float get_water_level() const;

            bool get_is_flight_mode_in_use() const;
            void set_is_flight_mode_in_use(const bool is_flight_mode_in_use);

            yli::ontology::ChildModule child_of_world;
            yli::ontology::ParentModule parent_of_default_camera;
            yli::ontology::ParentModule parent_of_cameras;
            yli::ontology::ParentModule parent_of_brains;
            yli::ontology::ParentModule parent_of_rigid_bodies;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // `yli::ontology::ShaderPriorityQueue` is a priority queue for `Shader`s.
            // `yli::ontology::ShaderPriorityQueue` also has
            // a function `remove(const std::size_t childID)`.
            //
            // A priority queue is needed for `Shader`s in the future so that GPGPU
            // `Shader`s are rendered first so that their output textures can then be
            // used as input textures in other `Shader`s.
            //
            // Note: the output textures of GPGPU `Shader`s may be used as input textures
            // in later GPGPU `Shader`s. The rendering order within GPGPU `Shader`s is
            // according to the `childID` values, the GPGPU `Shader` with the smallest
            // `childID` first.
            yli::ontology::ShaderPriorityQueue shader_priority_queue;
            std::vector<yli::ontology::Shader*> shader_pointer_vector;
            std::queue<std::size_t> free_shaderID_queue;
            std::size_t number_of_shaders { 0 };

            yli::ontology::Camera* active_camera { nullptr };

            yli::ontology::Species* terrain_species { nullptr }; // pointer to terrain `Species` (used in collision detection).

            // Variables related to location and orientation.

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            glm::vec3* cartesian_coordinates { nullptr };

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 direction;

            glm::vec3 right; // note: `right` can not be set directly using console.
            glm::vec3 up;    // note: `up` can not be set directly using console.

            // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
            yli::data::SphericalCoordinatesStruct* spherical_coordinates { nullptr };

            std::unique_ptr<btDiscreteDynamicsWorld> dynamics_world { nullptr };
            btAlignedObjectArray<btCollisionShape*> collision_shapes;

            float yaw   { NAN };
            float pitch { NAN };

            float turbo_factor      { 1.0f };
            float twin_turbo_factor { 1.0f };

            // Variables related to physics.
            float gravity;
            float fall_speed;

            float water_level;

            bool is_flight_mode_in_use;
    };
}

#endif
