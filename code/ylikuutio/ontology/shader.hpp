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

#ifndef __YLIKUUTIO_ONTOLOGY_SHADER_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SHADER_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "generic_master_module.hpp"
#include "master_module.hpp"
#include "code/ylikuutio/data/pi.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/load/shader_loader.hpp"
#include "code/ylikuutio/opengl/ubo_block_enums.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Universe;
    class Ecosystem;
    class Scene;
    class ShaderCompare;
    struct ShaderStruct;

    class Shader: public yli::ontology::Entity
    {
        public:
            // Set pointer to `shader` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_ecosystem_parent(yli::ontology::Shader& shader, yli::ontology::Ecosystem& new_parent);

            // Set pointer to `shader` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(yli::ontology::Shader& shader, yli::ontology::Scene& new_parent);

            Shader(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ShaderStruct& shader_struct,
                    yli::ontology::GenericParentModule* const scene_or_ecosystem_parent_module);

            Shader(const Shader&) = delete;            // Delete copy constructor.
            Shader& operator=(const Shader&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Shader();

            yli::ontology::Scene* get_scene() const override;
            yli::ontology::Entity* get_parent() const override;

            yli::ontology::MasterModule<yli::ontology::Shader*>* get_master_module() const
            {
                return const_cast<yli::ontology::MasterModule<yli::ontology::Shader*>*>(&this->master_of_materials);
            }

            std::size_t get_number_of_apprentices() const;

            GLuint get_program_id() const;

            friend class yli::ontology::ShaderCompare;
            template<typename T1>
                friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            yli::ontology::ChildModule child_of_scene_or_ecosystem;
            yli::ontology::GenericParentModule parent_of_compute_tasks;
            yli::ontology::MasterModule<yli::ontology::Shader*> master_of_materials;
            yli::ontology::GenericMasterModule master_of_symbioses;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            // This method renders all materials using this `Shader`.
            void render(const yli::ontology::Scene* const target_scene);

        private:
            GLuint program_id     { 0 };          // This `Shader`'s `program_id`, returned by `load_shaders`. Dummy value.
            GLuint scene_uniform_block_index   { 0 }; // Dummy value.
            GLuint movable_uniform_block_index { 0 }; // Dummy value.
            GLuint camera_uniform_block_index  { 0 }; // Dummy value.

            std::string vertex_shader;            // Filename of vertex shader.
            std::string fragment_shader;          // Filename of fragment shader.

            const char* char_vertex_shader;
            const char* char_fragment_shader;

            bool is_gpgpu_shader;                 // TODO: GPGPU `Shader`s are not rendered on screen but their result `ComputeTask`s can be used by `Material`s.
    };
}

#endif
