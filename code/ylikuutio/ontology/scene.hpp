// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_SCENE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SCENE_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "parent_of_pipelines_module.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>   // NAN
#include <cstddef> // std::size_t

// How `Scene` class works:
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

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
    class Camera;
    class Symbiosis;
    class RigidBodyModule;
    struct SceneStruct;

    class Scene final : public Entity
    {
        private:
            Scene(
                    yli::core::Application& application,
                    Universe& universe,
                    const SceneStruct& scene_struct,
                    GenericParentModule* const universe_parent_module);

            ~Scene();

        public:
            Scene(const Scene&) = delete;            // Delete copy constructor.
            Scene& operator=(const Scene&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            // this method processes the physics.
            void do_physics();

            // Intentional actors (AIs and keyboard controlled ones).
            void update();

            void activate() override;

            // this method renders all `Pipeline`s of this `Scene`.
            void render();

            Camera* get_default_camera() const;

            Camera* get_active_camera() const;
            void set_active_camera(Camera* camera);

            // this method returns a pointer to `yli::data::AnyValue` corresponding to the given `key`.
            float get_turbo_factor() const;
            void set_turbo_factor(const float turbo_factor);
            float get_twin_turbo_factor() const;
            void set_twin_turbo_factor(const float turbo_factor);

            float get_gravity() const;
            void set_gravity(const float gravity);

            void add_rigid_body_module(const RigidBodyModule& rigid_body_module, Scene& scene);

            const glm::vec4& get_light_position() const;
            float get_water_level() const;

            bool get_is_flight_mode_in_use() const;
            void set_is_flight_mode_in_use(const bool is_flight_mode_in_use);

            GenericParentModule* get_generic_parent_module(const int type);

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_universe;
            GenericParentModule parent_of_brains;
            GenericParentModule parent_of_waypoints;
            GenericParentModule parent_of_cameras;
            ParentOfPipelinesModule parent_of_pipelines;
            GenericParentModule parent_of_materials;
            GenericParentModule parent_of_species;
            GenericParentModule parent_of_objects;
            GenericParentModule parent_of_symbioses;
            GenericParentModule parent_of_holobionts;
            GenericParentModule parent_of_shapeshifters;
            GenericParentModule parent_of_text_3ds;

            Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            Camera* active_camera { nullptr };

            // Variables related to location and orientation.

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            glm::vec3* cartesian_coordinates { nullptr };

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 direction;

            glm::vec3 right; // note: `right` can not be set directly using console.
            glm::vec3 up;    // note: `up` can not be set directly using console.

            GLuint scene_uniform_block { 0 };

            float roll  { NAN };
            float yaw   { NAN };
            float pitch { NAN };

            float turbo_factor      { 1.0f };
            float twin_turbo_factor { 1.0f };

            // Variables related to physics.
            float gravity;

            glm::vec4 light_position;
            float water_level;

            bool is_flight_mode_in_use;
    };
}

#endif
