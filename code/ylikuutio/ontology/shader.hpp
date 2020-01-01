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

#ifndef __SHADER_HPP_INCLUDED
#define __SHADER_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "entity.hpp"
#include "glyph.hpp"
#include "shader_struct.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/shader_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Scene;
        class Material;
        class Species;
        class Symbiosis;
        class ComputeTask;
        class ShaderCompare;

        class Shader: public yli::ontology::Entity
        {
            public:
                void bind_Material(yli::ontology::Material* const material);
                void bind_Symbiosis(yli::ontology::Symbiosis* const symbiosis);
                void bind_ComputeTask(yli::ontology::ComputeTask* const compute_task);

                void unbind_Material(const std::size_t childID);
                void unbind_Symbiosis(const std::size_t childID);
                void unbind_ComputeTask(const std::size_t childID);

                // This method sets pointer to this `Shader` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Scene`.
                void bind_to_new_parent(yli::ontology::Scene* const new_parent);

                Shader(yli::ontology::Universe* const universe, const yli::ontology::ShaderStruct& shader_struct)
                    : Entity(universe)
                {
                    // constructor.

                    this->vertex_shader        = shader_struct.vertex_shader;
                    this->fragment_shader      = shader_struct.fragment_shader;

                    this->char_vertex_shader   = this->vertex_shader.c_str();
                    this->char_fragment_shader = this->fragment_shader.c_str();
                    this->parent               = shader_struct.parent;

                    this->programID            = 0; // dummy value.
                    this->matrixID             = 0; // dummy value.
                    this->view_matrixID        = 0; // dummy value.
                    this->model_matrixID       = 0; // dummy value.

                    // Each GPGPU `Shader` owns 0 or more output `ComputeTask`s.
                    // Each `Material` rendered after a given GPGPU `Shader`
                    // may also use the output `ComputeTask`s offered by
                    // a given GPGPU `Shader` as its texture.
                    this->is_gpgpu_shader         = shader_struct.is_gpgpu_shader;

                    this->opengl_in_use           = shader_struct.opengl_in_use;

                    this->number_of_materials     = 0;
                    this->number_of_symbioses     = 0;
                    this->number_of_compute_tasks = 0;

                    // Get `childID` from `Scene` and set pointer to this `Shader`.
                    this->bind_to_parent();

                    if (this->opengl_in_use)
                    {
                        // Create and compile our GLSL program from the shaders.
                        this->programID = yli::load::load_shaders(this->char_vertex_shader, this->char_fragment_shader);

                        // Get a handle for our "MVP" uniform.
                        this->matrixID = glGetUniformLocation(this->programID, "MVP");
                        this->view_matrixID = glGetUniformLocation(this->programID, "V");
                        this->model_matrixID = glGetUniformLocation(this->programID, "M");
                    }

                    // `yli::ontology::Entity` member variables begin here.
                    this->child_vector_pointers_vector.push_back(&this->material_pointer_vector);
                    this->child_vector_pointers_vector.push_back(&this->symbiosis_pointer_vector);
                    this->child_vector_pointers_vector.push_back(&this->compute_task_pointer_vector);
                    this->type_string = "yli::ontology::Shader*";
                    this->can_be_erased = true;
                }

                Shader(const Shader&) = delete;            // Delete copy constructor.
                Shader &operator=(const Shader&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Shader();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                // Set terrain `Species` pointers in `Scene` and `Universe` so that they point to the chosen terrain `Species`.
                // Currently there can be only one terrain `Species` in each `Scene` (used in collision detection).
                void set_terrain_species(yli::ontology::Species* terrain_species);

                uint32_t get_programID() const;
                uint32_t get_matrixID() const;
                uint32_t get_model_matrixID() const;

                friend yli::ontology::ShaderCompare;
                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                // This method renders all materials using this `Shader`.
                void render();

                yli::ontology::Scene* parent;         // Pointer to the `Scene`.

                uint32_t programID;                   // This `Shader`'s `programID`, returned by `load_shaders`.

                uint32_t matrixID;
                uint32_t view_matrixID;
                uint32_t model_matrixID;

                std::string vertex_shader;            // Filename of vertex shader.
                std::string fragment_shader;          // Filename of fragment shader.

                std::vector<yli::ontology::Material*> material_pointer_vector;
                std::vector<yli::ontology::Symbiosis*> symbiosis_pointer_vector;
                std::vector<yli::ontology::ComputeTask*> compute_task_pointer_vector;
                std::queue<std::size_t> free_materialID_queue;
                std::queue<std::size_t> free_symbiosisID_queue;
                std::queue<std::size_t> free_compute_taskID_queue;
                std::size_t number_of_materials;
                std::size_t number_of_symbioses;
                std::size_t number_of_compute_tasks;

                const char* char_vertex_shader;
                const char* char_fragment_shader;

                bool is_gpgpu_shader;                 // TODO: GPGPU `Shader`s are not rendered on screen but their result `ComputeTask`s can be used by `Material`s.
                bool opengl_in_use;                   // If `opengl_in_use` is `false, then no OpenGL-specific code shall be executed.
        };
    }
}

#endif
