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

#ifndef YLIKUUTIO_ONTOLOGY_PIPELINE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_PIPELINE_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "generic_master_module.hpp"
#include "master_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"
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
    class Universe;
    class Ecosystem;
    class Scene;
    class PipelineCompare;
    struct PipelineStruct;

    class Pipeline final : public Entity
    {
        public:
            // Set pointer to `pipeline` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_ecosystem_parent(
                    Pipeline& pipeline,
                    Ecosystem& new_parent);

            // Set pointer to `pipeline` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_scene_parent(
                    Pipeline& pipeline,
                    Scene& new_parent);

        private:
            Pipeline(
                    yli::core::Application& application,
                    Universe& universe,
                    const PipelineStruct& pipeline_struct,
                    GenericParentModule* const ecosystem_or_scene_parent_module);

            ~Pipeline();

        public:
            Pipeline(const Pipeline&) = delete;            // Delete copy constructor.
            Pipeline& operator=(const Pipeline&) = delete; // Delete copy assignment.

            Scene* get_scene() const override;
            Entity* get_parent() const override;

            MasterModule<Pipeline*>* get_master_module() const
            {
                return const_cast<MasterModule<Pipeline*>*>(&this->master_of_materials);
            }

            std::size_t get_number_of_apprentices() const;

            GLuint get_program_id() const;

            GenericParentModule* get_generic_parent_module(const int type);

            friend class PipelineCompare;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            template<typename T1>
                friend void yli::hierarchy::bind_child_to_parent(const T1& child, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children) noexcept;

            ChildModule child_of_ecosystem_or_scene;
            GenericParentModule parent_of_compute_tasks;
            MasterModule<Pipeline*> master_of_materials;
            GenericMasterModule master_of_symbioses;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            // This method renders all materials using this `Pipeline`.
            void render(const Scene* const target_scene);

        private:
            GLuint program_id                  { 0 }; // This `Pipeline`'s `program_id`, returned by `load_shaders`. Dummy value.
            GLuint scene_uniform_block_index   { 0 }; // Dummy value.
            GLuint movable_uniform_block_index { 0 }; // Dummy value.
            GLuint camera_uniform_block_index  { 0 }; // Dummy value.

            std::string vertex_shader;            // Filename of vertex shader.
            std::string fragment_shader;          // Filename of fragment shader.

            const char* char_vertex_shader;
            const char* char_fragment_shader;

            bool is_gpgpu_pipeline;               // TODO: GPGPU `Pipeline`s are not rendered on screen but their result `ComputeTask`s can be used by `Material`s.
    };
}

#endif
