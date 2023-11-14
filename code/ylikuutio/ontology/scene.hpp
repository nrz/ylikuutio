// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include <cmath>   // NAN, std::isnan, std::pow
#include <cstddef> // std::size_t
#include <string>  // std::string

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

namespace yli::core
{
    class Application;
}

namespace yli::data
{
    struct SphericalCoordinatesStruct;
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

    class Scene final : public yli::ontology::Entity
    {
        private:
            Scene(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::SceneStruct& scene_struct,
                    yli::ontology::GenericParentModule* const parent_module);

            ~Scene();

        public:
            Scene(const Scene&) = delete;            // Delete copy constructor.
            Scene& operator=(const Scene&) = delete; // Delete copy assignment.

            yli::ontology::Entity* get_parent() const override;

            // this method processes the physics.
            void do_physics();

            // Intentional actors (AIs and keyboard controlled ones).
            void act();

            void activate() override;

            // this method renders all `Pipeline`s of this `Scene`.
            void render();

            yli::ontology::Camera* get_default_camera() const;

            yli::ontology::Camera* get_active_camera() const;
            void set_active_camera(yli::ontology::Camera* camera);

            // this method returns a pointer to `yli::data::AnyValue` corresponding to the given `key`.
            float get_turbo_factor() const;
            void set_turbo_factor(const float turbo_factor);
            float get_twin_turbo_factor() const;
            void set_twin_turbo_factor(const float turbo_factor);

            float get_gravity() const;
            void set_gravity(const float gravity);

            void add_rigid_body_module(const yli::ontology::RigidBodyModule& rigid_body_module, yli::ontology::Scene& scene);

            const glm::vec4& get_light_position() const;
            float get_water_level() const;

            bool get_is_flight_mode_in_use() const;
            void set_is_flight_mode_in_use(const bool is_flight_mode_in_use);

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            yli::ontology::ChildModule child_of_universe;
            yli::ontology::ParentOfPipelinesModule parent_of_pipelines;
            yli::ontology::GenericParentModule parent_of_default_camera;
            yli::ontology::GenericParentModule parent_of_cameras;
            yli::ontology::GenericParentModule parent_of_brains;
            yli::ontology::GenericParentModule parent_of_materials;
            yli::ontology::GenericParentModule parent_of_species;
            yli::ontology::GenericParentModule parent_of_objects;
            yli::ontology::GenericParentModule parent_of_symbioses;
            yli::ontology::GenericParentModule parent_of_holobionts;

            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            yli::ontology::Camera* active_camera { nullptr };

            // Variables related to location and orientation.

            // `cartesian_coordinates` can be accessed as a vector or as single coordinates `x`, `y`, `z`.
            glm::vec3* cartesian_coordinates { nullptr };

            // `direction` can be accessed as a vector or as single coordinates `pitch`, `roll`, `yaw`.
            glm::vec3 direction;

            glm::vec3 right; // note: `right` can not be set directly using console.
            glm::vec3 up;    // note: `up` can not be set directly using console.

            // `spherical_coordinates` can be accessed as a vector or as single coordinates `rho`, `theta`, `phi`.
            yli::data::SphericalCoordinatesStruct* spherical_coordinates { nullptr };

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
