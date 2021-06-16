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

#ifndef __YLIKUUTIO_ONTOLOGY_SHADER_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SHADER_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

#include "entity.hpp"
#include "parent_module.hpp"
#include "universe.hpp"
#include "shader_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/pi.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/load/shader_loader.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class Scene;
    class ShaderCompare;

    class Shader: public yli::ontology::Entity
    {
        public:
            // This method sets pointer to this `Shader` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Scene`.
            void bind_to_new_scene_parent(yli::ontology::Scene* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            Shader(yli::ontology::Universe* const universe, const yli::ontology::ShaderStruct& shader_struct)
                : Entity(universe, shader_struct),
                parent_of_compute_tasks(this, &this->registry, "compute_tasks"),
                parent_of_materials(this, &this->registry, "materials"),
                parent_of_symbioses(this, &this->registry, "symbioses")
            {
                // constructor.

                this->vertex_shader        = shader_struct.vertex_shader;
                this->fragment_shader      = shader_struct.fragment_shader;

                this->char_vertex_shader   = this->vertex_shader.c_str();
                this->char_fragment_shader = this->fragment_shader.c_str();
                this->parent               = shader_struct.parent;

                // Each GPGPU `Shader` owns 0 or more output `ComputeTask`s.
                // Each `Material` rendered after a given GPGPU `Shader`
                // may also use the output `ComputeTask`s offered by
                // a given GPGPU `Shader` as its texture.
                this->is_gpgpu_shader      = shader_struct.is_gpgpu_shader;

                this->opengl_in_use        = shader_struct.opengl_in_use;

                // Get `childID` from `Scene` and set pointer to this `Shader`.
                this->bind_to_parent();

                if (this->universe != nullptr && !this->universe->get_is_headless() && this->opengl_in_use)
                {
                    // Create and compile our GLSL program from the shaders.
                    this->program_id = yli::load::load_shaders(this->char_vertex_shader, this->char_fragment_shader);

                    // Get a handle for our "MVP" uniform.
                    this->matrix_id = glGetUniformLocation(this->program_id, "MVP");
                    this->view_matrix_id = glGetUniformLocation(this->program_id, "V");
                    this->model_matrix_id = glGetUniformLocation(this->program_id, "M");
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Shader*";
                this->can_be_erased = true;
            }

            Shader(const Shader&) = delete;            // Delete copy constructor.
            Shader& operator=(const Shader&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Shader();

            yli::ontology::Entity* get_parent() const override;

            GLuint get_program_id() const;
            GLint get_matrix_id() const;
            GLint get_model_matrix_id() const;

            friend class yli::ontology::ShaderCompare;
            template<class T1>
                friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
            template<class T1, class T2>
                friend void yli::render::render_children(const std::vector<T1>& child_pointer_vector);

            yli::ontology::ParentModule parent_of_compute_tasks;
            yli::ontology::ParentModule parent_of_materials;
            yli::ontology::ParentModule parent_of_symbioses;

        private:
            void bind_to_parent();

            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // This method renders all materials using this `Shader`.
            void render();

            yli::ontology::Scene* parent;         // Pointer to the `Scene`.

            GLuint program_id     { 0 };          // This `Shader`'s `program_id`, returned by `load_shaders`. Dummy value.
            GLint matrix_id       { 0 };          // Dummy value.
            GLint view_matrix_id  { 0 };          // Dummy value.
            GLint model_matrix_id { 0 };          // Dummy value.

            std::string vertex_shader;            // Filename of vertex shader.
            std::string fragment_shader;          // Filename of fragment shader.

            const char* char_vertex_shader;
            const char* char_fragment_shader;

            bool is_gpgpu_shader;                 // TODO: GPGPU `Shader`s are not rendered on screen but their result `ComputeTask`s can be used by `Material`s.
            bool opengl_in_use;                   // If `opengl_in_use` is `false, then no OpenGL-specific code shall be executed.
    };
}

#endif
