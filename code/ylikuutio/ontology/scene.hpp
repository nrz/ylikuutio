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

#ifndef __SCENE_HPP_INCLUDED
#define __SCENE_HPP_INCLUDED

#include "entity.hpp"
#include "shader_priority_queue.hpp"
#include "scene_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::priority_queue, std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// How `yli::ontology::Scene` class works:
//
// By default no `Scene` is activated.
// Each `World` knows its active `Scene`.
//
// TODO: in the future, each `Scene` knows the coordinates and the angles.
//
// When the description below does not specifically say otherwise:
// * "active `Scene`" refers to the active `Scene` of the active `World`.
// * "active `Camera`" refers to the active `Camera` of the active `Scene`.
//
// When a `Scene` is activated:
// 1. If there is an active `Camera` in the current `Scene` and the `Camera`
//    is not static view `Camera`, then the coordinates and angles are
//    copied from the `Universe` to the `Camera`.
// 2. The `Scene` is marked as the active `Scene` of its parent `World`.
// 3. The parent `World` is marked as the active `World` of the `Universe`.
// 4. If the newly activated `Scene` has an activated `Camera`, then
//    the coordinates and angles of that `Camera` are copied to the `Universe`.
//
// When a `Scene` is deleted:
// 1. Every child of `Scene` gets deleted as usual, including the `Camera`s.

namespace yli
{
    namespace common
    {
        struct SphericalCoordinatesStruct;
    }

    namespace ontology
    {
        class Universe;
        class World;
        class Shader;
        class Species;
        class Symbiosis;
        class Camera;
        class Brain;

        class Scene: public yli::ontology::Entity
        {
            public:
                void bind_Shader(yli::ontology::Shader* const shader);
                void bind_Camera(yli::ontology::Camera* const camera);
                void bind_Brain(yli::ontology::Brain* const brain);

                void unbind_Shader(const std::size_t childID);
                void unbind_Camera(const std::size_t childID);
                void unbind_Brain(const std::size_t childID);

                // This method sets pointer to this `Scene` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `World`.
                void bind_to_new_parent(yli::ontology::World* const new_parent);
                void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

                // constructor.
                Scene(yli::ontology::Universe* const universe, const yli::ontology::SceneStruct& scene_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent                = scene_struct.world;
                    this->gravity               = scene_struct.gravity;
                    this->fall_speed            = scene_struct.gravity;
                    this->water_level           = scene_struct.water_level;
                    this->cartesian_coordinates = nullptr;
                    this->spherical_coordinates = nullptr;
                    this->horizontal_angle      = NAN;
                    this->vertical_angle        = NAN;
                    this->turbo_factor          = 1.0f;
                    this->twin_turbo_factor     = 1.0f;

                    this->number_of_shaders     = 0;
                    this->number_of_cameras     = 0;
                    this->number_of_brains      = 0;
                    this->active_camera         = nullptr;
                    this->terrain_species       = nullptr;

                    this->is_flight_mode_in_use = scene_struct.is_flight_mode_in_use;

                    // get `childID` from `World` and set pointer to this `Scene`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->child_vector_pointers_vector.push_back(&this->shader_priority_queue);
                    this->type_string = "yli::ontology::Scene*";
                    this->can_be_erased = true;
                }

                Scene(const Scene&) = delete;            // Delete copy constructor.
                Scene &operator=(const Scene&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Scene();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                // this method processes the physics.
                void do_physics();

                // Intentional actors (AIs and keyboard controlled ones).
                void act();

                // this method renders all `Shader`s of this `Scene`.
                void render();

                yli::ontology::Camera* get_active_camera() const;
                void set_active_camera(yli::ontology::Camera* camera);

                // this method returns a pointer to an `Entity` using the name as key.
                yli::ontology::Entity* get_entity(const std::string& name) const;

                // this method returns a pointer to `yli::common::AnyValue` corresponding to the given `key`.
                std::shared_ptr<yli::common::AnyValue> get_variable(const std::string& key) const;
                float get_turbo_factor() const;
                void set_turbo_factor(const float turbo_factor);
                float get_twin_turbo_factor() const;
                void set_twin_turbo_factor(const float turbo_factor);

                float get_gravity() const;
                void set_gravity(const float gravity);
                float get_fall_speed() const;
                void set_fall_speed(const float fall_speed);

                yli::ontology::Species* get_terrain_species() const;

                // set terrain `Species` pointers in `Scene` and `Universe` so that they point to the chosen terrain `Species`.
                // currently there can be only one terrain `Species` in each `Scene` (used in collision detection).
                void set_terrain_species(yli::ontology::Species* const terrain_species);

                yli::ontology::World* get_world_parent() const;

                float get_water_level() const;

                bool get_is_flight_mode_in_use() const;
                void set_is_flight_mode_in_use(const bool is_flight_mode_in_use);

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::World* parent;   // pointer to the `World`.

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
                std::size_t number_of_shaders;

                std::vector<yli::ontology::Camera*> camera_pointer_vector;
                std::queue<std::size_t> free_cameraID_queue;
                std::size_t number_of_cameras;

                std::vector<yli::ontology::Brain*> brain_pointer_vector;
                std::queue<std::size_t> free_brainID_queue;
                std::size_t number_of_brains;

                yli::ontology::Camera* active_camera;

                yli::ontology::Species* terrain_species; // pointer to terrain `Species` (used in collision detection).

                // For finding any `Entity`s of this `Scene` by using its name.
                std::unordered_map<std::string, yli::ontology::Entity*> name_map;

                // Variables related to location and orientation.

                // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
                glm::vec3* cartesian_coordinates;

                // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
                glm::vec3 direction;

                glm::vec3 right; // note: `right` can not be set directly using console.
                glm::vec3 up;    // note: `up` can not be set directly using console.

                // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
                yli::common::SphericalCoordinatesStruct* spherical_coordinates;

                double horizontal_angle;
                double vertical_angle;

                float turbo_factor;
                float twin_turbo_factor;

                // Variables related to physics.
                float gravity;
                float fall_speed;

                float water_level;

                bool is_flight_mode_in_use;
        };
    }
}

#endif
