// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_CAMERA_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CAMERA_HPP_INCLUDED

#include "movable.hpp"
#include "child_module.hpp"
#include "code/ylikuutio/opengl/ubo_block_enums.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

// How `yli::ontology::Camera` class works:
//
// By default no `Camera` is activated.
// `Universe` knows the coordinates and the angles.
// TODO: in the future, each `Scene` knows the coordinates and the angles.
//
// When the description below does not specifically say otherwise:
// * "active `Camera`" refers to the active `Camera` of the active `Scene`.
//
// When a `Camera` is activated:
// 1. If there is an active `Camera` in that `Scene` and the `Camera`
//    is not static view `Camera`, then the coordinates and angles are
//    copied from the `Universe` to the `Camera`.
// 2. The newly activated `Camera` is marked as the active `Camera` of
//    its parent `Scene`.
// 3. If parent `Scene` of the activated `Camera` is the active `Scene`,
//    then the coordinates and the angles of the `Camera` are copied
//    to the coordinates and angles of the `Universe`.
//
// When a `Scene` is activated:
// 1. If there is an active `Camera` in the current `Scene` and the `Camera`
//    is not static view `Camera`, then the coordinates and angles are
//    copied from the `Universe` to the `Camera`.
// 2. If the newly activated `Scene` has an activated `Camera`, then
//    the coordinates and angles of that `Camera` are copied to the `Universe`.
//
// When a `Camera` is deleted:
// 1. If the `Camera` is the active `Camera` in its parent `Scene`, then
//    the active `Camera` of that `Scene` is set to `nullptr`.
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
    class Entity;
    class Universe;
    class Scene;
    class GenericParentModule;
    class GenericMasterModule;
    struct CameraStruct;

    class Camera final : public Movable
    {
        private:
            Camera(
                    yli::core::Application& application,
                    Universe& universe,
                    const CameraStruct& camera_struct,
                    GenericParentModule* const scene_parent_module,
                    GenericMasterModule* const brain_master_module);

            ~Camera() = default;

        public:
            Camera(const Camera&) = delete;            // Delete copy constructor.
            Camera& operator=(const Camera&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            void activate() override;

            void render();

            const glm::mat4& get_projection_matrix() const;
            void set_projection_matrix(glm::mat4&& projection_matrix);

            const glm::mat4& get_view_matrix() const;
            void set_view_matrix(glm::mat4&& view_matrix);

            GLuint get_camera_uniform_block() const;

            friend class Universe;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_scene;

            Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        private:
            // variables related to the projection.
            glm::mat4 projection_matrix { glm::mat4(1.0f) }; // identity matrix (dummy value).
            glm::mat4 view_matrix { glm::mat4(1.0f) };       // identity matrix (dummy value).

            GLuint camera_uniform_block { 0 };
    };
}

#endif
