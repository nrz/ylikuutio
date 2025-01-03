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

#include "biont.hpp"
#include "mesh_module.hpp"
#include "universe.hpp"
#include "holobiont.hpp"
#include "symbiosis.hpp"
#include "symbiont_species.hpp"
#include "biont_struct.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ubo_block_enums.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_TYPE_PTR_HPP_INCLUDED
#define __GLM_GTC_TYPE_PTR_HPP_INCLUDED
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp> // glm::quat
#endif

// Include standard headers
#include <cstddef>   // std::size_t
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;
    class Scene;

    Biont::Biont(
            yli::core::Application& application,
            Universe& universe,
            const BiontStruct& biont_struct,
            GenericParentModule* const holobiont_parent_module,
            GenericMasterModule* const symbiont_species_master_module)
        : Movable(
                application,
                universe,
                biont_struct,
                nullptr),
        child_of_holobiont(holobiont_parent_module, *this),
        apprentice_of_symbiont_species(symbiont_species_master_module, this)
    {
        this->biontID       = biont_struct.biontID;
        this->should_render = biont_struct.should_render;

        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Biont*";
    }

    Entity* Biont::get_parent() const
    {
        return this->child_of_holobiont.get_parent();
    }

    void Biont::render()
    {
        // Render this `Biont`.
        //
        // Requirements:
        // `this->holobiont_parent` must not be `nullptr`.
        // `this->holobiont_parent->get_parent()` must not be `nullptr`.

        if (!this->should_render)
        {
            return;
        }

        const Holobiont* const holobiont_parent = static_cast<Holobiont*>(this->get_parent());

        if (holobiont_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Biont::render`: `holobiont_parent` is `nullptr`!");
        }

        const Symbiosis* const symbiosis_master_of_holobiont = holobiont_parent->get_symbiosis();

        if (symbiosis_master_of_holobiont == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Biont::render`: `symbiosis_master_of_holobiont` is `nullptr`!");
        }

        this->render_this_biont();
    }

    void Biont::render_this_biont()
    {
        // Requirements:
        // `this->holobiont_parent` must not be `nullptr`.
        // `this->symbiont_species` must not be `nullptr`.

        if (this->universe.get_render_system() == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Biont::render_this_biont`: `this->universe.get_render_system()` is `nullptr`!");
        }

        const Holobiont* const holobiont_parent = static_cast<Holobiont*>(this->get_parent());

        if (holobiont_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Biont::render_this_biont`: `holobiont_parent` is `nullptr`!");
        }

        Symbiosis* const symbiosis_master_of_holobiont = holobiont_parent->get_symbiosis();

        if (symbiosis_master_of_holobiont == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Biont::render_this_biont`: `symbiosis_master_of_holobiont` is `nullptr`!");
        }

        const SymbiontSpecies* const symbiont_species_master = static_cast<SymbiontSpecies*>(
                this->apprentice_of_symbiont_species.get_master());

        if (symbiont_species_master == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Biont::render_this_biont`: `symbiont_species_master` is `nullptr`!");
        }

        this->model_matrix = glm::mat4(1.0f);

        const std::string model_file_format = symbiosis_master_of_holobiont->get_model_file_format();

        if (this->initial_rotate_vectors.size() == this->initial_rotate_angles.size())
        {
            for (std::size_t i = 0; i < this->initial_rotate_vectors.size() && i < this->initial_rotate_angles.size(); i++)
            {
                this->model_matrix = glm::rotate(this->model_matrix, this->initial_rotate_angles[i], this->initial_rotate_vectors[i]);
            }
        }

        this->model_matrix = glm::scale(this->model_matrix, holobiont_parent->get_scale() * this->original_scale_vector);
        glm::vec3 euler_angles { holobiont_parent->orientation.roll, -holobiont_parent->orientation.pitch, holobiont_parent->orientation.yaw };
        glm::quat my_quaternion = glm::quat(euler_angles);
        glm::mat4 rotation_matrix = glm::mat4_cast(my_quaternion);
        this->model_matrix = rotation_matrix * this->model_matrix;
        this->model_matrix[3][0] = holobiont_parent->location.get_x();
        this->model_matrix[3][1] = holobiont_parent->location.get_y();
        this->model_matrix[3][2] = holobiont_parent->location.get_z();

        this->mvp_matrix = this->universe.get_projection_matrix() * this->universe.get_view_matrix() * this->model_matrix;

        if (this->universe.get_is_opengl_in_use())
        {
            // '`Material`' part begins here.

            // Bind our texture in Texture Unit 0.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, symbiosis_master_of_holobiont->get_texture(this->biontID));
            // Set our "texture_sampler" sampler to user Texture Unit 0.
            yli::opengl::uniform_1i(symbiosis_master_of_holobiont->get_openGL_textureID(this->biontID), 0);

            // '`Material`' part ends here.

            // '`Species`' part begins here.

            const MeshModule& mesh = symbiont_species_master->mesh;

            // 1st attribute buffer : vertices.
            yli::opengl::enable_vertex_attrib_array(mesh.get_vertex_position_modelspace_id());

            // 2nd attribute buffer : UVs.
            yli::opengl::enable_vertex_attrib_array(mesh.get_vertex_uv_id());

            // 3rd attribute buffer : normals.
            yli::opengl::enable_vertex_attrib_array(mesh.get_vertex_normal_modelspace_id());

            // '`Species`' part ends here.

            // Send our transformation to the uniform buffer object (UBO).

            // Matrices' uniform block gets updated by `Object`s and `Biont`s.
            glBindBuffer(GL_UNIFORM_BUFFER, this->movable_uniform_block);
            glBufferSubData(GL_UNIFORM_BUFFER, yli::opengl::movable_ubo::MovableUboBlockOffsets::MVP, sizeof(glm::mat4), glm::value_ptr(this->mvp_matrix)); // mat4
            glBufferSubData(GL_UNIFORM_BUFFER, yli::opengl::movable_ubo::MovableUboBlockOffsets::M, sizeof(glm::mat4), glm::value_ptr(this->model_matrix)); // mat4
            glBindBuffer(GL_UNIFORM_BUFFER, 0);

            glBindBufferBase(GL_UNIFORM_BUFFER, yli::opengl::UboBlockIndices::MOVABLE, this->movable_uniform_block);

            GLuint vao                             = mesh.get_vao();
            GLuint vertexbuffer                    = mesh.get_vertexbuffer();
            uint32_t vertex_position_modelspace_id = mesh.get_vertex_position_modelspace_id();
            GLuint uvbuffer                        = mesh.get_uvbuffer();
            uint32_t vertex_uv_id                  = mesh.get_vertex_uv_id();
            GLuint normalbuffer                    = mesh.get_normalbuffer();
            uint32_t vertex_normal_modelspace_id   = mesh.get_vertex_normal_modelspace_id();
            GLuint elementbuffer                   = mesh.get_elementbuffer();
            uint32_t indices_size                  = mesh.get_indices_size();

            glBindVertexArray(vao);

            // 1st attribute buffer : vertices.
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    vertex_position_modelspace_id, // The attribute we want to configure
                    3,                            // size
                    GL_FLOAT,                     // type
                    GL_FALSE,                     // normalized?
                    0,                            // stride
                    nullptr                       // array buffer offset
                    );
            yli::opengl::enable_vertex_attrib_array(vertex_position_modelspace_id);

            // 2nd attribute buffer : UVs.
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glVertexAttribPointer(
                    vertex_uv_id,                   // The attribute we want to configure
                    2,                            // size : U+V => 2
                    GL_FLOAT,                     // type
                    GL_FALSE,                     // normalized?
                    0,                            // stride
                    nullptr                       // array buffer offset
                    );
            yli::opengl::enable_vertex_attrib_array(vertex_uv_id);

            // 3rd attribute buffer : normals.
            glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
            glVertexAttribPointer(
                    vertex_normal_modelspace_id,   // The attribute we want to configure
                    3,                            // size
                    GL_FLOAT,                     // type
                    GL_FALSE,                     // normalized?
                    0,                            // stride
                    nullptr                       // array buffer offset
                    );
            yli::opengl::enable_vertex_attrib_array(vertex_normal_modelspace_id);

            // Index buffer.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

            // Draw the triangles!
            glDrawElements(
                    GL_TRIANGLES,                 // mode
                    indices_size,                 // count
                    GL_UNSIGNED_INT,              // type
                    nullptr                       // element array buffer offset
                    );

            yli::opengl::disable_vertex_attrib_array(mesh.get_vertex_position_modelspace_id());
            yli::opengl::disable_vertex_attrib_array(mesh.get_vertex_uv_id());
            yli::opengl::disable_vertex_attrib_array(mesh.get_vertex_normal_modelspace_id());
            yli::opengl::disable_vertex_attrib_array(vertex_position_modelspace_id);
            yli::opengl::disable_vertex_attrib_array(vertex_uv_id);
            yli::opengl::disable_vertex_attrib_array(vertex_normal_modelspace_id);
        }
        else if (this->universe.get_is_vulkan_in_use())
        {
            throw std::runtime_error("ERROR: `Biont::render_this_biont`: Vulkan is not supported yet!");
        }
    }

    Scene* Biont::get_scene() const
    {
        const Entity* const holobiont_parent = this->get_parent();

        if (holobiont_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Biont::get_scene`: `holobiont_parent` is `nullptr`!");
        }

        return holobiont_parent->get_scene();
    }

    std::size_t Biont::get_number_of_children() const
    {
        return 0; // `Biont` has no children.
    }

    std::size_t Biont::get_number_of_descendants() const
    {
        return 0; // `Biont` has no children.
    }
}
