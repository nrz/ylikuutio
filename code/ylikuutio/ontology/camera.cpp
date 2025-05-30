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

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "camera.hpp"
#include "movable.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "camera_struct.hpp"
#include "code/ylikuutio/geometry/degrees_to_radians.hpp"
#include "code/ylikuutio/opengl/ubo_block_enums.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cerr
#include <utility>  // std::move

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;

    Camera::Camera(
            yli::core::Application& application,
            Universe& universe,
            const CameraStruct& camera_struct,
            GenericParentModule* const scene_parent_module,
            GenericMasterModule* const brain_master_module)
        : Movable(
                application,
                universe,
                camera_struct,
                brain_master_module),
        child_of_scene(scene_parent_module, *this)
    {
        if (this->universe.get_is_opengl_in_use())
        {
            // Uniform block for this `Camera`.
            glGenBuffers(1, &this->camera_uniform_block);
            glBindBuffer(GL_UNIFORM_BUFFER, this->camera_uniform_block);
            glBufferData(GL_UNIFORM_BUFFER, yli::opengl::camera_ubo::CameraUboBlockOffsets::TOTAL_SIZE, nullptr, GL_STATIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }
        else if (this->universe.get_is_vulkan_in_use())
        {
            std::cerr << "ERROR: `Camera::Camera`: Vulkan is not supported yet!\n";
        }

        this->activate();

        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Camera*";
    }

    Entity* Camera::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    void Camera::activate()
    {
        Scene* const scene = this->get_scene();

        if (scene != nullptr)
        {
            scene->set_active_camera(this);
        }
    }

    void Camera::render()
    {
        // Set the uniform values specific to a `Camera`.
        // This is a work in progress.

        glBindBufferBase(GL_UNIFORM_BUFFER, yli::opengl::UboBlockIndices::CAMERA, this->camera_uniform_block);
    }

    Scene* Camera::get_scene() const
    {
        return static_cast<Scene*>(this->child_of_scene.get_parent());
    }

    std::size_t Camera::get_number_of_children() const
    {
        return 0; // `Camera` has no children.
    }

    std::size_t Camera::get_number_of_descendants() const
    {
        return 0; // `Camera` has no children.
    }

    void Camera::compute_and_update_matrices_from_inputs(const float initial_fov, const float aspect_ratio, const float znear, const float zfar)
    {
        // Compute the projection matrix.
        this->set_projection_matrix(glm::perspective(
                    yli::geometry::degrees_to_radians(initial_fov),
                    aspect_ratio,
                    znear,
                    zfar));

        // Compute the view matrix.
        this->set_view_matrix(glm::lookAt(
                    this->location.xyz,                   // Camera coordinates.
                    this->location.xyz + this->direction, // Camera looks here: at the same position, plus "current_camera_direction".
                    this->up));                           // Head is up (set to 0,-1,0 to look upside-down).
    }

    const glm::mat4& Camera::get_projection_matrix() const
    {
        return this->projection_matrix;
    }

    void Camera::set_projection_matrix(glm::mat4&& projection_matrix)
    {
        this->projection_matrix = std::move(projection_matrix);
    }

    const glm::mat4& Camera::get_view_matrix() const
    {
        return this->view_matrix;
    }

    void Camera::set_view_matrix(glm::mat4&& view_matrix)
    {
        this->view_matrix = std::move(view_matrix);
    }

    GLuint Camera::get_camera_uniform_block() const
    {
        return this->camera_uniform_block;
    }
}
