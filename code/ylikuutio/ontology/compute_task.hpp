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

#ifndef YLIKUUTIO_ONTOLOGY_COMPUTE_TASK_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_COMPUTE_TASK_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

// `ComputeTask` is a class which contains the data for a single
// computing task. `ComputeTask` does not have the OpenGL shaders used to process
// the data. Instead, the shaders are contained by the parent `Entity` which is
// an `Pipeline` instance.
//
// For example, `Pipeline` can have vertex and fragment shaders for
// computing the distances between nodes of a graph. Then, each `ComputeTask`
// would contain the graph data, eg. as a distance matrix. Then, rendering a
// `ComputeTask` means computing that task.
//
// Rendering a `ComputeTask` is done by iterating the task until
// `n_max_iterations` is reached.

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
    class GenericParentModule;
    class GenericMasterModule;
    class Universe;
    class Scene;
    struct ComputeTaskStruct;

    class ComputeTask final : public Entity
    {
        private:
            ComputeTask(
                    yli::core::Application& application,
                    Universe& universe,
                    const ComputeTaskStruct& compute_task_struct,
                    GenericParentModule* const pipeline_parent_module);

            ~ComputeTask();

        public:
            ComputeTask(const ComputeTask&) = delete;            // Delete copy constructor.
            ComputeTask& operator=(const ComputeTask&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            ChildModule child_of_pipeline;

        public:
            Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            // This method renders this `ComputeTask`, that is, computes this task.
            void render(const Scene* const);

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

        private:
            std::string texture_file_format; // Type of the texture file. Supported file formats so far: `"png"`/`"PNG"`, `"csv"`/`"CSV"`.
            std::string texture_filename;    // Filename of the model file.
            std::string output_filename;     // Filename of the output file.

            yli::data::AnyValue left_filler_vector_any_value;
            yli::data::AnyValue right_filler_vector_any_value;

            std::shared_ptr<std::vector<uint8_t>> result_vector { nullptr };

            // This is the maximum number of iterations.
            std::size_t n_max_iterations;

            std::size_t compute_taskID;

            uint32_t texture_width;
            uint32_t texture_height;
            uint32_t texture_size { 0 }; // Some dummy value.

            uint32_t n_index_characters; // For intermediate results' filenames.

            uint32_t vertices_size { 0 };
            uint32_t uvs_size      { 0 };

            // variables related to the framebuffer.
            GLuint framebuffer              { 0 }; // Some dummy value.
            GLuint source_texture           { 0 }; // Some dummy value.
            GLuint target_texture           { 0 }; // Some dummy value.
            GLint opengl_texture_id         { 0 }; // Some dummy value.
            bool is_texture_loaded          { false };
            bool is_framebuffer_initialized { false };
            bool is_ready                   { false };

            GLint vertex_position_modelspace_id { 0 }; // Some dummy value.
            GLint vertex_uv_id                  { 0 }; // Some dummy value.
            GLint screen_width_uniform_id       { 0 }; // Some dummy value. Location of the program's window width uniform.
            GLint screen_height_uniform_id      { 0 }; // Some dummy value. Location of the program's window height uniform.
            GLint iteration_i_uniform_id        { 0 }; // Some dummy value. Location of the program's iteration index uniform.

            GLuint vao           { 0 }; // Some dummy value.
            GLuint vertex_buffer { 0 }; // Some dummy value.
            GLuint uvbuffer      { 0 }; // Some dummy value.
            GLuint elementbuffer { 0 }; // Some dummy value.

            GLenum format;
            GLenum internal_format;
            GLenum output_format;
            GLenum type;

            bool should_save_intermediate_results;
            bool should_flip_texture;
    };
}

#endif
