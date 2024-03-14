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

#include "pipeline.hpp"
#include "universe.hpp"
#include "ecosystem.hpp"
#include "scene.hpp"
#include "pipeline_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> Pipeline::bind_to_new_ecosystem_parent(
            yli::ontology::Pipeline& pipeline,
            yli::ontology::Ecosystem& new_parent)
    {
        // Set pointer to `Pipeline` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Entity* const old_ecosystem_or_scene_parent = pipeline.get_parent();

        if (old_ecosystem_or_scene_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Pipeline::bind_to_new_ecosystem_parent`: `old_ecosystem_or_scene_parent` is `nullptr`!");
        }

        if (&new_parent == old_ecosystem_or_scene_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(pipeline.local_name))
        {
            std::cerr << "ERROR: `Pipeline::bind_to_new_ecosystem_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        // `Ecosystem`s do not care in which `Ecosystem`s their apprentices reside,
        // so binding to an `Ecosystem` does not unbind any apprentices.
        pipeline.child_of_ecosystem_or_scene.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_pipelines);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Pipeline::bind_to_new_scene_parent(
            yli::ontology::Pipeline& pipeline,
            yli::ontology::Scene& new_parent)
    {
        // Set pointer to `pipeline` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Entity* const old_ecosystem_or_scene_parent = pipeline.get_parent();

        if (old_ecosystem_or_scene_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Pipeline::bind_to_new_scene_parent`: `old_ecosystem_or_scene_parent` is `nullptr`!");
        }

        if (&new_parent == old_ecosystem_or_scene_parent)
        {
            // Setting current parent as the new parent. Nothing to do.
            return std::nullopt;
        }

        if (new_parent.has_child(pipeline.local_name))
        {
            std::cerr << "ERROR: `Pipeline::bind_to_new_scene_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        pipeline.master_of_materials.unbind_all_apprentice_modules_belonging_to_other_scenes(&new_parent);
        pipeline.master_of_symbioses.unbind_all_apprentice_modules_belonging_to_other_scenes(&new_parent);
        pipeline.child_of_ecosystem_or_scene.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_pipelines);

        return std::nullopt;
    }

    Pipeline::Pipeline(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::PipelineStruct& pipeline_struct,
            yli::ontology::GenericParentModule* const ecosystem_or_scene_parent_module)
        : Entity(application, universe, pipeline_struct),
        child_of_ecosystem_or_scene(ecosystem_or_scene_parent_module, *this),
        parent_of_compute_tasks(
                *this,
                this->registry,
                application.get_memory_allocator(yli::data::Datatype::COMPUTETASK),
                "compute_tasks"),
        master_of_materials(this, &this->registry, "materials", nullptr),
        master_of_symbioses(this, &this->registry, "symbioses")
    {
        // constructor.

        this->vertex_shader        = pipeline_struct.vertex_shader;
        this->fragment_shader      = pipeline_struct.fragment_shader;

        this->char_vertex_shader   = this->vertex_shader.c_str();
        this->char_fragment_shader = this->fragment_shader.c_str();

        // Each GPGPU `Pipeline` owns 0 or more output `ComputeTask`s.
        // Each `Material` rendered after a given GPGPU `Pipeline`
        // may also use the output `ComputeTask`s offered by
        // a given GPGPU `Pipeline` as its texture.
        this->is_gpgpu_pipeline    = pipeline_struct.is_gpgpu_pipeline;

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
        this->type_string = "yli::ontology::Pipeline*";
        this->can_be_erased = true;
    }

    Pipeline::~Pipeline()
    {
        // destructor.

        if (this->universe.get_is_opengl_in_use())
        {
            glDeleteProgram(this->program_id);
        }
    }

    void Pipeline::render(const yli::ontology::Scene* const target_scene)
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

        if (render_system == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Pipeline::render`: `render_system` is `nullptr`!");
        }

        // [Re]bind `program_id` program.
        glUseProgram(this->program_id);

        render_system->render_compute_tasks(this->parent_of_compute_tasks, new_target_scene);
        render_system->render_materials(this->master_of_materials, new_target_scene);
        render_system->render_symbioses(this->master_of_symbioses, new_target_scene);
    }

    yli::ontology::Scene* Pipeline::get_scene() const
    {
        return this->child_of_ecosystem_or_scene.get_scene();
    }

    yli::ontology::Entity* Pipeline::get_parent() const
    {
        return this->child_of_ecosystem_or_scene.get_parent();
    }

    std::size_t Pipeline::get_number_of_children() const
    {
        return this->parent_of_compute_tasks.get_number_of_children();
    }

    std::size_t Pipeline::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_compute_tasks.child_pointer_vector);
    }

    std::size_t Pipeline::get_number_of_apprentices() const
    {
        return this->master_of_materials.get_number_of_apprentices() +
            this->master_of_symbioses.get_number_of_apprentices();
    }

    GLuint Pipeline::get_program_id() const
    {
        return this->program_id;
    }
}
