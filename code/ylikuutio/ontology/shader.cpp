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

#include "shader.hpp"
#include "master_module.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_master.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;

    void Shader::bind_to_new_scene_parent(yli::ontology::Scene* const new_parent)
    {
        // This method sets pointer to this `Shader` to `nullptr`, sets `parent` according to the input,
        // and requests a new `childID` from the new `Scene`.
        //
        // requirements:
        // `this->parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Entity* const scene = this->child_of_scene.get_parent();

        if (scene == nullptr)
        {
            std::cerr << "ERROR: `Shader::bind_to_new_scene_parent`: `scene` is `nullptr`!\n";
            return;
        }

        if (new_parent == nullptr)
        {
            std::cerr << "ERROR: `Shader::bind_to_new_scene_parent`: `new_parent` is `nullptr`!\n";
            return;
        }

        if (new_parent->has_child(this->local_name))
        {
            std::cerr << "ERROR: `Shader::bind_to_new_scene_parent`: local name is already in use!\n";
            return;
        }

        // Unbind from the old parent `Scene`.
        this->child_of_scene.unbind_child();

        // Get `childID` from `Scene` and set pointer to this `Shader`.
        this->child_of_scene.set_parent_module_and_bind_to_new_parent(&new_parent->parent_of_shaders);
    }

    void Shader::bind_to_new_parent(yli::ontology::Entity* const new_parent)
    {
        // this method sets pointer to this `Shader` to `nullptr`, sets `parent` according to the input,
        // and requests a new `childID` from the new `Scene`.
        //
        // requirements:
        // `this->parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Scene* const scene = dynamic_cast<yli::ontology::Scene*>(new_parent);

        if (scene == nullptr)
        {
            std::cerr << "ERROR: `Shader::bind_to_new_parent`: `new_parent` is not `yli::ontology::Scene*`!\n";
            return;
        }

        this->bind_to_new_scene_parent(scene);
    }

    Shader::~Shader()
    {
        // destructor.
        std::cout << "`Shader` with childID " << std::dec << this->childID << " will be destroyed.\n";

        if (this->universe != nullptr && !this->universe->get_is_headless() && this->opengl_in_use)
        {
            glDeleteProgram(this->program_id);
        }
    }

    void Shader::render()
    {
        if (!this->should_be_rendered || this->universe == nullptr)
        {
            return;
        }

        yli::render::RenderMaster* const render_master = this->universe->get_render_master();

        if (render_master == nullptr)
        {
            return;
        }

        this->prerender();

        // [Re]bind `program_id` shader.
        glUseProgram(this->program_id);

        // `glUniformMatrix4fv` doesn't change between objects,
        // so this can be done once for all objects that use the same `program_id`.
        glUniformMatrix4fv(this->view_matrix_id, 1, GL_FALSE, &this->universe->get_view_matrix()[0][0]);

        render_master->render_compute_tasks(this->parent_of_compute_tasks);
        render_master->render_materials(this->master_of_materials.get_apprentice_module_pointer_vector_reference());
        render_master->render_symbioses(this->master_of_symbioses.get_apprentice_module_pointer_vector_reference());

        this->postrender();
    }

    yli::ontology::Scene* Shader::get_scene() const
    {
        return static_cast<yli::ontology::Scene*>(this->child_of_scene.get_parent());
    }

    yli::ontology::Entity* Shader::get_parent() const
    {
        return this->child_of_scene.get_parent();
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
        return this->master_of_materials.get_number_of_apprentices();
    }

    GLuint Shader::get_program_id() const
    {
        return this->program_id;
    }

    GLint Shader::get_matrix_id() const
    {
        return this->matrix_id;
    }

    GLint Shader::get_model_matrix_id() const
    {
        return this->model_matrix_id;
    }
}
