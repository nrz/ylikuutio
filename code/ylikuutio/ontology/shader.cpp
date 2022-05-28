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

#include "shader.hpp"
#include "universe.hpp"
#include "ecosystem.hpp"
#include "scene.hpp"
#include "shader_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> Shader::bind_to_new_ecosystem_parent(yli::ontology::Shader& shader, yli::ontology::Ecosystem& new_parent)
    {
        // Set pointer to `Shader` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        yli::ontology::Entity* const old_parent = shader.get_parent();

        if (old_parent == nullptr)
        {
            std::cerr << "ERROR: `Shader::bind_to_new_ecosystem_parent`: `old_parent` is `nullptr`!\n";
            return std::nullopt;
        }

        if (&new_parent == old_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(shader.local_name))
        {
            std::cerr << "ERROR: `Shader::bind_to_new_ecosystem_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        // `Ecosystem`s do not care in which `Ecosystem`s their apprentices reside,
        // so binding to an `Ecosystem` does not unbind any apprentices.
        shader.child_of_scene_or_ecosystem.unbind_and_bind_to_new_parent(&new_parent.parent_of_shaders);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Shader::bind_to_new_scene_parent(yli::ontology::Shader& shader, yli::ontology::Scene& new_parent)
    {
        // Set pointer to `shader` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        yli::ontology::Entity* const old_parent = shader.get_parent();

        if (old_parent == nullptr)
        {
            std::cerr << "ERROR: `Shader::bind_to_new_scene_parent`: `old_parent` is `nullptr`!\n";
            return std::nullopt;
        }

        if (&new_parent == old_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(shader.local_name))
        {
            std::cerr << "ERROR: `Shader::bind_to_new_scene_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        shader.master_of_materials.unbind_all_apprentice_modules_belonging_to_other_scenes(&new_parent);
        shader.master_of_symbioses.unbind_all_apprentice_modules_belonging_to_other_scenes(&new_parent);
        shader.child_of_scene_or_ecosystem.unbind_and_bind_to_new_parent(&new_parent.parent_of_shaders);
        return std::nullopt;
    }

    Shader::Shader(
            yli::ontology::Universe& universe,
            const yli::ontology::ShaderStruct& shader_struct,
            yli::ontology::GenericParentModule* const scene_or_ecosystem_parent_module)
        : Entity(universe, shader_struct),
        child_of_scene_or_ecosystem(scene_or_ecosystem_parent_module, this),
        parent_of_compute_tasks(this, &this->registry, "compute_tasks"),
        master_of_materials(this, &this->registry, "materials", nullptr),
        master_of_symbioses(this, &this->registry, "symbioses")
    {
        // constructor.

        this->vertex_shader        = shader_struct.vertex_shader;
        this->fragment_shader      = shader_struct.fragment_shader;

        this->char_vertex_shader   = this->vertex_shader.c_str();
        this->char_fragment_shader = this->fragment_shader.c_str();

        // Each GPGPU `Shader` owns 0 or more output `ComputeTask`s.
        // Each `Material` rendered after a given GPGPU `Shader`
        // may also use the output `ComputeTask`s offered by
        // a given GPGPU `Shader` as its texture.
        this->is_gpgpu_shader      = shader_struct.is_gpgpu_shader;

        if (this->universe.get_is_opengl_in_use())
        {
            // Create and compile our GLSL program from the shaders.
            this->program_id = yli::load::load_shaders(this->char_vertex_shader, this->char_fragment_shader);

            this->scene_uniform_block_index = glGetUniformBlockIndex(this->program_id, "scene_uniform_block");
            this->movable_uniform_block_index = glGetUniformBlockIndex(this->program_id, "movable_uniform_block");
            this->camera_uniform_block_index = glGetUniformBlockIndex(this->program_id, "camera_uniform_block");

            glUniformBlockBinding(this->program_id, this->scene_uniform_block_index, yli::opengl::UboBlockIndices::SCENE);
            glUniformBlockBinding(this->program_id, this->movable_uniform_block_index, yli::opengl::UboBlockIndices::MOVABLE);
            glUniformBlockBinding(this->program_id, this->camera_uniform_block_index, yli::opengl::UboBlockIndices::CAMERA);
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Shader*";
        this->can_be_erased = true;
    }

    Shader::~Shader()
    {
        // destructor.
        std::cout << "`Shader` with childID " << std::dec << this->childID << " will be destroyed.\n";

        if (this->universe.get_is_opengl_in_use())
        {
            glDeleteProgram(this->program_id);
        }
    }

    void Shader::render(const yli::ontology::Scene* const target_scene)
    {
        if (!this->should_be_rendered)
        {
            return;
        }

        yli::ontology::Scene* const scene = this->get_scene();

        if (target_scene != nullptr && scene != nullptr && scene != target_scene)
        {
            // Different `Scene`s, do not render.
            return;
        }

        const yli::ontology::Scene* const new_target_scene = (target_scene != nullptr ? target_scene : scene);

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr)
        {
            std::cerr << "ERROR: `Shader::render`: `render_system` is `nullptr`!\n";
            return;
        }

        // [Re]bind `program_id` shader.
        glUseProgram(this->program_id);

        render_system->render_compute_tasks(this->parent_of_compute_tasks, new_target_scene);
        render_system->render_materials(this->master_of_materials, new_target_scene);
        render_system->render_symbioses(this->master_of_symbioses, new_target_scene);
    }

    yli::ontology::Scene* Shader::get_scene() const
    {
        return this->child_of_scene_or_ecosystem.get_scene();
    }

    yli::ontology::Entity* Shader::get_parent() const
    {
        return this->child_of_scene_or_ecosystem.get_parent();
    }

    std::size_t Shader::get_number_of_children() const
    {
        return this->parent_of_compute_tasks.get_number_of_children();
    }

    std::size_t Shader::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_compute_tasks.child_pointer_vector);
    }

    std::size_t Shader::get_number_of_apprentices() const
    {
        return this->master_of_materials.get_number_of_apprentices() +
            this->master_of_symbioses.get_number_of_apprentices();
    }

    GLuint Shader::get_program_id() const
    {
        return this->program_id;
    }
}
